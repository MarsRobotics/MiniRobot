int rightPin = 50; 
int leftPin = 48; 

void setup() {
  Serial.begin(9600); 
  pinMode(leftPin, OUTPUT); 
  pinMode(rightPin, OUTPUT); 

}

void loop() {
  Serial.println("I'm crying"); 
  digitalWrite(leftPin, HIGH); 
  digitalWrite(rightPin, HIGH); 

  delay(500); 
  turnLeft(); 

  digitalWrite(leftPin, LOW); 
  digitalWrite(rightPin, LOW); 

  delay(3000); 

}

void turnLeft(){
  digitalWrite(rightPin, HIGH); 
  digitalWrite(leftPin, LOW); 

  delay(1000); 
}
