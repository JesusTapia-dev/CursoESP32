## API REST 

Una API REST (Representational State Transfer) es un conjunto de normas que permiten que los sistemas se comuniquen entre sí utilizando el protocolo HTTP. En el contexto de IoT, una API REST puede ser utilizada para permitir que un dispositivo como una ESP32 interactúe con otros dispositivos o servicios en la red.

Los datos suelen ser intercambiados en formatos como JSON o XML.

Algunos ejemplos de cómo se puede utilizar una API REST en un proyecto con ESP32:

- Recopilación de Datos de Sensores: La ESP32 puede leer datos de varios sensores (temperatura, humedad, etc.) y enviar estos datos a un servidor remoto utilizando solicitudes HTTP POST a una API REST.

- Control Remoto: A través de una API REST, se pueden enviar comandos a la ESP32 para controlar actuadores conectados a ella (como luces, motores, etc.) utilizando solicitudes HTTP PUT o POST.

- Monitorización y Notificaciones: La ESP32 puede utilizar una API REST para enviar notificaciones sobre el estado del dispositivo o alertas a un servidor, que luego puede procesar y enviar notificaciones al usuario.

## Websockets

WebSockets es un protocolo de comunicación bidireccional de baja latencia entre un navegador web y un servidor.  Permite la comunicación en tiempo real entre el cliente y el servidor, lo que significa que tanto el cliente como el servidor pueden enviar mensajes en cualquier momento. 

Se establece una conexión persistente entre el cliente y el servidor, lo que permite la transmisión de datos sin la sobrecarga de las solicitudes HTTP tradicionales. 

