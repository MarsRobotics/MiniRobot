#include <RPLidar.h>
int rightPin = 27; 
int leftPin = 26; 
bool newCycle = false;
bool commenceMovement = false;
bool detectedObject = false;
bool turningLeft = false;
bool turningRight = false;
RPLidar lidar;

int ri1 = 25; 
int ri2 = 24; 
int li1 = 22; 
int li2 = 23;

float margin = 30.0f;


//stepper vars
#include <Stepper.h>
const int stepsPerRevolution = 2048;
const int stepsPerTurn = 256;
const int rpm = 12;

Stepper stepper1 = Stepper(stepsPerRevolution, 52, 50, 53, 51); //FL and BR
Stepper stepper2 = Stepper(stepsPerRevolution, 41, 43, 40, 42); //FR and BL



//Vars for finding closest point
float closeDist = 20000.0f;
float closeAngle = 20000.0f;



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
        
       if((closeAngle <= 12.5f + margin/3 || closeAngle >= 347.5f - margin/3 && closeAngle <= 360.0f) && !turningLeft && !turningRight){ //if object directly infront, move forward
         forward();
        }
       else{ //turn towards object
         if(closeAngle < 347.5f - margin/3 && closeAngle > 270.0f && !turningLeft){
           if(turningRight){
              turningRight = false;
//              setTurnPositionBase();
            }
//           setTurnPositionOut();
           turningLeft = true;
          }
          if(closeAngle > 12.5f + margin/3 && closeAngle < 90.0f && !turningRight){
            if(turningLeft){
              turningLeft = false;
//              setTurnPositionBase();
            }
//            setTurnPositionOut();
            turningRight = true;
          }
          if((352.5f <= closeAngle && closeAngle <= 360.0f) || closeAngle <= 7.5f){  //try val <= Var <= val 
            turningLeft = false;
            turningRight = false;
//            setTurnPositionBase();
          }
          if(turningLeft){
            turnLeft();
          }
          if(turningRight){
            turnRight();
          }
        } 

        
        closeDist = 20000.0f;
        closeAngle = 20000.0f;
      }
      newCycle = true;
    }

    
    if(angle <= 20.3f + margin || angle >= 339.7f - margin){ //see if an object is within our range
      if(distance >= 150.0f && distance  <= 400.0f){
        detectedObject = true;
        if(distance < closeDist){
          if((closeAngle <= 90.f && closeAngle + 5.0f < angle) || (closeAngle >= 270.0f && closeAngle - 5.0f > angle)){
                      closeAngle = angle;

          }
          closeDist = distance;
        }  
      }
    }
 

    if(!detectedObject){
      turningRight = false;
      turningLeft = false;
      killAll();
    }
 
    
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
//  killAll(); 
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

void turnLeft(){
  
  digitalWrite(ri1, LOW); 
  digitalWrite(li1, HIGH);

  digitalWrite(ri2, HIGH);
  digitalWrite(li2, LOW);
  
  delay(100); 
//  killAll(); 

}

void turnRight(){
  
  digitalWrite(ri1, HIGH); 
  digitalWrite(li1, LOW);

  digitalWrite(ri2, LOW);
  digitalWrite(li2, HIGH);

  delay(100); 
//  killAll(); 

  
}

void killAll(){
//  digitalWrite(leftPin, LOW); 
//  digitalWrite(rightPin, LOW);
  digitalWrite(ri1, LOW); 
  digitalWrite(li1, LOW); 

  digitalWrite(ri2, LOW); 
  digitalWrite(li2, LOW); 
}
