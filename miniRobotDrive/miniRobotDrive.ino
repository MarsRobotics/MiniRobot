int rightPin = 50; 
int leftPin = 48; 

void setup() {
  Serial.begin(9600); 
	//leftPin and rightPin control transistors which turn motors on and off
  pinMode(leftPin, OUTPUT); 
  pinMode(rightPin, OUTPUT); 

}

void loop() {
	//turn on both motors for half a second
  digitalWrite(leftPin, HIGH); 
  digitalWrite(rightPin, HIGH); 

  delay(500); 
  turnLeft(); 

  digitalWrite(leftPin, LOW); 
  digitalWrite(rightPin, LOW); 

  delay(3000); 

}

void turnLeft(){
	//run right side forward and keep left stagnant
  digitalWrite(rightPin, HIGH); 
  digitalWrite(leftPin, LOW); 

  delay(1000); 
}
