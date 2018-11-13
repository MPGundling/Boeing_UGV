#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>

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

Servo panServo;
Servo tiltServo;

int incomingbyte = 0;
int _speed = 64;
int _speed_intake = 64;

char previous_input;

int servoHome = 90; //Default position of Servo
int panServoSweep = servoHome;
int tiltServoSweep = servoHome;

int panServoPin = 9;
int tiltServoPin = 10;

void setup() {
  Serial.begin(9600);
  Serial.println("BOEING UGV - START");

  AFMS.begin();  // create with the default frequency 1.6KHz

  panServo.attach(panServoPin);
  tiltServo.attach(tiltServoPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {
    incomingbyte = Serial.read();
  }
  switch (incomingbyte)
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
      _speed_intake = 64;
      incomingbyte = '*';

      Serial.println("Intake - 25% Power");
      break;

    case 'k':
      _speed_intake = 128;
      incomingbyte = '*';

      Serial.println("Intake - 50% Power");
      break;

    case 'l':
      _speed_intake = 250;
      incomingbyte = '*';

      Serial.println("Intake - 100% Power");
      break;

    //MARK: Belt intake control.

    case 'i':
      for (int i = 0; i < (_speed_intake); i++) {
        intakeMotor -> setSpeed(_speed_intake);
        intakeMotor -> run(BACKWARD);
        delay(4);
      }
      incomingbyte = '*';

      Serial.println("Intake accepting");
      break;

    case 'o':
      for (int i = 0; i < (_speed_intake); i++) {
        intakeMotor -> setSpeed(_speed_intake);
        intakeMotor -> run(FORWARD);
        delay(4);
      }
      incomingbyte = '*';

      Serial.println("Intake rejecting");
      break;

    case 'p':
      intakeMotor -> setSpeed(0);
      intakeMotor -> run(RELEASE);
      delay(4);
      incomingbyte = '*';

      Serial.println("Intake halting");
      break;

    //MARK: Movement control.

    case 'w':
      if (previous_input = 'w') {
        leftMotor -> run(FORWARD);
        rightMotor -> run(FORWARD);
      }

      else {
        for (int i = 0; i < (_speed); i++) {
          leftMotor -> setSpeed(i);
          rightMotor -> setSpeed(i);
          leftMotor -> run(FORWARD);
          rightMotor -> run(FORWARD);
          previous_input = 'w';
          delay(2);
        }
      }
      incomingbyte = '*';

      Serial.println("Forward");
      break;


    case 'a':
      if (previous_input = 'a') {
        leftMotor -> run(RELEASE);
        rightMotor -> run(FORWARD);
      }
      
      else {
        for (int i = 0; i < (_speed); i++) {
          leftMotor -> setSpeed(0);
          rightMotor -> setSpeed(i);
          leftMotor -> run(RELEASE);
          rightMotor -> run(FORWARD);
          previous_input = 'a';
          delay(2);
        }
      }
      incomingbyte = '*';

      Serial.println("Left");
      break;

    case 's':
      if (previous_input = 's') {
        leftMotor -> run(BACKWARD);
        rightMotor -> run(BACKWARD);
      }
      
      else {
        for (int i = 0; i < (_speed); i++) {
          leftMotor -> setSpeed(i);
          rightMotor -> setSpeed(i);
          leftMotor -> run(BACKWARD);
          rightMotor -> run(BACKWARD);
          previous_input = 's';
          delay(2);
        }
      }
      incomingbyte = '*';

      Serial.println("Backward");
      break;

    case 'd':
      if (previous_input = 'd') {
        leftMotor -> run(FORWARD);
        rightMotor -> run(RELEASE);
      }
      
      else {
        for (int i = 0; i < (_speed); i++) {
          leftMotor -> setSpeed(i);
          rightMotor -> setSpeed(0);
          leftMotor -> run(FORWARD);
          rightMotor -> run(RELEASE);
          previous_input = 'd';
          delay(2);
        }
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
      previous_input = 'x';
      incomingbyte = '*';

      Serial.println("No input");
      break;

      delay(10);
  }//end switch
}//end void loop
