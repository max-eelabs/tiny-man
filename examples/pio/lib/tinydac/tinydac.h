#include <avr/io.h>

/**
 * PWM controlled DAC using OC1A (PB1) output. The output is low-pass filtered.
 *
 * PB1 --4.7k--+--4.7k--+--> OUT
 *             |        |
 *            100nF    100nF
 *             |        |
 *            GND      GND
 */
void pwm_dac_pb1(uint8_t value);