#include <RFControl.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <Wire.h>
#include "pulse-generator.h"
#include "command-handler.h"
#include "auth-handler.h"
#include "wifi-config.h"
#include "config.h"

// Load configuration from config.h
String pin = AUTH_PIN;
WiFiConfig wifiConfig = WIFI_CONFIG;
Controller controller = CONTROLLER_CONFIG;

// Instantiate server at port with configured port
AsyncWebServer server(SERVER_PORT);

void setup() {
  Serial.begin(115200);

  // Initialize LittleFS
  if (!LittleFS.begin()) {
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(wifiConfig.ssid, wifiConfig.password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  server
  .serveStatic("/", LittleFS, "/www/")
  .setDefaultFile("index.html")
  .setCacheControl("max-age=86400");

  server.on("/authenticate", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (!isAuthorized(pin, request)) {
      request->send(401);
      return;
    }

    request->send(204);
  });

  server.on("/up", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (!isAuthorized(pin, request)) {
      request->send(401);
      return;
    }

    handleChannelCommand(controller, "up", request);
  });

  server.on("/down", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (!isAuthorized(pin, request)) {
      request->send(401);
      return;
    }

    handleChannelCommand(controller, "down", request);
  });

  server.on("/stop", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (!isAuthorized(pin, request)) {
      request->send(401);
      return;
    }

    handleChannelCommand(controller, "stop", request);
  });

  server.onNotFound([](AsyncWebServerRequest * request) {
    request->send(404);
  });

  server.begin();

  Serial.println("Web server started!");
}

void loop() {
}
