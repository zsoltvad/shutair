#ifndef CONFIG_EXAMPLE_H
#define CONFIG_EXAMPLE_H

#include "../controller.h"
#include "../wifi-config.h"

/* ======== LOCAL CONFIGURATION TEMPLATE ======== */
/* Copy this file to config.h and update with your local values */

// Authentication PIN
const String AUTH_PIN = "YOUR_PIN_HERE";

// WiFi Configuration
const WiFiConfig WIFI_CONFIG = {
  .ssid = "YOUR_SSID_HERE",
  .password = "YOUR_PASSWORD_HERE"
};

// Controller Configuration
// For ESP32, transmitterPin can be any GPIO pin (e.g., GPIO 4)
const Controller CONTROLLER_CONFIG = {
  .transmitterPin = 4, // GPIO 4
  .buckets = { 366, 736, 1600, 5204, 10896 },
  .id = 108289123
};

// Server Configuration
const int SERVER_PORT = 8181;

/* ======== END OF LOCAL CONFIGURATION TEMPLATE ======== */

#endif
