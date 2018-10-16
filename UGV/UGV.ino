
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
int _speed = 64;
void setup() {
  Serial.begin(9600);
  Serial.println("Boeing UGV - Press 'W' for forward, 'S' for reverse, 'A' for left, 'D' for right, 'SPACE' for stop");
  
  AFMS.begin();  // create with the default frequency 1.6KHz
  
}

void loop() {
  // put your main code here, to run repeatedly:
 if(Serial.available() > 0)
 {
  incomingbyte = Serial.read();
 }
 switch(incomingbyte)
 {
  //MARK: Movement speed toggle.
  
  case 'b':  
    _speed = 64; 
    incomingbyte = '*';
    
    Serial.println("Movement - 25% Power");
    break;
  
  case 'n':
    _speed = 128;
    incomingbyte = '*';

    Serial.println("Movement - 50% Power");
    break;
  
  case 'm':
    _speed = 250;
    incomingbyte = '*';

    Serial.println("Movement - 100% Power");
    break;

  //MARK: Belt intake speed toggle.

  case 'j':  
    _speed = 64; 
    incomingbyte = '*';
    
    Serial.println("Intake - 25% Power");
    break;
  
  case 'k':
    _speed = 128;
    incomingbyte = '*';

    Serial.println("Intake - 50% Power");
    break;
  
  case 'l':
    _speed = 250;
    incomingbyte = '*';

    Serial.println("Intake - 100% Power");
    break;

  //MARK: Belt intake control.

  case 'i':
    intakeMotor -> setSpeed(250);
    intakeMotor -> run(REVERSE);
    delay(4);
    incomingbyte = '*';

    Serial.println("Intake accepting");
    break;

  case 'o':
    intakeMotor -> setSpeed(100);
    intakeMotor -> run(FORWARD);
    delay(4);
    incomingbyte = '*';

    Serial.println("Intake rejecting");
    break;

  //MARK: Movement control.
  
  case 'w':
  // TODO: Potentially refactor to setSpeed to _speed without for loop as this loop may be causing issues with successive inputs.
    for (int i = 0; i < (_speed); i++) {
      leftMotor -> setSpeed(i);
      rightMotor -> setSpeed(i);
      leftMotor -> run(FORWARD);
      rightMotor -> run(FORWARD);
      delay(4);
    }  
    incomingbyte = '*';
    
    Serial.println("Forward");
    break;
  
  case 's':
    for (int i = 0; i < (_speed); i++) {
      leftMotor -> setSpeed(i);
      rightMotor -> setSpeed(i);
      leftMotor -> run(BACKWARDS);
      rightMotor -> run(BACKWARDS);
      delay(4);
    }
    incomingbyte = '*';
    
    Serial.println("Backward");
    break;
    
  case 'a':
    for (int i = 0; i < (_speed); i++) {
      leftMotor -> setSpeed(0);
      rightMotor -> setSpeed(i);
      leftMotor -> run(RELEASE);
      rightMotor -> run(FORWARD);
    }
    incomingbyte = '*';
    
    Serial.println("Left");
    break;
 
  case 'd':
    for (int i = 0; i < (_speed); i++) {
      leftMotor -> setSpeed(i);
      rightMotor -> setSpeed(0);
      leftMotor -> run(FORWARD);
      rightMotor -> run(RELEASE);
    }
    incomingbyte = '*';

    Serial.println("Right");
    break;

   case ' ':
    leftMotor -> setSpeed(0);
    rightMotor -> setSpeed(0);
    leftMotor -> run(RELEASE);
    rightMotor -> run(RELEASE);
    incomingbyte = '*';

    Serial.println("STOP");
    break;

    default:
    // If no input, stop all motors, but maintain speed setting.
      leftMotor -> run(RELEASE);
      rightMotor -> run(RELEASE);
      intakeMotor -> run(RELEASE);
      incomingbyte = '*';

      Serial.println("No input");
      break;
      
  delay(10);
 }//end switch
}//end void loop
