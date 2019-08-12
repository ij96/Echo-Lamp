#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"
#include "wifi_config.h"

#define SERIAL_BAUDRATE   115200
#define DEVICE_ID_LAMP    "the garden lamp"

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
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  
  pinMode(BLUE_LED_PIN, OUTPUT);
  digitalWrite(BLUE_LED_PIN, LOW);
  
  Serial.begin(SERIAL_BAUDRATE);

  // Wifi
  wifiSetup();

  // Fauxmo
  fauxmo.createServer(true);
  fauxmo.setPort(80);

  fauxmo.enable(true);
  
  fauxmo.addDevice(DEVICE_ID_LAMP);

  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
    Serial.print("[MAIN] Device: ");Serial.print(device_name);
    Serial.print(" state ");
    if(state) {
      Serial.println("ON");
      digitalWrite(RELAY_PIN, HIGH);
    } else {
      Serial.println("OFF");
      digitalWrite(RELAY_PIN, LOW);
    }
  
  });
}

void loop() {
  fauxmo.handle();

  // print heap
  //static unsigned long last = millis();
  //if (millis() - last > 5000) {
  //  last = millis();
  //  Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());
  //}
}
