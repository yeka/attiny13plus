#include<avr/io.h>

#define SHLD 0
#define CLK 1
#define DATA 2

#define Lo(bit) (PORTB &= ~(1 << bit))
#define Hi(bit) (PORTB |= (1 << bit))

uint8_t inA = 0;

void UpdateInput();

int main() {
    DDRB |= (1 << SHLD) | (1 << CLK); // Set as output
    DDRB &= ~(1 << DATA);
    Hi(DATA); // Input DATA is Pulled-Up
    Hi(SHLD); // Set OE Low

    while (1) {
        UpdateInput();
        if (~inA & 0b00000001) { // Check input on pin 0 (0-7)
            Lo(4); // Turn on LED on PORTB.4
        } else {
            Hi(4); // Turn off LED on PORTB.4
        }
    }
}

void UpdateInput() {
    Lo(SHLD);
    Lo(CLK);
    uint8_t x = 0;
    for (uint8_t i = 0; i < 8; i++) {
        Hi(CLK);
        x = x >> 1;
        if (PINB & (1 << DATA)) {
            x |= 128;
        }
        Lo(CLK);
    }
    Hi(SHLD);
    inA = x;
}