#include "SwerveCalc.h"

/**
 * @brief Take 2 pot inputs, speed & rotation (+/- 1.0), and calculate 2 commands to send to motors (+/- 1.0).
 */
SwerveCalc::SwerveCalc()
{}

bool SwerveCalc::prtDiag = false;	 // Print diagnostics

/**
 * @brief Take 2 pot inputs, speed & rotation (+/- 1.0), and calculate 2 commands to send to motors (+/- 1.0).
 * 
 * @param _potInSpd potentiometer for Speed (+/- 1.0)
 * @param _potInRot potentiometer for Rotation (+/- 1.0)
 * @return Signed signal (+/- 1.0)
 */
double * SwerveCalc::update(double potInSpd, double potInRot)
{
	if(potInRot > 0.0){
		mtrCmd[0] = potInSpd;
		mtrCmd[1] = mtrCmd[0] * (1.0 - mtrCmd[0]);
	}else{
		mtrCmd[1] = potInSpd;
		mtrCmd[0] = mtrCmd[1] * (1.0 - mtrCmd[0]);
	}

	if(prtDiag){
		Serial.print("Pot Spd:"); Serial.print(potInSpd);
		Serial.print("\tPot Rot:"); Serial.print(potInRot);
		Serial.println();
		Serial.print("Mtr A cmd: "); Serial.print(mtrCmd[0]);
		Serial.print("\tMtr B cmd: "); Serial.print(mtrCmd[1]);
	}
	return mtrCmd;
}

