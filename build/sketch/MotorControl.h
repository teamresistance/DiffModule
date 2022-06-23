#line 1 "c:\\Users\\Hofmjc\\Documents\\_FRC\\DiffModule\\DiffModule04\\MotorControl.h"
#ifndef MotorControl_h
#define MotorControl_h

#include "Arduino.h"

#define OFF 0
#define FWD 1
#define Rev -1
/**
 * @brief Control a motor.
 * 
 * @param _fwdPin assigned pin for forward cmd
 * @param _revPin assigned pin for reverse cmd
 * @param _sigPin assigned pin for speed signal cmd
 * @param _sigMin - min motor signal returned if not in DB.
 * 
 */
class MotorControl
{
  public:
    MotorControl(int, int, int, double);
    void cmdMotor(double);
    static bool prtDiag;
  private:
    int fwdPin;
    int revPin;
    int sigPin;
    double minSig;
};

#endif
