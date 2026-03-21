#include <LiquidCrystal.h>
#include <Wire.h>
#include <stdint.h>

constexpr uint8_t SLAVE_I2C_ADDR = 8;

constexpr uint8_t PIN_RS = 12;
constexpr uint8_t PIN_E = 11;
constexpr uint8_t PIN_D0 = 2;
constexpr uint8_t PIN_D1 = 3;
constexpr uint8_t PIN_D2 = 4;
constexpr uint8_t PIN_D3 = 5;
constexpr uint8_t PIN_D4 = 6;
constexpr uint8_t PIN_D5 = 7;
constexpr uint8_t PIN_D6 = 8;
constexpr uint8_t PIN_D7 = 9;

LiquidCrystal lcd(PIN_RS, PIN_E, PIN_D0, PIN_D1, PIN_D2, PIN_D3, PIN_D4, PIN_D5, PIN_D6, PIN_D7);

void callback_recepcion_i2c(int receivedBytes)
{
    if (receivedBytes >= 2) {
        int byteLow = Wire.read();
        int byteHigh = Wire.read();

        if (byteLow != -1 && byteHigh != -1) {
            uint16_t distance = (byteHigh << 8) | byteLow;

            lcd.setCursor(0, 1);
            lcd.print("                ");
            lcd.setCursor(0, 1);
            lcd.print(distance);
            lcd.print(" cm");
        } else {
            lcd.setCursor(0, 1);
            lcd.print("Error RX        ");
        }
    }
}

void setup()
{
    lcd.begin(16, 2);
    lcd.print("20/03/26 M.A.D.");

    Wire.begin(SLAVE_I2C_ADDR);
    Wire.onReceive(callback_recepcion_i2c);
}

void loop() { }
