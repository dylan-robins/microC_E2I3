#include <stdint.h>

#define TIM2_Base 100000 /* 100 KHz */

void led_init();
void toggle_led();

void led_pwm_init(uint32_t TIM2_freq);
void toggle_pwm_led();
void update_pwm_duty_cycle(float dc);
