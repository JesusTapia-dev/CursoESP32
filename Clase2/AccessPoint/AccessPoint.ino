#include <ESP8266WiFi.h>
// Ponemos las credenciales de la red WIFI
const char* ssid="DESKTOP";
const char* password="12345678";
byte max_intentos=50;
byte cont=0;
void setup(){
  //Iniciamos la comunicacion serial
  Serial.begin(115200);
  Serial.println("\n");
  //Nos conectamos a internet
  WiFi.mode(WIFI_AP);
  WiFi.begin(ssid,password);
  while(WiFi.status()!= WL_CONNECTED and cont<max_intentos){
    delay(50);
    Serial.print(".");
    cont=cont+1;
    }
    Serial.println("");
    Serial.println("**************************************");
    Serial.print("Conectado a la red WiFi: ");
    Serial.println(WiFi.SSID());

    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    Serial.print("macAdress: ");
    Serial.println(WiFi.macAddress());
    Serial.println("**************************************"); 
  }

  void loop(){
    }
