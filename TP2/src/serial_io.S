	.syntax unified

	.text

	.globl init_USART2

init_USART2:
	push {r0, r2, r3, r4, lr}

	/* Enable USART2 on APB1 */
	/* RCC.APB1EN = (1 << 17) */
	/* RCC.APB1LPENR = (1 << 17) */
	ldr r3, =RCC
	ldr r2, [r3,0x40]
	orr r2, r2, #0x20000
	str r2, [r3,0x40]
	ldr r2, [r3,0x60]
	orr r2, r2, #0x20000
	str r2, [r3,0x60]	

	/* Configuration of baudrate */	
	/* FPCLK=24MHz, OVER8=0 for oversampling of 16*/
	/* 9600 bauds, 156,25 to be programmed in USART_BRR */
	ldr r3, =USART2	
	/* ldr r4, =0x09C4 */	/* FPCLK = 24 Mhz */
	/* ldr r4, =0x1117 */	/* FPCLK = 42 Mhz */
	cmp r0, #115200
	beq L115200

L9600:	ldr r4, =0x0683	/* FPCLK = 16 Mhz */
	b  LconfBRR

L115200:
	ldr r4, =0x008B	/* FPCLK = 16 Mhz */

LconfBRR:
	str r4, [r3,0x08]

	/* Configure CR3 : SCEN=0, IREN=0, HDSEL=0 */
	ldr r2, [r3,0x14]
	ldr r4, =0xFDD
	and r2, r2, r4
	str r2, [r3,0x14]

	/* Configure CR2 : LINEN=0, STOP=0, CLKEN=0 */
	ldr r2, [r3,0x10]
	and r2, r2, #0xFF
	str r2, [r3,0x10]

	/* Configure CR1 : USART enable, no parity, 8 bits */
	/* RE=1, TE=1, PCE=0, M=0, OVER8=0 */
	ldr r2, [r3,0x0C]
	ldr r4, =0x6BFF
	and r2, r2, r4
	ldr r4, =0x200C
	orr r2, r2, r4
	str r2, [r3,0x0C]

	pop {r0, r2, r3, r4, pc}


	.globl init_USART2_GPIOA

init_USART2_GPIOA:
	push {r2, r3, lr}
	/* Enable GPIOA - deja fait dans le main */
	/* Enable GPIOA - RCC.AHB1ENR <- 0x01 */
	/* Reset GPIOA - RCC.AHB1ENR <- 0x01 */
	ldr r3, =RCC
	ldr r2, [r3,0x30]	
	orr r2, r2, #1
	str r2, [r3,0x30]
	ldr r2, [r3,0x50]	
	orr r2, r2, #1
	str r2, [r3,0x50]

	/* Enable PA2 & PA3 alternate function */
	ldr r3, =GPIOA
	ldr r2, [r3,0x20]
	bic r2, r2, #0xFF00
	orr r2, r2, #0x7700
	str r2, [r3,0x20]	/* 0b0111 for AFRL2 & AFRL3 - AF7 */

	/* Mode register as Alternate Function */
	ldr r2, [r3, 0x0]
	bic r2, r2, #0xF0
	orr r2, r2, #0xA0
	str r2, [r3,0x0]	/* MODER2 = MODER3 = 0b10 */

	pop {r2, r3, pc}




	.globl _putch

_putch:
	push {r0, r2, r3, lr}
	ldr r3, =USART2	

Lputc:	ldr r2, [r3,#0]
	and r2, r2, #0x80	/* test of TXNE */
	cmp r2, #0		
	beq Lputc		/* polling until TXNE bit = 1 */
	and r0, r0, #0xFF
	str r0, [r3,#4]

	pop {r0, r2, r3, pc}
	
	
	.globl _getch

_getch:
	push {r2, r3, lr}
	ldr r3, =USART2	

Lgetc:	ldr r2, [r3,#0]
	and r2, r2, #(1<<5)	/* test of RXNE */
	cmp r2, #0		
	beq Lgetc		/* polling until RXNE bit = 1 */
	ldr r0, [r3,#4]

	pop {r2, r3, pc}

