#include <Servo.h>
#include <Ultrasonic.h>
Servo leftServo;
Servo rightServo;
Ultrasonic sonic1(5,3);
const int qtr1 = A0;
const int qtr2 = A1;
int rightQtrThreshold = 900;
int leftQtrThreshold = 800;
boolean go = true;
boolean backup = false;
int brakeLight = 12;
int leftLight = 10;
int rightLight = 11;
void setup() {
  rightServo.attach(10);
  leftServo.attach(11);
  rightServo.write(90);
  leftServo.write(90);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(brakeLight, OUTPUT);
  pinMode(leftLight, OUTPUT);
  pinMode(rightLight, OUTPUT);
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly
  int right = checkQtrRight();
  int left = checkQtrLeft();
  if (checkUltra() > 15){
    digitalWrite(brakeLight, LOW);
    if (right > rightQtrThreshold){
      goRight();
      Serial.println("RIGHT");
      digitalWrite(rightLight, HIGH);
      digitalWrite(leftLight, LOW);
    }else if (left > leftQtrThreshold){
      goLeft();
      Serial.println("LEFT");
      digitalWrite(leftLight, HIGH);
      digitalWrite(rightLight, LOW);
    }else{
     goForward(); 
     digitalWrite(leftLight, HIGH);
     digitalWrite(rightLight, HIGH);
     Serial.println("FORWARD");
    }
  }else{
    digitalWrite(brakeLight, HIGH);
    digitalWrite(leftLight, LOW);
    digitalWrite(rightLight, LOW);
    rightServo.write(90);
    leftServo.write(90);
    Serial.println("STOP");
  }
//  checkQtrLeft();
}
int checkQtrLeft(){
  int val = analogRead(qtr2);
//  Serial.println(val);
  return val;
}
int checkQtrRight(){
  int val = analogRead(qtr1);
//  Serial.println(val);
  return val;
}
int checkUltra(){
  int val = sonic1.read();
//  delayMicroseconds(1000);
//  Serial.println(val);
  return val;
}
void beep(unsigned char delayms){ 
  analogWrite(3, 50);
}

void goForward(){
  rightServo.write(70);
  leftServo.write(110);
}
void goRight(){
  rightServo.write(70);
  leftServo.write(70);
}
void goLeft(){
  rightServo.write(110);
  leftServo.write(110);
}
void goBack(){
  rightServo.write(110);
  leftServo.write(70);
}
