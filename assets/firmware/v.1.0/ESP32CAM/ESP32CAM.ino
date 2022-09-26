#include <ArduinoJson.h>

#define reqPin 2

#include "globals.h""
#include "MOTOR.h"
#include "ESP32CAM.h"
//#define RXD2 16

int firstLoad=1;
int cntSensors=0;
const char *ssid = "zad-solutions2.4G";
const char *password = "SunnyDay";

void setup()
{
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // disable brownout detector
  Serial.begin(115200);
  //Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  //mySerial.begin(115200, SERIAL_8N1, TXD2, RXD2); //<- set your TX/RX Pin
  pinMode(reqPin, OUTPUT);


  Serial.setDebugOutput(true);
  //Serial2.setDebugOutput(true);

  //robotDistance.init();
  robotCamera.init();
  robotMotors.init();
  // Wi-Fi connection
    if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());

}

void loop()
{
  if (firstLoad) {
    robotCamera.startCameraServer();
    firstLoad = 0;
  }

    if (Serial.available() > 0) {
      payload = Serial.readStringUntil('\n');
      //Serial.println(payload);
      robotCamera.decodePayload(payload);
    }
}
