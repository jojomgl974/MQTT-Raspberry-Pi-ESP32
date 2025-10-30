# Transmission Température & Humidité depuis ESP32 vers Raspberry Pi puis affichage des valeurs sur Afficheur LCD

# Matériel
- Raspberry Pi
- ESP32
- Borne Wi-Fi
- Ordinateur
- DHT22
- Afficheur LCD 1602

# Installation du matériel
- Connecter l'Afficheur LCD 1602 à la Raspberry Pi
- Connecter le DHT22 à l'ESP32

# Déroulement de l'expérience
- Programmer l'envoi des températures et humidités avec l'environnement Arduino sur l'ordinateur
- Programmer la réception et l'affichage des températures et humidités avec IDE Python sur Raspberry Pi

# Installation d'un serveur MQTT dans le terminal d'un Raspberry Pi sur Raspberry Pi
`sudo apt update && sudo apt upgrade`

`sudo apt-get install mosquitto mosquitto-clients`
