/*
  Board Versions
    Arduino AVR - 1.8.6
    Arduino ESP32 Boards - 2.0.13
    esp32 - 2.011
  
  Libraries used
  - ESPAsyncWebServer by ESP32ASync 3.7.10
  - AsyncTCP 1.1.4
*/

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "ESP32 Vibration Sense";
const char* password = "12345678";
const IPAddress localIP(192, 168, 4, 1);
const IPAddress gateway(192, 168, 4, 1);
const IPAddress subnet(255, 255, 255, 0);

const uint16_t PRINT_BUFFER_SIZE = 2000;
const uint8_t LED_PIN = 2;

AsyncWebServer espWebServer(80);

String linkedClientIP;

bool clientIsLinked = false;

// Mutex for critical section
portMUX_TYPE dataMutex = portMUX_INITIALIZER_UNLOCKED;

char printBuffer[PRINT_BUFFER_SIZE];

void setup() 
{
  Serial.begin(921600);
  
  // Delay for Serial to Initailize
  delay(1000);
  
  // Indent new line for printing
  Serial.println("");

  initializeGpioPins();

  initializeWifiAp();

  initializeAsyncWebServer();

  // Set onboard LED high
  digitalWrite(LED_PIN, HIGH);

  printToSerial("Main Program Running!\n");
}

void loop() 
{

}

void initializeGpioPins()
{
  pinMode(LED_PIN, OUTPUT);
}

void initializeWifiAp()
{
  // Set network configurations
  WiFi.softAPConfig(localIP, gateway, subnet);

  // Set Wi-Fi mode to Access Point
  WiFi.softAP(ssid, password);

  // Print the IP address of the ESP32
  IPAddress IP = WiFi.softAPIP();
  printToSerial("Wifi Access Point Started. ESP32 IP Address: %s\n", IP.toString().c_str());
}

void initializeAsyncWebServer()
{
  espWebServer.on("/", HTTP_GET, handleConnectRequest);
  espWebServer.on("/data", HTTP_GET, handleDataRequest);
  espWebServer.begin();
}

void handleConnectRequest(AsyncWebServerRequest *request)
{
  portENTER_CRITICAL(&dataMutex);
  String requestClientIP = request->client()->remoteIP().toString();
  portEXIT_CRITICAL(&dataMutex);

  printToSerial("Link requested from IP Address: %s\n", requestClientIP.c_str());

  if(!clientIsLinked)
  {
    clientIsLinked = true;
    linkedClientIP = requestClientIP;
    printToSerial("Client IP: %s is linked to server!\n", linkedClientIP.c_str());
  }
  else
  {
    printToSerial("Link request denied, a client has already been linked.\n");
  }

  String response = "Connection to Server Initialized!";
  request->send(200, "text/plain", response);
}

void handleDataRequest(AsyncWebServerRequest *request)
{
  portENTER_CRITICAL(&dataMutex);

  portEXIT_CRITICAL(&dataMutex);

  String response = "Data!";
  request->send(200, "text/plain", response);
}

void printToSerial(const char *fmt, ...) 
{
  va_list args;
  va_start(args, fmt);
  vsnprintf(printBuffer, PRINT_BUFFER_SIZE, fmt, args);
  va_end(args);

  Serial.print(printBuffer);
}
