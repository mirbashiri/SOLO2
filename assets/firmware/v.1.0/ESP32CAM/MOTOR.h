#include "CytronMotorDriver.h"
CytronMD motor1(PWM_PWM, 12, 13);
CytronMD motor2(PWM_PWM, 15, 14);

#define LED 4

class MOTOR
{
private:

public:
    void init()
    {
        pinMode(LED, OUTPUT);
    }
    void Backward()
    {
        if (myRobot.gear == 1)
        {
            motor1.setSpeed(110);
            motor2.setSpeed(110);
        }
        else if (myRobot.gear == 2)
        {
            motor1.setSpeed(160);
            motor2.setSpeed(160);
        }
        else if (myRobot.gear == 3)
        {
            motor1.setSpeed(200);
            motor2.setSpeed(200);
        }
        else if (myRobot.gear == 4)
        {
            motor1.setSpeed(250);
            motor2.setSpeed(250);
        }
    }
    void Right()
    {
        if (myRobot.gear == 1 || myRobot.gear == 2)
        {
            motor1.setSpeed(-150);
            motor2.setSpeed(150);
        }
        else if (myRobot.gear == 3 || myRobot.gear == 4)
        {
            motor1.setSpeed(-210);
            motor2.setSpeed(210);
        }
    }
    void Left()
    {
        if (myRobot.gear == 1 || myRobot.gear == 2)
        {
            motor1.setSpeed(150);
            motor2.setSpeed(-150);
        }
        else if (myRobot.gear == 3 || myRobot.gear == 4)
        {
            motor1.setSpeed(210);
            motor2.setSpeed(-210);
        }
    }
    void Forward()
    {
        if (myRobot.gear == 1)
        {
            motor1.setSpeed(-110);
            motor2.setSpeed(-110);
        }
        else if (myRobot.gear == 2)
        {
            motor1.setSpeed(-160);
            motor2.setSpeed(-160);
        }
        else if (myRobot.gear == 3)
        {
            motor1.setSpeed(-200);
            motor2.setSpeed(-200);
        }
        else if (myRobot.gear == 4)
        {
            motor1.setSpeed(-250);
            motor2.setSpeed(-250);
        }
    }
    void Stop()
    {
        motor1.setSpeed(0);
        motor2.setSpeed(0);
    }
};
MOTOR robotMotors;
