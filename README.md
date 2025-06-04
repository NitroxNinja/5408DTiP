# 5408DTiP

Here I will be hopefully updating the code for the robot on GitHub monthly or so,

Or not, this code has been retired and is considered obsolete. 

This features all of 5408D Dynamo's code for the Tipping Point Season

-  Me
  
![image](https://github.com/user-attachments/assets/413b77a8-6787-4e4b-9e42-b95c4ca6e1c6)

![image](https://github.com/user-attachments/assets/cd2ebfce-0e10-4062-a6f7-49908ee3e2a5)

## Intro 

This code is more or less the same as the Change Up code but I think I put some lifting PID, since I had a to use a lift, so this sort of dives into the concept of parallel computing of tasks or something. 

## Driver-focused... sorta 

There is also very little drive macros and automated tasks. **This is a driver's robot. Not a neat robot.** Everything is raw control and skill. It's supposed to be a **viseral experience to drive one of my robots!** Even my drivetrain uses voltage control instead of PID (but this does come at some consequences such as low torque in both ends of the RPM limits), and features a autolocking drive (most people complain that this may damage the motors, but if you drive properly, it shouldn't). It uses arguably the most difficult to control setting, right hand single-stick arcade, and absolutely no power curves to the thing, just linear pure movement. 

But out of all my of my robots, this robot is the most simple to control, since the center of gravity most of the time was in the center, and I didn't really do that much throughout the match. There are 6 wheels, 4 being omni, and 2 tractions in the center. This prevents drifting, which means it isn't fun to drive. If you want fun to drive, try my Spin Up (the code for this is unique, it features the usage of both VEXcode Pro AND PROS EZ-Template) or Over Under robot. If you want horrible to drive try my Change Up robot. 

## Driver Control Methodology

Driver control functions are located in `opControl.cpp` and functions can be listed in main.h (which isn't on this repo, go check my other repos), and use a right hand single-stick arcade drive, which allows me (the driver) to do other tasks with the left hand. People in countries that drive RHD will find this workable, however most people may find this weird, so they can move it to their left hand. To be honest figuring out macros and other driver widgets is pretty easy,`if, else` and whatnot can be used. 

If you are still learning how to code, I highly recommend watching some videos on control structures, boolean statements, variables, functions, and more basic C++ topics. I have no idea how I taught myself C++ so good luck!

## Autonomous Routine Methodology

To adjust the lateral and turning PID, simply go to the `kP`, `kI`, and `kD` and tune accordingly. You can always adjust these values on the go, I think you could make a function to do that or something. 

There is an autonomous button selector, that when you run this code, 8 buttons will pop up. You can possibly add more but I think 8 is enough. Put your autonomous code into the autonomous function where there are `if` statements with the corresponding function/button. You could make a function to do that but nah. 

If you go to the autonomous function of the code, you may notice that I turn "on" my drivePID, but in my driver code I turn "off" my drivePID. This will be important as you do want your robot to move accurately in autonomous, but you do not want your robot to move against your will (of your controller) in drive control. 

## Autonomous Programming Tips and Remarks

### i. How to use this code
'`dV`' and '`dTV`' are short for "desiredValue" and "desiredTurnValue" respectively. The reason why I named it like this was so that it would be easier for me to input instructions on the go. '`resetDriveSensors`' is a boolean variable, that once is set to true, will reset all the IMEs and IMUs so that you can achieve a new movement from that pose. I will warn you to avoid using `resetDriveSensors` when possible and simply learn how to link movements by connecting the lines of code together, and adjusting the `task::sleep();` values. You can also make a function for to do that or something. For this README, I won't include any examples since it's practically the same as last year, so check out the code or my other repos. 

This represents the most raw form of control and it often is kind of hard to think about, but once you get the gist of it, you can code super advanced movements without requiring advanced odom or pure pursuit systems. Given that those systems are probably better, but this code presents a challenge to be independent and develop my own solutions to coding. 

### ii. Tips in developing autonomous routines (KISS, Keep it simple, stupid)
Make movements simple as possible. Make it fast. Make it reasonable. Why go in a curve when you just drive in a straight line? More crazier movements mean more crazier readings from your IMU and IMEs (aka this is called noise). There is a lack of kalman filtering on this system, and you're gonna have to be careful. 
But you may be asking why the hell would I do that? Well VEX is a very small field, and it doesn't have to dive deep into the real world sh-t of nonlinear systems, and special instrumentation devices. You should be able to go very far based on this code, and create more functions and make my code a WHOLE lot neater to help you simplify your programming. 

### iii. Include some comments 
I know CS teachers make a huge deal out of this, but to be honest take a chill pill. You don't always have to include comments on obivious things, just include comments where they may be complicated movements. In the code snippet above, I just included a lot to help you get a more intuitive sense on how our team programs. In reality, I just include one comment like "the robot is (should be) doing a right curve turn into the goal". Don't spend all your time on documentation.

### iv. Improve this code 
You get this. Don't just take this code at face value. There's so much work that can be done to this program which can make moving your robot better. I don't suggest using the same code for more than 4 years like how I did. I have an excuse to use the same code since our team didn't really invest into programming R&D, and most of the time it was me just building the robot and figuring out ideas rather than figuring out how to code. Try to make improvements to it every week or atleast monthly. 

You can also alternatively switch to another coding library like EZ-Template or LemLib, but I am different. 

## Conclusion 

This code is very simple. It is basically a spin-off of my previous code, since I used more or less a similar wheelbase, and ratio for everything. You should also watch my -1 Driver Skills video [here]( https://youtu.be/_R0UAOexxKs?si=k1NFltalZHmkeWsq). 
