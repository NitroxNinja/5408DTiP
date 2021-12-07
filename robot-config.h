using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor frontL;
extern motor middleL;
extern motor backL;
extern motor frontR;
extern motor middleR;
extern motor backR;
extern motor lift;
extern motor intake;
extern pneumatics clamp;
extern pneumatics mogoDrag;
extern inertial iner;
extern encoder lateralEnc;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );