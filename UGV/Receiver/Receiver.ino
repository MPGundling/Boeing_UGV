#include <Adafruit_MotorShield.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <Wire.h>
#include <Servo.h>

// R/T variable instantiation.
RF24 receiver(7, 8);
byte address [6] = "00001";

// Adafruit Motorshield variable instantiation.
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Left motor (M1)
Adafruit_DCMotor *leftMotor = AFMS.getMotor(3);
//Right Motor (M2)
Adafruit_DCMotor *rightMotor = AFMS.getMotor(4);
// Intake motor
Adafruit_DCMotor *intakeMotor = AFMS.getMotor(2);

Servo pan;
Servo tilt;
int init_pan = 90;
int init_tilt = 90;

void setup() {
  Serial.begin(9600);
  Serial.println("Serial open");
  receiver.begin();
  receiver.openReadingPipe(0, address);
  receiver.setPALevel(RF24_PA_MIN);
  receiver.setDataRate(RF24_250KBPS);
  receiver.setChannel(20);
  receiver.startListening();

  AFMS.begin();  // create with the default frequency 1.6KHz

  pan.attach(9);
  //pan.write(init_pan);
  tilt.attach(10);
  //tilt.write(init_tilt);
  
  
}

void loop() {
  delay(5);
  while (receiver.available()) {
    //Serial.println("Starting program");
    // data structure: [left motor, right motor, pan servo, tilt servo, belt intake on/off]
    int incoming[6];
    receiver.read(&incoming, sizeof(incoming));
    //Serial.println(incoming[4]);

    // Idle motorL behavior.
    if (475 < incoming[0] < 525) {
      leftMotor -> setSpeed(0);
      leftMotor -> run(RELEASE);
      //Serial.println("L IDLE");
    }

    // Idle motorR behavior.
    if (475 < incoming[1] < 525) {
      rightMotor -> setSpeed(0);
      rightMotor -> run(RELEASE);
      //Serial.println("R IDLE");
    }
    
    // Backward motorL logic.
    if (incoming[0] > 525) {
      int FL_speed = map(incoming[0], 525, 1023, 0, 255);
      leftMotor -> setSpeed(FL_speed);
      leftMotor -> run(BACKWARD);
      //Serial.println("L FORWARD");
    }

    // Forward motorR logic.
    if (incoming[1] > 525) {
      int FR_speed = map(incoming[1], 525, 1023, 0, 255);
      rightMotor -> setSpeed(FR_speed);
      rightMotor -> run(FORWARD);
      //Serial.println("R FORWARD");
    }

    // Forward motorL logic. 
    if (incoming[0] < 475) {
      int BL_speed = map(incoming[0], 0, 475, 255, 0);
      leftMotor -> setSpeed(BL_speed);
      leftMotor -> run(FORWARD);
      //Serial.println("L BACKWARD");
    }

    // Backward motorR logic. 
    if (incoming[1] < 475) {
      int BL_speed = map(incoming[1], 0, 475, 255, 0);
      rightMotor -> setSpeed(BL_speed);
      rightMotor -> run(BACKWARD);
      //Serial.println("R BACKWARD");
    }

    // Intake motor logic.
    if (incoming[4] == 0) {
      intakeMotor -> setSpeed(75);
      intakeMotor -> run(BACKWARD);
      //Serial.println("Intake running...");
    }

    else {
      intakeMotor -> setSpeed(0);
      intakeMotor -> run(RELEASE);
      //Serial.println("Intake stopped.");
    }

  pan.write(incoming[3]);
  tilt.write(incoming[2]);
    
    Serial.print(incoming[0]);
  Serial.print("     ");
  Serial.print(incoming[1]);
  Serial.print("     ");
  Serial.print(incoming[2]);
  Serial.print("     ");
  Serial.print(incoming[3]);
  Serial.print("     ");
  Serial.print(incoming[4]);
  Serial.println("");
  }
}
