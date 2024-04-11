#include <WiFi.h>
#include <HTTPClient.h>

// Sustituir por los datos de vuestro WiFi
const char* ssid="DESKTOP";
const char* password="12345678";
String start="http://jsonplaceholder.typicode.com/comments?";
String id = "id=1";
String url=start+id;

void setup()
{
  Serial.begin(115200);
  delay(10);

  // Conectar WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
    delay(500);
}

void loop()
{
  HTTPClient http;
  WiFiClient client;

  if (http.begin(client, url)) //Iniciar conexión
  {
    Serial.print("[HTTP] GET...\n");
    int httpCode = http.GET();  // Realizar petición

    if (httpCode > 0) {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();  // Obtener respuesta
        Serial.println(payload);  // Mostrar respuesta por serial
      }
    }
    else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }
  else {
    Serial.printf("[HTTP} Unable to connect\n");
  }

  delay(30000);
}