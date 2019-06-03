#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library

//our relay control pins
const int LeftMotorForward = 3;
const int LeftMotorBackward = 2;
const int RightMotorForward = 4;
const int RightMotorBackward = 5;
const int Cleaner = 8;
char t='A';
char k='w';
int flag = 1;
float distanceRight = 0;
float distanceLeft = 0;

//sensor pins
//#define trig_pin A1 //analog input 1
//#define echo_pin A2 //analog input 2
const int trig=13;
const int echo=12;
#define maximum_distance 200

float distance = 100;

NewPing ultra(trig, echo); //sensor function
Servo servo_motor; //our servo name

//functions
////////////////////////


float lookRight(){  
  servo_motor.write(0);
  makedelay(300);
  return readPing();
}

float lookLeft(){
  servo_motor.write(180);
  makedelay(300);
  return readPing();
}

/////////////////////////////////
void makedelay(int times)
{
  for (int i=0; i<times; ++i)
  {
    delay(1);
    k=Serial.read();
    Serial.println(t);
    if(k=='w'){
      digitalWrite(8,LOW);
    }
    else if(k=='W'){
      digitalWrite(8,HIGH);   
    }
  }
}

float readPing(){
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  float distance=pulseIn(echo,HIGH);
  distance= (distance/2)/29.1;
  Serial.print(distance);
  Serial.println(" cm");
  return distance; 
}

void moveStop(){
  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward(){
    
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
  
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW); }
  

void moveBackward(){
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
}
  //makedelay(100);


void turnRight(){
  if(t=='R'){
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(RightMotorForward, LOW);
  }
  else{
  for(int i=0;i<25000;++i){
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(RightMotorForward, LOW);
  }
  //makedelay(300);
}
}

void turnLeft(){
  if(t=='L'){
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  }
  else{
  for(int i=0;i<25000;++i){
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  }
  }
  //makedelay(300);
}

////////////////////////////////
void setup(){
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  servo_motor.attach(10); //our servo pin 
  servo_motor.write(90);
  pinMode(8,OUTPUT); 
}

void loop(){
  
 /* digitalWrite(13,HIGH);
  delay(300);
  digitalWrite(13,LOW);
  delay(300);*/
/* digitalWrite(Cleaner, HIGH);
 delay(5000);
  digitalWrite(Cleaner, LOW);
  delay(5000);*/
  if(Serial.available()){
  t = Serial.read();
  
  Serial.println(t);}

 
if(t == 'F'){            //move forward(all motors rotate in forward direction)
  moveForward();
}
 
else if(t == 'B'){      //move reverse (all motors rotate in reverse direction)
  moveBackward();
} 
else if(t == 'L'){      //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
  turnLeft();
} 
else if(t == 'R'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
  turnRight();
}
else if(t == 'W'){
digitalWrite(8,HIGH);
Serial.println("W");
 }

else if(t == 'w')
{
digitalWrite(8,LOW);
Serial.println("w");
}

else if(t == 'S'){      //STOP (all motors stop)
  moveStop();
}
//makedelay(100);

else if(t == 'A')
{
 
    distance=readPing();
    if (distance <= 20){
    moveStop();
    makedelay(300);
    distanceRight = lookRight();
    makedelay(300);
    servo_motor.write(90);
    makedelay(300);
    distanceLeft = lookLeft();
    makedelay(300);
    servo_motor.write(90);
    makedelay(100);
    Serial.print("right");
    Serial.print(distanceRight);
    Serial.print("left");
    Serial.print(distanceLeft);
    if (distanceRight >= distanceLeft){
      turnRight();
      makedelay(100);
      moveStop();
      makedelay(100);
      moveForward();
      makedelay(100);
    }
    else{
      turnLeft();
      makedelay(100);
      moveStop();
      makedelay(100);
      moveForward();
      makedelay(100);
    }
  }
  else{
    moveForward(); }
   }   
}
