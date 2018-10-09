#include<avr/io.h>
#include<util/delay.h>

#define OE 0
#define CLK 1
#define DATA 2
#define SHLD 3

#define Lo(bit) (PORTB &= ~(1 << bit))
#define Hi(bit) (PORTB |= (1 << bit))
#define Clear(x, bit) (x &= ~(1 << bit))
#define Set(x, bit) (x |= (1 << bit))

uint8_t outA = 0;
uint8_t outB = 0;

void UpdateOutput();
void Output(uint8_t x);

int main() {
    DDRB |= 0b00001111; // B.0 - B.3 = Output
    PORTB &= 0b11110000; // B.0 - B.3 Set to low

    Lo(OE); // Disable output
    Hi(SHLD); // Disable load

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
    Lo(CLK);
    Set(DDRB, DATA); // Set data as output
    Output(outB);
    Output(outA);
    Hi(OE);
    Lo(OE);
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