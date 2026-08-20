#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <MQTT.h>

#include "IR_CODE_STRUCT.h"
#include "LED_CODES.h"
#include "SAMSUNG_CODES.h"
#include "TIVO_CODES.h"
#include "TOSHIBA_CODES.h"
#include "wifiCredentials.h"

const uint16_t ir_out_pin = 4;
const int CARRIER_WAVE = 38;

IRsend ir_send(ir_out_pin);

const uint16_t kRecvPin = 14;

IRrecv ir_rec(kRecvPin);
decode_results results;

WiFiClient wifi_client;
MQTTClient mqtt_client;

volatile int16_t mqtt_in_index = -1;
volatile int16_t ir_in_index = -1;

#define TOPIC_IR_IN "/hb_mqtt/ir_bridge/livingroom/ir_in"
#define TOPIC_IR_OUT "/hb_mqtt/ir_bridge/livingroom/ir_out"

const int IR_CODE_COUNT = 151;
ir_code_item led_ir_items[IR_CODE_COUNT] = {
    LED_BRIGHTNESS_STRUCT,
    LED_BRIGHTNESS_DOWN_STRUCT,
    LED_OFF_STRUCT,
    LED_ON_STRUCT,
    LED_RED_STRUCT,
    LED_GREEN_STRUCT,
    LED_BLUE_STRUCT,
    LED_WHITE_STRUCT,
    LED_LIGHT_RED_STRUCT,
    LED_LIGHT_GREEN_STRUCT,
    LED_LIGHT_BLUE_STRUCT,
    LED_FLASH_STRUCT,
    LED_DARK_ORANGE_STRUCT,
    LED_SKY_BLUE_STRUCT,
    LED_PURPLE_STRUCT,
    LED_STROBE_STRUCT,
    LED_LIGHT_ORANGE_STRUCT,
    LED_SWAMP_BLUE_STRUCT,
    LED_LIGHT_PURPLE_STRUCT,
    LED_FADE_STRUCT,
    LED_YELLOW_STRUCT,
    LED_SEA_BLUE_STRUCT,
    LED_PONK_STRUCT,
    LED_SMOOTH_STRUCT,
    LED_REPEAT_STRUCT,
    SAMSUNG_POWER_STRUCT,
    SAMSUNG_SOURCE_STRUCT,
    SAMSUNG_ONE_STRUCT,
    SAMSUNG_TWO_STRUCT,
    SAMSUNG_THREE_STRUCT,
    SAMSUNG_FOUR_STRUCT,
    SAMSUNG_FIVE_STRUCT,
    SAMSUNG_SIX_STRUCT,
    SAMSUNG_SEVEN_STRUCT,
    SAMSUNG_EIGHT_STRUCT,
    SAMSUNG_NINE_STRUCT,
    SAMSUNG_TTX_STRUCT,
    SAMSUNG_ZERO_STRUCT,
    SAMSUNG_PRE_CH_STRUCT,
    SAMSUNG_VOLUME_UP_STRUCT,
    SAMSUNG_MUTE_STRUCT,
    SAMSUNG_CHANNEL_UP_STRUCT,
    SAMSUNG_VOLUME_DOWN_STRUCT,
    SAMSUNG_CH_LIST_STRUCT,
    SAMSUNG_CHANNEL_DOWN_STRUCT,
    SAMSUNG_MENU_STRUCT,
    SAMSUNG_SMART_HUB_STRUCT,
    SAMSUNG_GUIDE_STRUCT,
    SAMSUNG_TOOLS_STRUCT,
    SAMSUNG_UP_STRUCT,
    SAMSUNG_INFO_STRUCT,
    SAMSUNG_LEFT_STRUCT,
    SAMSUNG_ENTER_STRUCT,
    SAMSUNG_RIGHT_STRUCT,
    SAMSUNG_RETURN_STRUCT,
    SAMSUNG_DOWN_STRUCT,
    SAMSUNG_EXIT_STRUCT,
    SAMSUNG_RED_STRUCT,
    SAMSUNG_GREEN_STRUCT,
    SAMSUNG_YELLOW_STRUCT,
    SAMSUNG_BLUE_STRUCT,
    SAMSUNG_E_MANUAL_STRUCT,
    SAMSUNG_SPORTS_STRUCT,
    SAMSUNG_AD_SUBT_STRUCT,
    SAMSUNG_STOP_STRUCT,
    SAMSUNG_REWIND_STRUCT,
    SAMSUNG_PLAY_STRUCT,
    SAMSUNG_PAUSE_STRUCT,
    SAMSUNG_FAST_FORWARD_STRUCT,
    TIVO_POWER_STRUCT,
    TIVO_GUIDE_STRUCT,
    TIVO_MUTE_STRUCT,
    TIVO_REWIND_STRUCT,
    TIVO_PAUSE_STRUCT,
    TIVO_FAST_FORWARD_STRUCT,
    TIVO_RED_STRUCT,
    TIVO_GREEN_STRUCT,
    TIVO_YELLOW_STRUCT,
    TIVO_BLUE_STRUCT,
    TIVO_UP_STRUCT,
    TIVO_LEFT_STRUCT,
    TIVO_OK_STRUCT,
    TIVO_RIGHT_STRUCT,
    TIVO_DOWN_STRUCT,
    TIVO_RETURN_STRUCT,
    TIVO_TIVO_STRUCT,
    TIVO_INFO_STRUCT,
    TIVO_VOLUME_UP_STRUCT,
    TIVO_VOLUME_DOWN_STRUCT,
    TIVO_CHANNEL_UP_STRUCT,
    TIVO_CHANNEL_DOWN_STRUCT,
    TIVO_YOUTUBE_STRUCT,
    TIVO_NETFLIX_STRUCT,
    TIVO_PRIME_VIDEO_STRUCT,
    TIVO_DISNEY_STRUCT,
    TIVO_FREE_STRUCT,
    TIVO_FREELY_STRUCT,
    TIVO_ONE_STRUCT,
    TIVO_TWO_STRUCT,
    TIVO_THREE_STRUCT,
    TIVO_FOUR_STRUCT,
    TIVO_FIVE_STRUCT,
    TIVO_SIX_STRUCT,
    TIVO_SEVEN_STRUCT,
    TIVO_EIGHT_STRUCT,
    TIVO_NINE_STRUCT,
    TIVO_SUB_STRUCT,
    TIVO_ZERO_STRUCT,
    TIVO_SETTINGS_STRUCT,
    TOSHIBA_SOURCE_STRUCT,
    TOSHIBA_POWER_STRUCT,
    TOSHIBA_STILL_PICTURE_STRUCT,
    TOSHIBA_TEXT_STRUCT,
    TOSHIBA_SUBTITLE_STRUCT,
    TOSHIBA_STEREO_STRUCT,
    TOSHIBA_ONE_STRUCT,
    TOSHIBA_TWO_STRUCT,
    TOSHIBA_THREE_STRUCT,
    TOSHIBA_FOUR_STRUCT,
    TOSHIBA_FIVE_STRUCT,
    TOSHIBA_SIX_STRUCT,
    TOSHIBA_SEVEN_STRUCT,
    TOSHIBA_EIGHT_STRUCT,
    TOSHIBA_NINE_STRUCT,
    TOSHIBA_AD_STRUCT,
    TOSHIBA_ZERO_STRUCT,
    TOSHIBA_ATV_DTV_STRUCT,
    TOSHIBA_VOLUME_UP_STRUCT,
    TOSHIBA_VOLUME_DOWN_STRUCT,
    TOSHIBA_INFO_STRUCT,
    TOSHIBA_MUTE_STRUCT,
    TOSHIBA_QUICK_STRUCT,
    TOSHIBA_CHANNEL_UP_STRUCT,
    TOSHIBA_CHANNEL_DOWN_STRUCT,
    TOSHIBA_GUIDE_STRUCT,
    TOSHIBA_UP_STRUCT,
    TOSHIBA_EXIT_STRUCT,
    TOSHIBA_LEFT_STRUCT,
    TOSHIBA_OK_STRUCT,
    TOSHIBA_RIGHT_STRUCT,
    TOSHIBA_MENU_STRUCT,
    TOSHIBA_DOWN_STRUCT,
    TOSHIBA_RETURN_STRUCT,
    TOSHIBA_RED_STRUCT,
    TOSHIBA_GREEN_STRUCT,
    TOSHIBA_YELLOW_STRUCT,
    TOSHIBA_BLUE_STRUCT,
    TOSHIBA_QUESTION_STRUCT,
    TOSHIBA_ZOOM_OUT_STRUCT,
    TOSHIBA_ZOOM_IN_STRUCT,
    TOSHIBA_TIME_STRUCT,
};

void mqtt_data_in(String& topic, String& payload) {
    Serial.println("incoming: " + topic + " - " + payload);

    if (topic != TOPIC_IR_OUT) {
        Serial.println("Error");
    }

    for (int i = 0; i < IR_CODE_COUNT; i++) {
        // if (payload == led_ir_items[i].name) {
        //     mqtt_in_index = i;
        //     return;
        // }
    }

    Serial.println("Command Not Found.");
    mqtt_in_index = -1;
}

void connect_to_mqtt() {
    Serial.print("checking wifi...");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }

    Serial.print("\nconnecting...");
    while (!mqtt_client.connect("arduino", MQTT_USERNAME, MQTT_PASSWORD)) {
        Serial.print("-");
        delay(1000);
    }

    Serial.println("\nconnected!");

    mqtt_client.subscribe(TOPIC_IR_OUT);
}

void setup() {
    ir_send.begin();

    ir_rec.enableIRIn();

    Serial.begin(115200);

    WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

    mqtt_client.begin(MQTT_HOSTNAME, wifi_client);
    mqtt_client.onMessage(mqtt_data_in);

    connect_to_mqtt();

    delay(3000);

    Serial.println("CODES:");
    for (int i = 0; i < IR_CODE_COUNT; i++) {
        // Serial.println(led_ir_items[i].decoded);
    }

    Serial.println("END:");
}

void got_ir(const uint64_t received_code) {
    for (int i = 0; i < IR_CODE_COUNT; i++) {
        // if (received_code == led_ir_items[i].decoded) {
        //     Serial.println(led_ir_items[i].name);
        //     return;
        // }
    }
}

void loop() {
    mqtt_client.loop();

    delay(10);  // <- fixes some issues with WiFi stability

    if (!mqtt_client.connected()) {
        Serial.println("Reconnecting To MQTT Broker");
        connect_to_mqtt();
    }

    if (mqtt_in_index != -1) {
        Serial.print("MQTT Requested: ");
        // Serial.println(led_ir_items[mqtt_in_index].name);
        // ir_send.sendRaw(led_ir_items[mqtt_in_index].raw_data,
        //                 led_ir_items[mqtt_in_index].length, CARRIER_WAVE);

        mqtt_in_index = -1;
    }
    if (ir_in_index != -1) {
        Serial.print("IR Requested: ");
        //         Serial.println(COMMAND_NAME[ir_in_index]);
        //
        //         mqtt_client.publish(TOPIC_last_ir_in)

        ir_in_index = -1;
    }

    if (ir_rec.decode(&results)) {
        Serial.println("<===========+--o");
        got_ir(results.value);

        ir_rec.resume();
    }

    // static unsigned long last_ran = 0;
    // if (millis() - last_ran > 1000) {
    //     Serial.print("Still Alive: ");
    //     Serial.println(millis());
    //     last_ran = millis();
    // }
}