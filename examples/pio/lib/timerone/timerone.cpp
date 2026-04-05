#include <timerone.h>

void timer1_pb1_5Hz(void)
{
    // OC1A (PB1) as output
    DDRB |= (1 << PB1);

    TCCR1 =
    (1 << CTC1)   |   // Clear Timer on Compare
    (1 << COM1A0) |   // Toggle OC1A on compare match
    (1 << CS13)   |
    (1 << CS12)   |
    (1 << CS11)   |
    (1 << CS10);      // clk/16384

    OCR1A = 97;
    OCR1C = 97;
}

void timer1_pb1_15Hz(void)
{

    // OC1A (PB1) as output
    DDRB |= (1 << PB1);

    /*
     * Timer1 configuration:
     * - CTC mode (TOP = OCR1C)
     * - Toggle OC1A on compare match
     * - Prescaler = clk / 16384
     */
    TCCR1 =
        (1 << CTC1)   |   // Clear Timer on Compare
        (1 << COM1A0) |   // Toggle OC1A on compare
        (1 << CS13)   |   // Prescaler bits
        (1 << CS12)   |
        (1 << CS11)   |
        (1 << CS10);      // clk/16384

    // TOP and compare value
    OCR1A = 31;
    OCR1C = 31;
}

void timer1_pb1_1MHz(void)
{
    DDRB |= (1 << PB1);   // OC1A output

    TCCR1 =
        (1 << CTC1)   |   // CTC mode
        (1 << COM1A0) |   // toggle OC1A on compare
        (1 << CS10);      // prescaler = 1

    OCR1A = 7;
    OCR1C = 7;
}
