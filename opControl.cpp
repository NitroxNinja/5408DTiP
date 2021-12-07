#include "main.h"
#include "vex.h"
#include <cmath>

void joystickControl()
{
   int X,Y;
 
  if(abs(Controller1.Axis2.value())>9)
    Y = Controller1.Axis2.value() * 0.11;
    
  else
    Y = 0;
   
  if(abs(Controller1.Axis1.value()) >9)
    X = Controller1.Axis1.value() * 0.095 ;  

  else
  X = 0;

  frontL.spin(forward,(X + Y), volt);
  middleL.spin(forward,(X + Y),volt);
  backL.spin(forward,(X + Y), volt);
  frontR.spin(forward,(Y - X), volt);
  middleR.spin(forward,(Y - X), volt);
  backR.spin(forward,(Y - X), volt);  

  frontL.setStopping(brakeType::hold);
  middleL.setStopping(brakeType::hold);
  backL.setStopping(brakeType::hold);
  frontR.setStopping(brakeType::hold);
  middleR.setStopping(brakeType::hold);
  backR.setStopping(brakeType::hold);
}

void liftControl()
{
  if(Controller1.ButtonL1.pressing())
    lift.spin(forward,12,volt);
  else if(Controller1.ButtonL2.pressing())
    lift.spin(reverse,12,volt);
  else
    lift.stop(brakeType::hold);
}

void intakeControl()
{
  if(Controller1.ButtonR1.pressing())
    intake.spin(forward,90,percent);
  else if(Controller1.ButtonR2.pressing())
    intake.spin(reverse,100,percent);
  else
    intake.stop(brakeType::coast);
}


//mogo clamp
bool clampToggle = false;
bool latch = false;

void mogoClampControl()
{
   if(Controller1.ButtonLeft.pressing())
   {

    if(!latch)
    {
    clampToggle = !clampToggle;
    latch = true;
    }

    }
  else {
  latch = false;
  clamp.open();
  }

  if(clampToggle)
  {
    clamp.close();
  }
}

//mogo drag
bool dragToggle = false;
bool latch2 = false;

void mogoDragControl()
{
   if(Controller1.ButtonRight.pressing())
   {

    if(!latch2)
    {
    dragToggle = !dragToggle;
    latch2 = true;
    }

    }
  else {
  latch2 = false;
  mogoDrag.open();
  }

  if(dragToggle)
  {
    mogoDrag.close();
  }
}