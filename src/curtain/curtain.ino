/*
 Electric curtain controller
 - three functionalities: open, close, stop
 - simulated by using two FauxMo devices
   - curtain opener: on = open curtain,  off = stop
   - curtain closer: on = close curtain, off = stop
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"
#include "wifi_config.h"

fauxmoESP fauxmo;

#define SERIAL_BAUDRATE   115200

// LED used as status indicators - both active low
#define BLUE_LED_PIN      2
#define RED_LED_PIN       LED_BUILTIN

// curtain control pins - all active high
#define CLOSE_PIN         D5
#define OPEN_PIN          D6
#define STOP_PIN          D7

#define DEVICE_ID_OPENER  "living room curtain opener"
#define DEVICE_ID_CLOSER  "living room curtain closer"

////////// FUNCTIONS ///////////////////////////////////////////////////////////

#define ENABLE_ACTIVE_HIGH(pin)       digitalWrite(pin, HIGH)
#define DISABLE_ACTIVE_HIGH(pin)      digitalWrite(pin, LOW)
#define TRIGGER_ACTIVE_HIGH(pin, ms)  digitalWrite(pin, HIGH);delay(ms);digitalWrite(pin, LOW)

#define ENABLE_ACTIVE_LOW(pin)       digitalWrite(pin, LOW)
#define DISABLE_ACTIVE_LOW(pin)      digitalWrite(pin, HIGH)
#define TRIGGER_ACTIVE_LOW(pin, ms)  digitalWrite(pin, LOW);delay(ms);digitalWrite(pin, HIGH)

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

////////// MAIN ////////////////////////////////////////////////////////////////

void setup() {
  // init serial port and clean garbage
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println();
  Serial.println();

  // pins
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(CLOSE_PIN, OUTPUT);
  pinMode(OPEN_PIN, OUTPUT);
  pinMode(STOP_PIN, OUTPUT);
  DISABLE_ACTIVE_LOW(BLUE_LED_PIN);
  DISABLE_ACTIVE_LOW(RED_LED_PIN);
  DISABLE_ACTIVE_HIGH(CLOSE_PIN);
  DISABLE_ACTIVE_HIGH(OPEN_PIN);
  DISABLE_ACTIVE_HIGH(STOP_PIN);

  // Wi-Fi
  wifi_setup();

  fauxmo.createServer(true);
  fauxmo.setPort(80);

  fauxmo.enable(true);

  // add virtual devices
  fauxmo.addDevice(DEVICE_ID_OPENER);
  fauxmo.addDevice(DEVICE_ID_CLOSER);

  // callback when a command from Alexa is received
  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
    Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
    if (strcmp(device_name, DEVICE_ID_OPENER)==0) {
      //TRIGGER_ACTIVE_LOW(RED_LED_PIN, 1);
      if (state == HIGH) {
        ENABLE_ACTIVE_HIGH(OPEN_PIN);
        DISABLE_ACTIVE_HIGH(CLOSE_PIN);
        DISABLE_ACTIVE_HIGH(STOP_PIN);
      } else {
        DISABLE_ACTIVE_HIGH(OPEN_PIN);
        DISABLE_ACTIVE_HIGH(CLOSE_PIN);
        ENABLE_ACTIVE_HIGH(STOP_PIN);
      }
      fauxmo.setState(DEVICE_ID_CLOSER, false, 255);
    } else if (strcmp(device_name, DEVICE_ID_CLOSER)==0) {
      //TRIGGER_ACTIVE_LOW(BLUE_LED_PIN, 1);
      if (state == HIGH) {
        DISABLE_ACTIVE_HIGH(OPEN_PIN);
        ENABLE_ACTIVE_HIGH(CLOSE_PIN);
        DISABLE_ACTIVE_HIGH(STOP_PIN);
      } else {
        DISABLE_ACTIVE_HIGH(OPEN_PIN);
        DISABLE_ACTIVE_HIGH(CLOSE_PIN);
        ENABLE_ACTIVE_HIGH(STOP_PIN);
      }
      fauxmo.setState(DEVICE_ID_OPENER, false, 255);
    }
  });
}

void loop() {
  fauxmo.handle();
}
