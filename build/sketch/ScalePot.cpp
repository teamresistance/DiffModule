#line 1 "c:\\Users\\Hofmjc\\Documents\\_FRC\\DiffModule\\DiffModule04\\ScalePot.cpp"
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
ScalePot::ScalePot(int _potPin)
{
	potPin = _potPin;
}

bool ScalePot::prtDiag = false;	 // Print diagnostics

/**
 * @brief Read the pot value, apply a DB then scale min speed to max, 255. 
 * 
 * @return int Sign scaled signal.
 */
double ScalePot::readPot() {
	//=================== Motor X =========================
	double pot_Sig = (analogRead(potPin)/512.0)  - 1.0;	// rescale from 0 - 1023 to -1.0 - +1.0
	pot_Sig = constrain(pot_Sig, -1.0, 1.0);
	if(prtDiag){
		Serial.print("Pin:"); Serial.print(potPin); Serial.print(" = "); 
		Serial.print(analogRead(potPin)); Serial.print(" => "); Serial.print(pot_Sig);	//Troubleshooting
	}
	return pot_Sig;
}

