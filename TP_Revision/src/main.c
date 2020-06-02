#include <math.h>
#include <stdio.h>

#include "sys/clock.h"
#include "sys/cm4.h"
#include "sys/devices.h"
#include "sys/init.h"
#include "sys/serial_io.h"
#include "systick.h"

/* Inclusion des fichiers d'entête - a décomenter si besoin */
#include "button.h"
#include "counter.h"
#include "led.h"

#define __EXO1__

#ifdef __EXO1__

/*****************************************************************************/
/*                                 TYPEDEFS                                  */
/*****************************************************************************/

typedef enum { SIMPLE_MODE, PWM_MODE } runmode_t;

/*****************************************************************************/
/*                                  GLOBALS                                  */
/*****************************************************************************/

volatile runmode_t mode_g = SIMPLE_MODE;
volatile uint16_t max_ms_g = 500;
volatile uint32_t swell_time_g = 5 * 1000;
volatile float duty_cycle_g = 1;

char _getch() {
    while (((USART2.SR >> 5) & 0b1) != 1) {
    }
    return (char)USART2.DR;
}

/*****************************************************************************/
/*                            INTERRUPT HANDLERS                             */
/*****************************************************************************/

void __attribute__((interrupt)) SysTick_Handler() {
    // Pas besoin de unset l'interrupt flag avec le systick

    volatile static uint16_t ms_counter_s = 0;


    if (mode_g == SIMPLE_MODE) {
        // incr le compteur de ms
        ms_counter_s += 1;
        
        // mode simple: la led clignote toutes les $max_ms_g ms
        if (ms_counter_s >= max_ms_g) {
            ms_counter_s = 0;
            toggle_led();
        }
        if (ms_counter_s % 50 == 0) {
            printf("         %2.2f s       %5d                \r", ms_counter_s/1000.0, max_ms_g);
        }

    } else if (mode_g == PWM_MODE) {
        duty_cycle_g -= 1.0 / swell_time_g;
        if (duty_cycle_g <= 0) {
            duty_cycle_g = 1;
        }
        update_pwm_duty_cycle(duty_cycle_g);
    }
}

void __attribute__((interrupt)) EXTI15_10_Handler() {
    // reset le flag d'interruption
    EXTI.PR |= (1 << 13);

    // changer de mode d'exécution
    if (mode_g == SIMPLE_MODE) {
        printf("Activation du mode PWM !\r\n");
        mode_g = PWM_MODE;
        led_pwm_init(1000);
        toggle_pwm_led();
    } else {
        printf("Activation du mode simple !\r\n");
        printf("** | CHRONO-M0 | PERIODE | **\r\n");
        mode_g = SIMPLE_MODE;
        led_init();
    }
}

void __attribute__((interrupt)) USART2_Handler() {
    USART2.SR &= ~(1 << 5);

    char c = (char) USART2.DR;
    if (mode_g == SIMPLE_MODE) {
        if (c == '+') {
            max_ms_g += 100;
        } else if (c == '-') {
            max_ms_g -= 100;
        }
        // apply limits: max_ms_g in [2^0, 2^12]
        if (max_ms_g > 4096) {
            max_ms_g = 4096;
        } else if (max_ms_g < 1) {
            max_ms_g = 1;
        }
        
    } else {
        if (c == '+') {
            swell_time_g += 100;
        } else if (c == '-') {
            swell_time_g -= 100;
        }
        // apply limits: swell_time_g in [1*1000, 10*1000]
        if (swell_time_g > 10000) {
            swell_time_g = 10000;
        } else if (swell_time_g < 1000) {
            swell_time_g = 1000;
        }
    }
}

/*****************************************************************************/
/*                                    MAIN                                   */
/*****************************************************************************/
int main(void) {

    enable_GPIOA();  // PA5 => LED
    // Setup mode simple
    led_init();
    // Setup mode pwm
    enable_TIM2();

    enable_GPIOC();  // PC13 => Bouton poussoir
    enable_SYSCFG();
    PC13_init();
    PC13_irq_init();
    

    SysTick_init(1000);

    setup_USART2(9600);
    // USART2.CR1 |= (1 << 5); // enable RXNE interrupt for USART2
    // NVIC.ISER[1] |= (0b1 << 6);

    printf("** | CHRONO-M0 | PERIODE | **\n\r");
    // main loop
    while (1) {
        char c = _getch();
        if (mode_g == SIMPLE_MODE) {
            if (c == '+') {
                max_ms_g += 100;
            } else if (c == '-') {
                max_ms_g -= 100;
            }
            // apply limits: max_ms_g in [2^0, 2^12]
            if (max_ms_g > 4096) {
                max_ms_g = 4096;
            } else if (max_ms_g < 1) {
                max_ms_g = 1;
            }
            
        } else {
            if (c == '+') {
                swell_time_g += 100;
            } else if (c == '-') {
                swell_time_g -= 100;
            }
            // apply limits: swell_time_g in [1*1000, 10*1000]
            if (swell_time_g > 10000) {
                swell_time_g = 10000;
            } else if (swell_time_g < 1000) {
                swell_time_g = 1000;
            }
        }
        printf("         %d ms       %5d\r", 42, max_ms_g);
        continue;
    }
    return 0;
}

#endif