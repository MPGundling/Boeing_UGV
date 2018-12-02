# Boeing_UGV
This repository holds the programming logic for Boeing (Team 3) for CMPEN482 at the Pennsylvania State University.

Overview:
Progammed in Arduino extensively using the Adafruit Motorshield_v2 library. We have two arduino programs, one to transmit data, and the other to receive data and command the UGV. Transmission is handled using the nrfl01 R/T pair and the associated library.
In accordance with our efforts to maintain a afe device, a key-fob is implemented in between our power supply and controls, allowing us to disable the UGV remotely, and restart it.
Contributors:

Mark Gundling

Christian Lim

Control Overview:
Movement Controls:

  Left joystick: Movement control with left motor.
  
  Central joystick: Pan/Tilt control with motor.
  
  Right joystick: Movement control with right motor.

  Button: Intake control motor.
  
