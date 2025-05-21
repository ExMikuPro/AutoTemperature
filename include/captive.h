#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <EEPROM.h>

#define EEPROM_SIZE 96
#define SSID_ADDR 0
#define PASS_ADDR 32


// 配置入口函数
void tryConnectWiFi();        // 尝试读取 EEPROM 并连接 WiFi

// 工具函数
void clearWiFiConfig();                       // 清除 EEPROM 中 WiFi 配置
void serverLoop();