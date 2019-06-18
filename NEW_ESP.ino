#include "core_header.h"

void setup() {
  serialSetup(); // begin serial communication
  espSetup(); // setup esp8266
  connectToWifi(); // connect to network
}

