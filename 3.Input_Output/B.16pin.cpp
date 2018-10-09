#include<avr/io.h>

#define OE 0
#define CLK 1
#define DATA 2
#define SHLD 3

#define Lo(bit) (PORTB &= ~(1 << bit))
#define Hi(bit) (PORTB |= (1 << bit))

uint8_t outA = 0;
uint8_t outB = 0;
uint8_t inA = 0;
uint8_t inB = 0;

void UpdateOutput();
void UpdateInput();

int main() {
    DDRB |= (1 << SHLD) | (1 << OE) | (1 << DATA) | (1 << CLK); // Set as output
    Lo(OE);
    Hi(SHLD);

    while (1) {
        UpdateInput();
        if (inA & 0b00000001) {
            outA |= 0b00000001;
        } else {
            outA &= ~0b00000001;
        }

        if (inB & 0b00000001) {
            outB |= 0b00000001;
        } else {
            outB &= ~0b00000001;
        }
        UpdateOutput();
    }
}

void Output(uint8_t x) {
    for (uint8_t i = 0; i < 8; i++) {
        if (x & 128) {
            Hi(DATA);
        } else {
            Lo(DATA);
        }
        Hi(CLK);
        Lo(CLK);
        x = x << 1;
    }
}
void UpdateOutput() {
    DDRB |= 1 << DATA; // Switch DATA pin as output
    Lo(CLK);
    Output(outA);
    Output(outB);
    Hi(OE);
    Lo(OE);
}

uint8_t Input() {
    uint8_t x = 0;
    for (uint8_t i = 0; i < 8; i++) {
        Hi(CLK);
        x = x >> 1;
        if (PINB & (1 << DATA)) {
            x |= 128;
        }
        Lo(CLK);
    }
    return x;
}

void UpdateInput() {
    Lo(SHLD); // Enable 74165 pin reading, load it to 74165 internal register
    Hi(SHLD); // Disable pin reading
    DDRB &= ~(1 << DATA); // Switch DATA pin as input
    Hi(DATA); // Pull up resistor

    Lo(CLK);
    inA = Input();
    inB = Input();
}
