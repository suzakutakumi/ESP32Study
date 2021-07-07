#include <WiFi.h>
#include <WebServer.h>

const char *ssid = "SUZAKU_PC";
const char *password = "Suzaku2121";

WebServer server(80);
String mes="Test";

void mainPage() {
  String html="<html>"+mes+"</html>";
  server.send(200, "text/html",mes);
}

void PostData() {
  if(server.method()==HTTP_POST){
    mes=server.arg("plain");
  }
  server.send(200, "text/plain", mes);
}

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", mainPage);
  server.on("/post",PostData);
  server.begin();
}

void loop(void) {
  server.handleClient();
}
