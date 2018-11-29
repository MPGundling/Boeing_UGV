#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

//nRF24 constants and variables
String serialdata; //Holds data coming in
char msg[32]; //Char array to send data out with
RF24 transmit (7,8);                    //create RF24 object called transmit
byte address [6] = "00001";             //set address to 00001

//Joystick constants
const int left_y_axis = 0;             //left joystick y-axis for left motor control (pin A0)
const int right_y_axis = 1;            //right joystick y-axis for right motor control (pin A1)
const int pan_x_axis = 2;              //pan/tilt joystick x axis for pan control (Pin A2)
const int tilt_y_axis = 3;             //pan/tilt joystick y-axis for tilt control (pin A3)
int left_motor = 0;                    //left motor speed initialization
int right_motor = 0;                   //right motor speed initialization
int pan_angle = 90;                    //initial pan angle (center)
int tilt_angle = 0;                    //initial tilt angle (down)
int pot_value = 0;                     //variable for servo mapping

void setup() {
  Serial.begin(115200);
  Serial.println ("Serial Port Open");

  //wireless setup
  transmit.begin();
  transmit.openWritingPipe(address);    //open writing pipe to address 00001
  transmit.setPALevel(RF24_PA_MAX);     //set RF power output to maximum
  transmit.setDataRate(RF24_250KBPS);   //set datarate to 250kbps
  transmit.setChannel(20);              //set frequency to channel 20
  transmit.stopListening();             //stop receiving

  //button digital pin setup (for whatever buttons we need)
   
   }

void loop() {
//commented wireless for joystick test
 /*while(Serial.available()){
    
    //Serial.println ("I found Serial Data");// If you are having issues, these will help you find where your code doesnt work.
    serialdata=Serial.read();//put text from serial in serialdata string¸
    serialdata.toCharArray(msg, 4);//convert serialdat the the msg char array
    //Serial.println ("I converted it to a CHAR ARRAY");
    //Serial.println("Text to be Sent-");//debugging
    //Serial.println("");//debugging
    Serial.print(msg);//debugging
    //Serial.println("");//debugging
   }

  delay(10);
  transmit.write(msg, 4);
  
  for(int i=0; i <= sizeof(msg); i++){
    msg[i] = 0;
  }*/
  left_motor = analogRead(left_y_axis);           //read 0-1023 value from left joystick
  right_motor = analogRead(right_y_axis);         //read 0-1023 value from right joystick
  pot_value = analogRead(pan_x_axis);             //read 0-1023 value from pan/tilt x-axis
  pan_angle = map(pot_value, 0, 1023, 0, 180);    //map x-axis value to 0-180 degrees for servo position
  pot_value = analogRead(tilt_y_axis);            //read 0-1023 value from pan/tilt y-axis
  tilt_angle = map(pot_value, 0, 1023, 0, 180);    //map y-axis value to 0-180 degrees

  Serial.print("Left motor: ");
  Serial.println(left_motor);
  Serial.print("Right motor: ");
  Serial.println(right_motor);
  Serial.print("Pan angle: ");
  Serial.println(pan_angle);
  Serial.print("Tilt angle: ");
  Serial.println(tilt_angle);

  delay(100);

}
