	.syntax unified

    .data
str:
    .asciz "Janvier"

	.text

	.globl main
	.thumb_func
main:
	push    {lr}
/* Insert program here */

    bl init_USART2

    bl init_USART2_GPIOA
    

    ldr r5, =str
    mov r6, #0

boucle:
    ldrb r0, [r5, r6]
    add r6, #1
    
    cmp r0, #0
    beq fin

    bl _putch

    bal boucle

fin:
    mov r0, #'\n'
    bl _putch
    mov r0, #'\r'
    bl _putch

/* return 0; */	 
	mov     r0,#0  
	pop     {pc}
