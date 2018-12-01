#include <Adafruit_MotorShield.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <Wire.h>

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

void setup() {
  Serial.begin(9600);
  receiver.begin();
  receiver.openReadingPipe(0, address);
  receiver.setPALevel(RF24_PA_MIN);
  receiver.setDataRate(RF24_250KBPS);
  receiver.setChannel(20);
  receiver.startListening();

  AFMS.begin();  // create with the default frequency 1.6KHz
}

void loop() {
  while (receiver.available()) {
    Serial.println("Starting program");
    int incoming[6];
    receiver.read(&incoming, sizeof(incoming));
    Serial.println(incoming[4]);

    // Idle motorL behavior.
    if (400 < incoming[0] < 600) {
      leftMotor -> setSpeed(0);
      leftMotor -> run(RELEASE);
      Serial.println("L IDLE");
    }

    // Idle motorR behavior.
    if (400 < incoming[1] < 600) {
      rightMotor -> setSpeed(0);
      rightMotor -> run(RELEASE);
      Serial.println("R IDLE");
    }
    
    // Forward motorL logic.
    if (incoming[0] > 600) {
      int FL_speed = map(incoming[0], 600, 1023, 0, 255);
      leftMotor -> setSpeed(FL_speed);
      leftMotor -> run(BACKWARD);
      Serial.println("L FORWARD");
    }

    // Forward motorR logic.
    if (incoming[1] > 600) {
      int FR_speed = map(incoming[1], 600, 1023, 0, 255);
      rightMotor -> setSpeed(FR_speed);
      rightMotor -> run(FORWARD);
      Serial.println("R FORWARD");
    }

    // Backward motorL logic. 
    if (incoming[0] < 400) {
      //int BL_speed = map(incoming[0], 0, 400, 0, 255);
      leftMotor -> setSpeed(125);
      leftMotor -> run(FORWARD);
      Serial.println("L BACKWARD");
    }

    // Backward motorR logic. 
    if (incoming[1] < 400) {
      rightMotor -> setSpeed(250);
      rightMotor -> run(BACKWARD);
      Serial.println("R BACKWARD");
    }

    // Intake motor logic.
    if (incoming[4] == 0) {
      intakeMotor -> setSpeed(75);
      intakeMotor -> run(BACKWARD);
      Serial.println("Intake running...");
    }

    else {
      intakeMotor -> setSpeed(0);
      intakeMotor -> run(RELEASE);
      Serial.println("Intake stopped.");
    }
  }
}
