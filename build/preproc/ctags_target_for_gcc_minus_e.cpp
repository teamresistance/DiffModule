# 1 "c:\\Users\\Hofmjc\\Documents\\_FRC\\DiffModule\\DiffModule04\\DiffModule04.ino"
/*

 * Author: Jim Hofmann

 * History

 * 2022/06/03 Rev: 0.1 - Test motors and interaction using pots.

 * 2022/06/03 Rev: 0.2 - Start isolating code modules

 * 2022/06/05 Rev: 0.3 - Move modules to classes

 * 2022/06/07 Rev: 0.4 - Rescale pots to +/- 1.0.  PotA is speed (Y) & potB is rotation (X).

 * <p>                   Motor takes +/- 1.0.  MtrA<=Spd+rot+corr, mtrB<=Spd - Rot - Corr.

 * <p>                   Move minInput & minSig to MotorControl

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
# 20 "c:\\Users\\Hofmjc\\Documents\\_FRC\\DiffModule\\DiffModule04\\DiffModule04.ino"
// Include files & classes
# 22 "c:\\Users\\Hofmjc\\Documents\\_FRC\\DiffModule\\DiffModule04\\DiffModule04.ino" 2
# 23 "c:\\Users\\Hofmjc\\Documents\\_FRC\\DiffModule\\DiffModule04\\DiffModule04.ino" 2
# 24 "c:\\Users\\Hofmjc\\Documents\\_FRC\\DiffModule\\DiffModule04\\DiffModule04.ino" 2

// Variables
double mtrs_Spd = 0.0;
double mtrs_Cor = 0.0;
double mots_Trn = 0.0;
bool prtDiag = true;
// Objects
ScalePot potA = ScalePot(kMtrA_PotPin); //Define function to read potentiometer and scale.
ScalePot potB = ScalePot(kMtrB_PotPin); //Define function to read potentiometer and scale.
MotorControl mtrA = MotorControl(kMtrA_FwdPin, kMtrA_RevPin, kMtrA_SpdPin, 0.1, 0.55); //Motor A controller
MotorControl mtrB = MotorControl(kMtrB_FwdPin, kMtrB_RevPin, kMtrB_SpdPin, 0.1, 0.45); //Motor B controller

void setup()
{
 // put your setup code here, to run once:
 Serial.begin(57600);
 Serial.println("Hello!");

 ScalePot::prtDiag = prtDiag;
 MotorControl::prtDiag = prtDiag;
 delay(2000);

}

void loop()
{
 // put your main code here, to run repeatedly:
 mtrs_Spd = potA.readPot();
 if(prtDiag) Serial.print(" \t");
 mots_Trn = potB.readPot();
 if(prtDiag) Serial.println();
 //=================== Motor A =========================
 //Read and scale the pot then issue motor cmds.  Direction & speed.
 mtrA.cmdMotor(mtrs_Spd * (1.0 + mots_Trn) + mtrs_Cor);
    if(prtDiag) Serial.print("  \t||\t  ");

 //=================== Motor B =========================
 //Read and scale the pot then issue motor cmds.  Direction & speed.
 mtrB.cmdMotor(mtrs_Spd * (1.0 - mots_Trn) - mtrs_Cor);
    if(prtDiag) Serial.println();

 delay(1000);
}
