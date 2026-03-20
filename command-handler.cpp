#include "command-handler.h"
#include "pulse-generator.h"

const void handleChannelCommand(struct Controller controller, const char* command, AsyncWebServerRequest *request) {
  int channel = 0;

  if(request->hasArg("id")) {
    String arg = request->arg("id");
    channel = arg.toInt();
  }

  Serial.println("SHUTTER channel to interact: #" + String(channel));
  Serial.println("Command: " + String(command));

  if (channel < 0 || channel > 15) {
    request->send(404, "application/json", "{ \"status\": \"INVALID CHANNEL\" }");
    return;
  }

  try {
    std::string pulseStr = getPulse(controller.id, channel, std::string(command));
    char *pulse = const_cast<char*>(pulseStr.c_str());
    
    Serial.print("Controller ID: ");
    Serial.println(controller.id);
    Serial.print("Transmitter Pin: ");
    Serial.println(controller.transmitterPin);
    Serial.print("Pulse length: ");
    Serial.println(strlen(pulse));
    Serial.print("Pulse: ");
    Serial.println(pulse);
    
    Serial.println("Sending RF signal...");
    RFControl::sendByCompressedTimings(controller.transmitterPin, controller.buckets, pulse);
    Serial.println("RF signal sent successfully");
  } catch (...) {
    Serial.println("ERROR: Exception during RF transmission");
  }
  
  request->send(204, "application/json", "");
}
