#include <Arduino.h>
#include <ArduinoHA.h>
#include <ESP8266WiFi.h>
#include <IRac.h>
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRtext.h>
#include <IRutils.h>
#include <assert.h>

#include "codes.h"
#include "wifiCredentials.h"

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

const uint16_t kRecvPin = 14;
const uint32_t kBaudRate = 115200;
const uint16_t kCaptureBufferSize = 1024;
const uint8_t kTimeout = 50;
const uint16_t kMinUnknownSize = 12;
const uint8_t kTolerancePercentage = kTolerance;

byte mac[] = {0x00, 0x10, 0xFA, 0x6E, 0x39, 0x4A};

const uint64_t BRIGHTNESS_UP_CODE = 0xFF906F;
const uint64_t BRIGHTNESS_DOWN_CODE = 0xFFB847;
const uint64_t OFF_CODE = 0xFFF807;
const uint64_t ON_CODE = 0xFFB04F;
const uint64_t RED_CODE = 0xFF9867;
const uint64_t GREEN_CODE = 0xFFD827;
const uint64_t BLUE_CODE = 0xFF8877;
const uint64_t WHITE_CODE = 0xFFA857;
const uint64_t LIGHT_RED_CODE = 0xFFE817;
const uint64_t LIGHT_GREEN_CODE = 0xFF48B7;
const uint64_t LIGHT_BLUE_CODE = 0xFF6897;
const uint64_t FLASH_CODE = 0xFFB24D;
const uint64_t DARK_ORANGE_CODE = 0xFF02FD;
const uint64_t SKY_BLUE_CODE = 0xFF32CD;
const uint64_t PURPLE_CODE = 0xFF20DF;
const uint64_t STROBE_CODE = 0xFF00FF;
const uint64_t LIGHT_ORANGE_CODE = 0xFF50AF;
const uint64_t SWAMP_BLUE_CODE = 0xFF7887;
const uint64_t LIGHT_PURPLE_CODE = 0xFF708F;
const uint64_t FADE_CODE = 0xFF58A7;
const uint64_t YELLOW_CODE = 0xFF38C7;
const uint64_t SEA_BLUE_CODE = 0xFF28D7;
const uint64_t PONK_CODE = 0xFFF00F;
const uint64_t SMOOTH_CODE = 0xFF30CF;
const uint64_t REPEAT_CODE = 0xFFFFFFFFFFFFFFFF;

WiFiClient wifi_client;
HADevice device(mac, sizeof(mac));
HAMqtt mqtt(wifi_client, device);

// Use turn on the save buffer feature for more complete capture coverage.
IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);
decode_results results;  // Somewhere to store the results

// "myButtonA" and "myButtonB" are unique IDs of buttons. You should define you
// own ID.
HAButton buttonA("PowerButton");

HABinarySensor BRIGHTNESS_UP_sensor("BRIGHTNESS_UP_sensor");
HABinarySensor BRIGHTNESS_DOWN_sensor("BRIGHTNESS_DOWN_sensor");
HABinarySensor OFF_sensor("OFF_sensor");
HABinarySensor ON_sensor("ON_sensor");
HABinarySensor RED_sensor("RED_sensor");
HABinarySensor GREEN_sensor("GREEN_sensor");
HABinarySensor BLUE_sensor("BLUE_sensor");
HABinarySensor WHITE_sensor("WHITE_sensor");
HABinarySensor LIGHT_RED_sensor("LIGHT_RED_sensor");
HABinarySensor LIGHT_GREEN_sensor("LIGHT_GREEN_sensor");
HABinarySensor LIGHT_BLUE_sensor("LIGHT_BLUE_sensor");
HABinarySensor FLASH_sensor("FLASH_sensor");
HABinarySensor DARK_ORANGE_sensor("DARK_ORANGE_sensor");
HABinarySensor SKY_BLUE_sensor("SKY_BLUE_sensor");
HABinarySensor PURPLE_sensor("PURPLE_sensor");
HABinarySensor STROBE_sensor("STROBE_sensor");
HABinarySensor LIGHT_ORANGE_sensor("LIGHT_ORANGE_sensor");
HABinarySensor SWAMP_BLUE_sensor("SWAMP_BLUE_sensor");
HABinarySensor LIGHT_PURPLE_sensor("LIGHT_PURPLE_sensor");
HABinarySensor FADE_sensor("FADE_sensor");
HABinarySensor YELLOW_sensor("YELLOW_sensor");
HABinarySensor SEA_BLUE_sensor("SEA_BLUE_sensor");
HABinarySensor PONK_sensor("PONK_sensor");
HABinarySensor SMOOTH_sensor("SMOOTH_sensor");
HABinarySensor REPEAT_sensor("REPEAT_sensor");

bool button_pressed = false;

void onButtonCommand(HAButton* sender) { button_pressed = true; }

void setup() {
    irsend.begin();

    // Not fully sure what SERIAL_8N1 and SERIAL_TX_ONLY do.
    // Taken from
    Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

    // optional device's details
    device.setName("Livingroom_TV_Remote");
    device.setSoftwareVersion("1.0.1");

    // optional properties
    buttonA.setIcon("mdi:remote-tv");
    buttonA.setName("Power_Button");

    BRIGHTNESS_UP_sensor.setName("BRIGHTNESS_UP");
    BRIGHTNESS_UP_sensor.setIcon("mdi:gesture-tap-button");

    BRIGHTNESS_DOWN_sensor.setName("BRIGHTNESS_DOWN");
    BRIGHTNESS_DOWN_sensor.setIcon("mdi:gesture-tap-button");

    OFF_sensor.setName("OFF");
    OFF_sensor.setIcon("mdi:gesture-tap-button");

    ON_sensor.setName("ON");
    ON_sensor.setIcon("mdi:gesture-tap-button");

    RED_sensor.setName("RED");
    RED_sensor.setIcon("mdi:gesture-tap-button");

    GREEN_sensor.setName("GREEN");
    GREEN_sensor.setIcon("mdi:gesture-tap-button");

    BLUE_sensor.setName("BLUE");
    BLUE_sensor.setIcon("mdi:gesture-tap-button");

    WHITE_sensor.setName("WHITE");
    WHITE_sensor.setIcon("mdi:gesture-tap-button");

    LIGHT_RED_sensor.setName("LIGHT_RED");
    LIGHT_RED_sensor.setIcon("mdi:gesture-tap-button");

    LIGHT_GREEN_sensor.setName("LIGHT_GREEN");
    LIGHT_GREEN_sensor.setIcon("mdi:gesture-tap-button");

    LIGHT_BLUE_sensor.setName("LIGHT_BLUE");
    LIGHT_BLUE_sensor.setIcon("mdi:gesture-tap-button");

    FLASH_sensor.setName("FLASH");
    FLASH_sensor.setIcon("mdi:gesture-tap-button");

    DARK_ORANGE_sensor.setName("DARK_ORANGE");
    DARK_ORANGE_sensor.setIcon("mdi:gesture-tap-button");

    SKY_BLUE_sensor.setName("SKY_BLUE");
    SKY_BLUE_sensor.setIcon("mdi:gesture-tap-button");

    PURPLE_sensor.setName("PURPLE");
    PURPLE_sensor.setIcon("mdi:gesture-tap-button");

    STROBE_sensor.setName("STROBE");
    STROBE_sensor.setIcon("mdi:gesture-tap-button");

    LIGHT_ORANGE_sensor.setName("LIGHT_ORANGE");
    LIGHT_ORANGE_sensor.setIcon("mdi:gesture-tap-button");

    SWAMP_BLUE_sensor.setName("SWAMP_BLUE");
    SWAMP_BLUE_sensor.setIcon("mdi:gesture-tap-button");

    LIGHT_PURPLE_sensor.setName("LIGHT_PURPLE");
    LIGHT_PURPLE_sensor.setIcon("mdi:gesture-tap-button");

    FADE_sensor.setName("FADE");
    FADE_sensor.setIcon("mdi:gesture-tap-button");

    YELLOW_sensor.setName("YELLOW");
    YELLOW_sensor.setIcon("mdi:gesture-tap-button");

    SEA_BLUE_sensor.setName("SEA_BLUE");
    SEA_BLUE_sensor.setIcon("mdi:gesture-tap-button");

    PONK_sensor.setName("PONK");
    PONK_sensor.setIcon("mdi:gesture-tap-button");

    SMOOTH_sensor.setName("SMOOTH");
    SMOOTH_sensor.setIcon("mdi:gesture-tap-button");

    REPEAT_sensor.setName("REPEAT");
    REPEAT_sensor.setIcon("mdi:gesture-tap-button");

    // press callbacks
    buttonA.onCommand(onButtonCommand);

    mqtt.begin(BROKER_ADDR, 1883, MQTT_USERNAME, MQTT_PASSWORD);

    // Ignore messages with less than minimum on or off pulses.
    irrecv.setUnknownThreshold(kMinUnknownSize);

    // Override the default tolerance.
    irrecv.setTolerance(kTolerancePercentage);

    // Start the receiver
    irrecv.enableIRIn();
}

void loop() {
    mqtt.loop();

    if (button_pressed == true) {
        button_pressed = false;
        Serial.println("Power_button");
        irsend.sendRaw(power_button_raw, 135,
                       38);  // Send a raw data capture at 38kHz.
    }

    // Check if the IR code has been received.
    if (irrecv.decode(&results)) {
        static uint64_t last_code;
        uint64_t current_code = results.value;
        Serial.println("<===========+--o");

        if (current_code == REPEAT_CODE) {
            current_code = last_code;
        }

        last_code = current_code;
        switch (current_code) {
            case (BRIGHTNESS_UP_CODE):
                BRIGHTNESS_UP_sensor.setState(1);
                Serial.println("BRIGHTNESS_UP_sensor");
                break;

            case (BRIGHTNESS_DOWN_CODE):
                BRIGHTNESS_DOWN_sensor.setState(1);
                Serial.println("BRIGHTNESS_DOWN_sensor");
                break;

            case (OFF_CODE):
                OFF_sensor.setState(1);
                Serial.println("OFF_sensor");
                break;

            case (ON_CODE):
                ON_sensor.setState(1);
                Serial.println("ON_sensor");
                break;

            case (RED_CODE):
                RED_sensor.setState(1);
                Serial.println("RED_sensor");
                break;

            case (GREEN_CODE):
                GREEN_sensor.setState(1);
                Serial.println("GREEN_sensor");
                break;

            case (BLUE_CODE):
                BLUE_sensor.setState(1);
                Serial.println("BLUE_sensor");
                break;

            case (WHITE_CODE):
                WHITE_sensor.setState(1);
                Serial.println("WHITE_sensor");
                break;

            case (LIGHT_RED_CODE):
                LIGHT_RED_sensor.setState(1);
                Serial.println("LIGHT_RED_sensor");
                break;

            case (LIGHT_GREEN_CODE):
                LIGHT_GREEN_sensor.setState(1);
                Serial.println("LIGHT_GREEN_sensor");
                break;

            case (LIGHT_BLUE_CODE):
                LIGHT_BLUE_sensor.setState(1);
                Serial.println("LIGHT_BLUE_sensor");
                break;

            case (FLASH_CODE):
                FLASH_sensor.setState(1);
                Serial.println("FLASH_sensor");
                break;

            case (DARK_ORANGE_CODE):
                DARK_ORANGE_sensor.setState(1);
                Serial.println("DARK_ORANGE_sensor");
                break;

            case (SKY_BLUE_CODE):
                SKY_BLUE_sensor.setState(1);
                Serial.println("SKY_BLUE_sensor");
                break;

            case (PURPLE_CODE):
                PURPLE_sensor.setState(1);
                Serial.println("PURPLE_sensor");
                break;

            case (STROBE_CODE):
                STROBE_sensor.setState(1);
                Serial.println("STROBE_sensor");
                break;

            case (LIGHT_ORANGE_CODE):
                LIGHT_ORANGE_sensor.setState(1);
                Serial.println("LIGHT_ORANGE_sensor");
                break;

            case (SWAMP_BLUE_CODE):
                SWAMP_BLUE_sensor.setState(1);
                Serial.println("SWAMP_BLUE_sensor");
                break;

            case (LIGHT_PURPLE_CODE):
                LIGHT_PURPLE_sensor.setState(1);
                Serial.println("LIGHT_PURPLE_sensor");
                break;

            case (FADE_CODE):
                FADE_sensor.setState(1);
                Serial.println("FADE_sensor");
                break;

            case (YELLOW_CODE):
                YELLOW_sensor.setState(1);
                Serial.println("YELLOW_sensor");
                break;

            case (SEA_BLUE_CODE):
                SEA_BLUE_sensor.setState(1);
                Serial.println("SEA_BLUE_sensor");
                break;

            case (PONK_CODE):
                PONK_sensor.setState(1);
                Serial.println("PONK_sensor");
                break;

            case (SMOOTH_CODE):
                SMOOTH_sensor.setState(1);
                Serial.println("SMOOTH_sensor");
                break;

            case (REPEAT_CODE):
                REPEAT_sensor.setState(1);
                Serial.println("REPEAT_sensor");
                break;
        }

    } else {
        BRIGHTNESS_UP_sensor.setState(0);
        BRIGHTNESS_DOWN_sensor.setState(0);
        OFF_sensor.setState(0);
        ON_sensor.setState(0);
        RED_sensor.setState(0);
        GREEN_sensor.setState(0);
        BLUE_sensor.setState(0);
        WHITE_sensor.setState(0);
        LIGHT_RED_sensor.setState(0);
        LIGHT_GREEN_sensor.setState(0);
        LIGHT_BLUE_sensor.setState(0);
        FLASH_sensor.setState(0);
        DARK_ORANGE_sensor.setState(0);
        SKY_BLUE_sensor.setState(0);
        PURPLE_sensor.setState(0);
        STROBE_sensor.setState(0);
        LIGHT_ORANGE_sensor.setState(0);
        SWAMP_BLUE_sensor.setState(0);
        LIGHT_PURPLE_sensor.setState(0);
        FADE_sensor.setState(0);
        YELLOW_sensor.setState(0);
        SEA_BLUE_sensor.setState(0);
        PONK_sensor.setState(0);
        SMOOTH_sensor.setState(0);
        REPEAT_sensor.setState(0);
    }
}