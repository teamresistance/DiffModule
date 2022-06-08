#include "MotorControl.h"

/**
 * @brief Control a motor.
 * 
 * @param fwdPin assigned pin for forward cmd
 * @param revPin assigned pin for reverse cmd
 * @param sigPin assigned pin for speed signal cmd
 */
MotorControl::MotorControl(int _fwdPin, int _revPin, int _sigPin){
    fwdPin = _fwdPin;
    revPin = _revPin;
    sigPin = _sigPin;

	pinMode(fwdPin, OUTPUT); // Define DIO type
	pinMode(revPin, OUTPUT);
	pinMode(sigPin, OUTPUT);

}

/**
 * @brief Sets direction and speed of motor.
 * 
 * @param mtrX_Sig signed speed signal (+/-255) to be issued.
 */
void MotorControl::cmdMotor(int mtrX_Sig){
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

	if(prtDiag){
		Serial.print("    Fwd: ");
		Serial.print(digitalRead(fwdPin));
		Serial.print(" / Rev: ");
		Serial.print(digitalRead(revPin));
		Serial.print(" / Sig: ");
		Serial.print(mtrX_Sig);
	}
}
bool MotorControl::prtDiag = false;	 // Print diagnostics

/**
 * @brief Enable/Disable printing diagnostics.
 * 
 * @param _prtDiag 
 */
void MotorControl::setPrtDiag(bool _prtDiag){
	prtDiag = _prtDiag;
}

