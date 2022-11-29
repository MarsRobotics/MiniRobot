#include <RPLidar.h>
int rightPin = 27; 
int leftPin = 26; 
bool newCycle = false;
bool commenceMovement = false;
bool detectedObject = false;
RPLidar lidar;

int ri1 = 25; 
int ri2 = 24; 
int li1 = 22; 
int li2 = 23;


//stepper vars
#include <Stepper.h>
const int stepsPerRevolution = 2048;
const int stepsPerTurn = 256;
const int rpm = 12;

Stepper stepper1 = Stepper(stepsPerRevolution, 52, 50, 53, 51); //FL and BR
Stepper stepper2 = Stepper(stepsPerRevolution, 41, 43, 40, 42); //FR and BL



//Vars for finding closest point
float closeDist = 0.0f;
float closeAngle = 0.0f;



#define RPLIDAR_MOTOR 2 // The PWM pin for control the speed of RPLIDAR's motor.
//                         This pin should connected with the RPLIDAR's MOTOCTRL signal 
void setup() {
  Serial.begin(9600); 

  Serial.println("Starting LIDAR");
	//leftPin and rightPin control transistors which turn motors on and off
  pinMode(leftPin, OUTPUT); 
  pinMode(rightPin, OUTPUT); 
  pinMode(ri1, OUTPUT); 
  pinMode(ri2, OUTPUT); 
  pinMode(li1, OUTPUT); 
  pinMode(li2, OUTPUT);
  stepper1.setSpeed(rpm);
  stepper2.setSpeed(rpm);

  //enable motors 
  digitalWrite(rightPin, HIGH); 
  digitalWrite(leftPin, HIGH); 

  //--------------LIDAR-------------------//
  lidar.begin(Serial2);
  
  // set pin modes
  pinMode(RPLIDAR_MOTOR, OUTPUT);

}

//4.3 SECONDS to do a full 360

void loop() {
    
    if (IS_OK(lidar.waitPoint())) {
    float distance = lidar.getCurrentPoint().distance; //distance value in mm unit
    float angle    = lidar.getCurrentPoint().angle; //anglue value in degree
    bool  startBit = lidar.getCurrentPoint().startBit; //whether this point is belong to a new scan
   

  //basically in one cycle, pick the angle corresponding with the smallest distance


    //on the first start set newCycle to true for the first time so movement does activate instantly
    //once a new startbit occurs, commencemovement is true and robot will move towards closest point
    if(startBit){
      detectedObject = false;
      if(newCycle){
        delay(1000);
        commenceMovement = true;
      }
      newCycle = true;
    }
    else{
      commenceMovement = false;
    }


    if(commenceMovement){
      killAll();
      if(closeAngle >= 270){
        turnLeft(convertAngleToSec(closeAngle));
      }
      if(closeAngle <= 90){
        turnRight(convertAngleToSec(closeAngle));
      }

      closeDist = 0.0f;
      closeAngle = 0.0f;
    }

    
    if(angle <= 20.3f || angle >= 339.7f){
      if(distance >= 150.0f && distance  <= 500.0f){
        detectedObject = true;
        if(distance < closeDist){
          
          closeAngle = angle;
          closeDist = distance;
        } 
        
      }

    }

//    if(detectedObject){
//      forward();
//    }
//    else{
//      killAll();
//    }
 
    
  } else {//if lidar is not currently moving, this will start it up
    analogWrite(RPLIDAR_MOTOR, 0); //stop the rplidar motor
    
    // try to detect RPLIDAR... 
    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100))) {
       // detected...
       lidar.startScan();//begin using the laser and scanning
       
       // start motor rotating at max allowed speed
       analogWrite(RPLIDAR_MOTOR, 255);
       delay(1000);
    }
  }
  


}


//if we rotate wheels while turning its better, but we cant do that
//with current wheel rotation setup
void setTurnPositionOut(){
  stepper1.step(stepsPerTurn);
  
  delay(500);
  
  stepper2.step(-stepsPerTurn);

  delay(500);
}

void setTurnPositionBase(){
  stepper1.step(-stepsPerTurn);
  
  delay(500);
  
  stepper2.step(stepsPerTurn);

  delay(500);
}

void forward(){
  digitalWrite(ri1, LOW); 
  digitalWrite(li1, LOW); 

  digitalWrite(ri2, HIGH); 
  digitalWrite(li2, HIGH); 

  delay(100);
  killAll(); 
}

//or maybe .0125? 4.3 seconds per a 360 degrees
float convertAngleToSec(float angle){
  float seconds = 0.0125f;
  if(angle >= 270){
    angle = 360 - angle;
  }
  
  

  //using our turning speed where moving x seconds moves us y degrees
  //anglesPerSecond * seconds = angleMoved
  //so unknownConstant * seconds = angle
  //seconds = angle/unknownConstant
  
  return seconds * angle * 1000;
}

void backward(){
  digitalWrite(ri1, HIGH); 
  digitalWrite(li1, HIGH); 

  digitalWrite(ri2, LOW); 
  digitalWrite(li2, LOW);

   delay(100); 
//   killAll(); 
}

void turnLeft(float seconds){

  setTurnPositionOut();
  
  digitalWrite(ri1, LOW); 
  digitalWrite(li1, HIGH);

  digitalWrite(ri2, HIGH);
  digitalWrite(li2, LOW);
  
  delay(seconds); 
  killAll(); 

  setTurnPositionBase();
}

void turnRight(float seconds){

  setTurnPositionOut();
  
  digitalWrite(ri1, HIGH); 
  digitalWrite(li1, LOW);

  digitalWrite(ri2, LOW);
  digitalWrite(li2, HIGH);

  delay(seconds); 
  killAll(); 

  setTurnPositionBase();
  
}

void killAll(){
//  digitalWrite(leftPin, LOW); 
//  digitalWrite(rightPin, LOW);
  digitalWrite(ri1, LOW); 
  digitalWrite(li1, LOW); 

  digitalWrite(ri2, LOW); 
  digitalWrite(li2, LOW); 
}
