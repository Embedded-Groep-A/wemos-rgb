#include <Arduino.h>
#include <ESP8266WiFi.h>

const char* ssid = "NSELab";
const char* password = "NSELabWiFi";
const char* hostname = "rpibentree.local";
IPAddress serverip;
const int port = 8069;

WiFiClient client;

#define LED_R D5
#define LED_G D6
#define LED_B D7

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi.");
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(WiFi.localIP());

  WiFi.hostByName(hostname, serverip);

  if (client.connect(serverip, port)) {
    Serial.println("Connected to server on port " + String(port));
  }
  client.println("je moeder ik ben wemos-rgb");

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
}

void loop() {
  if (client.connected()) {
    while (client.available()) {
      String line = client.readStringUntil('\n');
      Serial.println(line);

      if (line == "R") {
        digitalWrite(LED_R, HIGH);
        digitalWrite(LED_G, LOW);
        digitalWrite(LED_B, LOW);
        client.println("R Received");
      } else if (line == "G") {
        digitalWrite(LED_R, LOW);
        digitalWrite(LED_G, HIGH);
        digitalWrite(LED_B, LOW);
        client.println("G Received");
      } else if (line == "B") {
        digitalWrite(LED_R, LOW);
        digitalWrite(LED_G, LOW);
        digitalWrite(LED_B, HIGH);
        client.println("B Received");
      } else if (line == "off") {
        digitalWrite(LED_R, LOW);
        digitalWrite(LED_G, LOW);
        digitalWrite(LED_B, LOW);
        client.println("off Received");
      }
    }
  }

}
