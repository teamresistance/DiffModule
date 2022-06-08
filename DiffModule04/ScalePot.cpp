#include "ScalePot.h"

/**
 * @brief Read potentiometer, apply +/-DB around center (0.0) 
 * and scale from min to rotate motor to 1.0.
 * 
 * @param _potPin analog pin (A0 - A5) to read 
 * @param _inDB   deadband for anaIn signal (0.0 - 1.0), returns 0.
 * @param _sigMin min motor signal returned if not in DB (0.0 - 1.0)
 * @return int - signed signal to send motor (+/- 1.0)
 */
ScalePot::ScalePot(int _potPin, double _inDB, double _sigMin)
{
	potPin = _potPin;
	inDB = _inDB;
	minSig = _sigMin;
}

bool ScalePot::prtDiag = false;	 // Print diagnostics

/**
 * @brief Read the pot value, apply a DB then scale min speed to max, 255. 
 * 
 * @return int Sign scaled signal.
 */
int ScalePot::readPot() {
	//=================== Motor X =========================
	double mtrX_Sig = (analogRead(potPin)/512.0)  - 1.0;	// rescale from 0 - 1023 to -1.0 - +1.0
	mtrX_Sig = constrain(mtrX_Sig, -1.0, 1.0);
	if(prtDiag){
		Serial.print("Pins:"); Serial.print(potPin); Serial.print(" = "); 
		Serial.print(analogRead(potPin)); Serial.print(" => "); Serial.print(mtrX_Sig);	//Troubleshooting
	}

	// Rescale from DB => min torque
	if(abs(mtrX_Sig) > inDB)  return mtrX_Sig;		//Positive DB
	return 0;	//Within DB
}

