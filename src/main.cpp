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

byte mac[] = {0x00, 0x10, 0xFA, 0x6E, 0x39, 0x4A};

WiFiClient wifi_client;
HADevice device(mac, sizeof(mac));
HAMqtt mqtt(wifi_client, device);

HAButton POWER_BUTTON("POWER_BUTTON");
HAButton SOURCE_BUTTON("SOURCE_BUTTON");
HAButton VOLUME_UP_BUTTON("VOLUME_UP_BUTTON");
HAButton MUTE_BUTTON("MUTE_BUTTON");
HAButton VOLUME_DOWN_BUTTON("VOLUME_DOWN_BUTTON");
HAButton SMART_HUB_BUTTON("SMART_HUB_BUTTON");
HAButton UP_BUTTON("UP_BUTTON");
HAButton LEFT_BUTTON("LEFT_BUTTON");
HAButton ENTER_BUTTON("ENTER_BUTTON");
HAButton RIGHT_BUTTON("RIGHT_BUTTON");
HAButton RETURN_BUTTON("RETURN_BUTTON");
HAButton DOWN_BUTTON("DOWN_BUTTON");
HAButton REWIND_BUTTON("REWIND_BUTTON");
HAButton PLAY_BUTTON("PLAY_BUTTON");
HAButton PAUSE_BUTTON("PAUSE_BUTTON");
HAButton FAST_FORWARD_BUTTON("FAST_FORWARD_BUTTON");

HAButton* last_button_requested = nullptr;

void onButtonCommand(HAButton* sender) { last_button_requested = sender; }

void setup() {
    irsend.begin();

    // Not fully sure what SERIAL_8N1 and SERIAL_TX_ONLY do.
    // Taken from
    Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

    // optional device's details
    device.setName("Livingroom_TV_Remote");
    device.setSoftwareVersion("1.0.2");

    POWER_BUTTON.setIcon("mdi:remote-tv");
    POWER_BUTTON.setName("PowerButton");
    POWER_BUTTON.onCommand(onButtonCommand);

    SOURCE_BUTTON.setIcon("mdi:remote-tv");
    SOURCE_BUTTON.setName("SAMSUNG_SOURCE_RAW");
    SOURCE_BUTTON.onCommand(onButtonCommand);

    VOLUME_UP_BUTTON.setIcon("mdi:remote-tv");
    VOLUME_UP_BUTTON.setName("SAMSUNG_VOLUME_UP_RAW");
    VOLUME_UP_BUTTON.onCommand(onButtonCommand);

    MUTE_BUTTON.setIcon("mdi:remote-tv");
    MUTE_BUTTON.setName("SAMSUNG_MUTE_RAW");
    MUTE_BUTTON.onCommand(onButtonCommand);

    VOLUME_DOWN_BUTTON.setIcon("mdi:remote-tv");
    VOLUME_DOWN_BUTTON.setName("SAMSUNG_VOLUME_DOWN_RAW");
    VOLUME_DOWN_BUTTON.onCommand(onButtonCommand);

    SMART_HUB_BUTTON.setIcon("mdi:remote-tv");
    SMART_HUB_BUTTON.setName("SAMSUNG_SMART_HUB_RAW");
    SMART_HUB_BUTTON.onCommand(onButtonCommand);

    UP_BUTTON.setIcon("mdi:remote-tv");
    UP_BUTTON.setName("SAMSUNG_UP_RAW");
    UP_BUTTON.onCommand(onButtonCommand);

    LEFT_BUTTON.setIcon("mdi:remote-tv");
    LEFT_BUTTON.setName("SAMSUNG_LEFT_RAW");
    LEFT_BUTTON.onCommand(onButtonCommand);

    ENTER_BUTTON.setIcon("mdi:remote-tv");
    ENTER_BUTTON.setName("SAMSUNG_ENTER_RAW");
    ENTER_BUTTON.onCommand(onButtonCommand);

    RIGHT_BUTTON.setIcon("mdi:remote-tv");
    RIGHT_BUTTON.setName("SAMSUNG_RIGHT_RAW");
    RIGHT_BUTTON.onCommand(onButtonCommand);

    RETURN_BUTTON.setIcon("mdi:remote-tv");
    RETURN_BUTTON.setName("SAMSUNG_RETURN_RAW");
    RETURN_BUTTON.onCommand(onButtonCommand);

    DOWN_BUTTON.setIcon("mdi:remote-tv");
    DOWN_BUTTON.setName("SAMSUNG_DOWN_RAW");
    DOWN_BUTTON.onCommand(onButtonCommand);

    REWIND_BUTTON.setIcon("mdi:remote-tv");
    REWIND_BUTTON.setName("SAMSUNG_REWIND_RAW");
    REWIND_BUTTON.onCommand(onButtonCommand);

    PLAY_BUTTON.setIcon("mdi:remote-tv");
    PLAY_BUTTON.setName("SAMSUNG_PLAY_RAW");
    PLAY_BUTTON.onCommand(onButtonCommand);

    PAUSE_BUTTON.setIcon("mdi:remote-tv");
    PAUSE_BUTTON.setName("SAMSUNG_PAUSE_RAW");
    PAUSE_BUTTON.onCommand(onButtonCommand);

    FAST_FORWARD_BUTTON.setIcon("mdi:remote-tv");
    FAST_FORWARD_BUTTON.setName("SAMSUNG_FAST_FORWARD_RAW");
    FAST_FORWARD_BUTTON.onCommand(onButtonCommand);

    mqtt.begin(BROKER_ADDR, 1883, MQTT_USERNAME, MQTT_PASSWORD);
}

void loop() {
    mqtt.loop();

    if (last_button_requested != nullptr) {
        if (&POWER_BUTTON == last_button_requested) {
            Serial.println("SAMSUNG_POWER_RAW");
            irsend.sendRaw(SAMSUNG_POWER_RAW, 135, 38);
        }
        if (&SOURCE_BUTTON == last_button_requested) {
            Serial.println("SAMSUNG_SOURCE_RAW");
            irsend.sendRaw(SAMSUNG_SOURCE_RAW, 135, 38);
        }
        if (&VOLUME_UP_BUTTON == last_button_requested) {
            Serial.println("SAMSUNG_VOLUME_UP_RAW");
            irsend.sendRaw(SAMSUNG_VOLUME_UP_RAW, 135, 38);
        }
        if (&MUTE_BUTTON == last_button_requested) {
            Serial.println("SAMSUNG_MUTE_RAW");
            irsend.sendRaw(SAMSUNG_MUTE_RAW, 135, 38);
        }
        if (&VOLUME_DOWN_BUTTON == last_button_requested) {
            Serial.println("SAMSUNG_VOLUME_DOWN_RAW");
            irsend.sendRaw(SAMSUNG_VOLUME_DOWN_RAW, 135, 38);
        }
        if (&SMART_HUB_BUTTON == last_button_requested) {
            Serial.println("SAMSUNG_SMART_HUB_RAW");
            irsend.sendRaw(SAMSUNG_SMART_HUB_RAW, 135, 38);
        }
        if (&UP_BUTTON == last_button_requested) {
            Serial.println("SAMSUNG_UP_RAW");
            irsend.sendRaw(SAMSUNG_UP_RAW, 67, 38);
        }
        if (&LEFT_BUTTON == last_button_requested) {
            Serial.println("SAMSUNG_LEFT_RAW");
            irsend.sendRaw(SAMSUNG_LEFT_RAW, 135, 38);
        }
        if (&ENTER_BUTTON == last_button_requested) {
            Serial.println("SAMSUNG_ENTER_RAW");
            irsend.sendRaw(SAMSUNG_ENTER_RAW, 135, 38);
        }
        if (&RIGHT_BUTTON == last_button_requested) {
            Serial.println("SAMSUNG_RIGHT_RAW");
            irsend.sendRaw(SAMSUNG_RIGHT_RAW, 135, 38);
        }
        if (&RETURN_BUTTON == last_button_requested) {
            Serial.println("SAMSUNG_RETURN_RAW");
            irsend.sendRaw(SAMSUNG_RETURN_RAW, 135, 38);
        }
        if (&DOWN_BUTTON == last_button_requested) {
            Serial.println("SAMSUNG_DOWN_RAW");
            irsend.sendRaw(SAMSUNG_DOWN_RAW, 135, 38);
        }
        if (&REWIND_BUTTON == last_button_requested) {
            Serial.println("SAMSUNG_REWIND_RAW");
            irsend.sendRaw(SAMSUNG_REWIND_RAW, 135, 38);
        }
        if (&PLAY_BUTTON == last_button_requested) {
            Serial.println("SAMSUNG_PLAY_RAW");
            irsend.sendRaw(SAMSUNG_PLAY_RAW, 135, 38);
        }
        if (&PAUSE_BUTTON == last_button_requested) {
            Serial.println("SAMSUNG_PAUSE_RAW");
            irsend.sendRaw(SAMSUNG_PAUSE_RAW, 135, 38);
        }
        if (&FAST_FORWARD_BUTTON == last_button_requested) {
            Serial.println("SAMSUNG_FAST_FORWARD_RAW");
            irsend.sendRaw(SAMSUNG_FAST_FORWARD_RAW, 135, 38);
        }

        last_button_requested = nullptr;
    }
}