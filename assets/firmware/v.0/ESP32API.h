#include <WiFiAP.h>
#include <WebServer.h>
#include <ArduinoJson.h>

WebServer server(80);

const char *AP_PASSWORD = "1234567890";
IPAddress AP_LOCAL_IP(192, 168, 1, 160);
IPAddress AP_GATEWAY_IP(192, 168, 1, 4);
IPAddress AP_NETWORK_MASK(255, 255, 255, 0);
uint8_t MAC_array[6];
char MAC_char[18];
class ESP32API
{
private:
    static void softAP_MAC_INFO()
    {
        WiFi.mode(WIFI_AP);
        String checkDgit = "";
        String AP_SSID_Str = "";
        String checkDgit_Str = "";
        // WiFi.macAddress(MAC_array);
        WiFi.softAPmacAddress(MAC_array);
        for (int i = 0; i < sizeof(MAC_array); ++i)
        {
            sprintf(MAC_char, "%s%02x-", MAC_char, MAC_array[i]);
        }
        myDevice.MAC = String(MAC_char).substring(0, String(MAC_char).length() - 1);
        checkDgit = myDevice.MAC.substring(15, 17);
        checkDgit.toUpperCase();
        myDevice.AP_CHECK = checkDgit;
        AP_SSID_Str = String(myDevice.AP_BASE + myDevice.AP_CHECK);
        AP_SSID_Str.toCharArray(myDevice.AP_SSID, 10); // APmode SSID

#ifdef DEBUG
//        Serial.println(myDevice.MAC);
//        Serial.println(myDevice.AP_BASE);
//        Serial.println(myDevice.AP_CHECK);
#endif
    }

public:
    void WebServer_init()
    {
        server.on("/", handshake); // CONNECTION HEALTH CHECK
        server.on("/cmd", cmd);    // COMMAND CHANNEL
        server.on("/getDistance", getDistance); // SAVE WIFI CRE
        server.begin();
    }
    void loop()
    {
        server.handleClient();
    }
    static void softAP_ON()
    {
        softAP_MAC_INFO();
        //Serial.println(myDevice.AP_SSID);
        WiFi.softAP(myDevice.AP_SSID, AP_PASSWORD, 1, 0, 4, false);
        // WiFi.softAP(AP_SSID, AP_PASSWORD);
        if (!WiFi.softAPConfig(AP_LOCAL_IP, AP_GATEWAY_IP, AP_NETWORK_MASK))
        {
            Serial.println("AP Config Failed");
            myNET_MODE.AP_ON = false;
            return;
        }
        IPAddress IP = WiFi.softAPIP();
        myDevice.IP_AP = IpAddress2String(WiFi.softAPIP());
        myNET_MODE.AP_ON = true;
        //Serial.println(myDevice.IP_AP);
    }
    static void handshake()
    {
        Serial.println("handshake");
        server.sendHeader("Access-Control-Allow-Origin", "*");
        server.send(200, "DONE");
    }
    static bool cmd()
    {
        String data = server.arg("plain");
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, data);
        myRobot.speedMotor_1 = doc["motorSpeed1"];
        myRobot.speedMotor_2 = doc["motorSpeed2"];
        myRobot.timeCTRL_Motor_1 = doc["motorCTRL1"];
        myRobot.timeCTRL_Motor_2 = doc["motorCTRL2"];
        myRobot.frontLED_ON = doc["frontLED_ON"];
        Serial.println("M1-" + String(myRobot.speedMotor_1) + String(myRobot.timeCTRL_Motor_1));
        Serial.println("M2-" + String(myRobot.speedMotor_2) + String(myRobot.timeCTRL_Motor_2));
        server.sendHeader("Access-Control-Allow-Origin", "*");
        server.send(204, "DONE");
        return true;
    }

    static void getDistance()
    {
        DynamicJsonDocument doc(1024);
        StaticJsonDocument<200> d;
        JsonArray array = d.to<JsonArray>();
        robotDistance.getDistance();
        doc["distanceRight"] = myRobot.distanceRight;
        doc["distanceLeft"] = myRobot.distanceLeft;
        array.add(doc);
        String json_string;
        serializeJson(array, json_string);
        server.sendHeader("Access-Control-Allow-Origin", "*");
        server.send(200, "application/json", json_string);
    }
    static String IpAddress2String(const IPAddress &ipAddress)
    {
        return String(ipAddress[0]) + String(".") +
               String(ipAddress[1]) + String(".") +
               String(ipAddress[2]) + String(".") +
               String(ipAddress[3]);
    }
    //     static bool setNetwork()
    //     {
    //         String data = server.arg("plain");
    //         DynamicJsonDocument doc(1024);
    //         deserializeJson(doc, data);
    //         String _ssid = doc["ssid"];
    //         String _pass = doc["pass"];
    // #ifdef DEBUG
    //         Serial.println(myDevice.STA_SSID);
    //         Serial.println(myDevice.STA_PASS);
    //         Serial.println(_ssid);
    //         Serial.println(_pass);
    // #endif
    //         server.sendHeader("Access-Control-Allow-Origin", "*");
    //         server.send(204, "DONE");
    //         return true;
    //     }
};
ESP32API myAPI;
