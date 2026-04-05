#include <Arduino.h>
#include <avr/interrupt.h>
#include <tinydac.h>

void pwm_dac_pb1(uint8_t value)
{
    static bool initialized = false;

    if (!initialized) {
        DDRB |= (1 << PB1);
        TCCR1 =
            (1 << PWM1A)  |  // enable PWM mode with OCR1A as comparator
            (1 << COM1A1) |  // non-inverting output on OC1A
            (1 << CS10);     // prescaler = 1 (timer clock = sysclk)

        OCR1C = 0xFF; // full 8-bit period
        initialized = true;
    }

    OCR1A = value;
}