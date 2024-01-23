#include "DFRobot_BloodOxygen_S.h"
#include <Wire.h>
#include <SPI.h>
#include <WiFiNINA.h>

// WiFi Credentials
char ssid[] = "NUMERICABLE-D879";      // WiFi SSID
char pass[] = "bjflsyjr";              // WiFi password

int status = WL_IDLE_STATUS;

DFRobot_BloodOxygen_S_I2C MAX30102(&Wire, 0x57);
WiFiServer server(80);

void connectToAP() {
    Serial.print("Connecting to ");
    Serial.println(ssid);

    // 尝试连接到 WiFi 网络
    status = WiFi.begin(ssid, pass);

    // 等待连接结果
    while (status != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        status = WiFi.status(); // 更新 WiFi 连接状态
    }

    Serial.println("Connected to WiFi");
    printWifiStatus();
}

void printWifiStatus() {
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    long rssi = WiFi.RSSI();
    Serial.print("Signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}

void setup() {
    Serial.begin(19200);

    // 等待串口连接
    while (!Serial);

    if (!WiFi.status() == WL_NO_MODULE) {
        Serial.println("Communication with WiFi module failed!");
        while (true);
    }

    String fv = WiFi.firmwareVersion();
    if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
        Serial.println("Please upgrade the firmware");
    }

    // 初始化传感器
    while (!MAX30102.begin()) {
        Serial.println("init fail!");
        delay(1000);
    }
    Serial.println("init success!");
    MAX30102.sensorStartCollect();

    // 连接到 WiFi
    connectToAP();

    // 启动服务器
    server.begin();
}

void loop() {
    WiFiClient client = server.available();
    if (client) {
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                if (c == '\n' && currentLineIsBlank) {
                    MAX30102.getHeartbeatSPO2();
                    float spo2 = MAX30102._sHeartbeatSPO2.SPO2;
                    float heartRate = MAX30102._sHeartbeatSPO2.Heartbeat;
                    float temperature = MAX30102.getTemperature_C();

                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close");
                    client.println();
                    client.println("<!DOCTYPE HTML>");
                    client.println("<html>");
                    client.println("<head>");
                    client.println("  <style>");
                    client.println("    body {font-family: 'Arial', sans-serif; text-align: center; background-color: #f8f0e6; margin: 0; padding: 0; color: #020BA4;}");
                    client.println("    h2 {margin-bottom: 30px;}");
                    client.println("    p {color: #4D6080; font-size: 18px;}");
                    client.println("    table {margin: auto; border-collapse: collapse; width: 80%; margin-top: 30px;}");
                    client.println("    th, td {border: 1px solid #ddd; padding: 15px; text-align: left; font-size: 16px;}");
                    client.println("    tr:nth-child(even) {background-color: #f2f2f2;}");
                    client.println("    th {padding-top: 15px; padding-bottom: 15px; background-color: #4D6080; color: white; font-size: 18px;}");
                    client.println("    p.slogan {margin-top: 30px; font-style: italic; color: #020BA4;}");
                    client.println("  </style>");
                    client.println("</head>");
                    client.println("<body>");
                    client.println("  <h2>Moniteur de Santé IoT Nano 33</h2>");
                    client.println("  <p>Projet de Microcontrôleurs et leurs environnements</p>");
                    client.println("  <p>Ecole Centrale Méditerranée</p>");
                    client.println("  <table>");
                    client.println("    <tr><th>Mesure</th><th>Valeur</th></tr>");
                    client.println("    <tr><td>Fréquence Cardiaque</td><td>" + String(heartRate) + " BPM</td></tr>");
                    client.println("    <tr><td>SpO2</td><td>" + String(spo2) + "%</td></tr>");
                    client.println("    <tr><td>Température</td><td>" + String(temperature) + " C</td></tr>");
                    client.println("  </table>");
                    client.println("  <p class='slogan'>Sécurité maximale, performances optimales : Vivez le sport en toute confiance !</p>");
                    client.println("</body></html>");
                    break;
                }
                if (c == '\n') {
                    currentLineIsBlank = true;
                } else if (c != '\r') {
                    currentLineIsBlank = false;
                }
            }
        }
        delay(1);
        client.stop();
    }
}
