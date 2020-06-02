	.syntax unified

	.data

str1:
    .asciz "Ceci est une chaine"
str2:
    .space 0x0, 0x100

	.text

	.globl main
	.thumb_func
main:
	push    {lr}
/* Insert program here */

    ldr     r1, =str1
    ldr     r2, =str2
    
    mov     r3, #0

boucle:
    ldrb    r4, [r1, r3]
    // si fin de chaine; goto fin
    cmp     r4, #0
    beq     fin
    // sinon copier et boucler
    strb    r4, [r2, r3]
    add     r3, #1
    bal     boucle

fin:
    nop

/* return 0; */	 
	mov     r0,#0  
	pop     {pc}
