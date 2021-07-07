#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

const char* ssid = "SUZAKU_PC";
const char* password = "suzaku1212";

WebServer server(80);

const int led = 13;

void handleRoot() {
  digitalWrite(led, HIGH);
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(led, LOW);
}

void handleNotFound() {
  digitalWrite(led, HIGH);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, LOW);
}

void setup(void) {
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/H", []() {
    digitalWrite(led,HIGH);
    server.send(200, "text/plain", "LED ON");
  });
  server.on("/L", []() {
    digitalWrite(led,LOW);
    server.send(200, "text/plain", "LED OFF");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
