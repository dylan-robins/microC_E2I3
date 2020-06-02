#ifndef __BUTTON_H
#define __BUTTON_H

#include<stdint.h>

void enable_GPIOC();
void enable_SYSCFG();
void button_init();
void button_irq_init();
uint32_t button_poll();

#endif