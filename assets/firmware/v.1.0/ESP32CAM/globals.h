#include <WiFi.h>
#include "esp_http_server.h"
#include "esp_timer.h"
#include "esp_camera.h"
#include "img_converters.h"
#include "Arduino.h"
#include "fb_gfx.h"
#include "soc/soc.h"          // disable brownout problems
#include "soc/rtc_cntl_reg.h" // disable brownout problems

#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

#define PART_BOUNDARY "123456789000000000000987654321"

static const char *_STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
static const char *_STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
static const char *_STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";

struct Robot
{
  int speedMotor_1 = 0;
  int speedMotor_2 = 0;
  int timeCTRL_Motor_1 = 0;
  int timeCTRL_Motor_2 = 0;
  bool frontLED_ON = false;
  float distanceRight;
  float distanceLeft;
  int batteryLVL;
  int gear = 1;
} myRobot;

String payload="";
String readString;
//IPAddress local_IP(192, 168, 0, 110); //1
IPAddress local_IP(192, 168, 0, 10);//2
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 0, 0);
