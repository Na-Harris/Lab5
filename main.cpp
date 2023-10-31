//Copy_Paste your main.cpp file here
#include <Arduino.h>
#include <Pololu3piPlus32U4.h>
#include <Pololu3piPlus32U4IMU.h>
#include <Pololu3piPlus32U4LineSensors.h>

using namespace Pololu3piPlus32U4;

Motors motor;
IMU imu;
ButtonA buttonA;
ButtonB buttonB;
ButtonC buttonC;
LineSensors lineSensors;
OLED display;

#include "turnSensor.h"
/*
the turnSensor.h used has the turnSensorUpdate() function adjusted,
such that it returns an int value as (the heading). please note this in the 
turning functions below, as it provides context for the use of the
variable "heading" in the while loops
*/


void turnCounterClockwise()
{
  turnSensorReset();
  heading = turnSensorUpdate();
  while (heading <= 90)  
  {
    heading = turnSensorUpdate();
    motor.setRightSpeed(100);
    motor.setLeftSpeed(-100);
  }
  motor.setRightSpeed(0);
  motor.setLeftSpeed(0);
}

void turnClockwise()
{
  turnSensorReset();
  heading = turnSensorUpdate();
  while (heading >= -90)  
  {
    heading = turnSensorUpdate();
    motor.setRightSpeed(-100);
    motor.setLeftSpeed(100);
  }
  motor.setRightSpeed(0);
  motor.setLeftSpeed(0);
}

void hitBlackLine()
{
  motor.setSpeeds(100,100);
  uint16_t sensorValues[5];
  bool t = true;
  while (t)
  {
    lineSensors.readCalibrated(sensorValues);
    for (int i = 0; i < 4; i++)
    {
      if(sensorValues[i] == 1000)
      {
        motor.setSpeeds(0,0);
        t = false;
      }
    }
  }
}

void calibrateSensors()
{
  // Wait 1 second and then begin automatic sensor calibration
  // by rotating in place to sweep the sensors over the line
  delay(1000);
  for(uint16_t i = 0; i < 80; i++)
  {
    if (i > 20 && i <= 60)
    {
      motor.setSpeeds(-60, 60);
    }
    else
    {
      motor.setSpeeds(60, -60);
    }

    lineSensors.calibrate();
  }
  motor.setSpeeds(0, 0);
}

void lab5()
{
  
  if (buttonA.getSingleDebouncedPress())
  {
    //display turning right
    display.gotoXY(0,1);
    display.print("Turning Right");
    //pause before turning, then turn
    delay(750);
    turnClockwise();
    //clear display
    display.gotoXY(0,1);
    display.print("                ");
  }
  else if (buttonB.getSingleDebouncedPress()) 
  {
    //display turning left
    display.gotoXY(0,1);
    display.print("Turning Left");
    //pause before turning left, then turn
    delay(750);
    turnCounterClockwise();
    //clear display
    display.gotoXY(0,1);
    display.print("                ");
  }
  else if (buttonC.getSingleDebouncedPress())
  {
    //display moving forward
    display.gotoXY(0,1);
    display.print("Moving Forward");
    //pause before moving forward, then move until black line is found
    delay(750);
    hitBlackLine();
    //clear display
    display.gotoXY(0,1);
    display.print("                ");
  }
  else
  {
    display.gotoXY(0,1);
    display.print("Waiting...");
  }
}

void setup() {
  //initialize display
  display.init();
  // display name on top line
  display.setLayout21x8();
  display.clear();
  display.print("Harris");
  //initialize turn sensor
  turnSensorSetup();
  //remind user to press "B" while robot is over black line to calibrate line sensors
  display.gotoXY(0,1);
  display.print("Press B");
  display.gotoXY(0,2);
  display.print("To Calibrate");
  display.gotoXY(0,3);
  display.print("Line Sensors");
  //calibrate line sensor when "B" is pressed
  bool wait = true;
  while (wait)
  {
    if (buttonB.getSingleDebouncedPress())
    {
      //clear extra messages
      display.gotoXY(0,1);
      display.print("                ");
      display.gotoXY(0,2);
      display.print("                ");
      display.gotoXY(0,3);
      display.print("                ");
      //calibrate line sensor
      delay(1000);
      calibrateSensors();
      wait = false;
    }
  }
}

void loop()
{
  lab5();

  // delay(500);
  /*
  the delay makes it so the robot only takes input to lab5() for an instant every half second.
  it is unneccessary given the function already waits for future inputs after completing an action.
  the delay is staying commented out
  */

}
