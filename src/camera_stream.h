#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>

void cameraInit();
void cameraStreamTask(void *pv);
void attachCameraSocket(AsyncWebSocket *ws);
