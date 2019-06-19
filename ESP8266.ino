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

void sendDataToApi(String data) {
  String getData = "GET /update?api_key=" + API + "&" + field + "=" + data;
  sendATCommand("AT+CIPMUX=0", 5, "OK");
  sendATCommand("AT+CIPSTART=\"TCP\",\"" + HOST + "\"," + PORT, 15, "OK"); // open connection at specified port in single conn mode
  sendATCommand("AT+CIPSEND=" + String(getData.length() + 4), 8, ">");
  esp8266Println(getData); // send the data
  delay(1500);
  countTrueCommand++;
  sendATCommand("AT+CIPCLOSE", 8, "OK"); // close connection
}


void connectToWifi() {
  esp8266.println(F("AT+CIPSTA?")); // get IP address of ESP8266 Station
  delay(1000);
  while (esp8266.available()) {
    String incomingString = esp8266.readString();
    Serial.println(incomingString);

    if (incomingString.indexOf("0.0.0.0") > 1) { // if No IP address
      Serial.println("NO IP ADDRESS");
      String cmdm = F("AT+CWJAP=\""); cmdm += netSSID; cmdm += F("\",\""); cmdm += psk; cmdm += F("\"");
      // esp8266.println(cmdm);
      esp8266Println(cmdm); // connect to network if NO IP Address is Found!
      // sendATCommand("AT+CWJAP=\"" + AP + "\",\"" + PASS + "\"", 20, "OK"); // connect to network if NO IP Address is Found!
    }
    else {
      wifiConnected = true;
    }
  }
}
