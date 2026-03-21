#include <Wire.h>
#include <stdint.h>

// Se usa constexpr ya que tiene internal linkeage en C++ por defect
constexpr uint8_t TRIGGER_PIN = 5;
constexpr uint8_t ECHO_PIN = 4;
constexpr uint16_t TIMEOUT_ECO = 23200;
constexpr uint8_t SLAVE_I2C_ADDR = 8;

unsigned long mide_distancia(uint8_t triggerPin, uint8_t ecoPin)
{
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    return pulseIn(ecoPin, HIGH, TIMEOUT_ECO);
}

void setup()
{
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    digitalWrite(TRIGGER_PIN, LOW);
    Wire.begin();
}

void loop()
{
    auto distanceCM = mide_distancia(TRIGGER_PIN, ECHO_PIN) / 58;

    if (distanceCM >= 40 && distanceCM <= 290) {
        Wire.beginTransmission(SLAVE_I2C_ADDR);
        Wire.write(lowByte(distanceCM));
        Wire.write(highByte(distanceCM));
        Wire.endTransmission();
    }
    delay(100);
}
