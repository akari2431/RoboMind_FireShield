#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebSrv.h>
#include <WebSocketsServer.h>
#include <AsyncEventSource.h>

///sensor de flama
int flama1=34;
int tierra1=35;

int a,b,c,d,f;


const uint16_t dataTxTimeInterval = 500; // ms
html
const char* ssid = "UTMA-STAFF";
const char* password = "ST2022#utma";

AsyncWebServer server(80);
WebSocketsServer websockets(81);

void setup() {
 Serial.begin(115200);


    if (!SPIFFS.begin(true))
    {
        Serial.println("Error al montar SPIFFS!");
        return;        
    }

  WiFi.softAP("fireshield","");
  Serial.println("\nsoftAP");
  Serial.println(WiFi.softAPIP());  
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
  delay(1000);
  Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/page.html", "text/html"); });
 

    server.onNotFound(notFound);

    server.begin();
    websockets.begin();
    websockets.onEvent(webSocketEvent);
}

void loop() 
{
  websockets.loop();
  flama();
  tierra();

    static uint32_t prevMillis = 0;
    if (millis() - prevMillis >= dataTxTimeInterval)
    {
        prevMillis = millis();
        float fuego = a;
        String data = "{\"Fuego\": " + String(fuego) + "}";
        websockets.broadcastTXT(data);
        Serial.println(data);
        delay(10);
        float thumedad = b;
        String data2 = "{\"THumedad\": " + String(thumedad) + "}";
        websockets.broadcastTXT(data2);
        Serial.println(data2);
    }
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{
    switch (type)
    {
    case WStype_DISCONNECTED:
        Serial.printf("[%u] Desconectado!\n", num);
        break;
    case WStype_CONNECTED:
    {
        IPAddress ip = websockets.remoteIP(num);
        Serial.printf("[%u] Conectado en %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

        websockets.sendTXT(num, "Conectado en servidor:");
    }
    break;
}

void notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "¡Página no encontrada!");
}

void flama()
{
  a=analogRead(flama1);
  delay(200);
  a=map(a,0,1023,0,100);
}

void tierra()
{
  b=analogRead(tiera1);
  delay(200);
  b=map(b,0,1023,0,100);
}


