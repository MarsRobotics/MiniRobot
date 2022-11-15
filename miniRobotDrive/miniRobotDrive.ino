#include <RPLidar.h>
int rightPin = 50; 
int leftPin = 48; 
bool detected = false;
RPLidar lidar;

#define RPLIDAR_MOTOR 2 // The PWM pin for control the speed of RPLIDAR's motor.
//                         This pin should connected with the RPLIDAR's MOTOCTRL signal 
void setup() {
  Serial.begin(9600); 

  Serial.println("Starting LIDAR");
	//leftPin and rightPin control transistors which turn motors on and off
  pinMode(leftPin, OUTPUT); 
  pinMode(rightPin, OUTPUT); 

  //--------------LIDAR-------------------//
  lidar.begin(Serial2);
  
  // set pin modes
  pinMode(RPLIDAR_MOTOR, OUTPUT);

}

void loop() {
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
//  }


  
//	//turn on both motors for half a second
//  digitalWrite(leftPin, HIGH); 
//  digitalWrite(rightPin, HIGH); 
//
//  delay(500); 
//  turnLeft(); 
//
//  digitalWrite(leftPin, LOW); 
//  digitalWrite(rightPin, LOW); 
//
//  delay(3000); 

turnLeft();


//delay(10000);

}

void turnLeft(){
	//run right side forward and keep left stagnant
  digitalWrite(rightPin, HIGH); 
  digitalWrite(leftPin, LOW); 

  delay(5000); 
  digitalWrite(rightPin, LOW);

  delay(5000);
}
