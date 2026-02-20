#pragma once
#include <ESPAsyncWebServer.h>

void setupWebControl(AsyncWebServer &server);
AsyncWebSocket* getCameraSocket();
