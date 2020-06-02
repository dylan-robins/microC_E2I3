#include <stdint.h>

#define TIM2_Base 100000 /* 100 KHz */

void TIM2_irq_init(uint32_t TIM2_freq);
void clear_TIM2_UIF();
