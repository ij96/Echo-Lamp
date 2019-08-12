# Echo Things

IoT things to be controlled via Alexa (Amazon Echo).

Controller: NodeMCU DEVKIT 1.0 / Adafruit Feather HUZZAH ESP8266

Language: C++ (Arduino)

## Things

- Garden Lamp: see folder `src/garden_lamp`
- Curtain: see folder `src/curtain`

## User instructions

### Prerequisites
- Hardware required: [NodeMCU DEVKIT 1.0 board](http://www.nodemcu.com)
- Software required: [Arduino IDE](https://www.arduino.cc/en/Main/Software)

- Add NodeMCU board:
  - in Arduino IDE, go to File > Preferences, and add the following to Additional Boards Manager URLs:

  ```
  http://arduino.esp8266.com/stable/package_esp8266com_index.json
  ```

  - go to Tools > Board > Boards Manager, search and install `ESP8266`

- Install library: in Arduino IDE, go to Sketch > Include Library > Manage Libraries, search and install `FauxmoESP`

### Upload code
- **Copy `src/wifi_config.h` into the same directory as the Arduino sketch, and modify the Wi-Fi SSID and password to your own**.
- Open Arduino IDE.
- In Tools > Board, choose `NodeMCU 1.0 (ESP-12E Module)` or `Adafruit Feather HUZZAH ESP8266`.
- In Tools > Port, choose the port connected to the NodeMCU / Feather HUZZAH
- Upload sketch

## Notes
- WeMo (and thus `fauxmo`) devices could only respond to two commands: on and off. For more complicated functionalities, we need to use Amazon Skill.
- Wi-Fi module consumes a lot of power - sleep often to conserve battery.
