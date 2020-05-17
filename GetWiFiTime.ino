/*
 * A very simple sketch for the Nano 33 IoT to retrieve the time from the WiFi module.
 */
#include <WiFiNINA.h>
#include <time.h>
#include "secrets.h"

const char ssid[] = SECRET_SSID;
const char pwd[] = SECRET_PASS;

time_t currentTime;

#define MAX_LINEBUFF 128
char lineBuff[MAX_LINEBUFF];

unsigned long lastTime = 0;

int connectWiFi() {
  int retVal;
  
  WiFi.setTimeout(45 * 1000);
  retVal = WiFi.begin(ssid, pwd);
  if ( retVal != WL_CONNECTED) {
    Serial.print("Error connecting to WiFi = "); Serial.println(WiFi.reasonCode());
    delay(1500);
  }
  return retVal;
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(19200);
  delay(1500);

  Serial.println("Starting");
}

void loop() {
 
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not Connected!");
    connectWiFi();
  }
  
  if ((millis() - lastTime) >= 10000) {
    lastTime = millis();
    if(WiFi.status() == WL_CONNECTED) {
      currentTime = WiFi.getTime();
      struct tm* t = gmtime(&currentTime);
      snprintf(lineBuff, MAX_LINEBUFF, "Time = %04d-%02d-%02d %02d:%02d:%02d\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
      Serial.print(lineBuff);
    } else {
      Serial.println("WiFi disconnected!");
    }
  }
}
