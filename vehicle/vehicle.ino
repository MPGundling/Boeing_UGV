
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <printf.h>

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

RF24 receive (2,3);                         //create object called receive
byte address [6] = "00001";                 //creat an array with 5 elements, where each element is 1 byte;

int incomingbyte = 0;
int _speed = 64;
void setup() {
  //setup serial terminal
  Serial.begin(9600);
  Serial.println("Boeing UGV - Press 'W' for forward, 'S' for reverse, 'A' for left, 'D' for right, 'SPACE' for stop");
 
  //setup motor controller 
  AFMS.begin();  // create with the default frequency 1.6KHz

  //setup receiever
  receive.begin();
  receive.openReadingPipe(0,address);      //open reading pipe 0 at address 00001 
  receive.setPALevel(RF24_PA_MIN);         //Set RF output to minimum
  receive.setDataRate(RF24_250KBPS);       //set datarate to 250kbps
  receive.setChannel(100);                 //set frequency to channel 100 
  receive.startListening();
}

void loop() {
  // put your main code here, to run repeatedly:
 if(receive.available())
 {
  char incomingbtye;
  receive.read(&incomingbyte,sizeof(incomingbtye));
 }
 switch(incomingbyte)
 {
  case '1':
    Serial.println("25% Power");
    _speed = 64; 
    incomingbyte = '*';
    break;
  
  case '2':
    Serial.println("50% Power");
    _speed = 128;
    incomingbyte='*';
    break;
  
  case '3':
    Serial.println("100% Power");
    _speed = 250;
    incomingbyte='*';
    break;
  
  case 'w':
    Serial.println("Forward");
    for (int i=0; i<(_speed); i++){
      leftMotor->setSpeed(i);
      rightMotor->setSpeed(i);
      leftMotor->run(FORWARD);
      rightMotor->run(FORWARD);
      delay(4);
    }
    
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
  case 't':
    Serial.println("Current test. All on");
    intakeMotor->setSpeed(_speed);
    leftMotor->setSpeed(_speed);
    rightMotor->setSpeed(_speed);
    intakeMotor->run(FORWARD);
    leftMotor->run(FORWARD);
    rightMotor->run(FORWARD);
    incomingbyte='*';
    break;
   case ' ':
    Serial.println("STOP");
    leftMotor->setSpeed(0);
    rightMotor->setSpeed(0);
    leftMotor->run(RELEASE);
    rightMotor->run(RELEASE);
    intakeMotor->run(RELEASE);
    incomingbyte = '*';
    break;
  
  delay(10);
 }//end switch
}//end void loop
