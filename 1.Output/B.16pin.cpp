#include<avr/io.h>
#include<util/delay.h>

#define LATCH 0
#define CLK 1
#define DATA 2

#define Lo(bit) (PORTB &= ~(1 << bit))
#define Hi(bit) (PORTB |= (1 << bit))
#define Clear(x, bit) (x &= ~(1 << bit))
#define Set(x, bit) (x |= (1 << bit))
#define Rise(bit) Lo(bit); Hi(bit);

uint8_t outA = 0;
uint8_t outB = 0;

void UpdateOutput();
void Output(uint8_t x);

int main() {
    DDRB |= 0b00001111; // B.0 - B.3 = Output
    PORTB &= 0b11110000; // B.0 - B.3 Set to low

    while (1) {
        outA |= 1;
        outB |= 1;
        UpdateOutput();
        _delay_ms(1000);
        outA &= ~1;
        outB &= ~1;
        UpdateOutput();
        _delay_ms(1000);
    }
}

void UpdateOutput() {
    Output(outB);
    Output(outA);
    Rise(LATCH);
}

void Output(uint8_t x) {
        for (uint8_t i = 0; i < 8; i++) {
        if (x & 128) {
            Hi(DATA);
        } else {
            Lo(DATA);
        }
        Rise(CLK);
        x = x << 1;
    }
}