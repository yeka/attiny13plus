# ATTiny13 Plus

This project focus on utilizing ATTiny13 and extending its GPIO at lowest cost possible.
Serial In Parallel Out, 74595, and its counterpart, 74165, is used because of its price.

IO Extender like PCF8574T have the price as much as ATTiny13 itself.
ATTiny85 price is even higher than ATMega8 that it's better to utilize ATMega8 instead.
Price comparison is provided below.
Of course the condition may vary for you.

The aim of this projects is to provide an insight on what can be done with ATTiny13 with 74595/74165.
Also, by create a minimal code to handle additional GPIO, we can see how much space is left for the main logic.
In the end, it's up to you to decide wether it's worthy to utilize it.

## Price Comparison

This price is compiled at Oct 8th, 2018, using AliExpress, for 100pcs of items and with free shipping, sorted by the lowest price.
```
- ATTiny13a at US  $26.00
- 74HC595   at US   $2.75
- 74HC165   at US   $4.30
- PCF8574T  at US  $19.78
- ATTiny85  at US $118.00
- ATMega8a  at US  $51.00
```

Below is price comparison alongside available GPIO
```
ATTiny13a                          = US $26.00 - 5 GPIO (leaving RST alone)
ATTiny13a + 74HC595                = US $28.75 - 2 GPIO, +8 Out (3 GPIO is used to drive output extension)
ATTiny13a + 74HC165                = US $30.30 - 2 GPIO, +8 In
ATTiny13a + 2x74HC595              = US $31.50 - 2 GPIO, +16 Out
ATTiny13a + 74HC595 + 74HC165      = US $33.05 - 1 GPIO, +8 In, +8 Out (additional 1 GPIO to control input)
ATTiny13a + 2x74HC165              = US $34.60 - 2 GPIO, +16 In
ATTiny13a + 2x74HC595 + 2x74HC165  = US $40.10 - 1 GPIO, +16 In, +16 Out
ATTiny13a + PCF8574T               = US $45.78 - 3 GPIO, +8 IO - I2C
ATMega8a                           = US $51.00 - 23 GPIO (18 more GPIO)
```

## Technique

Driving 74HC595 and/or 74HC165 require at minimum 3 valuable GPIO, since additional IO won't have features such as PWM, INT, ADC and such.
The 3 GPIO can be freely selected, so we can save which GPIO feature we want to keep.

74HC595 require at least DATA pin, CLK pin and OE (Output Enable) pin.
74HC165 require at least DATA pin, CLK pin and SHLD (Shift/Load) pin.
When using both together, we can combine DATA & CLK pin, so that we can only require 4 pin.
Hacking forward, SHLD pin can be driven from 74HC595 output, so that only 3 GPIO is required while decreasing the additional output by 1.

Now, ATTiny13a has only 1024 bytes of program memory.
Below are examples of minimal implementation with different function to drive additional output and/or input.
We will see how many bytes is required and how many bytes is left available for main logic.

### 1. Simple Additional Output
### 2. Simple Additional Input
### 3. Simple Additional Input/Output
### 4. Additional Input/Output using 3 GPIO
### 5. I2C
### 6. UART
