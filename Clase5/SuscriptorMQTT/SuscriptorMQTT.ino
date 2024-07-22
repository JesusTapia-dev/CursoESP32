#include <WiFi.h>
#include <PubSubClient.h>
#include <math.h>

const char *ssid = "DESKTOP";
const char *password = "12345678";
const char *mqtt_server = "192.168.1.35";
const int mqtt_port = 1883;
const char *mqtt_client_id = "ESP32_Client";
const char *subscribe_topic = "cursoTest/control";
const char *publish_respuesta_topic="cursoTest/result";
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Conectado a la red WiFi");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
}
void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Mensaje recibido en el tópico: ");
  Serial.println(topic);
  // Convierte el payload a una cadena de caracteres
  char receivedValue[length + 1];
  strncpy(receivedValue, (char *)payload, length);
  receivedValue[length] = '\0';
  // Convierte la cadena a un número (en este caso, asume que es un float)
  float valorfloat = atof(receivedValue);
  float control=valorfloat*valorfloat; 
  // Publica el resultado en el tópico cursoTest/result"
  char result[10];
  snprintf(result, sizeof(result), "%.2f", control);
  client.publish(publish_respuesta_topic, result);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando conexión MQTT...");

    if (client.connect(mqtt_client_id)) {
      Serial.println("Conectado al servidor MQTT");
      client.subscribe(subscribe_topic);
    } else {
      Serial.print("Falló, rc=");
      Serial.print(client.state());
      Serial.println(" Intentando de nuevo en 5 segundos");
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
