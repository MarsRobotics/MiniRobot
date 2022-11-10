int rightPin = 50; 
int leftPin = 48; 

int ri1 = 36; 
int ri2 = 37; 
int li1 = 22; 
int li2 = 23; 

#define lr A15
#define ud A14

int xVal = 0; 
int yVal = 0; 

void setup() {
  Serial.begin(9600); 
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
