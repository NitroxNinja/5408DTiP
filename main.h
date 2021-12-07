#ifndef MAIN_H
#define MAIN_H

//opControl.cpp

void joystickControl(void);
void liftControl(void);
void intakeControl(void);
void mogoClampControl(void);
void mogoDragControl(void);

//functions.cpp

void calib(void);
void liftUp(double revs,double speed);
//void backLiftUp(double revs,double speed);
void spinUp(bool spinIndex);
void spinUpReverse(bool spinIndex);

//autonSelector.cpp

void displayButtonControls( int index, bool pressed );
void userTouchCallbackPressed(void);
void userTouchCallbackReleased(void);

#endif 