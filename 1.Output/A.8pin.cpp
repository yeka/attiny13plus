#include<avr/io.h>
#include<util/delay.h>

#define LATCH 0 // Pin 12 of 74595
#define CLK 1   // Pin 11 of 74595
#define DATA 2  // Pin 14 of 74595

#define Lo(bit) PORTB &= ~(1 << bit);
#define Hi(bit) PORTB |= (1 << bit);
#define Rise(bit) Lo(bit); Hi(bit);

uint8_t outA = 0;

void UpdateOutput();

int main() {
    DDRB |= (1 << LATCH) | (1 << DATA) | (1 << CLK); // Set as output

    while (1) {
        outA |= 1;
        UpdateOutput();
        _delay_ms(1000);
        outA &= ~1;
        UpdateOutput();
        _delay_ms(1000);
    }
}

void UpdateOutput() {
    uint8_t x = outA;
    for (uint8_t i = 0; i < 8; i++) {
        if (x & 128) {
            Hi(DATA);
        } else {
            Lo(DATA);
        }
        Rise(CLK); // Data shifted on rise
        x = x << 1;
    }
    Rise(LATCH); // Output transfered on rise
}
