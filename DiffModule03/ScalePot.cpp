#include "ScalePot.h"

/**
 * @brief Read potentiometer, apply +/-DB around center (512) 
 * and scale from min to rotate motor to 255.
 * 
 * @param _potPin analog pin (A0 - A5) to read 
 * @param _inDB   deadband for anaIn signal (0 - 512), return 0.
 * @param _sigMin min motor signal returned if not in DB
 * @return int - signed signal to send motor.
 */
ScalePot::ScalePot(int _potPin, int _inDB = 50, int _sigMin = 125)
{
	potPin = _potPin;
	inDB = _inDB;
	minSig = _sigMin;

}

/**
 * @brief Read the pot value, apply a DB then scale min speed to max, 255. 
 * 
 * @return int Sign scaled signal.
 */
int ScalePot::readPot() {
	//=================== Motor X =========================
	int mtrX_Sig = analogRead(potPin) - 511; // and rescale -511 to 512
	if(prtDiag){
		Serial.print("Pins:"); Serial.print(potPin); Serial.print(" = "); 
		Serial.print(analogRead(potPin)); Serial.print(" => "); Serial.print(mtrX_Sig);	//Troubleshooting
	}

	// Rescale from DB => min torque
	if(mtrX_Sig < -inDB) return map(mtrX_Sig, -511, -inDB, -255, -minSig); //Negative DB
	if(mtrX_Sig > inDB)  return map(mtrX_Sig, inDB, 512, minSig, 255);		 //Positive DB
	return 0;	//Within DB
}

bool ScalePot::prtDiag = false;	 // Print diagnostics

/**
 * @brief Enable/Disable printing diagnostics.
 * 
 * @param _prtDiag 
 */
void ScalePot::setPrtDiag(bool _prtDiag){
	prtDiag = _prtDiag;
}
