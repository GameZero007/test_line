#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#define TokenLine "iAhzsuww44XTvtBrsLZlWY2csiZRh3nHdt7XQiSWyex"
const char* ssid = "NAPHAT_2.4G";
const char* password = "0918703498";
String txtfull;  
unsigned long  timebegin;

void NotifyLine(String t) {
    WiFiClientSecure client;
    if (!client.connect("notify-api.line.me", 443)) {
      Serial.println("Connection failed");
      return;
    }
    String req = "";
    req += "POST /api/notify HTTP/1.1\r\n";
    req += "Host: notify-api.line.me\r\n";
    req += "Authorization: Bearer " + String(TokenLine) + "\r\n";
    req += "Cache-Control: no-cache\r\n";
    req += "User-Agent: ESP32\r\n";
    req += "Content-Type: application/x-www-form-urlencoded\r\n";
    req += "Content-Length: " + String(String("message=" + t).length()) + "\r\n";
    req += "\r\n";
    req += "message=" + t;
    Serial.println(req);
    client.print(req);
    delay(20);
    Serial.println("-------------");
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
          break;
      }
    } //while
} // void Noti
void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200); delay(200);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  timebegin = millis();
  while(WiFi.status() != WL_CONNECTED && (millis()-timebegin<=15000) ) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  timebegin=millis();
}

void loop() {
 
txtfull="ภูชนะ 6204000007";
if (millis()-timebegin>=15000)  {
  NotifyLine(txtfull);
  Serial.print(txtfull);
  timebegin=millis();
  }
}
