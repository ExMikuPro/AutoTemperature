#include <Arduino.h>
#include <EEPROM.h>
#include "captive.h"

void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);

  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    if (command == "clear") {
      clearWiFiConfig();
    }
  }

  tryConnectWiFi();
}

void loop() {
  serverLoop();
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    if (command == "clear") {
      clearWiFiConfig();
      ESP.restart();
    }
  }
}
