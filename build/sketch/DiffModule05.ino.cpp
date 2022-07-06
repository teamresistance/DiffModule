#include <Arduino.h>
#line 1 "c:\\Users\\Hofmjc\\Documents\\_FRC\\DiffModule\\DiffModule05\\DiffModule05.ino"
/*
 * Author: Jim Hofmann
 * History
 * 2022/06/03 Rev: 0.1 - Test motors and interaction using pots.
 * 2022/06/03 Rev: 0.2 - Start isolating code modules
 * 2022/06/05 Rev: 0.3 - Move modules to classes
 * 2022/06/07 Rev: 0.4 - Rescale pots to +/- 1.0.  PotA is speed (Y) & potB is rotation (X).
 * <p>                   Motor takes +/- 1.0.  MtrA<=Spd+rot+corr, mtrB<=Spd - Rot - Corr.
 * <p>                   Move minInput & minSig to MotorControl
 * 2022/06/13 Rev: 0.4a - Move inDB back to pot.  Motor scales 0.0+ - 1.0 to minOut to 1.0.
 * 2022/06/23 Rev. 0.5 - Add Swerve calcs to calculate commands, move & rotate.  Convert to motor commands.
 *
 * This is to test the differential swerve module motors and interaction.
 * It is 3d printed and mechanically not tight but good for demo purposes.
 * I am running 2 TT motors (3 - 6 VDC) thru a L298N motor(s) controller.  PS is a buck convertor set at 7.2 vdc.
 * With 7.2 volts applied to the controller the motors need 3.2 VDC to move.  This is 125 pwm signal and max's at 255.
 * To reverse the motor requires reversing the signals at In1 & In2, Fwd & Rev.
 * I am using 2 pots to control the motors.  The pot read 0 - 1023 counts.  I scale this -511 to +512.
 * I then apply 10% deadband +/-50 counts around the zero reading.  I then scale this to a pwm signal from minimum
 * pwm, 25, to move the motor, 3 vdc to 255, 6 vdc.
 */
// Include files & classes
#include "Constants.h"		//Includes pin assignments
#include "ScalePot.h"		//Read pot and scale
#include "MotorControl.h"	//Issue motor commands
#include "SwerveCalc.h"		//Calc Motor A & B Speeds

// Variables
double mtrs_Spd = 0.0;	//Motors Speed +/-1.0
double mtrs_Cor = 0.0;	//Coorection to be added to A and subtracted from B to equalize at 0 turn
double mtrs_Trn = 0.0;	//Turn ratio.  Simple mult. complement by Spd and add to ASpd and minus BSpd.
bool prtDiag = true;
double * ptrMtrCmds;		//Pointer to a swerve motor cmds.
// Objects
ScalePot potA = ScalePot(kMtrA_PotPin);	//Potentiometer scaled +/-1.0 w/DB (default 0.10).
ScalePot potB = ScalePot(kMtrB_PotPin, 0.05);	//Potentiometer scaled +/-1.0 w/DB (default 0.10).
SwerveCalc rfSwerveMod = SwerveCalc();			//Swerve calcs for a swerve module
MotorControl mtrA = MotorControl(kMtrA_FwdPin, kMtrA_RevPin, kMtrA_SpdPin, 0.45);	//Motor A controller
MotorControl mtrB = MotorControl(kMtrB_FwdPin, kMtrB_RevPin, kMtrB_SpdPin, 0.45);	//Motor B controller

#line 41 "c:\\Users\\Hofmjc\\Documents\\_FRC\\DiffModule\\DiffModule05\\DiffModule05.ino"
void setup();
#line 54 "c:\\Users\\Hofmjc\\Documents\\_FRC\\DiffModule\\DiffModule05\\DiffModule05.ino"
void loop();
#line 41 "c:\\Users\\Hofmjc\\Documents\\_FRC\\DiffModule\\DiffModule05\\DiffModule05.ino"
void setup()
{
	// put your setup code here, to run once:
	Serial.begin(57600);
	Serial.println("Hello!");

	// ScalePot::prtDiag = prtDiag;
	MotorControl::prtDiag = prtDiag;
	SwerveCalc::prtDiag = prtDiag;
	delay(2000);

}

void loop()
{
	// put your main code here, to run repeatedly:
	//Read and scale the pot, direction & speed.
	mtrs_Spd = potA.readPot();
	if(potA.prtDiag) Serial.print(" \t");
	mtrs_Trn = potB.readPot();
	if(potB.prtDiag) Serial.println();
	//Use Speed & turn to calculate motor power cmds.
	ptrMtrCmds = rfSwerveMod.update(mtrs_Spd, mtrs_Trn);
    if(rfSwerveMod.prtDiag) Serial.println();

	//=================== Motor A =========================
	mtrA.cmdMotor(ptrMtrCmds[0]);
    if(mtrA.prtDiag) Serial.print("  \t||\t  ");

	//=================== Motor B =========================
	//Read and scale the pot then issue motor cmds.  Direction & speed.
	mtrB.cmdMotor(ptrMtrCmds[1]);

    if(prtDiag) Serial.println();
	delay(500);
}


