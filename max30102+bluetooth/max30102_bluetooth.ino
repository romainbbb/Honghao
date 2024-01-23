#include <ArduinoBLE.h>
#include "DFRobot_BloodOxygen_S.h"

// Configuration du capteur d'oxygène sanguin DFRobot
#define I2C_COMMUNICATION
#ifdef I2C_COMMUNICATION
#define I2C_ADDRESS    0x57
DFRobot_BloodOxygen_S_I2C MAX30102(&Wire, I2C_ADDRESS);
#else
// Si vous utilisez un port série logiciel ou un autre moyen de communication, veuillez le définir ici
#endif

// UUID du service et de la caractéristique BLE
const char* healthServiceUUID = "12345678-1234-1234-1234-123456789ABC";
const char* healthCharacteristicUUID = "87654321-4321-4321-4321-ABCDEF987654";

// Création du service BLE
BLEService healthService(healthServiceUUID);

// Création de la caractéristique BLE
BLEStringCharacteristic healthCharacteristic(healthCharacteristicUUID, BLERead | BLENotify, 60); // Maximum 60 octets

void setup() {
  Serial.begin(19200);
  Wire.begin();

  // Initialisation du capteur d'oxygène sanguin
  if (!MAX30102.begin()) {
    Serial.println("Echec init capteur O2!");
    while (1);
  }
  Serial.println("Capteur O2 ok!");

  // Démarrage du BLE
  if (!BLE.begin()) {
    Serial.println("Echec BLE!");
    while (1);
  }

  // Configuration du nom local du dispositif BLE et du service
  BLE.setLocalName("Nano33HealthMonitor");
  BLE.setAdvertisedService(healthService);

  // Ajout de la caractéristique au service
  healthService.addCharacteristic(healthCharacteristic);

  // Ajout du service
  BLE.addService(healthService);

  // Commencement de la publicité
  BLE.advertise();

  Serial.println("BLE prêt!");
}

void loop() {
  // Écoute des connexions des appareils centraux BLE
  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("Connecté: ");
    Serial.println(central.address());

    while (central.connected()) {
      // Lecture de l'oxygène sanguin, du rythme cardiaque et de la température
      MAX30102.getHeartbeatSPO2();

      // Formatage des données en un seul String
      String data = "HR:" + String(MAX30102._sHeartbeatSPO2.Heartbeat);
      data += ";SPO2:" + String(MAX30102._sHeartbeatSPO2.SPO2);
      data += ";T:" + String(MAX30102.getTemperature_C()) ;

      // Envoi des données à la caractéristique BLE
      healthCharacteristic.writeValue(data);

      delay(1000); // Ajuster le délai selon le besoin
    }

    Serial.print("Déconnecté: ");
    Serial.println(central.address());
  }
}
