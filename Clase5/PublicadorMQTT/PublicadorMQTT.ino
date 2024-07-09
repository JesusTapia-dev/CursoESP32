#include <WiFi.h>
#include <PubSubClient.h>
#include <math.h>

const char *ssid = "DESKTOP";
const char *password = "12345678";
const char *mqtt_server = "192.168.1.35";// direccion IP de la computadora donde esta el broker
const int mqtt_port = 1883;
const char *mqtt_client_id = "ESP32_Client";
const char *publish_topic = "cursoTest/aleatorio";

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
void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando conexión MQTT...");

    if (client.connect(mqtt_client_id)) {
      Serial.println("Conectado al servidor MQTT");
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
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  char str[16];
  sprintf(str, "%u", random(100));
  client.publish(publish_topic, str);
  unsigned long startTime=millis();
  while((millis()-startTime)<300);
}
