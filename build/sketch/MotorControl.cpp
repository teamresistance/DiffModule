#line 1 "c:\\Users\\Hofmjc\\Documents\\_FRC\\DiffModule\\DiffModule04\\MotorControl.cpp"
#include "MotorControl.h"

/**
 * @brief Control a motor.
 * 
 * @param _fwdPin assigned pin for forward cmd
 * @param _revPin assigned pin for reverse cmd
 * @param _sigPin assigned pin for speed signal cmd
 * @param _inDB   deadband for anaIn signal (0 - 1.0), return 0.
 * @param _sigMin min motor signal returned if not in DB.
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
 * @param cmdIn signed speed signal (+/-1.0) to be issued.
 */
void MotorControl::cmdMotor(double cmdIn){
  	// Controlling spin direction of motors:
	if (abs(cmdIn) >= inDB)
	{	// ---- G.E. DB ----
		// double tmpCmd = (cmdIn > 0) - (cmdIn < 0);	//Equals +1, 0, -1
		cmdIn = minSig + ((abs(cmdIn) - inDB) / (1.0 - inDB) * (1.0 - minSig));
		bool tmpB = cmdIn > 0;
		digitalWrite(fwdPin, tmpB);
		digitalWrite(revPin, !tmpB);
	}
	else
	{ // ---- Within DB ----
		cmdIn = 0.0;
		digitalWrite(fwdPin, LOW);
		digitalWrite(revPin, LOW);
	}

	// Controlling speed (0 = off and 255 = max speed):
	analogWrite(sigPin, abs(cmdIn * 255)); // ENA pin

	if(prtDiag){
		Serial.print("    Fwd: ");
		Serial.print(digitalRead(fwdPin));
		Serial.print(" / Rev: ");
		Serial.print(digitalRead(revPin));
		Serial.print(" / Sig: ");
		Serial.print(cmdIn);
		Serial.print(" / Out: ");
		Serial.print(int(cmdIn * 255));
	}
}
