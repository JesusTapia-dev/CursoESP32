import matplotlib.pyplot as plt
import matplotlib.animation as animation
import paho.mqtt.client as mqtt
import numpy as np


# Configuración del cliente MQTT
mqtt_broker = "localhost"  # Reemplaza con la dirección de tu broker MQTT
mqtt_topic = "mimqtt/test"  # Reemplaza con el tópico MQTT que estás utilizando

# Inicialización de la lista para almacenar los datos
data = []

# Función de inicialización para la gráfica
def init():
    ax.set_ylim(0, 100)  # Ajusta los límites de la gráfica según tus necesidades
    ax.set_xlim(0,30)
    line.set_data([], [])
    return line,

# Función de actualización para la animación
def update(frame):
    y_data = np.array(data)
    x_data = np.arange(len(y_data))
    line.set_data(x_data, y_data)
    return line,

# Configuración del cliente MQTT
def on_connect(client, userdata, flags, rc):
    print("Conectado con el código de resultado: " + str(rc))
    client.subscribe(mqtt_topic)

# Función que se llama cuando llega un nuevo mensaje MQTT
def on_message(client, userdata, msg):
    payload = float(msg.payload)
    print("Nuevo dato recibido: {}".format(payload))
    data.append(payload)

# Configuración del cliente MQTT
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

# Conexión al broker MQTT
client.connect(mqtt_broker, 1883, 60)

# Configuración de la gráfica
fig, ax = plt.subplots()
line, = ax.plot([], [], lw=2)
ax.set_xlabel('Numero de dato')
ax.set_ylabel('Magnitud')
ax.grid(True) 
# Configuración de la animación
ani = animation.FuncAnimation(fig, update, frames=None, init_func=init, blit=True,cache_frame_data=False)

# Arranque del bucle del cliente MQTT
client.loop_start()

# Mostrar la ventana de la gráfica
plt.show()

# Detener el bucle del cliente MQTT al cerrar la ventana de la gráfica
client.loop_stop()
