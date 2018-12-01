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

    // Idle motor behavior.
    if ((400 < incoming[0] < 600) && (400 < incoming[1] < 600)) {
      leftMotor -> setSpeed(0);
      rightMotor -> setSpeed(0);
      leftMotor -> run(RELEASE);
      rightMotor -> run(RELEASE);
      Serial.println("IDLE");
    }
    
    // Motor forwards logic.
    if (incoming[0] > 600 && incoming[1] > 600) {
      leftMotor -> setSpeed((incoming[0] + incoming[1]) / 2);
      rightMotor -> setSpeed((incoming[0] + incoming[1]) / 2);
      leftMotor -> run(FORWARD);
      rightMotor -> run(FORWARD);
      Serial.println("FORWARD");
    }

    // Motor backward logic. 
    if (incoming[0] < 400 && incoming[1] < 400) {
      leftMotor -> setSpeed((incoming[0] + incoming[1]) / 2);
      rightMotor -> setSpeed((incoming[0] + incoming[1]) / 2);
      leftMotor -> run(BACKWARD);
      rightMotor -> run(BACKWARD);
      Serial.println("BACKWARD");
    }

    // Motor left logic.
    if (incoming[0] < 400 && incoming[1] > 600) {
      leftMotor -> setSpeed((incoming[0] + incoming[1]) / 2);
      rightMotor -> setSpeed((incoming[0] + incoming[1]) / 2);
      leftMotor -> run(BACKWARD);
      rightMotor -> run(FORWARD);
      Serial.println("LEFT");
    }

    // Motor right logic.
    if (incoming[0] > 600 && incoming[1] < 400) {
      leftMotor -> setSpeed((incoming[0] + incoming[1]) / 2);
      rightMotor -> setSpeed((incoming[0] + incoming[1]) / 2);
      leftMotor -> run(FORWARD);
      rightMotor -> run(BACKWARD);
      Serial.println("RIGHT");
    }

    // intake logic.
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
