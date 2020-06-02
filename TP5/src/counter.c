#include "sys/devices.h"
#include "sys/cm4.h"
#include "sys/clock.h"
#include "counter.h"

void TIM2_irq_init(uint32_t TIM2_freq)
{
	/* configure TIM2_CH1 as counter */
	TIM2.CR1   = 0x0080; /* <-- to modify: Buffered preload up-counting mode, + counter enable */
	TIM2.CR2   = 0x0000;
	TIM2.SMCR  = 0x0000;
	TIM2.DIER  = 0x0000; /* <-- to modify: activate update interrupt enable */
	TIM2.CCMR1 = 0x0068; /* <-- select Frozen Mode - Channel 1 */
	TIM2.CCMR2 = 0x0000;
	TIM2.CCER  = 0x0010;
	TIM2.CNT   = 0x0000;
	TIM2.PSC   = get_APB1TIMCLK() / TIM2_Base ; /* <-- to modify: Prescaler */	
	TIM2.ARR   = TIM2_Base / TIM2_freq;   /* <-- to modify: Auto-reload register according to TIM2_freq */
	TIM2.EGR  |= 0x0001;   /* <-- to modify: activate update event */

	/* enable TIM2 IRQ */
	NVIC.ISER[28/32]=(1<<(28%32)); 
}

void clear_TIM2_UIF()
{
	TIM2.SR = 1; /* <-- to modify: clear update interrupt flag du TIM2 */
}
