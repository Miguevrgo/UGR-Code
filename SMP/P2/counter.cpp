#include <cstdint>

#ifndef ARDUINO
#define INPUT_PULLUP 2
#define OUTPUT 1
#define HIGH 1
#define LOW 0
void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);
int digitalRead(uint8_t pin);
unsigned long millis();
void delay(unsigned long ms);
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#else
#include <Arduino.h>
#endif

constexpr uint8_t PIN_BUTTON_PAUSE = 2;
constexpr uint8_t PIN_TRANSISTOR_TENS = 11;
constexpr uint8_t PIN_TRANSISTOR_UNITS = 12;
constexpr uint8_t DISPLAY_PINS[] = { 4, 5, 6, 7, 8, 9, 10 };

void set_segments(uint8_t current_digit)
{
    constexpr uint8_t DIGIT_MAP[10]
        = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };

    const auto mapped_segments = DIGIT_MAP[current_digit];

    for (uint8_t i = 0; i < 7; ++i) {
        digitalWrite(DISPLAY_PINS[i], !bitRead(mapped_segments, i));
    }
}

void setup()
{
    pinMode(PIN_BUTTON_PAUSE, INPUT_PULLUP);
    pinMode(PIN_TRANSISTOR_TENS, OUTPUT);
    pinMode(PIN_TRANSISTOR_UNITS, OUTPUT);

    digitalWrite(PIN_TRANSISTOR_TENS, HIGH);
    digitalWrite(PIN_TRANSISTOR_UNITS, HIGH);

    for (const auto pin : DISPLAY_PINS) {
        pinMode(pin, OUTPUT);
    }
}

void loop()
{
    static uint8_t seconds_counter = 0;
    static unsigned long last_update_time = 0;

    const auto current_time = millis();
    const bool is_paused = (digitalRead(PIN_BUTTON_PAUSE) == LOW);

    if (!is_paused) {
        if (current_time - last_update_time >= 1000) {
            last_update_time = current_time;
            if (++seconds_counter == 60) {
                seconds_counter = 0;
            }
        }

        const uint8_t tens = seconds_counter / 10;
        const uint8_t units = seconds_counter % 10;

        set_segments(tens);
        digitalWrite(PIN_TRANSISTOR_TENS, LOW);
        delay(10);
        digitalWrite(PIN_TRANSISTOR_TENS, HIGH);

        set_segments(units);
        digitalWrite(PIN_TRANSISTOR_UNITS, LOW);
        delay(10);
        digitalWrite(PIN_TRANSISTOR_UNITS, HIGH);
    } else {
        digitalWrite(PIN_TRANSISTOR_TENS, HIGH);
        digitalWrite(PIN_TRANSISTOR_UNITS, HIGH);
        last_update_time = current_time;
    }
}
