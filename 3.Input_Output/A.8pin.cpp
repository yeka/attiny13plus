#include<avr/io.h>

#define LATCH 0
#define CLK 1
#define DATA 2
#define SHLD 3

#define Lo(bit) (PORTB &= ~(1 << bit))
#define Hi(bit) (PORTB |= (1 << bit))
#define Rise(bit) Lo(bit); Hi(bit);

uint8_t outA = 0;
uint8_t inA = 0;

void UpdateOutput();
void UpdateInput();

int main() {
    DDRB |= (1 << SHLD) | (1 << LATCH) | (1 << DATA) | (1 << CLK); // Set as output
    Hi(SHLD);

    while (1) {
        UpdateInput();
        if (inA & 0b00000001) {
            outA |= 0b00000001;
        } else {
            outA &= ~0b00000001;
        }
        UpdateOutput();
    }
}

void UpdateOutput() {
    DDRB |= 1 << DATA; // Switch DATA pin as output
    uint8_t x = outA;
    for (uint8_t i = 0; i < 8; i++) {
        if (x & 128) {
            Hi(DATA);
        } else {
            Lo(DATA);
        }
        Rise(CLK);
        x = x << 1;
    }
    Rise(LATCH);
}

void UpdateInput() {
    Lo(SHLD); // Enable 74165 pin reading, load it to 74165 internal register
    Hi(SHLD); // Disable pin reading
    DDRB &= ~(1 << DATA); // Switch DATA pin as input
    Hi(DATA); // Pull up resistor

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
    inA = x;
}
