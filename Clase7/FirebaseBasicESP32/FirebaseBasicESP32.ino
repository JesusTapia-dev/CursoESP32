#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>

#include <FirebaseClient.h>
#include <WiFiClientSecure.h>

#define WIFI_SSID "DESKTOP"
#define WIFI_PASSWORD "12345678"

#define DATABASE_URL "https://curso-esp32-db-default-rtdb.firebaseio.com/"

WiFiClientSecure ssl;
DefaultNetwork network;
AsyncClientClass client(ssl, getNetwork(network));

FirebaseApp app;
RealtimeDatabase Database;
AsyncResult result;
NoAuth noAuth;
unsigned long sendDataPrevMillis = 0;
int count = 0;

void InitOTA(){
// Port defaults to 8266
// ArduinoOTA.setPort(8266);

// Hostname defaults to esp8266-[ChipID]
// ArduinoOTA.setHostname(hostname);

// No authentication by default
  ArduinoOTA.setPassword("admin");

// Password can be set with it's md5 value as well
// MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
// ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
  String type;
  if (ArduinoOTA.getCommand() == U_FLASH) {
    type = "sketch";
  } else { // U_SPIFFS
    type = "filesystem";
  }

  // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
  Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
  }
  });

  ArduinoOTA.begin();
  Serial.println("");
  Serial.println("OTA iniciado");
  }
void printError(int code, const String &msg)
{
    Firebase.printf("Error, msg: %s, code: %d\n", msg.c_str(), code);
}

void setup()
{

    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
    InitOTA();
    Firebase.printf("Firebase Client v%s\n", FIREBASE_CLIENT_VERSION);

    ssl.setInsecure();

    // Initialize the authentication handler.
    initializeApp(client, app, getAuth(noAuth));

    // Binding the authentication handler with your Database class object.
    app.getApp<RealtimeDatabase>(Database);

    // Set your database URL
    Database.url(DATABASE_URL);

    // In sync functions, we have to set the operating result for the client that works with the function.
    client.setAsyncResult(result);
    Serial.print("Push int... ");
    String name = Database.push<int>(client, "/test/push", 1234);
    if (client.lastError().code() == 0)
        Firebase.printf("ok, name: %s\n", name.c_str());
    else
        printError(client.lastError().code(), client.lastError().message());
//Push test/int
  Serial.print("Push str... ");
  Database.push<String>(client, "/test/str","a" );
  Database.push<String>(client, "/test/str","b" );
  Database.push<String>(client, "/test/str","c" );
  String valuetopush = Database.get<String>(client, "/test/str");
  delay(30000);
  Database.set<String>(client, "/test/str","d" );
}


void loop(){

   ArduinoOTA.handle();
  if((millis()-sendDataPrevMillis)>10000 || sendDataPrevMillis==0){
    sendDataPrevMillis = millis();
    int randomNumber = random(1,10);
    bool status = Database.set<int>(client, "/test/int", randomNumber);
    if (status)
        Serial.println("ok");
    else
        printError(client.lastError().code(), client.lastError().message());
//Leemos el valor random que acabamos de enviar y hacemos push a una nueva cola
    int v1 = Database.get<int>(client, "/test/int");
    Database.push<int>(client, "/test/push", v1);
//Leemos el valor directo de la base de datos y lo mostramos 
    int v2 = Database.get<int>(client, "/test/lectura");
    Database.set<int>(client, "/test/write", v2);

  } 

}

