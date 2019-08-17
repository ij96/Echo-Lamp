#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"
#include "wifi_config.h"

#define SERIAL_BAUDRATE   115200
#define DEVICE_ID_LAMP    "the garden lamp"

#define RELAY_PIN         14
#define BLUE_LED_PIN      2

fauxmoESP fauxmo;

void wifi_setup() {
  // set Wi-Fi module to STA mode
  WiFi.mode(WIFI_STA);

  // connect
  Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // wait
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(BLUE_LED_PIN, LOW);
    delay(1);
    digitalWrite(BLUE_LED_PIN, HIGH);
    delay(199);
  }
  Serial.println();

  // connected
  Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}

uint8_t prev_brightness = 0;
uint8_t brightness = 0;

void setup() {
  // init serial port and clean garbage
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println();
  Serial.println();

  // pins
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, HIGH);

  // Wi-Fi
  wifi_setup();

  // Fauxmo
  fauxmo.createServer(true);
  fauxmo.setPort(80);

  fauxmo.enable(true);

  // add virtual devices
  fauxmo.addDevice(DEVICE_ID_LAMP);

  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
    Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
    if (state) {
      brightness = value;
    } else {
      brightness = 0;
    }
  });
}

void loop() {
  fauxmo.handle();

  if (brightness != prev_brightness) {
    Serial.print("new brightness ");
    Serial.println(brightness);
    prev_brightness = brightness;
    if (brightness == 0) {
      digitalWrite(RELAY_PIN, LOW);
    } else {
      analogWrite(RELAY_PIN, brightness * 4); // ESP8266 analogWrite is 10-bit, unlike Arduino where it is 8-bit
    }
  }
}
