#include <Arduino.h>
#include <ArduinoHA.h>
#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

#include "codes.h"
#include "wifiCredentials.h"



const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

byte mac[] = {0x00, 0x10, 0xFA, 0x6E, 0x39, 0x4A};

WiFiClient wifi_client;
HADevice device(mac, sizeof(mac));
HAMqtt mqtt(wifi_client, device);

// "myButtonA" and "myButtonB" are unique IDs of buttons. You should define you
// own ID.
HAButton buttonA("PowerButton");

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
    device.setSoftwareVersion("1.0.0");

    // optional properties
    buttonA.setIcon("mdi:remote-tv");
    buttonA.setName("Power_Button");

    // press callbacks
    buttonA.onCommand(onButtonCommand);

    mqtt.begin(BROKER_ADDR, 1883, MQTT_USERNAME, MQTT_PASSWORD);
}

void loop() {
    mqtt.loop();

    if (button_pressed == true) {
        button_pressed = false;
        Serial.println("Power_button");
        irsend.sendRaw(power_button_raw, 135, 38);  // Send a raw data capture at 38kHz.
    }
}