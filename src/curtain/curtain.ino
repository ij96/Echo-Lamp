#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"
#include "wifi_config.h"

#define SERIAL_BAUDRATE   115200
#define DEVICE_ID_LAMP    "the curtain"

#define BLUE_LED_PIN      2
#define RELAY_PIN         12

fauxmoESP fauxmo;

void wifiSetup() {
  // set Wi-Fi module to STA mode
  WiFi.mode(WIFI_STA);

  // Connect
  Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Wait
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(BLUE_LED_PIN, LOW);
    delay(1);
    digitalWrite(BLUE_LED_PIN, HIGH);
    delay(199);
  }
  Serial.println();

  // Connected!
  Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}

void setup() {
}

void loop() {
}
