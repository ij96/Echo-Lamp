# Echo Things

IoT things to be controlled via Alexa (Amazon Echo).

Controller: NodeMCU DEVKIT 1.0 / Adafruit Feather HUZZAH ESP8266

Language: C++ (Arduino)

## Things

- Garden Lamp: see folder `src/garden_lamp`
- Curtain: see folder `src/curtain`

## User instructions

### Prerequisites
- hardware:
  - [Adafruit Feather HUZZAH ESP8266](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266)
  - [NodeMCU DEVKIT 1.0 board](http://www.nodemcu.com)
- software required:
  - [Arduino IDE](https://www.arduino.cc/en/Main/Software)

You will also need to:
- add ESP8266 boards:
  - in Arduino IDE, go to File > Preferences, and add the following to Additional Boards Manager URLs:

  ```
  http://arduino.esp8266.com/stable/package_esp8266com_index.json
  ```

  - go to Tools > Board > Boards Manager, search and install `ESP8266`. This installs the functionalities for both NodeMCU and Feather.

- install Arduino libraries:
  - [`FauxmoESP`](https://bitbucket.org/xoseperez/fauxmoesp/) (can be installed via Library Manager)
  - [`ESPAsyncTCP`](https://github.com/me-no-dev/ESPAsyncTCP)
  - [`ESPAsyncWebServer`](https://github.com/me-no-dev/ESPAsyncWebServer)

### Upload code
- **copy `src/wifi_config.h` into the same directory as the Arduino sketch, and modify the Wi-Fi SSID and password to your own**.
- open Arduino IDE.
- in Tools, choose the right board type and port.
- upload sketch

## Notes
- WeMo (and thus `fauxmo`) devices could only respond to two commands: on and off. For more complicated functionalities, we can use Amazon Skill.
- Wi-Fi module consumes a lot of power - sleep often to conserve battery.
