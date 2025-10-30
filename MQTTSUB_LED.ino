#include <WiFi.h>
#include <PubSubClient.h>

#define LED_PIN 4  // Définition de la broche GPIO4

// ⚙️ Paramètres Wi-Fi
const char* ssid = "TP-Link_02D9";        // Wi-Fi LAN
const char* password = "47240308";

// ⚙️ Paramètres MQTT
const char* mqtt_server = "192.168.1.104";  // IP du Raspberry Pi (broker)
const int mqtt_port = 1883;
const char* mqtt_topic = "test/topic";

// Objets Wi-Fi et MQTT
WiFiClient espClient;
PubSubClient client(espClient);

void led(const char* message) {
  pinMode(LED_PIN, OUTPUT);  // Configurer la broche en sortie
  if (strcmp(message, "1") ==  0) {
    digitalWrite(LED_PIN, HIGH); // Allumer la LED
  } else {
    if (strcmp(message, "0") ==  0) {
      digitalWrite(LED_PIN, LOW); // Eteindre la LED
      }
  }
}

// Fonction appelée à la réception d'un message
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message reçu sur topic: ");
  Serial.println(topic);

  // Copier le payload dans une chaîne de caractères
  char message[length + 1];
  for (unsigned int i = 0; i < length; i++) {
    message[i] = (char)payload[i];
  }
  message[length] = '\0';

  Serial.print("Contenu du message: ");
  Serial.println(message);
  led(message);
}

// Connexion au Wi-Fi
void setup_wifi() {
  delay(10);
  Serial.println("Connexion au Wi-Fi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnecté au Wi-Fi !");
}

// Reconnexion au broker MQTT si nécessaire
void reconnect() {
  while (!client.connected()) {
    Serial.print("Connexion au broker MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("connecté !");
      client.subscribe(mqtt_topic);  // s'abonner au topic
    } else {
      Serial.print("Échec, rc=");
      Serial.print(client.state());
      Serial.println(" nouvelle tentative dans 5 secondes...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
