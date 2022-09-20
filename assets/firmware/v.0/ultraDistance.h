#include "globals.h"
#include <HCSR04.h>

byte triggerPin = 2;
byte echoCount = 2;
byte *echoPins = new byte[echoCount]{3, 1}; // GPIO3 = RX GPIO1=TX
class ultraDistance
{

private:
public:
  void init()
  {
    HCSR04.begin(triggerPin, echoPins, echoCount);
  }
  void getDistance()
  {
    double *distances = HCSR04.measureDistanceCm();
    myRobot.distanceRight = distances[0];
    myRobot.distanceLeft = distances[1];
  }
};
ultraDistance robotDistance;
