#include <Arduino.h>
#include <EEPROM.h>
#include "captive.h"

#include <DHT11.h>

#include <Ticker.h>

#define DHT_Pin_0 4
#define DHT_Pin_1 5

DHT11 dht_env(D6);     // 环境传感器
DHT11 dht_out(D5);     // 出风口传感器

Ticker sensorTicker;

volatile bool shouldReadSensor = false;

void onSensorTick() {
  shouldReadSensor = true;
}

void readAndPrint(DHT11 &sensor, const char *label) {
  int temp = 0, hum = 0;
  int result = sensor.readTemperatureHumidity(hum, temp);
  if (result == 0) {
    Serial.printf("[%s] 温度: %d°C, 湿度: %d%%\n", label, temp, hum);
  } else {
    Serial.printf("[%s] 读取失败，错误码: %d\n", label, result);
  }
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);
  sensorTicker.attach(5, onSensorTick); // DHT11 获取标志

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

  if (shouldReadSensor && WiFi.status() == WL_CONNECTED){
    readAndPrint(dht_out,"出风口温度");
    readAndPrint(dht_env,"环境温度");
  }



  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    if (command == "clear") {
      clearWiFiConfig();
      ESP.restart();
    }
  }
}
