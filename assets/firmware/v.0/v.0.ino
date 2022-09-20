#include "ultraDistance.h"
#include "ESP32NET.h"
#include "CytronMotorDriver.h"

CytronMD motor1(PWM_PWM, 12, 13);
CytronMD motor2(PWM_PWM, 15, 14);

#define frontLEDPin 4
void setup()
{
    //Serial.begin(115200);
    pinMode(frontLEDPin,OUTPUT);
        robotDistance.init();
    myNETWORK.WiFi_FAC_ON();
    myAPI.WebServer_init();
    myAPI.softAP_ON();
    
}
void loop()
{
  if(myRobot.frontLED_ON){
    digitalWrite(frontLEDPin,HIGH);
  }
  else{
    digitalWrite(frontLEDPin,LOW);
  }
    myAPI.loop();
    if (myRobot.timeCTRL_Motor_2 > 1)
    {
        motor2.setSpeed(myRobot.speedMotor_2);
        myRobot.timeCTRL_Motor_2--;
    }
    else
    {
        motor2.setSpeed(0);
        myRobot.timeCTRL_Motor_2 = 0;
    }

    if (myRobot.timeCTRL_Motor_1 > 1)
    {
        motor1.setSpeed(myRobot.speedMotor_1);
        myRobot.timeCTRL_Motor_1--;
    }
    else
    {
        motor1.setSpeed(0);
        myRobot.timeCTRL_Motor_1 = 0;
    }
#ifdef DEBUG
    //Serial.println("STA:" + myDevice.IP_STA);
    //Serial.println("AP:" + myDevice.IP_AP);
#endif
}
