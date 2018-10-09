MCU=attiny13a
FCPU=9600000

default:
	@echo "Usage:"
	@echo "  make a     build example A"
	@echo "  make b     build example B"
a:
	@echo "Building..."
	@mkdir -p build
	@rm -f build/main.elf build/main.o build/main.hex
	@docker run --rm -it -v $(shell pwd):/app -e MCU=$(MCU) -e FCPU=$(FCPU) yeka/avr:latest avr-gcc -g -Os -c -mmcu=${MCU} -DF_CPU=${FCPU} -o /app/build/main.o -I /usr/include /app/A.8pin.cpp
	@docker run --rm -it -v $(shell pwd):/app -e MCU=$(MCU) -e FCPU=$(FCPU) yeka/avr:latest avr-gcc -g -Os -mmcu=${MCU} -DF_CPU=${FCPU} -o /app/build/main.elf /app/build/main.o
	@docker run --rm -it -v $(shell pwd):/app -e MCU=$(MCU) -e FCPU=$(FCPU) yeka/avr:latest avr-objcopy -j .text -j .data -O ihex /app/build/main.elf /app/build/main.hex
	@docker run --rm -it -v $(shell pwd):/app -e MCU=$(MCU) -e FCPU=$(FCPU) yeka/avr:latest avr-size /app/build/main.elf
b:
	@echo "Building..."
	@mkdir -p build
	@rm -f build/main.elf build/main.o build/main.hex
	@docker run --rm -it -v $(shell pwd):/app -e MCU=$(MCU) -e FCPU=$(FCPU) yeka/avr:latest avr-gcc -g -Os -c -mmcu=${MCU} -DF_CPU=${FCPU} -o /app/build/main.o -I /usr/include /app/B.16pin.cpp
	@docker run --rm -it -v $(shell pwd):/app -e MCU=$(MCU) -e FCPU=$(FCPU) yeka/avr:latest avr-gcc -g -Os -mmcu=${MCU} -DF_CPU=${FCPU} -o /app/build/main.elf /app/build/main.o
	@docker run --rm -it -v $(shell pwd):/app -e MCU=$(MCU) -e FCPU=$(FCPU) yeka/avr:latest avr-objcopy -j .text -j .data -O ihex /app/build/main.elf /app/build/main.hex
	@docker run --rm -it -v $(shell pwd):/app -e MCU=$(MCU) -e FCPU=$(FCPU) yeka/avr:latest avr-size /app/build/main.elf

sh:
	@docker run --rm -it -v $(shell pwd):/app -e MCU=$(MCU) -e FCPU=$(FCPU) yeka/avr:latest sh