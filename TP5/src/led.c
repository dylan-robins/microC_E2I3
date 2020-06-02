#include "led.h"

#include "sys/clock.h"
#include "sys/cm4.h"
#include "sys/devices.h"

/* LED as simple output */
/* ------------------------------------------------------------------------ */
void led_init() {
    /* Configure PA5 as output, pushpull, high speed */
    GPIOA.MODER = GPIOA.MODER & (~(0b1 << 11));
    GPIOA.MODER = GPIOA.MODER | (0b1 << 10);
    GPIOA.OTYPER = GPIOA.OTYPER & (~(0b1 << 5));
}

void toggle_led() {
    /* on/off PA5 (nucleo led) */
    GPIOA.ODR ^= (0b1 << 5);
}

/* LED as output using PWM */
/* ------------------------------------------------------------------------ */
void led_pwm_init(uint32_t TIM2_freq) {
    /* Configure PA5 as alternate function AF1 for TIM2_CH1 */
    GPIOA.MODER = (GPIOA.MODER & ~(0b11 << 10)) | ( 0b1 << 11);
    GPIOA.AFRL = (GPIOA.AFRL & ~(0xf << 20)) | (0b1 << 20);

    /* configure TIM2_CH1 as PWM output */
    TIM2.CR1 = 0x0080; /* <-- to modify: Buffered preload up-counting mode */
    TIM2.CR2 = 0x0000;
    TIM2.SMCR = 0x0000;
    TIM2.DIER = 0x0000;
    TIM2.CCMR1 = 0x0068; /* <-- to modify: mode */
    TIM2.CCMR2 = 0x0000; /* <-- to modify: mode */
    TIM2.CCER = 0x0001;  /* <-- to modify: Channel X output to pin X*/
    TIM2.CNT = 0x0000;
    TIM2.PSC = get_APB1TIMCLK() / TIM2_Base; /* <-- to modify: Prescaler */
    TIM2.ARR = TIM2_Base / TIM2_freq; /* <-- to modify: Auto-reload register according to TIM2_freq */
    TIM2.CCR1 = 0x0000; /* <-- to modify: duty cycle according to TIM2_freq */
    TIM2.CCR2 = 0x0000; /* <-- to modify: duty cycle according to TIM2_freq */
    TIM2.CCR3 = 0x0000; /* <-- to modify: duty cycle according to TIM2_freq */
    TIM2.CCR4 = 0x0000; /* <-- to modify: duty cycle according to TIM2_freq */
    TIM2.EGR |= 0x0001; /* <-- to modify: activate update event */
}

void toggle_pwm_led() {
    /* on/off timer */
    TIM2.CR1 ^= 0x1; /* <-- to modify : counter enable/disabled */
}

void update_pwm_duty_cycle(float dc) {
    /* Update duty cycle TIM2_CH1 */
    TIM2.CCR1 = TIM2.ARR * dc; /* <-- to modify : update duty cycle according to 'dc' variable */
}
