//#include "ultraDistance.h"
//#include <SoftwareSerial.h>
#include "UI.h"

httpd_handle_t camera_httpd = NULL;
httpd_handle_t stream_httpd = NULL;
httpd_handle_t live_httpd = NULL;

class ESP32CAM
{
  private:
  public:
    void init()
    {
      camera_config_t config;
      config.ledc_channel = LEDC_CHANNEL_0;
      config.ledc_timer = LEDC_TIMER_0;
      config.pin_d0 = Y2_GPIO_NUM;
      config.pin_d1 = Y3_GPIO_NUM;
      config.pin_d2 = Y4_GPIO_NUM;
      config.pin_d3 = Y5_GPIO_NUM;
      config.pin_d4 = Y6_GPIO_NUM;
      config.pin_d5 = Y7_GPIO_NUM;
      config.pin_d6 = Y8_GPIO_NUM;
      config.pin_d7 = Y9_GPIO_NUM;
      config.pin_xclk = XCLK_GPIO_NUM;
      config.pin_pclk = PCLK_GPIO_NUM;
      config.pin_vsync = VSYNC_GPIO_NUM;
      config.pin_href = HREF_GPIO_NUM;
      config.pin_sscb_sda = SIOD_GPIO_NUM;
      config.pin_sscb_scl = SIOC_GPIO_NUM;
      config.pin_pwdn = PWDN_GPIO_NUM;
      config.pin_reset = RESET_GPIO_NUM;
      config.xclk_freq_hz = 20000000;
      config.pixel_format = PIXFORMAT_JPEG;
      // init with high specs to pre-allocate larger buffers
      if (psramFound())
      {
        config.frame_size = FRAMESIZE_UXGA;
        config.jpeg_quality = 10;
        config.fb_count = 2;
      }
      else
      {
        // config.frame_size = FRAMESIZE_SVGA;
        config.frame_size = FRAMESIZE_VGA;
        config.jpeg_quality = 12;
        config.fb_count = 1;
      }

      // Camera init
      esp_err_t err = esp_camera_init(&config);
      if (err != ESP_OK)
      {
        // Serial.printf("Camera init failed with error 0x%x", err);
        return;
      }
    }
    void startCameraServer()
    {
      httpd_config_t config = HTTPD_DEFAULT_CONFIG();
      config.server_port = 80;
      httpd_uri_t index_uri = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = index_handler,
        .user_ctx = NULL
      };
      httpd_uri_t cmd_uri = {
        .uri = "/action",
        .method = HTTP_GET,
        .handler = cmd_handler,
        .user_ctx = NULL
      };
      httpd_uri_t stream_uri = {
        .uri = "/stream",
        .method = HTTP_GET,
        .handler = stream_handler,
        .user_ctx = NULL
      };
      httpd_uri_t live_uri = {
        .uri = "/live",
        .method = HTTP_GET,
        .handler = live_handler,
        .user_ctx = NULL
      };
      if (httpd_start(&camera_httpd, &config) == ESP_OK)
      {
        httpd_register_uri_handler(camera_httpd, &index_uri);
        httpd_register_uri_handler(camera_httpd, &cmd_uri);
      }
      config.server_port += 1;
      config.ctrl_port += 1;
      if (httpd_start(&stream_httpd, &config) == ESP_OK) // PORT 81
      {
        httpd_register_uri_handler(stream_httpd, &stream_uri);
      }
      config.server_port += 1;
      config.ctrl_port += 1;
      if (httpd_start(&live_httpd, &config) == ESP_OK) // PORT 82
      {
        httpd_register_uri_handler(live_httpd, &live_uri);
      }
    }
    static esp_err_t index_handler(httpd_req_t *req)
    {
      httpd_resp_set_type(req, "text/html");
      return httpd_resp_send(req, (const char *)INDEX_HTML, strlen(INDEX_HTML));
    }
    static esp_err_t stream_handler(httpd_req_t *req)
    {
      camera_fb_t *fb = NULL;
      esp_err_t res = ESP_OK;
      size_t _jpg_buf_len = 0;
      uint8_t *_jpg_buf = NULL;
      char *part_buf[64];

      res = httpd_resp_set_type(req, _STREAM_CONTENT_TYPE);
      if (res != ESP_OK)
      {
        return res;
      }

      while (true)
      {
        fb = esp_camera_fb_get();
        if (!fb)
        {
          // Serial.println("Camera capture failed");
          res = ESP_FAIL;
        }
        else
        {
          if (fb->width > 400)
          {
            if (fb->format != PIXFORMAT_JPEG)
            {
              bool jpeg_converted = frame2jpg(fb, 80, &_jpg_buf, &_jpg_buf_len);
              esp_camera_fb_return(fb);
              fb = NULL;
              if (!jpeg_converted)
              {
                // Serial.println("JPEG compression failed");
                res = ESP_FAIL;
              }
            }
            else
            {
              _jpg_buf_len = fb->len;
              _jpg_buf = fb->buf;
            }
          }
        }
        if (res == ESP_OK)
        {
          size_t hlen = snprintf((char *)part_buf, 64, _STREAM_PART, _jpg_buf_len);
          res = httpd_resp_send_chunk(req, (const char *)part_buf, hlen);
        }
        if (res == ESP_OK)
        {
          res = httpd_resp_send_chunk(req, (const char *)_jpg_buf, _jpg_buf_len);
        }
        if (res == ESP_OK)
        {
          res = httpd_resp_send_chunk(req, _STREAM_BOUNDARY, strlen(_STREAM_BOUNDARY));
        }
        if (fb)
        {
          esp_camera_fb_return(fb);
          fb = NULL;
          _jpg_buf = NULL;
        }
        else if (_jpg_buf)
        {
          free(_jpg_buf);
          _jpg_buf = NULL;
        }
        if (res != ESP_OK)
        {
          break;
        }
        // Serial.printf("MJPG: %uB\n",(uint32_t)(_jpg_buf_len));
      }
      return res;
    }
    static esp_err_t cmd_handler(httpd_req_t *req)
    {
      // robotDistance.getDistance();
      char *buf;
      size_t buf_len;
      char variable[32] = {
        0,
      };
      buf_len = httpd_req_get_url_query_len(req) + 1;
      if (buf_len > 1)
      {
        buf = (char *)malloc(buf_len);
        if (!buf)
        {
          httpd_resp_send_500(req);
          return ESP_FAIL;
        }
        if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK)
        {
          if (httpd_query_key_value(buf, "go", variable, sizeof(variable)) == ESP_OK)
          {
          }
          else
          {
            free(buf);
            httpd_resp_send_404(req);
            return ESP_FAIL;
          }
        }
        else
        {
          free(buf);
          httpd_resp_send_404(req);
          return ESP_FAIL;
        }
        free(buf);
      }
      else
      {
        httpd_resp_send_404(req);
        return ESP_FAIL;
      }

      sensor_t *s = esp_camera_sensor_get();
      int res = 0;

      if (!strcmp(variable, "LED_ON"))
      {
        digitalWrite(LED, HIGH);
      }
      if (!strcmp(variable, "LED_OFF"))
      {
        digitalWrite(LED, LOW);
      }
      if (!strcmp(variable, "forward"))
      {
        robotMotors.Forward();
      }
      else if (!strcmp(variable, "left"))
      {
        robotMotors.Left();
      }
      else if (!strcmp(variable, "right"))
      {
        robotMotors.Right();
      }
      else if (!strcmp(variable, "backward"))
      {
        robotMotors.Backward();
      }
      else if (!strcmp(variable, "stop"))
      {
        robotMotors.Stop();
      }
      else
      {
        res = -1;
      }

      if (res)
      {
        return httpd_resp_send_500(req);
      }

      httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
      return httpd_resp_send(req, NULL, 0);
    }
    static esp_err_t live_handler(httpd_req_t *req)
    {
      char *buf;
      size_t buf_len;
      char variable[32] = {
        0,
      };
      buf_len = httpd_req_get_url_query_len(req) + 1;
      if (buf_len > 1)
      {
        buf = (char *)malloc(buf_len);
        if (!buf)
        {
          httpd_resp_send_500(req);
          return ESP_FAIL;
        }
        if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK)
        {
          if (httpd_query_key_value(buf, "get", variable, sizeof(variable)) == ESP_OK)
          {
          }
          else
          {
            free(buf);
            httpd_resp_send_404(req);
            return ESP_FAIL;
          }
        }
        else
        {
          free(buf);
          httpd_resp_send_404(req);
          return ESP_FAIL;
        }
        free(buf);
      }
      else
      {
        httpd_resp_send_404(req);
        return ESP_FAIL;
      }
      if (!strcmp(variable, "distanceRight"))
      {
        esp_err_t res = ESP_OK;
        res = httpd_resp_set_type(req, "text/html");
        if (res != ESP_OK)
        {
          // Serial.println("live_handler_error");
          return res;
        }
        while (true)
        {
          if (res == ESP_OK)
          {
            char result[8];
            // myRobot.distanceRight = random(10, 200);
            dtostrf(myRobot.distanceRight, 6, 2, result);
            httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
            res = httpd_resp_send(req, result, 5);
          }
          else if (res != ESP_OK)
          {
            break;
          }
        }
        return res;
      }
      if (!strcmp(variable, "distanceLeft"))
      {
        esp_err_t res = ESP_OK;
        res = httpd_resp_set_type(req, "text/html");
        if (res != ESP_OK)
        {
          // Serial.println("live_handler_error");
          return res;
        }
        while (true)
        {
          if (res == ESP_OK)
          {
            char result[8];
            // myRobot.distanceLeft = random(10, 200);
            dtostrf(myRobot.distanceLeft, 6, 2, result);
            httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
            res = httpd_resp_send(req, result, 5);
          }
          else if (res != ESP_OK)
          {
            break;
          }
        }
        return res;
      }
      if (!strcmp(variable, "gear"))
      {
        esp_err_t res = ESP_OK;
        res = httpd_resp_set_type(req, "text/html");
        if (res != ESP_OK)
        {
          // Serial.println("live_handler_error");
          return res;
        }
        while (true)
        {
          if (res == ESP_OK)
          {
            char result[8];
            char tmp[8];
            dtostrf(myRobot.gear, 6, 2, result);
            int j = 0;
            for (int i = 0; i < 8; i++)
            {
              if (result[i] == ' ')
                continue;
              tmp[j++] = result[i];
            }
            httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
            res = httpd_resp_send(req, tmp, 1);
            // res = httpd_resp_send(req, "2.0", 3);
          }
          else if (res != ESP_OK)
          {
            break;
          }
        }
        return res;
      }
      if (!strcmp(variable, "gearUP"))
      {
        esp_err_t res = ESP_OK;
        res = httpd_resp_set_type(req, "text/html");
        if (res != ESP_OK)
        {
          // Serial.println("live_handler_error");
          return res;
        }
        if (res == ESP_OK)
        {
          char result[8];
          if (myRobot.gear < 4)
          {
            myRobot.gear++;
          }
          else
          {
            myRobot.gear = 4;
          }
          dtostrf(myRobot.gear, 6, 2, result);
          httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
          res = httpd_resp_send(req, result, 5);
        }
        else if (res != ESP_OK)
        {
        }
        return res;
      }
      if (!strcmp(variable, "gearDOWN"))
      {
        esp_err_t res = ESP_OK;
        res = httpd_resp_set_type(req, "text/html");
        if (res != ESP_OK)
        {
          // Serial.println("live_handler_error");
          return res;
        }

        if (res == ESP_OK)
        {
          char result[8];
          if (myRobot.gear > 0)
          {
            myRobot.gear--;
          }
          else
          {
            myRobot.gear = 0;
          }
          // myRobot.distanceLeft = random(10, 200);
          dtostrf(myRobot.gear, 6, 2, result);
          httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
          res = httpd_resp_send(req, result, 5);
        }
        else if (res != ESP_OK)
        {
        }
        return res;
      }
      if (!strcmp(variable, "battery"))
      {
        esp_err_t res = ESP_OK;
        res = httpd_resp_set_type(req, "text/html");
        if (res != ESP_OK)
        {
          // Serial.println("live_handler_error");
          return res;
        }
        while (true)
        {
          if (res == ESP_OK)
          {
            char result[8];
            char tmp[8];
            // myRobot.distanceLeft = random(10, 200);
            dtostrf(myRobot.batteryLVL, 6, 2, result);
            int j = 0;
            for (int i = 0; i < 8; i++)
            {
              if (result[i] == ' ')
                continue;
              tmp[j++] = result[i];
            }
            httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
            res = httpd_resp_send(req, tmp, 1);
            // res = httpd_resp_send(req, "2.0", 3);
          }
          else if (res != ESP_OK)
          {
            break;
          }
        }
        return res;
      }
    }
    static void decodePayload(String payload)
    {
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);
      JsonObject obj = doc.as<JsonObject>();
      myRobot.distanceLeft = obj[String("D1")];
      myRobot.distanceRight = obj[String("D2")];
      myRobot.batteryLVL = obj[String("B")];
      Serial.print(String(myRobot.distanceLeft));
      Serial.print(",");
      Serial.print(String(myRobot.distanceRight));
      Serial.print(",");
      Serial.println(String(myRobot.batteryLVL));
    }
};
ESP32CAM robotCamera;
