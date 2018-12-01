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
  receiver.startListening();

  AFMS.begin();  // create with the default frequency 1.6KHz
}

void loop() {
  if (receiver.available()) {
    char incoming[6] = "";
    receiver.read(&incoming, sizeof(incoming));
    Serial.println(incoming);

    if (incoming[4] == 0) {
      intakeMotor -> setSpeed(255);
      intakeMotor -> run(FORWARD);
      Serial.println("Intake running...");
    }

    else {
      intakeMotor -> setSpeed(0);
      intakeMotor -> run(RELEASE);
      Serial.println("Intake stopped.");
    }
  }
}
