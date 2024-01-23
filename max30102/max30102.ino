/*!
 * @file  gainHeartbeatSPO2.ino
 * @n experiment phenomena: get the heart rate and blood oxygenation, during the update the data obtained does not change
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      PengKaixing(kaixing.peng@dfrobot.com)
 * @version     V1.0.0
 * @date        2021-06-21
 * @url         https://github.com/DFRobot/DFRobot_BloodOxygen_S
 */
#include "DFRobot_BloodOxygen_S.h"

#define I2C_COMMUNICATION  //use I2C for communication, but use the serial port for communication if the line of codes were masked

#ifdef  I2C_COMMUNICATION
#define I2C_ADDRESS    0x57
  DFRobot_BloodOxygen_S_I2C MAX30102(&Wire ,I2C_ADDRESS);
#else
// [Serial communication configuration based on board type...]
#endif

void setup()
{
  Serial.begin(19200);
  while (false == MAX30102.begin())
  {
    Serial.println("init fail!");
    delay(1000);
  }
  Serial.println("init success!");
  Serial.println("start measuring...");
  MAX30102.sensorStartCollect();
}

void loop()
{
  MAX30102.getHeartbeatSPO2();
  
  // Check if the readings are valid
  if (MAX30102._sHeartbeatSPO2.SPO2 != -1 && MAX30102._sHeartbeatSPO2.Heartbeat != -1)
  {
    // Printing SpO2
    Serial.print("SpO2: ");
    Serial.print(MAX30102._sHeartbeatSPO2.SPO2);
    Serial.println("%");

    // Printing Heartbeat
    Serial.print("Heart Rate: ");
    Serial.print(MAX30102._sHeartbeatSPO2.Heartbeat);
    Serial.println(" BPM");

    // Printing Temperature
    Serial.print("Temperature: ");
    Serial.print(MAX30102.getTemperature_C());
    Serial.println(" °C");
  }
  else
  {
    Serial.println("Invalid reading");
  }
  
  // The sensor updates the data every 4 seconds
  delay(1000);
}
