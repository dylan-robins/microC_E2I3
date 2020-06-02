#ifndef __SERIAL_H
#define __SERIAL_H

#include<stdint.h>

void enable_USART2_GPIO();

void setup_USART2(uint32_t baudrate);

void serial_io_init();

#endif