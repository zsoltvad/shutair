#ifndef AUTH__HANDLER_H
#define AUTH__HANDLER_H

#include <ESPAsyncWebServer.h>

const boolean isAuthorized(String pin, AsyncWebServerRequest *request);

#endif
