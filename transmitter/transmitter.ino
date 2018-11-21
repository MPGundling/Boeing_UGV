#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

String serialdata; //Holds data coming in
char msg[32]; //Char array to send data out with

RF24 transmit (7,8);                    //create RF24 object called transmit

byte address [6] = "00001";             //set address to 00001

void setup() {
  Serial.begin(9600);
  Serial.println ("Serial Port Open");
  
  transmit.begin();
  transmit.openWritingPipe(address);    //open writing pipe to address 00001
  transmit.setPALevel(RF24_PA_MAX);     //set RF power output to maximum
  transmit.setDataRate(RF24_250KBPS);   //set datarate to 250kbps
  transmit.setChannel(20);             //set frequency to channel 20
  transmit.stopListening();   
   }

void loop() {

  if (Serial.available()){
    delay (100);
    Serial.println ("I found Serial Data");// If you are having issues, these will help you find where your code doesnt work.
    serialdata=Serial.readString();//put text from serial in serialdata string¸
  }
    
    else {

      serialdata.toCharArray(msg, 32);//convert serialdat the the msg char array
      Serial.println ("I converted it to a CHAR ARRAY");
      Serial.println("Text to be Sent-");//debugging
      Serial.println("");//debugging
      Serial.print(msg);//debugging
      Serial.println("");//debugging     
   }

  transmit.write(msg, 32);    
}

