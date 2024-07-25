## Protocolo MQTT

MQTT (Message Queuing Telemetry Transport) es un protocolo de mensajería ligera  diseñado para dispositivos con bajo ancho de banda o alta latencia, este es un protocolo usado en el Internet de las Cosas (IoT). Utiliza un modelo de comunicación de publicación/suscripción. En este protocolo, existen tres entidades principales: el broker, los publicadores y los suscriptores.

El broker es un servidor que actúa como intermediario para la distribución de mensajes, 
recibe mensajes de los publicadores y los envía a los suscriptores. Un publicador es un 
cliente que envía datos al broker en cierto tópico y un suscriptor es un cliente que recibe mensajes del broker en función de los tópicos a los que se ha suscrito. 

Una herramienta útil para trabajar es MQTT-Explorer.