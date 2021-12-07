/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Aug 16 2021                                               */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// lateralEnc           encoder       G, H , LMAO           
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "main.h"

using namespace vex;

// A global instance of competition
competition Competition;

int autonomousSelection = -1;

typedef struct _button {
    int    xpos;
    int    ypos;
    int    width;
    int    height;
    bool   state;
    vex::color offColor;
    vex::color onColor;
    const char *label;
} button;

button buttons[] = {
    {   25,  30, 75, 75,  false, 0x404040, 0x40826d , "AWP 1"},
    {  145,  30, 75, 75,  false, 0x404040, 0x40826d ,"MogoRings" },
    {  265,  30, 75, 75,  false, 0x404040, 0xE00000, "Red 3" },
    {  385,  30, 75, 75,  false, 0x404040, 0xE34234, "Skills" },
    {   25, 140, 75, 75,  false, 0x404040, 0x0000E0, "Blue 1" },
    {  145, 140, 75, 75,  false, 0x404040, 0x0000E0, "Blue 2" },
    {  265, 140, 75, 75,  false, 0x404040, 0x0000E0, "Blue 3" },
    {  385, 140, 75, 75,  false, 0x404040, 0XDC9E43 , "Simple" }
};

void displayButtonControls( int index, bool pressed );

int findButton(  int16_t xpos, int16_t ypos ) {
    int nButtons = sizeof(buttons) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      button *pButton = &buttons[ index ];
      if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) )
        continue;

      if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) )
        continue;

      return(index);
    }
    return (-1);
}

/*-----------------------------------------------------------------------------*/
/** @brief      Init button states                                             */
/*-----------------------------------------------------------------------------*/
void initButtons() {
    int nButtons = sizeof(buttons) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      buttons[index].state = false;
    }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been touched                                        */
/*-----------------------------------------------------------------------------*/
void userTouchCallbackPressed() {
    int index;
    int xpos = Brain.Screen.xPosition();
    int ypos = Brain.Screen.yPosition();

    if( (index = findButton( xpos, ypos )) >= 0 ) {
      displayButtonControls( index, true );
    }

}

/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been (un)touched                                    */
/*-----------------------------------------------------------------------------*/
void userTouchCallbackReleased() {
    int index;
    int xpos = Brain.Screen.xPosition();
    int ypos = Brain.Screen.yPosition();

    if( (index = findButton( xpos, ypos )) >= 0 ) {
      // clear all buttons to false, ie. unselected
      //      initButtons(); 

      // now set this one as true
      if( buttons[index].state == true) {
      buttons[index].state = false; }
      else    {
      buttons[index].state = true;}

      // save as auton selection
      autonomousSelection = index;

      displayButtonControls( index, false );
    }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Draw all buttons                                               */
/*-----------------------------------------------------------------------------*/
void displayButtonControls( int index, bool pressed ) {
    vex::color c;
    Brain.Screen.setPenColor( vex::color(0xe0e0e0) );

    for(int i=0;i<sizeof(buttons)/sizeof(button);i++) {

      if( buttons[i].state )
        c = buttons[i].onColor;
      else
        c = buttons[i].offColor;

      Brain.Screen.setFillColor( c );

      // button fill
      if( i == index && pressed == true ) {
        Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, c );
      }
      else
        Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height );

      // outline
      Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, vex::color::transparent );

// draw label
      if(  buttons[i].label != NULL )
        Brain.Screen.printAt( buttons[i].xpos + 8, buttons[i].ypos + buttons[i].height - 8, buttons[i].label );
    }
}

double speedCap = 1; 
double speedCapTurn = 1;

double kP = 0.118; //.13
double kI = 0.0; //integral control causes the robot to jitter
double kD = 0.27; //0.5
double turnkP = 0.285;//0.14
double turnkI = 0.0; //integral control causes the robot to jitter
double turnkD = 0.34;//0.0015; 0.44
 
float dV = 0;
int dTV = 0;
 
int error; //sensor-desired value positional value
int prevError = 0; //error 20 milliseconds ago
int derivative;
int totalError = 0; //what in the world is this
 
int turnError; //sensor-desired value positional value
int turnPrevError = 0; //error 20 milliseconds ago
int turnDerivative;
int turnTotalError = 0; //what in the world is this
 
bool resetDriveSensors = false;
bool enablePID = false;
 
int drivePID()
{
 
 while(enablePID)
 {
 
   if(resetDriveSensors)
   { 
     frontL.setPosition(0,degrees);
     frontR.setPosition(0,degrees);
  
     lateralEnc.setPosition(0, degrees);

     iner.setRotation(0,degrees);
     resetDriveSensors=false; //this is a bool, once the sensors have been reset, it will return as "true"
   }

   int trackingWheelPosition = -lateralEnc.rotation(degrees) * 1.4545;
  
   int inertialPosition = iner.rotation(degrees);

   //int averagePosition = (frontL.position(degrees) + frontR.position(degrees)) / 2;
   
   int averagePosition = trackingWheelPosition;

   error = averagePosition - ((360 * dV) * 1.05); 
 
   derivative = error - prevError; 

   totalError += error;  
 
   double lateralMotorPower = ((error * kP + derivative * kD + totalError * kI) / 12 );
  
   int turnDifference = inertialPosition; 
   
   turnError = turnDifference - dTV;
 
   turnDerivative = turnError - turnPrevError; 
 
   turnTotalError += turnError; 
 
   double turnMotorPower = (turnError * turnkP + turnDerivative * turnkD + turnTotalError * turnkI) / 2 ;
 
   frontL.spin(reverse , (lateralMotorPower * speedCap) + (turnMotorPower * speedCapTurn) , voltageUnits::volt);
   middleL.spin(reverse , (lateralMotorPower * speedCap) + (turnMotorPower * speedCapTurn) , voltageUnits::volt);
   backL.spin(reverse , (lateralMotorPower * speedCap) + (turnMotorPower * speedCapTurn) , voltageUnits::volt);   
   frontR.spin(reverse , (lateralMotorPower * speedCap) - (turnMotorPower * speedCapTurn) , voltageUnits::volt);
   middleR.spin(reverse , (lateralMotorPower * speedCap) - (turnMotorPower * speedCapTurn) , voltageUnits::volt);
   backR.spin(reverse , (lateralMotorPower * speedCap) - (turnMotorPower * speedCapTurn) , voltageUnits::volt);

   prevError = error;
   turnPrevError = turnError;
 
   vex::task::sleep(25);
 }
 return 1; 
}

float speedCapLift = 1;

double liftkP = 0.9; //.13
double liftkI = 0.0; //integral control causes the robot to jitter
double liftkD = 0.0; //0.5

float liftUpAsync = 0;

int liftError; //sensor-desired value positional value
int liftPrevError = 0; //error 20 milliseconds ago
int liftDerivative;
int liftTotalError = 0; //what in the world is this

bool resetLift = false;
bool enableLiftPID = false;

int asyncLiftControl()
{
  while(enableLiftPID)
  {
    if(resetLift) 
    {
      lift.setPosition(0,degrees);
      resetLift = false;
    }
  
  int liftDegrees = lift.position(degrees);
  liftError = liftDegrees - ((360 * liftUpAsync) * 1.05);

   liftDerivative = liftError - liftPrevError; 

   liftTotalError += liftError;  
 
   double liftMotorPower = ((liftError * liftkP + liftDerivative * liftkD + liftTotalError * liftkI) / 12 );

   lift.spin(reverse , (liftMotorPower * speedCapLift) , voltageUnits::volt);

   liftPrevError = liftError;
  }
  return 1;
}



void pre_auton(void) {
  calib();
  vexcodeInit();
  //mogoDrag.close();
}



void autonomous(void) {
  vex::task bill(drivePID);
  vex::task drill(asyncLiftControl);
  enablePID = true;
  resetDriveSensors= true;

  int Red1   = buttons[0].state; //auton selector 
  int Red2   = buttons[1].state;
  int Red3   = buttons[2].state;
  int Skills = buttons[3].state;
  int Blue1  = buttons[4].state;
  int Blue2  = buttons[5].state;
  int Simple = buttons[7].state;

  int Blue3  = buttons[6].state;
  if(Red1)
  {

    liftUp(-0.07,100);
    mogoDrag.open();
    spinUp(true);
    task::sleep(300);
    spinUp(false);
    mogoDrag.close();

    speedCap = 0.55;
    dV = 4.85;
    dTV = 90;
    task::sleep(2500);
    resetDriveSensors = true;

    speedCapTurn = 1;
    dV = 0;
    dTV = 90;
    task::sleep(900);
    resetDriveSensors = true;

    speedCap = 0.8;

    dV = 16;
    dTV = 0;
    task::sleep(3000);
    resetDriveSensors = true;

    speedCap = 1;

    dV = 1;
    dTV = 0;
    task::sleep(500);

    clamp.open();
    task::sleep(250);
    resetDriveSensors = true;

    dV = -4;
    dTV = 0;
    task::sleep(1400);

    clamp.close();
    task::sleep(250);
    resetDriveSensors = true;

    dV = 0;
    dTV = -90;
    task::sleep(500);
    resetDriveSensors = true;

    dV = 5;
    dTV = 30;
    task::sleep(1500);
    resetDriveSensors=true;

    clamp.open();
    task::sleep(250);
    //clamp.close();

    dV=0;
    dTV=57;
    task::sleep(750);
   resetDriveSensors=true;

    speedCap=0.8;
    dV=-4;
    dTV=0;
    task::sleep(750);
    resetDriveSensors=true;

    mogoDrag.open();
    task::sleep(250);

    speedCap=0.7;
    dV=8;
    dTV=135;
    task::sleep(3000);

   /* speedCap = 0.3;
    dV = -6;
    dTV = 55;
    task::sleep(2000);*/
 
  }
  if(Red2){
    //make sure the kick stand is kicked 
    liftUp(-0.05,100);
    dV = 7;
    dTV = 10;
    task::sleep(1700);

    clamp.open();
    task::sleep(100);
    resetDriveSensors = true;

    dV = -9;
    dTV = 0;
    task::sleep(2000);
    resetDriveSensors = true;

    dV = 0;
    dTV = 80;
    task::sleep(850);

    clamp.close();
    task::sleep(50);
    resetDriveSensors = true;


    enableLiftPID = true; //resets the lift in preparation for the next movement 
    resetLift = true;

    dV = -5;
    dTV = 0;
    task::sleep(1000);
    
    mogoDrag.open();
    task::sleep(250);
    spinUp(true);
    resetDriveSensors = true;

    liftUpAsync = 2; //lift up while going forward to intake rings 
    dV = 4;
    dTV = 0;
    task::sleep(900);
    resetDriveSensors = true;

    dV = -3.5;
    dTV = 0;
    task::sleep(900);
    resetDriveSensors = true;

    dV = 3.5;
    dTV = 0;
    task::sleep(900);
    resetDriveSensors = true;

    dV = -3.5;
    dTV = 0;
    task::sleep(850);
    resetDriveSensors = true;

    dV = 3.5;
    dTV = 0;
    task::sleep(850);
    resetDriveSensors = true;




    



  
  }
  if(Red3){}
  if(Skills){
     enableLiftPID = true;
    //resetLift =true;
    liftUp(-0.05,100);
    dV = -0.5;
    dTV = 0;
    task::sleep(750);

    mogoDrag.open();
    task::sleep(200);
    resetDriveSensors = true;

   
    dV = 3;
    dTV = 80;
    task::sleep(1750);
    resetDriveSensors=true;

    /*speedCap=0.4;
    dV = 0.5;
    dTV = 0;
    task::sleep(1000);
    resetDriveSensors=true;*/

    speedCap=0.6;
    dV=6.25;
    dTV=28;
    task::sleep(2500);
    //resetDriveSensors = true;

    clamp.open();
    task::sleep(499);
    resetDriveSensors = true;

       

    
    liftUpAsync = 2;
    dV = 8.25;
    dTV = 27;
    task::sleep(2400);
    resetDriveSensors = true;
  

    

    //what if you put th lift up during the go dV commanddd
   


   // liftUp(2,100);
    //resetDriveSensors=true;

    
    dV=1.75;
    dTV=-35;
    task::sleep(1000);
    //resetDriveSensors=true;



    clamp.close();
    task::sleep(250);




    /*dV=-0.5;
    dTV=0;
    task::sleep(500);
    resetDriveSensors=true;

    speedCap=1;
    dV=0;
    dTV=-45;
    task::sleep(750);
    resetDriveSensors=true;

    mogoDrag.close();
    task::sleep(250);

    dV=4;
    dTV=0;
    task::sleep(1500);
    //resetDriveSensors=true;

    clamp.open();
    task::sleep(250);*/    
  }
  if(Blue1){}
  if(Blue2){}
  if(Blue3){}
  if(Simple)
  {

    printf("Hello World");
    enableLiftPID = true;
    resetLift =true;
    clamp.open();
    //no
    task::sleep(500);
    liftUpAsync = 2;
    dV = 4;
    dTV = 0;
    task::sleep(2400);

  }


}



void usercontrol(void) {
  // User control code here, inside the loop
  enablePID = false;
  while (1) {
    joystickControl();
    liftControl();
    intakeControl();
    mogoClampControl();
    mogoDragControl();
  
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  Brain.Screen.pressed(userTouchCallbackPressed);
  Brain.Screen.released(userTouchCallbackReleased);
  displayButtonControls(0,false);
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  //Brain.Screen.clearLine(1, black);

  
  

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {

    Brain.Screen.setFont(mono20);
    Brain.Screen.setCursor(2,14);
    Brain.Screen.print(lateralEnc);
    wait(100, msec);
  }
}
