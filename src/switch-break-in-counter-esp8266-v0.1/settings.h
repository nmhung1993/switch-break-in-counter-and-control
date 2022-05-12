/**************************************************************

                            Settings

 **************************************************************/
#define MAX_SPEED 255
#define MIN_SPEED 0
/*
     WIFI Credentials. Either use a static library, or enter the details below.
*/
//#include <wifi_credentials.h>
#define WIFI_SSID                  "MinhHung-Mesh"
#define WIFI_PASS                  "@nmhung1993"

/*
     Blynk Auth Code
*/
#define AUTH_SW_BREAKER_COUNTER     "rszqM5PivFk-DBiB4MjVVR4UPyz75ZXx"

/*
   Over The Air Hostname
*/
#define OTA_HOSTNAME                "MinhHung-SwBreaker-OTA"

/*
   Local Server Settings (uncomment to use local server)
*/
//#define LOCAL_SERVER                IPAddress(192, 168, 4, 2)

/*
   Modules
*/
#define SW_BREAKER_01
#define SW_BREAKER_02
#define SW_BREAKER_03
/*
   Hardware Pins
*/
#ifdef SW_BREAKER_01
#define PIN_BREAKER_01              5  //DPIO05 D1  SCL
#endif
#ifdef SW_BREAKER_02
#define PIN_BREAKER_02              4  //DPIO04 D2  SDA
#endif
#ifdef SW_BREAKER_03
#define PIN_BREAKER_03              0  //DPIO00 D3  FLASH
#endif
             
#define PIN_RELAY_01                3  //DPIO02 D4  TXD1

#define PIN_L298N_IN1               14 //DPIO14 D5  SCLK
#define PIN_L298N_IN2               12 //DPIO12 D6  MISO
#define PIN_L298N_IN3               13 //DPIO13 D7  MOSI  RXD2
#define PIN_L298N_IN4               15 //DPIO15 D8  CS    TXD2

#define PIN_SWITCH_01               9  //DPIO09 SD2 SDD2
#define PIN_SWITCH_02               10 //DPIO10 SD3 SDD3
/*
   Address EEPROM
*/
#define ADR_BREAKER_01_CUR_COUNTER  0
#define ADR_BREAKER_01_TARGET       4
#define ADR_BREAKER_01_SET_SPEED    8
#define ADR_BREAKER_01_BPM_SPEED    12
#define ADR_BREAKER_01_HRS_LEFT     16

#define ADR_BREAKER_02_CUR_COUNTER  20
#define ADR_BREAKER_02_TARGET       24
#define ADR_BREAKER_02_SET_SPEED    28
#define ADR_BREAKER_02_BPM_SPEED    32
#define ADR_BREAKER_02_HRS_LEFT     36

#define ADR_BREAKER_03_CUR_COUNTER  40
#define ADR_BREAKER_03_TARGET       44
#define ADR_BREAKER_03_SET_SPEED    48
#define ADR_BREAKER_03_BPM_SPEED    52
#define ADR_BREAKER_03_HRS_LEFT     56
/*
   Virtual Pins
*/
#define vPIN_BREAKER_01_TARGET      V0
#define vPIN_BREAKER_01_CUR_COUNTER V1
#define vPIN_BREAKER_01_SET_SPEED   V2
#define vPIN_BREAKER_01_CUR_SPEED   V3
#define vPIN_BREAKER_01_HRS_REMAIN  V4
#define vPIN_BREAKER_01_RELAY_01    V5
#define vPIN_BREAKER_01_HOLD1       V6
#define vPIN_BREAKER_01_HOLD2       V7
#define vPIN_BREAKER_01_HOLD3       V8
#define vPIN_BREAKER_01_CLEAR       V9

#define vPIN_BREAKER_02_TARGET      V10
#define vPIN_BREAKER_02_CUR_COUNTER V11
#define vPIN_BREAKER_02_SET_SPEED   V12
#define vPIN_BREAKER_02_CUR_SPEED   V13
#define vPIN_BREAKER_02_HRS_REMAIN  V14
#define vPIN_BREAKER_02_HOLD1       V15
#define vPIN_BREAKER_02_HOLD2       V16
#define vPIN_BREAKER_02_HOLD3       V17
#define vPIN_BREAKER_02_HOLD4       V18
#define vPIN_BREAKER_02_CLEAR       V19

#define vPIN_BREAKER_03_TARGET      V20
#define vPIN_BREAKER_03_CUR_COUNTER V21
#define vPIN_BREAKER_03_SET_SPEED   V22
#define vPIN_BREAKER_03_CUR_SPEED   V23
#define vPIN_BREAKER_03_HRS_REMAIN  V24
#define vPIN_BREAKER_03_HOLD1       V25
#define vPIN_BREAKER_03_HOLD2       V26
#define vPIN_BREAKER_03_HOLD3       V27
#define vPIN_BREAKER_03_HOLD4       V28
#define vPIN_BREAKER_03_CLEAR       V29
/*
   Local Variables
*/
byte          SwBreaker_01_Prev = HIGH, SwBreaker_02_Prev = HIGH, SwBreaker_03_Prev = HIGH;
int           SwBreaker_01_Cur, SwBreaker_02_Cur, SwBreaker_03_Cur, SwBreaker_01_BPM, SwBreaker_02_BPM, SwBreaker_03_BPM;
long          SwBreaker_01_Counter = 0, SwBreaker_01_Last_Value = 0, SwBreaker_01_Counter_Left = 0, SwBreaker_01_Hours_Left = 0, SwBreaker_01_Target = 1000000,
              SwBreaker_02_Counter = 0, SwBreaker_02_Last_Value = 0, SwBreaker_02_Counter_Left = 0, SwBreaker_02_Hours_Left = 0, SwBreaker_02_Target = 1000000,
              SwBreaker_03_Counter = 0, SwBreaker_03_Last_Value = 0, SwBreaker_03_Counter_Left = 0, SwBreaker_03_Hours_Left = 0, SwBreaker_03_Target = 1000000;
char          buf[32];
