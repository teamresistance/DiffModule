#include "MotorControl.h"

/**
 * @brief Control a motor.
 * 
 * @param fwdPin assigned pin for forward cmd
 * @param revPin assigned pin for reverse cmd
 * @param sigPin assigned pin for speed signal cmd
 */
MotorControl::MotorControl(int _fwdPin, int _revPin, int _sigPin, double _inDB, double _minSig){
    fwdPin = _fwdPin;
    revPin = _revPin;
    sigPin = _sigPin;
	inDB = _inDB;
	minSig = _minSig;

	pinMode(fwdPin, OUTPUT); // Define DIO type
	pinMode(revPin, OUTPUT);
	pinMode(sigPin, OUTPUT);

}

bool MotorControl::prtDiag = false;	 // Print diagnostics

/**
 * @brief Sets direction and speed of motor.
 * 
 * @param mtrX_Sig signed speed signal (+/-255) to be issued.
 */
void MotorControl::cmdMotor(double cmdIn){
	// Condition cmdIn
	if(abs(cmdIn) < inDB)  cmdIn = 0;		//Positive DB

  	// Controlling spin direction of motors:
	if (cmdIn != 0.0)
	{
		bool tmpB = cmdIn > 0;
		digitalWrite(fwdPin, tmpB);
		digitalWrite(revPin, !tmpB);
	}
	else
	{ // Within DB
		digitalWrite(fwdPin, LOW);
		digitalWrite(revPin, LOW);
	}

	// Controlling speed (0 = off and 255 = max speed):
	analogWrite(sigPin, abs(cmdIn)); // ENA pin

	if(prtDiag){
		Serial.print("    Fwd: ");
		Serial.print(digitalRead(fwdPin));
		Serial.print(" / Rev: ");
		Serial.print(digitalRead(revPin));
		Serial.print(" / Sig: ");
		Serial.print(cmdIn);
	}
}
