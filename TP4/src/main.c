#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "sys/clock.h"
#include "sys/cm4.h"
#include "sys/devices.h"
#include "sys/init.h"
#include "sys/serial_io.h"
#include "button.h"
#include "systick.h"

#define __EXO1__

#ifdef __EXO1__

volatile uint8_t led_is_on = 0;
volatile uint8_t counter_0_99 = 0;

void __attribute__((interrupt)) SysTick_Handler() {
    // == 0 test because pull-up resistor: when button is pressed, GND is connected to the pin
    if (counter_0_99 == 99) {
        if (led_is_on == 0) {
            GPIOA.ODR |= (0b1 << 10);
        } else {
            GPIOA.ODR &= ~(0b1 << 10);
        }
        led_is_on ^= 1;
        counter_0_99 = 0;
    } else {
        counter_0_99++;
    }
}

int main() {
    printf("*** Welcome to Nucleo F446 ! ***\r\n");
    // Set LED (PA10) to digital output
    enable_GPIOA();
    GPIOA.MODER = GPIOA.MODER & (~(0b1 << 21));
    GPIOA.MODER = GPIOA.MODER | (0b1 << 20);
    GPIOA.OTYPER = GPIOA.OTYPER & (~(0b1 << 10));

    /* 100 Hz */
    SysTick_init(100);

    while (1) {
        continue;
    }

    return 0;
}
#endif

#ifdef __EXO2__

volatile uint8_t led_is_on = 0;
volatile uint8_t counter_0_99 = 0;

void __attribute__((interrupt)) SysTick_Handler() {
    // == 0 test because pull-up resistor: when button is pressed, GND is connected to the pin
    if (counter_0_99 == 99) {
        led_is_on ^= 1;
        counter_0_99 = 0;
    } else {
        counter_0_99++;
    }
}

int main() {
    printf("*** Welcome to Nucleo F446 ! ***\r\n");
    // Set LED (PA10) to digital output
    enable_GPIOA();
    GPIOA.MODER = GPIOA.MODER & (~(0b1 << 21));
    GPIOA.MODER = GPIOA.MODER | (0b1 << 20);
    GPIOA.OTYPER = GPIOA.OTYPER & (~(0b1 << 10));

    /* 100 Hz */
    SysTick_init(100);

    while (1) {
        if (led_is_on == 0) {
            GPIOA.ODR |= (0b1 << 10);
        } else {
            GPIOA.ODR &= ~(0b1 << 10);
        }
    }

    return 0;
}
#endif

#ifdef __EXO3__
volatile uint8_t led_is_on = 0;


void __attribute__((interrupt)) SysTick_Handler() {
    led_is_on ^= 1;
    SysTick.CTRL &= ~(0b1 << 0);
}

void __attribute__((interrupt)) EXTI15_10_Handler(){
    /* 500 Hz */
    SysTick_init(500);
    EXTI.PR |= (0b1 << 13);
}

int main() {
    printf("*** Welcome to Nucleo F446 ! ***\r\n");
    // Set LED (PA10) to digital output
    enable_GPIOA();
    GPIOA.MODER = GPIOA.MODER & (~(0b1 << 21));
    GPIOA.MODER = GPIOA.MODER | (0b1 << 20);
    GPIOA.OTYPER = GPIOA.OTYPER & (~(0b1 << 10));

    // Set blue button (PC13) to standard input (no pu/pd because already present on board)
    enable_GPIOC();
    GPIOC.MODER &= ~(0b11 << 26);
    GPIOC.PUPDR &= ~(0b11 << 26);

    /* ici */
    enable_SYSCFG();
    SYSCFG.EXTICR4 = (SYSCFG.EXTICR4 & ~(0b1111 << 4)) | (0b1 << 5);
    EXTI.IMR |= (0b1 << 13);
    EXTI.RTSR &= ~(0b1 << 13);
    EXTI.FTSR |= (0b1 << 13);
    EXTI.PR |= (0b1 << 13);
    NVIC.ISER[1] |= (0b1 << 8);
    /* ici */
    
    while (1) {
        if (led_is_on == 1) {
            GPIOA.ODR |= (0b1 << 10);
        } else {
            GPIOA.ODR &= ~(0b1 << 10);
        }
    }

    return 0;
}
#endif

#ifdef __EXO4__
void tempo_500ms() {
    volatile int32_t i = 0;
    while (i < 1000*5155) {
        i++;
    }
    return;
}

volatile uint32_t time_elapsed = 0;
volatile uint32_t timer_enable = 1;

void __attribute__((interrupt)) SysTick_Handler() {
    if (timer_enable) {
        time_elapsed++;
    } else {
        // disable sysTick
        SysTick.CTRL &= ~(0b1 << 0);
    }
}

int main() {
    // timestep = 0.001 ms
    SysTick_init(1000000);
    tempo_500ms();
    timer_enable = 0;
    printf("%ld ticks - %.3lf ms\r\n", time_elapsed, (double)time_elapsed/1000);
}
#endif

#ifdef __EXO5__
#include "sys/serial_io.h"


volatile uint8_t led_is_on = 0;

void __attribute__((interrupt)) SysTick_Handler() {
    led_is_on ^= 1;
}

char _getch() {
    return (char) USART2.DR;
}

int main() {
    printf("*** Welcome to Nucleo F446 ! ***\r\n");
    // Set LED (PA10) to digital output
    enable_GPIOA();
    GPIOA.MODER = GPIOA.MODER & (~(0b1 << 21));
    GPIOA.MODER = GPIOA.MODER | (0b1 << 20);
    GPIOA.OTYPER = GPIOA.OTYPER & (~(0b1 << 10));

    enable_USART2();

    /* 15 Hz */
    uint32_t blink_freq = 15;
    char c;

    SysTick_init(blink_freq);
    printf("Frequency set to %ld Hz\n\r", blink_freq);

    while (1) {
        if (led_is_on == 0) {
            GPIOA.ODR |= (0b1 << 10);
        } else {
            GPIOA.ODR &= ~(0b1 << 10);
        }
        if (((USART2.SR >> 5) & 0b1)) {
            c = _getch();
            if (c  == '+') {
                SysTick_init(blink_freq += 1);
            } else if (c  == '-') {
                SysTick_init(blink_freq -= 1);
            }
            printf("Frequency changed to %ld Hz\n\r", blink_freq);
        }
    }
    return 0;
}

#endif
#ifdef __EXO6__
#include "sys/serial_io.h"

typedef enum {
    RESET,
    RUN,
    STOP
} runmode_t;

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

volatile runmode_t run_mode = 0;
volatile uint32_t time_elapsed = 0;

void await_debounce() {
    volatile uint32_t tmp = 0;
    while (tmp != 65536) {
        tmp++;
    }
}

void __attribute__((interrupt)) SysTick_Handler() {
    time_elapsed++;
}

void __attribute__((interrupt)) EXTI15_10_Handler(){
    EXTI.PR |= (0b1 << 13);
    await_debounce();
    switch (run_mode)
    {
    case RESET:
        run_mode = RUN;
        break;
    case RUN:
        run_mode = STOP;
        break;
    case STOP:
        run_mode = RESET;
        break;
    default:
        break;
    }
}

int main() {
    // enable sysTick clock at 1000Hz (1ms increments)
    SysTick_init(1000);
    enable_USART2();
    USART2.BRR = get_APB1CLK() / 115200; // baudrate 115200

    // Set blue button (PC13) to standard input (no pu/pd because already present on board)
    enable_GPIOC();
    GPIOC.MODER &= ~(0b11 << 26);
    GPIOC.PUPDR &= ~(0b11 << 26);

    enable_SYSCFG();
    SYSCFG.EXTICR4 = (SYSCFG.EXTICR4 & ~(0b1111 << 4)) | (0b1 << 5);
    EXTI.IMR |= (0b1 << 13);
    EXTI.RTSR &= ~(0b1 << 13);
    EXTI.FTSR |= (0b1 << 13);
    EXTI.PR |= (0b1 << 13);
    NVIC.ISER[1] |= (0b1 << 8);
    printf("Booting up...\n\r");

    while (1) {
        if (run_mode == RUN) {
            printf("\r%02ld:%02ld:%03ld", time_elapsed/1000/60, time_elapsed/1000%60, time_elapsed%1000);
        } else if (run_mode == RESET) {
            time_elapsed = 0;
            printf("\r%02ld:%02ld:%03ld", time_elapsed/1000/60, time_elapsed/1000%60, time_elapsed%1000);
        }
    }

    return 0;
}

#endif