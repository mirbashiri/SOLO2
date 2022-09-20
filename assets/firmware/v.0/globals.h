#define DEBUG
//----------------------------------------------------------------
struct device
{
  bool EULA = false;
  const String Name = "xxxx";
  const double Firmware = 1.15;
  double LFWU = 0.00; // Latest Firmware update
  const String OTA = "xxx";
  const String SPN = "xxx";
  String AP_BASE = "ROBOT";
  String AP_CHECK = "";
  char AP_SSID[10] = "";
  String MAC = "";
  String IP_STA = "";
  String IP_AP = "";
  String Date = "";
  String Time = "";
  const char *FACTORY_SSID = "xxx";
  const char *FACTORY_PASSWORD = "xxx";
  char *STA_SSID;
  char *STA_PASS;
  bool firmwareStat = false; // New Available=true
} myDevice;

struct Robot
{
  int speedMotor_1 = 0;
  int speedMotor_2 = 0;
  int timeCTRL_Motor_1 = 0;
  int timeCTRL_Motor_2 = 0;
  bool frontLED_ON = false;
  float distanceRight;
  float distanceLeft;

} myRobot;

struct ERRORS
{
  bool ToF_init = false;
  bool AP_init = false;
} myErrors;
struct NETMODE
{
  bool STA_FAC_ON = false; // WiFi Company
  bool STA_USR_ON = false; // User
  bool AP_ON = false;      // AP
  bool NTP_ON = false;     // NTP stats: false= No Time
} myNET_MODE;

int wifiMode = 0;     // 0:Disconnect 1:WiFi 2:AP 3:Update
String myDate = "";
String myTime = "";

String t_ssid;
String t_pass;
