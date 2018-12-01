#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

RF24 receiver(7,8);   
byte address [6] = "00001";   

void setup() {
    Serial.begin(9600);
    receiver.begin();
    receiver.openReadingPipe(0, address);
    receiver.setPALevel(RF24_PA_MIN);
    receiver.startListening();
}

void loop() {
    if (radio.available()) {
        char incoming[6] = "";
        receiver.read(&incoming, sizeof(incoming));
        Serial.println(incoming);
    }
}