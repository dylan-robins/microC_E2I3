#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "sys/clock.h"
#include "sys/cm4.h"
#include "sys/devices.h"
#include "sys/init.h"
#include "sys/serial_io.h"
#include "systick.h"
#include "button.h"

void pause(int32_t duration) {
    volatile int32_t i = 0;
    while (i < duration*5155) {
        i++;
    }
    return;
}

void ex1() {
    // Set LED (PA10) to digital output
    enable_GPIOA();
    GPIOA.MODER = GPIOA.MODER & (~(0b1 << 21));
    GPIOA.MODER = GPIOA.MODER | (0b1 << 20);
    GPIOA.OTYPER = GPIOA.OTYPER & (~(0b1 << 10));

    // Set blue button (PC13) to standard input (no pu/pd because already present on board)
    enable_GPIOC();
    GPIOC.MODER &= ~(0b11 << 26);
    GPIOC.PUPDR &= ~(0b11<< 26);

    while (1) {
        // == 0 test because pull-up resistor: when button is pressed, GND is connected to the pin
        if (((GPIOC.IDR >> 13) & 0b1) == 0) {
            GPIOA.ODR |= (0b1 << 10);
        } else {
            GPIOA.ODR &= ~(0b1 << 10);
        }
    }
}

void ex2() {
    // Activate GPIOA clock control
    RCC.AHB1ENR = RCC.AHB1ENR | (0b1 << 0);

    // PA10 (Digital Out 2) set to output push/pull mode
    GPIOA.MODER = GPIOA.MODER & (~(0b1 << 21));
    GPIOA.MODER = GPIOA.MODER | (0b1 << 20);
    GPIOA.OTYPER = GPIOA.OTYPER & (~(0b1 << 10));

    uint8_t state = 0;

    while (1) {
        pause(1000);
        if (state) {
            GPIOA.ODR = GPIOA.ODR & (~(0b1 << 10));
            state = 0;
        } else {
            GPIOA.ODR = GPIOA.ODR | (0b1 << 10);
            state = 1;
        }
    }
}

void _putch(const char c) {
    USART2.DR = c;
    if (c == '\n') _putch('\r');
    if (c == '\r') _putch('\n');
    while (((USART2.SR >> 7) & 0b1) != 1) {}
}

char _getch() {
    while (((USART2.SR >> 5) & 0b1) != 1) {}
    return (char) USART2.DR;
}

void _puts(const char* s) {
    uint32_t i = 0;
    do {
        _putch(s[i]);
    } while (s[i] != '\0');
}

void ex3() {
    enable_USART2();

    char c;
    while (1) {
        c = _getch();
        _putch(c);
    }
}

int main() {
    printf("*** Welcome to Nucleo F446 ! ***\r\n");

    ex1();
    //ex2();
    //ex3();

    return 0;
}
