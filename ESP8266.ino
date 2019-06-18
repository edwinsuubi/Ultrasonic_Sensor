#define espRX 3
#define espTX 2

String netSSID = "Alvin";
String psk = "123456789";
String API = "DTH1GUWRS2KSWDQ1";
String HOST = "api.thingspeak.com";
String PORT = "80";
String field = "field1";
int countTrueCommand;
int countTimeCommand;
boolean found = false;
boolean wifiConnected = false;

SoftwareSerial esp8266(espRX, espTX);

void espSetup() {
  esp8266.begin(115200);
  sendATCommand("AT", 5, "OK"); // ping esp8266
  sendATCommand("AT+CWMODE=3", 5, "OK"); // Set WiFi mode of operation -> 3 (AP + STA mode)
}

void testATcommands() { // MUST RUN ESP SETUP
  if (esp8266.available()) {
    Serial.write(esp8266.read());
  }
  if (Serial.available()) {
    esp8266.write(Serial.read());
  }
}

