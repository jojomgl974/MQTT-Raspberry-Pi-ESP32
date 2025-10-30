import paho.mqtt.client as mqtt
import rgb1602

BROKER_IP = "192.168.1.101"  # Remplace par l'IP de ton Pi sur le LAN
TOPIC = "maison/salon/temperature"       # Le topic auquel tu veux t'abonner

lcd = rgb1602.RGB1602(16,2)

def on_connect(client, userdata, flags, rc):
    print(f"Connecté avec le code de retour {rc}")
    client.subscribe(TOPIC)

def on_message(client, userdata, msg):
    print(f"Message reçu sur {msg.topic}: {msg.payload.decode()}")
    texte = msg.payload.decode()          # Décodage du message en chaîne de caractères
    chiffres = ''.join(c for c in texte if c.isdigit())  # On garde seulement les caractères qui sont des chiffres
    Temp = 'Temp: ' + chiffres[:2] + '.' + chiffres[2:3] + '°C'
    Hum = 'Hum: ' + chiffres[3:5] + '.' + chiffres[5:6] + '%RH'
    print(f"Valeur formatée : {Temp}")
    lcd.setCursor(0, 0)
    lcd.printout(Temp)
    lcd.setCursor(0, 1)
    lcd.printout(Hum)

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(BROKER_IP, 1883, 60)

client.loop_forever()


