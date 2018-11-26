

#include <Wire.h> //IIC Library


#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

RF24 receive (7,8);                         //create object called receive
byte address [6] = "00001";                 //creat an array with 5 elements, where each element is 1 byte;

String text = " ";//String to hold the text

void setup()
{
 

  Serial.begin(9600);
  Serial.print("Starting Receiver \n");
  receive.begin();
  receive.openReadingPipe(0,address);      //open reading pipe 0 at address 00001 
  receive.setPALevel(RF24_PA_MAX);         //Set RF output to maximum
  receive.setDataRate(RF24_250KBPS);       //set datarate to 250kbps
  receive.setChannel(20);                 //set frequency to channel 20 
  receive.startListening(); 

}

void loop(){
 
  
    if (receive.available())                //check when received data available
  {
    char buf[32];
    receive.read(&buf, sizeof(buf));
    text = (char*)buf;
    Serial.println(text);
  }
}
   
