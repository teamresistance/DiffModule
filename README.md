# DiffModule
Test code for a basic Differential Swerve module.  Code is C/C++ for an Arduino.

There are 2 motors.  Initially (rev: 0.1) individual potentiometers controlled each motor and allowed 

# VSCode and Arduino
I've had a few issues with VSCode and the Arduino compiler.  I've work through most.

One I know I <b>AM</b> the issue on one.  I didn't want to have a repo for each sketch version but I did want to keep each version in its' own folder.  By saving the versions we can review the progression of developement of the code.  However, VSC needs to know where we are playng.  So, in /.vscode/arduino.json when we switch sketches we need to edit the parmarmeter "sketch": "DiffModule01\\DiffModule01.ino" to the sketch we're working on.

# Revisions:
2022/06/03 Rev: 0.1 - Test motors and interaction using pots.  
2022/06/03 Rev: 0.2 - Start isolating code modules  
2022/06/05 Rev: 0.3 - Move modules to classes  
2022/06/07 Rev: 0.4 - Rescale pots to +/- 1.0.  PotA is speed (Y) & potB is rotation (X).    
.                   - Motor takes +/- 1.0.  MtrA<=Spd+rot+corr, mtrB<=Spd - Rot - Corr.
.                   - Move minInput & minSig to MotorControl
2022/06/13 Rev: 0.4a - Move inDB back to pot.  Motor scales 0.0+ - 1.0 to minOut to 1.0.
2022/06/23 Rev. 0.5 - Add Swerve calcs to calculate commands, move & rotate.  Convert to motor commands.
