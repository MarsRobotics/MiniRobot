#include <RPLidar.h>
int rightPin = 50; 
int leftPin = 48; 
bool detected = false;
RPLidar lidar;

int ri1 = 36; 
int ri2 = 37; 
int li1 = 22; 
int li2 = 23; 

#define lr A15
#define ud A14

int xVal = 0; 
int yVal = 0; 

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

  //enable motors 
  digitalWrite(rightPin, HIGH); 
  digitalWrite(leftPin, HIGH); 

  //--------------LIDAR-------------------//
  lidar.begin(Serial2);
  
  // set pin modes
  pinMode(RPLIDAR_MOTOR, OUTPUT);

}

void loop() {
  xVal = analogRead(lr); 
  yVal = analogRead(ud); 

//  forward(); 
//  backward(); 
//  killAll(); 
//  delay(500); 
//  Serial.print("EKS Val: "); 
//  Serial.println(xVal); 
//  Serial.print("Y Val: "); 
//  Serial.println(yVal); 
//  
	//turn on both motors for half a second
  if(yVal >= 923){
    forward(); 
//    yVal = analogRead(lr); 
  }
  if(yVal <= 100){
    backward(); 
//    yVal = analogRead(lr); 
  }
  if(xVal <= 100  ){
    turnLeft(); 
  }
  if(xVal >= 923){
    turnRight(); 
  }
  
  
  //  if (IS_OK(lidar.waitPoint())) {
//    float distance = lidar.getCurrentPoint().distance; //distance value in mm unit
//    float angle    = lidar.getCurrentPoint().angle; //anglue value in degree
//    bool  startBit = lidar.getCurrentPoint().startBit; //whether this point is belong to a new scan
//   
//
//    if(startBit){
//      detected = false;
//    }
//    
//    if(angle <= 11.124f || angle >= 348.876f){
//      if(distance >= 150.0f && distance  <= 500.0f){
//        detected = true;
//      }
//    }
//
//    if(detected){
//      digitalWrite(leftPin, HIGH); 
//      digitalWrite(rightPin, HIGH); 
//    }
//    else{
//      digitalWrite(leftPin, LOW); 
//      digitalWrite(rightPin, LOW);
//    }
//    
//    //perform data processing here... 
//    
//    
//  } else {//if lidar is not currently moving, this will start it up
//    analogWrite(RPLIDAR_MOTOR, 0); //stop the rplidar motor
//    
//    // try to detect RPLIDAR... 
//    rplidar_response_device_info_t info;
//    if (IS_OK(lidar.getDeviceInfo(info, 100))) {
//       // detected...
//       lidar.startScan();//begin using the laser and scanning
//       
//       // start motor rotating at max allowed speed
//       analogWrite(RPLIDAR_MOTOR, 255);
//       delay(1000);
//    }
  
  
  
}

void forward(){
  digitalWrite(ri1, LOW); 
  digitalWrite(li1, LOW); 

  digitalWrite(ri2, HIGH); 
  digitalWrite(li2, HIGH); 

  delay(50);
  killAll(); 
}

  

void backward(){
  digitalWrite(ri1, HIGH); 
  digitalWrite(li1, HIGH); 

  digitalWrite(ri2, LOW); 
  digitalWrite(li2, LOW);

   delay(50); 
   killAll(); 
}

void turnLeft(){
  digitalWrite(ri1, LOW); 
  digitalWrite(li1, HIGH);

  digitalWrite(ri2, HIGH);
  digitalWrite(li2, LOW);
  
  delay(50); 
  killAll(); 
}

void turnRight(){
  digitalWrite(ri1, HIGH); 
  digitalWrite(li1, LOW);

  digitalWrite(ri2, LOW);
  digitalWrite(li2, HIGH);

  delay(50); 
  killAll(); 
}

void killAll(){
//  digitalWrite(leftPin, LOW); 
//  digitalWrite(rightPin, LOW);
  digitalWrite(ri1, LOW); 
  digitalWrite(li1, LOW); 

  digitalWrite(ri2, LOW); 
  digitalWrite(li2, LOW); 
}
