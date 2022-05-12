#define BLYNK_PRINT Serial

#include <ArduinoOTA.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include "settings.h"
#include "functions.h"
#include "blynk_writes.h"

BlynkTimer timer;

void setup()
{
  Serial.begin(115200);
  
  EEPROM.begin(4096);
  
  WiFi.mode(WIFI_STA);

  /***********BLYNK*************/
  #ifdef LOCAL_SERVER
    Blynk.begin(AUTH_SW_BREAKER_COUNTER, WIFI_SSID, WIFI_PASS, LOCAL_SERVER);
  #else
    Blynk.begin(AUTH_SW_BREAKER_COUNTER, WIFI_SSID, WIFI_PASS);
  #endif
  while (Blynk.connect() == false) {}
  
  /*********** OTA *************/
  ArduinoOTA.setHostname(OTA_HOSTNAME);
  ArduinoOTA.begin();

  /*********pinModes************/
  pinMode(PIN_BREAKER_01, INPUT_PULLUP);
  pinMode(PIN_BREAKER_02, INPUT_PULLUP);
  pinMode(PIN_BREAKER_03, INPUT_PULLUP);
  
  pinMode(PIN_L298N_IN1, OUTPUT);
  pinMode(PIN_L298N_IN2, OUTPUT);
  pinMode(PIN_L298N_IN3, OUTPUT);
  pinMode(PIN_L298N_IN4, OUTPUT);
  
  pinMode(PIN_RELAY_01, OUTPUT);
  pinMode(PIN_SWITCH_02, OUTPUT);
  /**********SYNC**************/
  syncEEPROMToLocalVar();
  long curLongCounter = readLongFromEEPROM(0);
  if(curLongCounter > 0 && curLongCounter != SwBreaker_01_Counter)
    SwBreaker_01_Counter = curLongCounter;

  timer.setInterval(60000L, speedAndTimeEstEvent);
  printOutput(String("Switch Breaker 1 >> Current Counter: ") + String(ltos(readLongFromEEPROM(ADR_BREAKER_01_CUR_COUNTER), buf, 10)));
  printOutput(String("Switch Breaker 2 >> Current Counter: ") + String(ltos(readLongFromEEPROM(ADR_BREAKER_02_CUR_COUNTER), buf, 10)));
  printOutput(String("Switch Breaker 3 >> Current Counter: ") + String(ltos(readLongFromEEPROM(ADR_BREAKER_03_CUR_COUNTER), buf, 10)));
}

void loop() 
{
  Blynk.run();
  ArduinoOTA.handle();
  
  #ifdef SW_BREAKER_01
    triggerSwBrk01();
  #endif
  #ifdef SW_BREAKER_02
    triggerSwBrk02();
  #endif
  #ifdef SW_BREAKER_03
    triggerSwBrk03();
  #endif
  
    
  timer.run(); // Initiates BlynkTimer
}
