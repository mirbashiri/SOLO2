#include <WiFi.h>
#include "ESP32API.h"

class ESP32NET
{
private:
    uint8_t MAC_array[6];
    char MAC_char[18];
public:
    bool WiFi_FAC_ON()
    {
        WiFi.mode(WIFI_AP_STA);

        WiFi.begin(myDevice.FACTORY_SSID, myDevice.FACTORY_PASSWORD);
        Serial.println("Factory Mode");

        int cnt = 0;
        while (WiFi.status() != WL_CONNECTED)
        {
            cnt++;
            delay(1000);
            if (cnt > 10)
            {
                myNET_MODE.STA_FAC_ON = false;
                return false;
            }
#ifdef DEBUG
            Serial.println("Connecting to WiFi..");
#endif
        }
        myDevice.IP_STA = IpAddress2String(WiFi.localIP());
#ifdef DEBUG
        //Serial.println(myDevice.IP_STA);
#endif
        myNET_MODE.STA_FAC_ON = true;
        return true;
    }
    bool WiFi_USR_ON()
    {
        WiFi.mode(WIFI_AP_STA);
        WiFi.begin(myDevice.STA_SSID, myDevice.STA_PASS);
        Serial.println("User Mode");

        int cnt = 0;
        while (WiFi.status() != WL_CONNECTED)
        {
            cnt++;
            delay(1000);
            if (cnt > 10)
            {
                myNET_MODE.STA_USR_ON = false;
                return false;
            }
#ifdef DEBUG
            Serial.println("Connecting to WiFi..");
#endif
        }
        myDevice.IP_STA = IpAddress2String(WiFi.localIP());
#ifdef DEBUG
        //Serial.println(myDevice.IP_STA);
#endif
        myNET_MODE.STA_USR_ON = true;
        return true;
    }
    static void WIFI_OFF()
    {
        WiFi.disconnect();
    }
    String IpAddress2String(const IPAddress &ipAddress)
    {
        return String(ipAddress[0]) + String(".") +
               String(ipAddress[1]) + String(".") +
               String(ipAddress[2]) + String(".") +
               String(ipAddress[3]);
    }
};
ESP32NET myNETWORK;
