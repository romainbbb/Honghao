#include "DFRobot_BloodOxygen_S.h"
#include <Wire.h>
#include "rgb_lcd.h"


#define I2C_COMMUNICATION  //use I2C for communication


#ifdef I2C_COMMUNICATION
#define I2C_ADDRESS    0x57
DFRobot_BloodOxygen_S_I2C MAX30102(&Wire, I2C_ADDRESS);
#else
#if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
SoftwareSerial mySerial(4, 5);
DFRobot_BloodOxygen_S_SoftWareUart MAX30102(&mySerial, 9600);
#else
DFRobot_BloodOxygen_S_HardWareUart MAX30102(&Serial1, 9600);
#endif
#endif


rgb_lcd lcd;


void setup() {
  // Initialize Serial
  Serial.begin(19200);
  while (false == MAX30102.begin()) {
    Serial.println("init fail!");
    delay(1000);
  }
  Serial.println("init success!");
  Serial.println("start measuring...");
  MAX30102.sensorStartCollect();


  // Initialize the LCD
  lcd.begin(16, 2);
}




void loop() {
  MAX30102.getHeartbeatSPO2();
  float spo2 = MAX30102._sHeartbeatSPO2.SPO2;
  float heartRate = MAX30102._sHeartbeatSPO2.Heartbeat;
  float temperature = MAX30102.getTemperature_C();


  // Display SpO2
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SpO2: ");
  lcd.print(spo2);
  lcd.print("%");
  // Display Heart Rate on the second line
  lcd.setCursor(0, 1);
  lcd.print("HR: ");
  lcd.print(heartRate);
  lcd.print(" BPM");
  delay(2000); // Display for 2 seconds


  // Clear and Display Temperature
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");
  delay(2000); // Display for 2 seconds
}
