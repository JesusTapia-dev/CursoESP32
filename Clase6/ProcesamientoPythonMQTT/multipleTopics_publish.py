import paho.mqtt.client as mqtt
import time

# Variables para la dirección del broker y los tópicos
broker_address = "192.168.1.35"
topic1 = "Ambiente/temperatura"
topic2 = "Ambiente/humedad"
topicPublish="Alerta"
# Definir las funciones de callback
def on_connect(client, userdata, flags, rc):
    print(f"Conectado con código de resultado {rc}")
    # Suscribirse a los tópicos
    client.subscribe(topic1)
    client.subscribe(topic2)

def on_message_topico1(client, userdata, msg):
    print(f"Mensaje recibido en {topic1}: {msg.payload.decode()}")
    mensaje = float(msg.payload.decode())
    # Realizar alguna acción basada en el mensaje recibido en topic1
    if mensaje > 32:
        print("Temperatura demasiado alta")
        client.publish(topicPublish,"1")
    if mensaje<10:
        print("temperatura muy baja")
        client.publish(topicPublish,"2")
        
def on_message_topico2(client, userdata, msg):
    print(f"Mensaje recibido en {topic2}: {msg.payload.decode()}")
    mensaje=float(msg.payload.decode())
    # Realizar alguna acción basada en el mensaje recibido en topic2
    if mensaje>90:
        print("Humedad muy alta")
        client.publish(topicPublish,"3")
    if mensaje<30:
        print("Humedad muy baja")
        client.publish(topicPublish,"4")

# Crear una instancia del cliente MQTT
client = mqtt.Client()

# Asignar las funciones de callback para la conexión
client.on_connect = on_connect

# Asignar las funciones de callback para los mensajes
client.message_callback_add(topic1, on_message_topico1)
client.message_callback_add(topic2, on_message_topico2)

# Conectarse al broker MQTT
client.connect(broker_address, 1883, 60)

# Mantenerse en el loop para recibir mensajes
client.loop_start()
try:
    while True:
        time.sleep(1)
except KeyboardInterrupt:
    print("Programa detenido por el usuario.")
    client.disconnect()
    client.loop_stop()