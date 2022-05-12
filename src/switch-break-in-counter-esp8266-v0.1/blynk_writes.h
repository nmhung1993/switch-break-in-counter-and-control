BLYNK_WRITE(vPIN_BREAKER_01_TARGET)
{
  int targetValue = param.asInt();
  if (targetValue!= SwBreaker_01_Target){
    SwBreaker_01_Target = targetValue;
    EEPROM.write(ADR_BREAKER_01_TARGET, SwBreaker_01_Target);
    EEPROM.commit();
  }
  printOutput(String("Switch Breaker 01 TARGET >> ") + String(ltos( EEPROM.read(ADR_BREAKER_01_TARGET), buf, 10)));
}

BLYNK_WRITE(vPIN_BREAKER_02_TARGET)
{
  int targetValue = param.asInt();
  if (targetValue!= SwBreaker_02_Target){
    SwBreaker_02_Target = targetValue;
    EEPROM.write(ADR_BREAKER_02_TARGET, SwBreaker_02_Target);
    EEPROM.commit();
  }
  printOutput(String("Switch Breaker 02 TARGET >> ") + String(ltos( EEPROM.read(ADR_BREAKER_02_TARGET), buf, 10)));
}

BLYNK_WRITE(vPIN_BREAKER_01_SET_SPEED)
{
  int targetSpeed = param.asInt()*2.55;
  if (targetSpeed > 0) {
    setSpeedSwBrk01(targetSpeed);
    EEPROM.write(ADR_BREAKER_01_SET_SPEED, targetSpeed);
  } else {
    stopSwBrk01();
    EEPROM.write(ADR_BREAKER_01_SET_SPEED, targetSpeed);
  }
  printOutput(String("Switch Breaker 01 SPEED >> ") + EEPROM.read(ADR_BREAKER_01_SET_SPEED));
}

BLYNK_WRITE(vPIN_BREAKER_02_SET_SPEED)
{
  int targetSpeed = param.asInt()*2.55;
  if (targetSpeed > 0) {
    setSpeedSwBrk02(targetSpeed);
    EEPROM.write(ADR_BREAKER_02_SET_SPEED, targetSpeed);
  } else {
    stopSwBrk02();
    EEPROM.write(ADR_BREAKER_02_SET_SPEED, targetSpeed);
  }
  printOutput(String("Switch Breaker 02 SPEED >> ") + EEPROM.read(ADR_BREAKER_02_SET_SPEED));
}

BLYNK_WRITE(vPIN_BREAKER_01_RELAY_01)
{
  int pinValue = param.asInt();
  if (pinValue == 0) {
    // Todo: turn relay off
    digitalWrite(PIN_RELAY_01, HIGH);
    printOutput(String("RELAY 01 >> HIGH"));
  } else {
    // Todo: turn relay on
    digitalWrite(PIN_RELAY_01, LOW);
    
    printOutput(String("RELAY 01 >> LOW"));
  }
}

BLYNK_WRITE(vPIN_BREAKER_01_CLEAR)
{
  int pinValue = param.asInt();
  if (pinValue == 1) {
    SwBreaker_01_Counter = 0;
    SwBreaker_01_Last_Value = 0;
    writeLongIntoEEPROM(ADR_BREAKER_01_CUR_COUNTER,SwBreaker_01_Counter);
    Blynk.virtualWrite(vPIN_BREAKER_01_CUR_COUNTER, String(ltos(readLongFromEEPROM(ADR_BREAKER_01_CUR_COUNTER), buf, 10)));
    printOutput(String("Switch Breaker 01 >> RESET Counter: ") + String(ltos(readLongFromEEPROM(ADR_BREAKER_01_CUR_COUNTER), buf, 10)));
  }
}
BLYNK_WRITE(vPIN_BREAKER_02_CLEAR)
{
  int pinValue = param.asInt();
  if (pinValue == 1) {
    SwBreaker_02_Counter = 0;
    SwBreaker_02_Last_Value = 0;
    writeLongIntoEEPROM(ADR_BREAKER_02_CUR_COUNTER,SwBreaker_02_Counter);
    Blynk.virtualWrite(vPIN_BREAKER_02_CUR_COUNTER, String(ltos(readLongFromEEPROM(ADR_BREAKER_02_CUR_COUNTER), buf, 10)));
    printOutput(String("Switch Breaker 02 >> RESET Counter: ") + String(ltos(readLongFromEEPROM(ADR_BREAKER_02_CUR_COUNTER), buf, 10)));
  }
}
BLYNK_WRITE(vPIN_BREAKER_03_CLEAR)
{
  int pinValue = param.asInt();
  if (pinValue == 1) {
    SwBreaker_03_Counter = 0;
    SwBreaker_03_Last_Value = 0;
    writeLongIntoEEPROM(ADR_BREAKER_03_CUR_COUNTER,SwBreaker_03_Counter);
    Blynk.virtualWrite(vPIN_BREAKER_03_CUR_COUNTER, String(ltos(readLongFromEEPROM(ADR_BREAKER_03_CUR_COUNTER), buf, 10)));
    printOutput(String("Switch Breaker 03 >> RESET Counter: ") + String(ltos(readLongFromEEPROM(ADR_BREAKER_03_CUR_COUNTER), buf, 10)));
  }
}
