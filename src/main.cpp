#include <Arduino.h>
#include <IRac.h>
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRtext.h>
#include <IRutils.h>
#include <assert.h>

const uint16_t kRecvPin = 14;
const uint32_t kBaudRate = 115200;
const uint16_t kCaptureBufferSize = 1024;
const uint8_t kTimeout = 50;
const uint16_t kMinUnknownSize = 12;
const uint8_t kTolerancePercentage = kTolerance;

const uint64_t BRIGHTNESS_UP = 0xFF906F;
const uint64_t BRIGHTNESS_DOWN = 0xFFB847;
const uint64_t OFF = 0xFFF807;
const uint64_t ON = 0xFFB04F;
const uint64_t RED = 0xFF9867;
const uint64_t GREEN = 0xFFD827;
const uint64_t BLUE = 0xFF8877;
const uint64_t WHITE = 0xFFA857;
const uint64_t LIGHT_RED = 0xFFE817;
const uint64_t LIGHT_GREEN = 0xFF48B7;
const uint64_t LIGHT_BLUE = 0xFF6897;
const uint64_t FLASH = 0xFFB24D;
const uint64_t DARK_ORANGE = 0xFF02FD;
const uint64_t SKY_BLUE = 0xFF32CD;
const uint64_t PURPLE = 0xFF20DF;
const uint64_t STROBE = 0xFF00FF;
const uint64_t LIGHT_ORANGE = 0xFF50AF;
const uint64_t SWAMP_BLUE = 0xFF7887;
const uint64_t LIGHT_PURPLE = 0xFF708F;
const uint64_t FADE = 0xFF58A7;
const uint64_t YELLOW = 0xFF38C7;
const uint64_t SEA_BLUE = 0xFF28D7;
const uint64_t PONK = 0xFFF00F;
const uint64_t SMOOTH = 0xFF30CF;
const uint64_t REPEAT = 0xFFFFFFFFFFFFFFFF;

// Use turn on the save buffer feature for more complete capture coverage.
IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);
decode_results results;  // Somewhere to store the results

// This section of code runs only once at start-up.
void setup() {
    Serial.begin(115200);

    // Perform a low level sanity checks that the compiler performs bit field
    // packing as we expect and Endianness is as we expect.
    assert(irutils::lowLevelSanityCheck() == 0);

    Serial.printf("\n" D_STR_IRRECVDUMP_STARTUP "\n", kRecvPin);

    // Ignore messages with less than minimum on or off pulses.
    irrecv.setUnknownThreshold(kMinUnknownSize);

    // Override the default tolerance.
    irrecv.setTolerance(kTolerancePercentage);

    // Start the receiver
    irrecv.enableIRIn();
}

String check_code(uint64_t code) {
    static String last_value = "";
    String return_value;

    switch (code) {
        case (BRIGHTNESS_UP):
            return_value = "BRIGHTNESS_UP";
            break;

        case (BRIGHTNESS_DOWN):
            return_value = "BRIGHTNESS_DOWN";
            break;

        case (OFF):
            return_value = "OFF";
            break;

        case (ON):
            return_value = "ON";
            break;

        case (RED):
            return_value = "RED";
            break;

        case (GREEN):
            return_value = "GREEN";
            break;

        case (BLUE):
            return_value = "BLUE";
            break;

        case (WHITE):
            return_value = "WHITE";
            break;

        case (LIGHT_RED):
            return_value = "LIGHT_RED";
            break;

        case (LIGHT_GREEN):
            return_value = "LIGHT_GREEN";
            break;

        case (LIGHT_BLUE):
            return_value = "LIGHT_BLUE";
            break;

        case (FLASH):
            return_value = "FLASH";
            break;

        case (DARK_ORANGE):
            return_value = "DARK_ORANGE";
            break;

        case (SKY_BLUE):
            return_value = "SKY_BLUE";
            break;

        case (PURPLE):
            return_value = "PURPLE";
            break;

        case (STROBE):
            return_value = "STROBE";
            break;

        case (LIGHT_ORANGE):
            return_value = "LIGHT_ORANGE";
            break;

        case (SWAMP_BLUE):
            return_value = "SWAMP_BLUE";
            break;

        case (LIGHT_PURPLE):
            return_value = "LIGHT_PURPLE";
            break;

        case (FADE):
            return_value = "FADE";
            break;

        case (YELLOW):
            return_value = "YELLOW";
            break;

        case (SEA_BLUE):
            return_value = "SEA_BLUE";
            break;

        case (PONK):
            return_value = "PONK";
            break;

        case (SMOOTH):
            return_value = "SMOOTH";
            break;

        case (REPEAT):
            return_value = last_value;
            break;

        default:
            return_value = "NOT_FOUND";
            break;
    }

    last_value = return_value;
    return return_value;
}

// The repeating section of the code
void loop() {
    // Check if the IR code has been received.
    if (irrecv.decode(&results)) {
        uint64_t data = results.value;
        Serial.println("<===========+--o");
        Serial.println(check_code(data));
    }
}
