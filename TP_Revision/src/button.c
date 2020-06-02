#include "button.h"

#include "sys/cm4.h"
#include "sys/devices.h"

void PC13_init() {
    /* configure PC13 as input, no pull */
    GPIOC.MODER &= ~(0b11 << 26);
    GPIOC.PUPDR &= ~(0b11 << 26);
}

void PC13_irq_init() {
    /* configure interruptions on PC13 */
    /* set PC13 as EXTI13 input */
	SYSCFG.EXTICR4 = (SYSCFG.EXTICR4 & ~(0b1111 << 4)) | (0b1 << 5);


    /* setup interrupt for EXTI13, falling edge */
    /* ... to complete ... */
    EXTI.IMR |= (0b1 << 13);
    EXTI.RTSR &= ~(0b1 << 13);
    EXTI.FTSR |= (0b1 << 13);

	/* Reset interrupt flag */
    EXTI.PR |= (0b1 << 13);

    /* enable EXTI15_10 IRQ */
    NVIC.ISER[1] |= (0b1 << 8);
}
