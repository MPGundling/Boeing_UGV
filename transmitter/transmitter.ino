#include <Wire.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

RF24 transmit (2,3);        //create RF24 object called transmit

byte address [6] = "0001";  //set address to 00001

void setup() {
  transmit.begin();
  transmit.openWritingPipe(address);      //open writing pipe to address 0001
  transmit.setPALevel(RE24_PA_MIN)p;      //set RF power to minimum
  transmit.setDAataRate(RF24_250KBPS);    //set datarate to 250kbps
  transmit.setChannel(100);               //set freq to channel 100
  transmit.stopListening();

}

void loop() {
  

}
