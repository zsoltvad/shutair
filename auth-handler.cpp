#include "auth-handler.h"

const boolean isAuthorized(String pin, AsyncWebServerRequest *request) {
  if(!request->hasHeader("Authorization")) {
    return false;
  }

  const AsyncWebHeader* authorizationHeader = request->getHeader("Authorization");
  return authorizationHeader->value() == pin;
}
