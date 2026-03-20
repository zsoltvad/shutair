#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <ESPAsyncWebServer.h>
#include <RFControl.h>
#include "controller.h"

const void handleChannelCommand(struct Controller controller, const char* command, AsyncWebServerRequest *request);

#endif
