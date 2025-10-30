#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include "DHT.h"

#define DHTPIN 5        // GPIO utilisé pour le DATA du DHT22
#define DHTTYPE DHT22   // Type de capteur

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "TP-Link_02D9";        // Wi-Fi LAN
const char* password = "47240308";
const char* mqtt_server = "192.168.1.104";  // IP du Raspberry Pi (broker)

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  client.setServer(mqtt_server, 1883);
  Serial.begin(115200);
  dht.begin();
}

void loop() {
   // Lecture de la température et de l’humidité
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Celsius
  // float f = dht.readTemperature(true); // Fahrenheit

  // Vérifier si la lecture a échoué
  if (isnan(h) || isnan(t)) {
    Serial.println("Échec de lecture du capteur !");
    return;
  }
  StaticJsonDocument<200> doc;

  doc["temperature"] = t;
  doc["humidite"] = h;
  char buffer[256];
  serializeJson(doc, buffer);

  if (client.connect("ESP32Publisher")) {
    client.publish("maison/salon/temperature", String(buffer).c_str());
  }

  // Affichage
  Serial.println(buffer);

  delay(2000); // Lecture toutes les 2 secondes
  }
