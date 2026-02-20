#include "web_control.h"
#include "camera_stream.h"

static AsyncWebSocket wsCamera("/Camera");

AsyncWebSocket* getCameraSocket()
{
    return &wsCamera;
}

void setupWebControl(AsyncWebServer &server)
{
    wsCamera.onEvent(onCameraWS);
    server.addHandler(&wsCamera);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *req)
    {
        req->send(200, "text/plain",
                  "ESP32 Surveillance Rover Online");
    });
}
