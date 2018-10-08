
#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Left motor (M1)
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
//Right Motor (M2)
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);
// Intake motor
Adafruit_DCMotor *intakeMotor = AFMS.getMotor(3);

int incomingbyte = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Boeing UGV - Press 'W' for forward, 'S' for reverse, 'A' for left, 'D' for right");

  AFMS.begin();  // create with the default frequency 1.6KHz
  
}

void loop() {
  // put your main code here, to run repeatedly:
 if(Serial.available()>0)
 {
  incomingbyte = Serial.read();
 }
 switch(incomingbyte)
 {
  case 'w':
    Serial.println("Forward");
    leftMotor->setSpeed(150);
    rightMotor->setSpeed(150);
    leftMotor->run(FORWARD);
    rightMotor->run(FORWARD);
    incomingbyte = '*';
    break;
  
  case 's':
    Serial.println("Backward");
    leftMotor->setSpeed(150);
    rightMotor->setSpeed(150);
    leftMotor->run(BACKWARD);
    rightMotor->run(BACKWARD);
    incomingbyte = '*';
    break;
    
  case 'a':
    Serial.println("Left");
    leftMotor->setSpeed(0);
    rightMotor->setSpeed(150);
    leftMotor->run(RELEASE);
    rightMotor->run(FORWARD);
    incomingbyte = '*';
    break;
 
  case 'd':
    Serial.println("Right");
    leftMotor->setSpeed(150);
    rightMotor->setSpeed(0);
    leftMotor->run(FORWARD);
    rightMotor->run(RELEASE);
    incomingbyte = '*';
    break;
   
   case ' ':
    Serial.println("STOP");
    leftMotor->setSpeed(0);
    rightMotor->setSpeed(0);
    leftMotor->run(RELEASE);
    rightMotor->run(RELEASE);
    incomingbyte = '*';
    break;
  
  delay(10);
 }//end switch
}//end void loop
