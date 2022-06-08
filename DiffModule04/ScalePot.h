#ifndef ScalePot_h
#define ScalePot_h

#include "Arduino.h"

/**
 * @brief Read potentiometer, apply +/-DB around center (512) 
 * and scale from min to rotate motor to 255.
 * 
 * @param _potPin assigned analog pin (A0 - A5) for potentiometer read
 * @param _inDB   deadband for anaIn signal (0 - 512), return 0.
 * @param _sigPin sigMin - min motor signal returned if not in DB.
 */
class ScalePot
{
  public:
    ScalePot(int _potPin, double _inDB, double _minSig);
    int readPot();
    static bool prtDiag;
  private:
    int potPin;
    double inDB;
    double minSig;
};

#endif
