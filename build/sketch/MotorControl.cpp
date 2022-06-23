#line 1 "c:\\Users\\Hofmjc\\Documents\\_FRC\\DiffModule\\DiffModule04\\MotorControl.cpp"
#include "MotorControl.h"

/**
 * @brief Control a motor.
 * 
 * @param _fwdPin assigned pin for forward cmd
 * @param _revPin assigned pin for reverse cmd
 * @param _sigPin assigned pin for speed signal cmd
 * @param _sigMin min motor signal returned if not in DB.
 */
MotorControl::MotorControl(int _fwdPin, int _revPin, int _sigPin, double _minSig){
    fwdPin = _fwdPin;
    revPin = _revPin;
    sigPin = _sigPin;
	minSig = _minSig;

	pinMode(fwdPin, OUTPUT); 	// Define DIO type
	pinMode(revPin, OUTPUT);
	pinMode(sigPin, OUTPUT);	//PWM

}

bool MotorControl::prtDiag = false;	 // Print diagnostics

/**
 * @brief Sets direction and speed of motor.
 * 
 * @param cmdIn signed speed signal (+/-1.0) to be issued.
 */
void MotorControl::cmdMotor(double cmdIn){
  	// Controlling spin direction of motors:
	if (cmdIn != 0.0)
	{	// ---- NEQ. 0.0 ----
		bool tmpB = cmdIn > 0;
		digitalWrite(fwdPin, tmpB);
		digitalWrite(revPin, !tmpB);
		cmdIn = minSig + (abs(cmdIn) * (1.0 - minSig));
	}
	else
	{ // ---- EQ. 0.0 ----
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
