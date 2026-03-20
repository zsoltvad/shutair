#include "command-handler.h"
#include "pulse-generator.h"

const void handleChannelCommand(struct Controller controller, const char* command, AsyncWebServerRequest *request) {
  int channel = 0;

  // Serial.println("ARGS " + request->arg("id"));

  if(request->hasArg("id")) {
    String arg = request->arg("id");
    channel = arg.toInt();
  }

  // Serial.println("SHUTTER channel to interact: #" + String(channel));

  if (channel < 0 || channel > 15) {
    request->send(404, "application/json", "{ \"status\": \"INVALID CHANNEL\" }");
    return;
  }

  char *pulse = const_cast<char*>(getPulse(controller.id, channel, std::string(command)).c_str());
  RFControl::sendByCompressedTimings(controller.transmitterPin, controller.buckets, pulse);
  
  request->send(204, "application/json", "");
}
