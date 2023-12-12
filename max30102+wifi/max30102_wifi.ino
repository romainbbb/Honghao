#include "DFRobot_BloodOxygen_S.h"
#include <Wire.h>
#include <SPI.h>
#include <WiFiNINA.h>


// WiFi Credentials
char ssid[] = "your";      // Wifi SSID
char pass[] = "your";  // Wifi password


int status = WL_IDLE_STATUS;


DFRobot_BloodOxygen_S_I2C MAX30102(&Wire, 0x57);
WiFiServer server(80);


void connectToAP() {
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);
        status = WiFi.begin(ssid, pass);
        delay(1000);
    }
    Serial.println("Connected...");
}


void printWifiStatus() {
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);
}


void setup() {
    Serial.begin(19200);
    while (!MAX30102.begin()) {
        Serial.println("init fail!");
        delay(1000);
    }
    Serial.println("init success!");
    MAX30102.sensorStartCollect();


    connectToAP();
    printWifiStatus();


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


                    Serial.print("SpO2: ");
                    Serial.print(spo2);
                    Serial.println("%");
                    Serial.print("Heart Rate: ");
                    Serial.print(heartRate);
                    Serial.println(" BPM");
                    Serial.print("Temperature: ");
                    Serial.print(temperature);
                    Serial.println(" C");


                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close");
                    client.println();
                    client.println("<!DOCTYPE HTML>");
                    client.println("<html>");
                    client.println("<body>");
                    client.println("<h2>Nano 33 IoT Health Monitor</h2>");
                    client.print("SpO2: ");
                    client.print(spo2);
                    client.println("%<br>");
                    client.print("Heart Rate: ");
                    client.print(heartRate);
                    client.println(" BPM<br>");
                    client.print("Temperature: ");
                    client.print(temperature);
                    client.println(" C<br>");
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
