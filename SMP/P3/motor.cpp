#include <cstdint>
#ifndef ARDUINO
#define INPUT_PULLUP 2
#define OUTPUT 1
#define HIGH 1
#define LOW 0
void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);
void analogWrite(uint8_t pin, uint8_t val);
int digitalRead(uint8_t pin);
unsigned long millis();
void delay(unsigned long ms);
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#else
#include <Arduino.h>
#endif

constexpr uint8_t PIN_PHOTO_TRANSISTOR = 2;
constexpr uint8_t PIN_BUTTON_DIR = 3;
constexpr uint8_t PIN_BUTTON_SPEED = 7;
constexpr uint8_t PIN_ENABLE = 6;
constexpr uint8_t PIN_MOTOR_IN_1 = 4;
constexpr uint8_t PIN_MOTOR_IN_2 = 5;
constexpr uint8_t MAX_SPEED_LEVELS = 5;

uint8_t current_speed_level = 1;
bool is_direction_forward = true;

bool last_dir_button = HIGH;
bool last_speed_button = HIGH;

void setup()
{
    pinMode(PIN_BUTTON_DIR, INPUT_PULLUP);
    pinMode(PIN_BUTTON_SPEED, INPUT_PULLUP);
    pinMode(PIN_PHOTO_TRANSISTOR, INPUT_PULLUP);

    pinMode(PIN_ENABLE, OUTPUT);
    pinMode(PIN_MOTOR_IN_1, OUTPUT);
    pinMode(PIN_MOTOR_IN_2, OUTPUT);

    digitalWrite(PIN_MOTOR_IN_1, HIGH);
    digitalWrite(PIN_MOTOR_IN_2, LOW);
    analogWrite(PIN_ENABLE, 0);
}

void loop()
{
    auto current_dir_btn = digitalRead(PIN_BUTTON_DIR);
    if (current_dir_btn == LOW && last_dir_button == HIGH) {
        is_direction_forward = !is_direction_forward;
        delay(50);
    }
    last_dir_button = current_dir_btn;

    auto current_speed_btn = digitalRead(PIN_BUTTON_SPEED);
    if (current_speed_btn == LOW && last_speed_button == HIGH) {
        current_speed_level = (current_speed_level % MAX_SPEED_LEVELS) + 1;
        delay(50);
    }
    last_speed_button = current_speed_btn;

    auto is_light_detected = (digitalRead(PIN_PHOTO_TRANSISTOR) == LOW);

    if (is_light_detected) {
        if (is_direction_forward) {
            digitalWrite(PIN_MOTOR_IN_1, HIGH);
            digitalWrite(PIN_MOTOR_IN_2, LOW);
        } else {
            digitalWrite(PIN_MOTOR_IN_1, LOW);
            digitalWrite(PIN_MOTOR_IN_2, HIGH);
        }
        analogWrite(PIN_ENABLE, current_speed_level * (255 / MAX_SPEED_LEVELS));
    } else {
        digitalWrite(PIN_MOTOR_IN_1, LOW);
        digitalWrite(PIN_MOTOR_IN_2, LOW);
        analogWrite(PIN_ENABLE, 0);
    }
}
