#include <ArduinoJson.h>
#include <HCSR04.h>

byte triggerPin = 2;
byte echoCount = 2;
byte* echoPins = new byte[echoCount] { 5, 6 };

int D1;
int D2;
int B;


String cmd = "";

void setup() {
  Serial.begin(115200);
  HCSR04.begin(triggerPin, echoPins, echoCount);
}


void loop() {

  checkObstacleAvoidance();
  StaticJsonDocument<200> payload;
  payload["D1"] = D1;
  payload["D2"] = D2;
  payload["B"] = B;
  serializeJson(payload, Serial);
  Serial.println();
  delay(700);
}
void checkObstacleAvoidance() {
  double* distances = HCSR04.measureDistanceCm();
  delay(100);
  B = 2;
  D1 = distances[0];
  D2 = distances[1];

}
