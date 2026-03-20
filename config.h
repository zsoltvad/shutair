#ifndef CONFIG_H
#define CONFIG_H

#include "../controller.h"
#include "../wifi-config.h"

/* ======== LOCAL CONFIGURATION ======== */
/* WARNING: This file contains sensitive data and should never be committed to version control */

// Authentication PIN
const String AUTH_PIN = "210201";

// WiFi Configuration
const WiFiConfig WIFI_CONFIG = {
  .ssid = "HUAWEI-B535-0052",
  .password = "DML7YLEREA5"
};

// Controller Configuration
const Controller CONTROLLER_CONFIG = {
  .transmitterPin = 4, // D2
  .buckets = { 366, 736, 1600, 5204, 10896 },
  .id = 108289123
};

// Server Configuration
const int SERVER_PORT = 8181;

/* ======== END OF LOCAL CONFIGURATION ======== */

#endif
