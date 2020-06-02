	.syntax unified

	.data

alphabet:
	.ascii 	"AZERTYUIOPQSDFGHJKLMWXCVBN"

	.text

	.globl main
	.thumb_func
main:
	push    {lr}
/* Insert program here */

    mov     r1, #17
    ldr     r3, =alphabet
    ldrb    r0, [r3, r1]

    nop


/* return 0; */	 
	mov     r0,#0  
	pop     {pc}
