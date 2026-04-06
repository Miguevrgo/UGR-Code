constexpr uint8_t PIN_INT_ENCODER = 2;
constexpr uint8_t PIN_POTENTIOMETER = A0;
constexpr uint8_t PIN_PWM_MOTOR = 3;

constexpr uint32_t MOTOR_RPM_MULT = 84;
constexpr uint32_t ENCODER_PULSES_REV = 1656;
constexpr int32_t KI = 10;

volatile uint32_t current_rpm = 0;
volatile uint32_t prev_int_time = 0;

uint32_t target_rpm = 0;
int64_t accumulated_error = 0;

void encoder_isr()
{
    uint32_t current_time = micros();
    uint32_t period = max(1, current_time - prev_int_time);

    current_rpm = (MOTOR_RPM_MULT * 1000000UL) / period / ENCODER_PULSES_REV;

    prev_int_time = current_time;
}

uint8_t compute_i()
{
    static uint32_t prev_i_time = 0;
    uint32_t current_time = millis();
    uint32_t dt = current_time - prev_i_time;

    int32_t error = static_cast<int32_t>(target_rpm) - static_cast<int32_t>(current_rpm);
    accumulated_error += error * static_cast<int32_t>(dt);

    int32_t i_component = (KI * accumulated_error) / 1000;
    int32_t pwm_final = i_component;

    if (pwm_final > 255) {
        pwm_final = 255;
    } else if (pwm_final < 1) {
        pwm_final = 1;
    }

    prev_i_time = current_time;
    return static_cast<uint8_t>(pwm_final);
}

void setup()
{
    Serial.begin(9600);

    pinMode(PIN_POTENTIOMETER, INPUT);
    pinMode(PIN_INT_ENCODER, INPUT_PULLUP);
    pinMode(PIN_PWM_MOTOR, OUTPUT);

    analogWrite(PIN_PWM_MOTOR, 0);

    prev_int_time = micros();
    attachInterrupt(digitalPinToInterrupt(PIN_INT_ENCODER), encoder_isr, RISING);
}

void loop()
{
    uint16_t pot_voltage = analogRead(PIN_POTENTIOMETER);
    target_rpm = map(pot_voltage, 0, 1023, 10, 60);

    uint8_t pwm_signal = compute_i();
    analogWrite(PIN_PWM_MOTOR, pwm_signal);

    Serial.println(current_rpm);

    delay(100);
}
