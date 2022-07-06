#ifndef ScalePot_h
#define ScalePot_h

#include "Arduino.h"

/**
 * @brief Read potentiometer +/-1.0 (0 - 1023), apply +/-DB 0.10 (51) around center 0.0 (512) 
 * and scale DB - 1.0 to 0.0 - 1.0.
 * 
 * @param _potPin assigned analog pin (A0 - A5) for potentiometer read
 * @param _inDB   deadband for anaIn signal (0 - 1.0), return 0.  Default 0.10.
 */
class ScalePot
{
  public:
    ScalePot(int _potPin, double _potDB = 0.10);
    double readPot();
    static bool prtDiag;
  private:
    int potPin;   //Potentiometer pin
    double potDB; //Pot deaband, return 0.0,  Scale DB - 1.0 to 0.0 - 1.0.
};

#endif
