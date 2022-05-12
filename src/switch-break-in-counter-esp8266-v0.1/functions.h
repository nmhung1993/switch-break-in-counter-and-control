void printOutput(String a) {
  Serial.println(a);
}

void writeLongIntoEEPROM(int address, long value) {
  //Decomposition from a long to 4 bytes by using bitshift.
  //One = Most significant -> Four = Least significant byte
  byte four = (value & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);
  
  //Write the 4 bytes into the eeprom memory.
  EEPROM.write(address, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
}

long readLongFromEEPROM(int address) {
  //Read the 4 bytes from the eeprom memory.
  long four = EEPROM.read(address);
  long three = EEPROM.read(address + 1);
  long two = EEPROM.read(address + 2);
  long one = EEPROM.read(address + 3);
  
  //Return the recomposed long by using bitshift.
  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

char *ultos_recursive(unsigned long val, char *s, unsigned radix, int pos) {
  int c;

  if (val >= radix)
    s = ultos_recursive(val / radix, s, radix, pos+1);
  c = val % radix;
  c += (c < 10 ? '0' : 'a' - 10);
  *s++ = c;
  if (pos % 3 == 0) *s++ = ',';
  return s;
}

char *ltos(long val, char *s, int radix) {
  if (radix < 2 || radix > 36) {
    s[0] = 0;
  } else {
    char *p = s;
    if (radix == 10 && val < 0) {
      val = -val;
      *p++ = '-';
    }
    p = ultos_recursive(val, p, radix, 0) - 1;
    *p = 0;
  }
  return s;
}

void triggerSwBrk01() {
  SwBreaker_01_Cur = digitalRead(PIN_BREAKER_01);
  if (SwBreaker_01_Cur == LOW && SwBreaker_01_Prev == HIGH) 
  {
    if(SwBreaker_01_Counter < 0)
      SwBreaker_01_Counter = 0;
    else
      SwBreaker_01_Counter++;
    
    writeLongIntoEEPROM (ADR_BREAKER_01_CUR_COUNTER, SwBreaker_01_Counter);
    EEPROM.commit();

    Blynk.virtualWrite(vPIN_BREAKER_01_CUR_COUNTER, String(ltos(readLongFromEEPROM(ADR_BREAKER_01_CUR_COUNTER), buf, 10)));

    printOutput(String("Total switch counter << Machine 01: ") + String(ltos(readLongFromEEPROM(ADR_BREAKER_01_CUR_COUNTER), buf, 10)));
    SwBreaker_01_Prev = SwBreaker_01_Cur;
  }
  else SwBreaker_01_Prev = SwBreaker_01_Cur;
}

void triggerSwBrk02() {
  SwBreaker_02_Cur = digitalRead(PIN_BREAKER_02);
  if (SwBreaker_02_Cur == LOW && SwBreaker_02_Prev == HIGH) 
  {
    if(SwBreaker_02_Counter < 0)
      SwBreaker_02_Counter = 0;
    else
      SwBreaker_02_Counter++;

    writeLongIntoEEPROM (ADR_BREAKER_02_CUR_COUNTER, SwBreaker_02_Counter);
    EEPROM.commit();

    Blynk.virtualWrite(vPIN_BREAKER_02_CUR_COUNTER, String(ltos(readLongFromEEPROM(ADR_BREAKER_02_CUR_COUNTER), buf, 10)));

    printOutput(String("Total switch counter << Machine 02: ") + String(ltos(readLongFromEEPROM(ADR_BREAKER_02_CUR_COUNTER), buf, 10)));
    SwBreaker_02_Prev = SwBreaker_02_Cur;
  }
  else SwBreaker_02_Prev = SwBreaker_02_Cur;
}

void triggerSwBrk03() {
  SwBreaker_03_Cur = digitalRead(PIN_BREAKER_03);
  if (SwBreaker_03_Cur == LOW && SwBreaker_03_Prev == HIGH) 
  {
    if(SwBreaker_03_Counter < 0)
      SwBreaker_03_Counter = 0;
    else
      SwBreaker_03_Counter++;
    
    writeLongIntoEEPROM (ADR_BREAKER_03_CUR_COUNTER, SwBreaker_03_Counter);
    EEPROM.commit();

    Blynk.virtualWrite(vPIN_BREAKER_03_CUR_COUNTER, String(ltos(readLongFromEEPROM(ADR_BREAKER_03_CUR_COUNTER), buf, 10)));

    printOutput(String("Total switch counter << Machine 03: ") + String(ltos(readLongFromEEPROM(ADR_BREAKER_03_CUR_COUNTER), buf, 10)));
    SwBreaker_03_Prev = SwBreaker_03_Cur;
  }
  else SwBreaker_03_Prev = SwBreaker_03_Cur;
}

void stopSwBrk01() {
  digitalWrite(PIN_L298N_IN1, LOW);
  digitalWrite(PIN_L298N_IN2, LOW);
}
 
void stopSwBrk02() {
  digitalWrite(PIN_L298N_IN3, LOW);
  digitalWrite(PIN_L298N_IN4, LOW);
}

void setSpeedSwBrk01(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  digitalWrite(PIN_L298N_IN1, HIGH);
  analogWrite(PIN_L298N_IN2, 255 - speed);
}

void setSpeedSwBrk02(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  analogWrite(PIN_L298N_IN3, speed);
  digitalWrite(PIN_L298N_IN4,LOW);
}

void speedAndTimeEstEvent() {
  //Switch Breaker 1
  {
    SwBreaker_01_BPM = (SwBreaker_01_Counter - SwBreaker_01_Last_Value);
    SwBreaker_01_Counter_Left = SwBreaker_01_Target - SwBreaker_01_Counter;
    if(SwBreaker_01_BPM > 0){
      SwBreaker_01_Hours_Left = (SwBreaker_01_Counter_Left/(SwBreaker_01_BPM*60));
      if(SwBreaker_01_Hours_Left > 0){
        Blynk.virtualWrite(vPIN_BREAKER_01_HRS_REMAIN, SwBreaker_01_Hours_Left);
      }
    }
    else
      Blynk.virtualWrite(vPIN_BREAKER_01_HRS_REMAIN, 999);
    Blynk.virtualWrite(vPIN_BREAKER_01_CUR_SPEED, SwBreaker_01_BPM);
    
    printOutput(String("Current switch counter << Machine 01: ") + String(ltos(readLongFromEEPROM(ADR_BREAKER_01_CUR_COUNTER), buf, 10)));
    printOutput(String("Current beats per minute << Machine 01: ") + SwBreaker_01_BPM);
    printOutput(String("Current hours left << Machine 01: ") + SwBreaker_01_Hours_Left);
  
    SwBreaker_01_Last_Value = SwBreaker_01_Counter;
  }

  //Switch Breaker 2
  {
    SwBreaker_02_BPM = (SwBreaker_02_Counter - SwBreaker_02_Last_Value);
    SwBreaker_02_Counter_Left = SwBreaker_02_Target - SwBreaker_02_Counter;
    if(SwBreaker_02_BPM > 0){
      SwBreaker_02_Hours_Left = (SwBreaker_02_Counter_Left/(SwBreaker_02_BPM*60));
      if(SwBreaker_02_Hours_Left > 0){
        Blynk.virtualWrite(vPIN_BREAKER_02_HRS_REMAIN, SwBreaker_02_Hours_Left);
      }
    }
    else
      Blynk.virtualWrite(vPIN_BREAKER_02_HRS_REMAIN, 999);
    Blynk.virtualWrite(vPIN_BREAKER_02_CUR_SPEED, SwBreaker_02_BPM);
    
    printOutput(String("Current switch counter << Machine 02: ") + String(ltos(readLongFromEEPROM(ADR_BREAKER_02_CUR_COUNTER), buf, 10)));
    printOutput(String("Current beats per minute << Machine 02: ") + SwBreaker_02_BPM);
    printOutput(String("Current hours left << Machine 02: ") + SwBreaker_02_Hours_Left);
  
    SwBreaker_02_Last_Value = SwBreaker_02_Counter;
  }

  //Switch Breaker 3
  {
    SwBreaker_03_BPM = (SwBreaker_03_Counter - SwBreaker_03_Last_Value);
    SwBreaker_03_Counter_Left = SwBreaker_03_Target - SwBreaker_03_Counter;
    if(SwBreaker_03_BPM > 0){
      SwBreaker_03_Hours_Left = (SwBreaker_03_Counter_Left/(SwBreaker_03_BPM*60));
      if(SwBreaker_03_Hours_Left > 0){
        Blynk.virtualWrite(vPIN_BREAKER_03_HRS_REMAIN, SwBreaker_03_Hours_Left);
      }
    }
    else
      Blynk.virtualWrite(vPIN_BREAKER_03_HRS_REMAIN, 999);
    Blynk.virtualWrite(vPIN_BREAKER_03_CUR_SPEED, SwBreaker_03_BPM);
    
    printOutput(String("Current switch counter << Machine 03: ") + String(ltos(readLongFromEEPROM(ADR_BREAKER_03_CUR_COUNTER), buf, 10)));
    printOutput(String("Current beats per minute << Machine 03: ") + SwBreaker_03_BPM);
    printOutput(String("Current hours left << Machine 01: ") + SwBreaker_03_Hours_Left);
  
    SwBreaker_03_Last_Value = SwBreaker_03_Counter;
  }
}

void syncEEPROMToLocalVar() {
  //Switch Breaker 01
  {
    long curCounter = readLongFromEEPROM(ADR_BREAKER_01_CUR_COUNTER);
    if (curCounter != SwBreaker_01_Counter) {
      SwBreaker_01_Counter = curCounter;
      writeLongIntoEEPROM(ADR_BREAKER_01_CUR_COUNTER,curCounter);
      printOutput(String("Switch Breaker 01 >> Current Counter: ") + String(ltos(readLongFromEEPROM(ADR_BREAKER_01_CUR_COUNTER), buf, 10)));
    }
    
    long targetCounter = readLongFromEEPROM(ADR_BREAKER_01_TARGET);
    if (targetCounter != SwBreaker_01_Target) {
      SwBreaker_01_Target = targetCounter;
      writeLongIntoEEPROM(ADR_BREAKER_01_TARGET, targetCounter);
      printOutput(String("Switch Breaker 01 >> Target Counter: ") + String(ltos(readLongFromEEPROM(ADR_BREAKER_01_TARGET), buf, 10)));
    }
    
    if (SwBreaker_01_Last_Value != SwBreaker_01_Target) {
      SwBreaker_01_Last_Value = SwBreaker_01_Counter;
      printOutput(String("Switch Breaker 01 >> Last Counter: ") + String(ltos(SwBreaker_01_Last_Value, buf, 10)));
    }
  
    int setSpeed = EEPROM.read(ADR_BREAKER_01_SET_SPEED);
    setSpeed = constrain(setSpeed, 50*2.55, 100*2.55);
    if(setSpeed > 0) {
      setSpeedSwBrk01(setSpeed);
    } else {
      stopSwBrk01();
    }
  }

  //Switch Breaker 02
  {
    long curCounter = readLongFromEEPROM(ADR_BREAKER_02_CUR_COUNTER);
    if (curCounter != SwBreaker_02_Counter) {
      SwBreaker_02_Counter = curCounter;
      writeLongIntoEEPROM(ADR_BREAKER_02_CUR_COUNTER,curCounter);
      printOutput(String("Switch Breaker 02 >> Current Counter: ") + String(ltos(readLongFromEEPROM(ADR_BREAKER_02_CUR_COUNTER), buf, 10)));
    }
    
    long targetCounter = readLongFromEEPROM(ADR_BREAKER_02_TARGET);
    if (targetCounter != SwBreaker_02_Target) {
      SwBreaker_02_Target = targetCounter;
      writeLongIntoEEPROM(ADR_BREAKER_02_TARGET, targetCounter);
      printOutput(String("Switch Breaker 02 >> Target Counter: ") + String(ltos(readLongFromEEPROM(ADR_BREAKER_02_TARGET), buf, 10)));
    }
    
    if (SwBreaker_02_Last_Value != SwBreaker_02_Target) {
      SwBreaker_02_Last_Value = SwBreaker_02_Counter;
      printOutput(String("Switch Breaker 02 >> Last Counter: ") + String(ltos(SwBreaker_02_Last_Value, buf, 10)));
    }
  
    int setSpeed = EEPROM.read(ADR_BREAKER_02_SET_SPEED);
    setSpeed = constrain(setSpeed, 50*2.55, 100*2.55);
    if(setSpeed > 0) {
      setSpeedSwBrk02(setSpeed);
    } else {
      stopSwBrk02();
    }
  }

  //Switch Breaker 03
  {
    long curCounter = readLongFromEEPROM(ADR_BREAKER_03_CUR_COUNTER);
    if (curCounter != SwBreaker_03_Counter) {
      SwBreaker_03_Counter = curCounter;
      writeLongIntoEEPROM(ADR_BREAKER_03_CUR_COUNTER,curCounter);
      printOutput(String("Switch Breaker 02 >> Current Counter: ") + String(ltos(readLongFromEEPROM(ADR_BREAKER_03_CUR_COUNTER), buf, 10)));
    }
    
    long targetCounter = readLongFromEEPROM(ADR_BREAKER_03_TARGET);
    if (targetCounter != SwBreaker_03_Target) {
      SwBreaker_03_Target = targetCounter;
      writeLongIntoEEPROM(ADR_BREAKER_03_TARGET, targetCounter);
      printOutput(String("Switch Breaker 02 >> Target Counter: ") + String(ltos(readLongFromEEPROM(ADR_BREAKER_03_TARGET), buf, 10)));
    }
    
    if (SwBreaker_03_Last_Value != SwBreaker_03_Target) {
      SwBreaker_03_Last_Value = SwBreaker_03_Counter;
      printOutput(String("Switch Breaker 02 >> Last Counter: ") + String(ltos(SwBreaker_03_Last_Value, buf, 10)));
    }
  
    int setSpeed = EEPROM.read(ADR_BREAKER_03_SET_SPEED);
    setSpeed = constrain(setSpeed, 50*2.55, 100*2.55);
    if(setSpeed > 0) {
      setSpeedSwBrk02(setSpeed);
    } else {
      stopSwBrk02();
    }
  }
}
