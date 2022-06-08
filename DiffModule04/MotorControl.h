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
 * @param _inDB   deadband for anaIn signal (0 - 1.0), return 0.
 * @param _sigMin - min motor signal returned if not in DB.
 * 
 */
class MotorControl
{
  public:
    MotorControl(int, int, int, double, double);
    void cmdMotor(double);
    static bool prtDiag;
  private:
    int fwdPin;
    int revPin;
    int sigPin;
    double inDB;
    double minSig;
};

#endif
