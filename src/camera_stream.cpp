#include "camera_stream.h"
#include "esp_camera.h"

static AsyncWebSocket *cameraWS = nullptr;
static uint32_t cameraClientId = 0;

// ================= Camera Pins (AI Thinker ESP32-CAM) =================
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

// =========================================================

void attachCameraSocket(AsyncWebSocket *ws)
{
    cameraWS = ws;
}

void cameraInit()
{
    camera_config_t config;

    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer   = LEDC_TIMER_0;

    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;

    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;

    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;

    config.pin_pwdn  = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;

    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = psramFound() ? 2 : 1;

    if (esp_camera_init(&config) != ESP_OK)
    {
        Serial.println("❌ Camera init failed");
        return;
    }

    Serial.println("✅ Camera initialized");
}

// =========================================================
// ================= Camera Stream Task ====================
// =========================================================

void cameraStreamTask(void *pv)
{
    while (true)
    {
        if (cameraWS && cameraClientId != 0)
        {
            camera_fb_t *fb = esp_camera_fb_get();

            if (fb)
            {
                cameraWS->binary(cameraClientId, fb->buf, fb->len);
                esp_camera_fb_return(fb);
            }
        }

        vTaskDelay(pdMS_TO_TICKS(60)); // ~15 FPS
    }
}

// =========================================================
// ================= WebSocket Events ======================
// =========================================================

void onCameraWS(AsyncWebSocket *server,
                AsyncWebSocketClient *client,
                AwsEventType type,
                void *arg,
                uint8_t *data,
                size_t len)
{
    if (type == WS_EVT_CONNECT)
    {
        cameraClientId = client->id();
        Serial.println("📷 Camera client connected");
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        cameraClientId = 0;
        Serial.println("📷 Camera client disconnected");
    }
}
