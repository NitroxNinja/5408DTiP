#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor frontL = motor(PORT1, ratio6_1, true);
motor middleL = motor(PORT2, ratio6_1, false);
motor backL = motor(PORT3, ratio6_1, true);
motor frontR = motor(PORT8, ratio6_1, false);
motor middleR = motor(PORT9, ratio6_1, true);
motor backR = motor(PORT10, ratio6_1, false);
motor lift = motor(PORT7, ratio36_1, true);
motor intake =  motor(PORT5, ratio6_1, true);
pneumatics clamp(Brain.ThreeWirePort.A);
pneumatics mogoDrag(Brain.ThreeWirePort.B);
inertial iner = inertial(PORT6);
encoder lateralEnc = encoder(Brain.ThreeWirePort.G);
//

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}