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
struct SerialDummy { void begin(int); };
extern SerialDummy Serial;
#else
#include <Arduino.h>
#endif

constexpr uint8_t PIN_BUTTON_UP = 3;
constexpr uint8_t PIN_BUTTON_DOWN = 2;
constexpr uint8_t DISPLAY_PINS[] = { 4, 5, 6, 7, 8, 9, 10 };

void update_display(uint8_t current_digit)
{
    constexpr uint8_t DIGIT_MAP[10]
        = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };

    const auto mapped_segments = DIGIT_MAP[current_digit % 10];

    for (uint8_t i = 0; i < 7; ++i) {
        const bool is_lit = !bitRead(mapped_segments, i);
        digitalWrite(DISPLAY_PINS[i], is_lit);
    }
}

void setup()
{
    pinMode(PIN_BUTTON_UP, INPUT_PULLUP);
    pinMode(PIN_BUTTON_DOWN, INPUT_PULLUP);

    for (const auto pin : DISPLAY_PINS) {
        pinMode(pin, OUTPUT);
    }

    Serial.begin(9600);
}

void loop()
{
    static bool last_state_up = HIGH;
    static bool last_state_down = HIGH;
    static uint8_t counter = 0;

    const auto current_state_up = digitalRead(PIN_BUTTON_UP);
    const auto current_state_down = digitalRead(PIN_BUTTON_DOWN);

    if (current_state_up == LOW && last_state_up == HIGH) {
        counter++;
    }
    if (current_state_down == LOW && last_state_down == HIGH) {
        counter--;
    }

    last_state_up = current_state_up;
    last_state_down = current_state_down;
    update_display(counter);
    delay(100);
}
