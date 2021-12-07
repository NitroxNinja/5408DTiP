#include "vex.h"
#include "main.h"
#include <cmath>

using namespace vex; 

/*void driveSetVelocity( double speed){
  FL.setVelocity(speed,percent); 
  FR.setVelocity(speed,percent);
  BL.setVelocity(speed,percent); 
  BR.setVelocity(speed,percent); 
}

void rotateDrive(float count){
  FL.spinFor(count, rotationUnits::rev,false);
  BL.spinFor(count, rotationUnits::rev,false);
  BR.spinFor(count, rotationUnits::rev,false);
  FR.spinFor(count, rotationUnits::rev);       // block until complete
  task::sleep(50);   
}*/


/*void spinUpReverse(bool spinIndex)
{ 
  if(spinIndex == true)
  {
    intake.spin(reverse,90,percent);
  }

  if(spinIndex == false)
  {
    intake.stop(brakeType::brake);
  }
  task::sleep(5);
}*/

void liftUp(double revs,double speed)
{
  lift.setVelocity(speed,percent);
  lift.spinFor(revs, rotationUnits::rev);
}

/*void backLiftUp(double revs,double speed)
{
  backLift.setVelocity(speed,percent);
  backLift.spinFor(revs, rotationUnits::rev);
}*/

void spinUp(bool spinIndex){ 
  if(spinIndex == true){
    intake.spin(forward,12,voltageUnits::volt);
  }

  if(spinIndex == false){
    intake.stop(brakeType::brake);
  }

  task::sleep(5);
}


void createTag(){
  Brain.Screen.clearLine(1, black);
  Brain.Screen.setFont(mono20);
  Brain.Screen.setCursor(1, 14);
}

//calibration of sensor 

void calib(){
  iner.calibrate();
  
  while(iner.isCalibrating()){
    createTag();
    Brain.Screen.print("Inertial is Calibrating...");
    task::sleep(20);

    if(iner.isCalibrating() == false){
    createTag();
    Brain.Screen.print("Inertial is Calibrated!");
    }
  }
}
