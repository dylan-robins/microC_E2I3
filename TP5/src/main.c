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

#define __EXO5_3__

#ifdef __EXO5_1__

volatile uint8_t led_is_on = 0;
volatile uint8_t counter_0_99 = 0;

void __attribute__((interrupt)) SysTick_Handler() {
    // == 0 test because pull-up resistor: when button is pressed, GND is
    // connected to the pin
    if (counter_0_99 == 99) {
        if (led_is_on == 0) {
            GPIOA.ODR |= (0b1 << 5);
        } else {
            GPIOA.ODR &= ~(0b1 << 5);
        }
        led_is_on ^= 1;
        counter_0_99 = 0;
    } else {
        counter_0_99++;
    }
}

int main() {
    printf("*** Welcome to Nucleo F446 ! ***\r\n");
    // Set LED (PA5) to digital output
    enable_GPIOA();
    led_init();

    /* 100 Hz */
    SysTick_init(100);

    while (1) {
        continue;
    }

    return 0;
}
#endif

#ifdef __EXO5_2__
volatile float g_duty_cycle = 0;

void __attribute__((interrupt)) SysTick_Handler() {
    const uint16_t swell_time = 5000;  // ms

    g_duty_cycle += 1.0 / swell_time;
    if (g_duty_cycle >= 1) {
        g_duty_cycle = 0;
    }
    update_pwm_duty_cycle(g_duty_cycle);
}

int main() {
    printf("*** Welcome to Nucleo F446 ! ***\r\n");
    enable_GPIOA();

    /* Activer Systick 1000 Hz */
    SysTick_init(1000);

    /* Activer le Timer -  TIM2 */
    enable_TIM2();

    /* Initialiser TIM2 en mode PWM */
    led_pwm_init(1000);
    toggle_pwm_led();

    while (1) {
        continue;
    }

    return 0;
}
#endif

#ifdef __EXO5_3__
volatile float g_duty_cycle = 0;
volatile uint8_t g_state = 0;

/* Handler d'interruption du bouton sur PC13 - a décommenter ci-besoin
 * EXTI.PR permet d'abaisser le drapeau d'interruption (associé à PC13) */
void __attribute__((interrupt)) EXTI15_10_Handler() {
    EXTI.PR |= (1 << 13);
    g_state ^= 1;
    printf("PC13 interrupt received  - %s !\r\n", (g_state)?"ON":"OFF");
}

/* Handler d'interruption du TIM2 - a décommenter ci-besoin
 * clear_TIM2_UIF permet d'abaisser le drapeau d'it (update interrupt flag) du
 * TIM2 */

/*
void __attribute__((interrupt)) TIM2_Handler() {
        clear_TIM2_UIF();
}
*/

void __attribute__((interrupt)) SysTick_Handler() {
    const uint16_t swell_time = 5000;  // ms

    if (g_state) {
        g_duty_cycle += 1.0 / swell_time;
        if (g_duty_cycle >= 1) {
            g_duty_cycle = 0;
        }
        update_pwm_duty_cycle(g_duty_cycle);
    }
}

int main() {
    printf("*** Welcome to Nucleo F446 ! ***\r\n");
    /* Initialisation des GPIO - a decommenter en fonction du programme */
    enable_GPIOA();
    /* enable_GPIOB();*/
    enable_GPIOC();

    /* Activer Systick chaque ? Hz */
    SysTick_init(1000);

    /* Activer les  interruptions (boutton bleu - PC13)*/
    enable_SYSCFG();
    PC13_init();
    PC13_irq_init();

    /* Configuration de l'USART - baudrate */
    setup_USART2(115200);

    /* Activer le Timer -  TIM2 */
    enable_TIM2();

    /* Initialiser TIM2 en mode PWM */
    led_pwm_init(1000);
    toggle_pwm_led();

    /* Initialiser TIM2 pour generer une interruption */
    // TIM2_irq_init(1000);

    /* Initialiser la LED em mode simple (GPIO output on/off) */
    /* led_init(); */
    /* toggle_led(); */

    while (1) {
        continue;
    }

    return 0;
}
#endif
