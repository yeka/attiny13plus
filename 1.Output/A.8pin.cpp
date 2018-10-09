#include<avr/io.h>
#include<util/delay.h>

#define OE 0
#define CLK 1
#define DATA 2

#define Lo(bit) (PORTB &= ~(1 << bit))
#define Hi(bit) (PORTB |= (1 << bit))

uint8_t outA = 0;

void UpdateOutput();

int main() {
    DDRB |= (1 << OE) | (1 << DATA) | (1 << CLK); // Set as output
    Lo(OE); // Set OE Low

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
    Lo(CLK);
    uint8_t x = outA;
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
    Hi(OE);
    Lo(OE);
}
