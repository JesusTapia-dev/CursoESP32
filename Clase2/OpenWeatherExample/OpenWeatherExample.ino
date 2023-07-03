#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Arduino_JSON.h>

const char* ssid="DESKTOP";
const char* password="12345678";
//Ponemos nuestra API KEY y los datos de la ciudad
String openWeatherMapApiKey ="31ad1df817a08cfd6464305deb33fcf0";
//los codigos son segun la ISO
String city = "Porto";
String countryCode = "PT";
String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&APPID=" + openWeatherMapApiKey;

unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 10 seconds (10000)
unsigned long timerDelay = 10000;
String jsonBuffer;

void setup() {
   Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Conectandose");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("La dirección IP local es:");
  Serial.println(WiFi.localIP());
  Serial.println("Van a pasar 10 segundos antes de mostrar la primera lectura");

}

void loop() {
// Send an HTTP GET request
  if ((millis() - lastTime) > timerDelay) {
    // Nos aseguramos que la conexión de internet sea buena
    if(WiFi.status()== WL_CONNECTED){      
      jsonBuffer = httpGETRequest(serverPath.c_str());
      Serial.println(jsonBuffer);
      JSONVar myObject = JSON.parse(jsonBuffer);
      // JSON.typeof(jsonVar) can be used to get the type of the var
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
      Serial.print("JSON object = ");
      Serial.println(myObject);
      Serial.print("Temperatura: ");
      int temperatura=myObject["main"]["temp"];
      temperatura=temperatura-273;
      Serial.println(temperatura);
      Serial.print("Presión: ");
      Serial.println(myObject["main"]["pressure"]);
      Serial.print("Humedad: ");
      Serial.println(myObject["main"]["humidity"]);
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

String httpGETRequest(const char* serverName) {
  HTTPClient http;
  WiFiClient  client;  
  // Your Domain name with URL path or IP address with path
  http.begin(client,serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
