#line 1 "c:\\Users\\Hofmjc\\Documents\\_FRC\\DiffModule\\DiffModule05\\SwerveCalc.h"
#ifndef SwerveCalc_h
#define SwerveCalc_h

#include "Arduino.h"

/**
 * @brief Take 2 pot inputs, speed & rotation (+/- 1.0), and calculate 2 commands to send to motors (+/- 1.0).
 */
class SwerveCalc
{
  public:
    SwerveCalc();
    double * update(double potInSpd, double potInRot);
    static bool prtDiag;
  private:
    double spdCmd; //Pot deaband, return 0.0,  Scale DB - 1.0 to 0.0 - 1.0.
    double rotCmd; //Pot deaband, return 0.0,  Scale DB - 1.0 to 0.0 - 1.0.
    double mtrCmd[2];  //[0] = A mtr, [1] = mtr B
};

#endif
