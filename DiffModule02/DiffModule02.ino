/*
 * Author: Jim Hofmann
 * History
 * 2022/06/03 Rev: 0.1 - Test motors and interaction using pots.
 * 2022/06/03 Rev: 0.2 - Start isolating code modules
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

const uint8_t kMtrA_FwdPin = 4; // Motor A pin assignments
const uint8_t mtrA_RevPin = 5;
const uint8_t mtrA_SpdPin = 6;
const uint8_t mtrA_PotPin = A0;

const uint8_t mtrB_FwdPin = 8; // Motor B pin assignments
const uint8_t mtrB_RevPin = 9;
const uint8_t mtrB_SpdPin = 10;
const uint8_t mtrB_PotPin = A1;

int16_t mtrA_Sig = 0; // Cmd signals
int16_t mtrB_Sig = 0;

bool tmpB = false;

int readPot(int potPin, int inDB = 50, int sigMin = 125);         //Define function to read potentiometer and scale.
void cmdMotor(int mtrX_Sig, int fwdPin, int revPin, int sigPin);  //Define function to issue motor command(s).

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(9600);
	Serial.println("Hello!");
	delay(2000);

	pinMode(kMtrA_FwdPin, OUTPUT); // Define DIO type
	pinMode(mtrA_RevPin, OUTPUT);
	pinMode(mtrA_SpdPin, OUTPUT);

	pinMode(mtrB_FwdPin, OUTPUT);
	pinMode(mtrB_RevPin, OUTPUT);
	pinMode(mtrB_SpdPin, OUTPUT);
}

void loop()
{
	// put your main code here, to run repeatedly:

	//=================== Motor A =========================
	mtrA_Sig = readPot(mtrA_PotPin, 50, 125);   //Read and scale the pot
	cmdMotor(mtrA_Sig, kMtrA_FwdPin, mtrA_RevPin, mtrA_SpdPin); // Controlling spin direction of motors
    Serial.print("  ||  ");

	//=================== Motor B =========================
	mtrB_Sig = readPot(mtrB_PotPin);   //Read and scale the pot
	cmdMotor(mtrB_Sig, mtrB_FwdPin, mtrB_RevPin, mtrB_SpdPin); // Controlling spin direction of motors
    Serial.println();
  
	delay(1000);
}

/**
 * @brief Read potentiometer, apply +/-DB around center (512) 
 * and scale from min to rotate motor to 255.
 * 
 * @param potPin - analog pin (A0 - A5) to read 
 * @param inDB   - deadband for anaIn signal (0 - 512), return 0.
 * @param sigMin - min motor signal returned if not in DB
 * @return int - signed signal to send motor.
 */
int readPot(int potPin, int inDB = 50, int sigMin = 125) {
	//=================== Motor X =========================
	int mtrX_Sig = analogRead(potPin) - 511; // and rescale -511 to 512
	Serial.print("Pin:"); Serial.print(potPin); Serial.print(" = "); 
	Serial.print(analogRead(mtrA_PotPin)); Serial.print(" => "); Serial.print(mtrX_Sig);	//Troubleshooting

	// Rescale from DB => min torque
	if(mtrX_Sig < -inDB) return map(mtrX_Sig, -511, -inDB, -255, -sigMin); //Negative DB
	if(mtrX_Sig > inDB)  return map(mtrX_Sig, inDB, 512, sigMin, 255);		 //Positive DB
	return 0;	//Within DB
}

/**
 * @brief Control a motor.
 * 
 * @param mtrX_Sig - signed speed signal
 * @param fwdPin - assigned pin for forward cmd
 * @param revPin - assigned pin for reverse cmd
 * @param sigPin - assigned pin for speed signal cmd
 */
void cmdMotor(int mtrX_Sig, int fwdPin, int revPin, int sigPin){
	//=================== Motor X =========================
  	// Controlling spin direction of motors:
	if (mtrX_Sig != 0)
	{
		bool tmpB = mtrX_Sig > 0;
		digitalWrite(fwdPin, tmpB);
		digitalWrite(revPin, !tmpB);
	}
	else
	{ // Within DB
		digitalWrite(fwdPin, LOW);
		digitalWrite(revPin, LOW);
	}

	// Controlling speed (0 = off and 255 = max speed):
	analogWrite(sigPin, abs(mtrX_Sig)); // ENA pin

	Serial.print("    Fwd - ");
	Serial.print(digitalRead(fwdPin));
	Serial.print(" / Rev - ");
	Serial.print(digitalRead(revPin));
	Serial.print(" / Sig - ");
	Serial.print(mtrX_Sig);
}
