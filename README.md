# Boeing_UGV
This repository holds the programming logic for Boeing (Team 3) for CMPEN482 at the Pennsylvania State University.

Overview:
Progammed in Arduino extensively using the Adafruit Motorshield_v2 library. The command center sends serial bytes from the keyboard. The code expects a constant stream of bytes, and accepts a "no input" as default. Putty will be used in place of Arduino's serial monitor to enable us to hold down keys and control the UGV fluidly.

Contributors:

Mark Gundling

Christian Lim

Control Overview:
Movement Controls:

  w,a,s,d : Directional control of UGV (Forward, Left, Reverse, Right).
  
  b,n,m : Movement speed toggling at 25%, 50%, 100% power respectively.
  
  ' ' (spacebar) : Stop command. Sets speed to all movement motors to 0 and releases movement motors.

Intake Controls:

  i,o : Directional control of intake belt (In, Out).
  
  j,k,l : Intake speed toggling at 25%, 50%, 100% power respectively.

Miscellanous:
TODO: Camera pan, kill switch, R/T summaries.
  
