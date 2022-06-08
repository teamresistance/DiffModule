#ifndef MotorControl_h
#define MotorControl_h

#include "Arduino.h"

#define OFF 0
#define FWD 1
#define Rev -1
/**
 * @brief Control a motor.
 * 
 * @param fwdPin assigned pin for forward cmd
 * @param revPin assigned pin for reverse cmd
 * @param sigPin assigned pin for speed signal cmd
 * 
 */
class MotorControl
{
  public:
    MotorControl(int, int, int);
    void cmdMotor(int);
    static void setPrtDiag(bool);
  private:
    int fwdPin;
    int revPin;
    int sigPin;
    static bool prtDiag;
};

#endif
