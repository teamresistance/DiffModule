#include <Arduino.h>
#line 1 "c:\\Users\\Hofmjc\\Documents\\_FRC\\DiffModule\\DiffModule01\\DiffModule01.ino"
/*
 * Author: Jim Hofmann
 * History
 * 2022/06/03 Rev: 0.1 - Test motors and interaction using pots.
 * 
 * This is to test the differential swerve module motors and interaction.  
 * It is 3d printed and mechanically not tight but good for demo purposes.  
 * I am running 2 TT motors (3 - 6 VDC) thru a L298N motor(s) controller.  PS is a buck convertor set at 7.2 vdc.
 * With 7.2 volts applied to the controller the motors need 3.2 VDC to move.  This is 125 pwm signal and max's at 255.
 * To reverse the motor requires reversing the signals at In1 & In2, Fwd & Rev.
 * I am using 2 pots to control the motors.  The pot read 0 - 1023 counts.  I scale this -511 to +512.
 * I then apply 10% deadband +/-50 counts around the zero reading.  I then scale this to a pwm signal from minimum
 * pwm, 25, to move the motor, 3 vdc to 255, 6 vdc.
*/

const uint8_t kMtrA_FwdPin = 4;   //Motor A pin assignments
const uint8_t mtrA_RevPin = 5;
const uint8_t mtrA_SpdPin = 6;
const uint8_t mtrA_PotPin = A0;

const uint8_t mtrB_FwdPin = 8;   //Motor B pin assignments
const uint8_t mtrB_RevPin = 9;
const uint8_t mtrB_SpdPin = 10;
const uint8_t mtrB_PotPin = A1;

int16_t mtrA_Sig = 0;         //Cmd signals
int16_t mtrB_Sig = 0;

#line 29 "c:\\Users\\Hofmjc\\Documents\\_FRC\\DiffModule\\DiffModule01\\DiffModule01.ino"
void setup();
#line 45 "c:\\Users\\Hofmjc\\Documents\\_FRC\\DiffModule\\DiffModule01\\DiffModule01.ino"
void loop();
#line 29 "c:\\Users\\Hofmjc\\Documents\\_FRC\\DiffModule\\DiffModule01\\DiffModule01.ino"
void setup()
{
	// put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello!");
  delay(2000);
 
	pinMode(kMtrA_FwdPin, OUTPUT);  //Define DIO type
	pinMode(mtrA_RevPin, OUTPUT);
	pinMode(mtrA_SpdPin, OUTPUT);

	pinMode(mtrB_FwdPin, OUTPUT);
	pinMode(mtrB_RevPin, OUTPUT);
	pinMode(mtrB_SpdPin, OUTPUT);
}

void loop()
{
	// put your main code here, to run repeatedly:

  //=================== Motor A =========================
  mtrA_Sig = analogRead(mtrA_PotPin);  //Read Pot for motor A
  Serial.print("PotA - "); Serial.print(mtrA_Sig);

  mtrA_Sig -= 511;                  //and rescale -511 to 512
  Serial.print(" => "); Serial.print(mtrA_Sig);

	// Controlling spin direction of motors:
	if (mtrA_Sig < -50){              //Negative DB
    mtrA_Sig = map(mtrA_Sig, -511, -50, 255, 125);    //Rescale from DB => min torque
		digitalWrite(kMtrA_FwdPin, LOW);
		digitalWrite(mtrA_RevPin, HIGH);
	}else if (mtrA_Sig > 50){        //Positive DB
    mtrA_Sig = map(mtrA_Sig, 50, 512, 125, 255);     //Rescale from DB => min torque
		digitalWrite(kMtrA_FwdPin, HIGH);
		digitalWrite(mtrA_RevPin, LOW);
	}else{                                            //Within DB
    mtrA_Sig = 0;
		digitalWrite(kMtrA_FwdPin, LOW);
		digitalWrite(mtrA_RevPin, LOW);
	}
  // Controlling speed (0 = off and 255 = max speed):
  analogWrite(mtrA_SpdPin, mtrA_Sig); // ENA pin

  Serial.print("    ");
  Serial.print("A Fwd - "); Serial.print(digitalRead(kMtrA_FwdPin)); Serial.print(" / Rev - "); Serial.print(digitalRead(mtrA_RevPin));
  Serial.print(" / Sig - "); Serial.print(mtrA_Sig);
	

  //=================== Motor B =========================
    mtrB_Sig = analogRead(mtrB_PotPin);  //Read Pot for motor B
    Serial.print("    ||    ");
    Serial.print("PotB - "); Serial.print(mtrB_Sig);
  
    mtrB_Sig -= 511;                  //and rescale -511 to 512
    Serial.print(" => "); Serial.print(mtrB_Sig);


	// Controlling spin direction of motors:
	if (mtrB_Sig < -50){              //Negative DB
    mtrB_Sig = map(mtrB_Sig, -511, -50, 255, 125);    //Rescale from DB => min torque
		digitalWrite(mtrB_FwdPin, LOW);
		digitalWrite(mtrB_RevPin, HIGH);
	}else if (mtrB_Sig > 50){        //Positive DB
    mtrB_Sig = map(mtrB_Sig, 50, 512, 125, 255);     //Rescale from DB => min torque
		digitalWrite(mtrB_FwdPin, HIGH);
		digitalWrite(mtrB_RevPin, LOW);
	}else{                                            //Within DB
    mtrB_Sig = 0;
		digitalWrite(mtrB_FwdPin, LOW);
		digitalWrite(mtrB_RevPin, LOW);
	}
	// Controlling speed (0 = off and 255 = max speed):
	analogWrite(mtrB_SpdPin, mtrB_Sig); // ENA pin

  Serial.print("    ");
  Serial.print("B Fwd - "); Serial.print(digitalRead(mtrB_FwdPin)); Serial.print(" / Rev - "); Serial.print(digitalRead(mtrB_RevPin));
  Serial.print(" / Sig - "); Serial.println(mtrB_Sig);

  delay(1000);
}

