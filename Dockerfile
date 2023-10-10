FROM alpine:latest
RUN apk update && apk add gcc-avr avr-libc make
