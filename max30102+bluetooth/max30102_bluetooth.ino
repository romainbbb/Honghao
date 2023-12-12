#include <ArduinoBLE.h>
#include "DFRobot_BloodOxygen_S.h"


// 设置DFRobot血氧传感器
#define I2C_COMMUNICATION
#ifdef I2C_COMMUNICATION
#define I2C_ADDRESS    0x57
DFRobot_BloodOxygen_S_I2C MAX30102(&Wire, I2C_ADDRESS);
#else
// 如果使用的是软件串口或其他通信方式，请在此处定义
#endif


// BLE服务和特征的UUID
const char* healthServiceUUID = "12345678-1234-1234-1234-123456789ABC";
const char* healthCharacteristicUUID = "87654321-4321-4321-4321-ABCDEF987654";


// 创建BLE服务
BLEService healthService(healthServiceUUID);


// 创建BLE特性
BLEStringCharacteristic healthCharacteristic(healthCharacteristicUUID, BLERead | BLENotify, 30); // 最大30字节


void setup() {
  Serial.begin(19200);
  Wire.begin();


  // 初始化血氧传感器
  if (!MAX30102.begin()) {
    Serial.println("Blood oxygen sensor init failed!");
    while (1);
  }
  Serial.println("Blood oxygen sensor init success!");


  // 启动BLE
  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  }


  // 设置BLE设备名称和服务
  BLE.setLocalName("Nano33HealthMonitor");
  BLE.setAdvertisedService(healthService);


  // 添加特征到服务
  healthService.addCharacteristic(healthCharacteristic);


  // 添加服务
  BLE.addService(healthService);


  // 开始广告
  BLE.advertise();


  Serial.println("BLE ready!");
}


void loop() {
  // 监听BLE中心设备的连接
  BLEDevice central = BLE.central();


  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());


    while (central.connected()) {
      // 读取血氧、心跳和温度
      MAX30102.getHeartbeatSPO2();


      // 默认情况下，只发送心率
      //String data = "Heartbeat: " + String(MAX30102._sHeartbeatSPO2.Heartbeat) + "bpm";


      // 取消以下注释以发送血氧饱和度
      // String data = "SPO2: " + String(MAX30102._sHeartbeatSPO2.SPO2) + "%";
     
      // 取消以下注释以发送温度
      String data = "Temp: " + String(MAX30102.getTemperature_C()) + " C";


      // 发送数据到BLE特性
      healthCharacteristic.writeValue(data);


      delay(1000); // 根据需要调整延时
    }


    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}
