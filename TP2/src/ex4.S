	.syntax unified

	.data

str1:
    .asciz "Ceci est une chaine"
str2:
    .asciz " et ceci en est une autre"
str3:
    .space 0x0, 0x100

	.text

	.globl main
	.thumb_func
main:
	push    {lr}
/* Insert program here */

    ldr     r1, =str1
    ldr     r2, =str2
    ldr     r3, =str3
    
    mov     r4, #0

bcl_str1:
    //charger le i-ieme de str1
    ldrb    r5, [r1, r4]

    // arreter a la fin de la chaine
    cmp     r5, #0
    beq     fin_bcl_str1
    
    // ecrire au i-ieme de str3
    strb    r5, [r3, r4]
    add     r4, #1

    bal bcl_str1

fin_bcl_str1:
    mov     r6, #0

bcl_str2:
    // charger le j-ieme de str2
    ldrb    r5, [r2, r6]
    // ecrire au i-ieme de str3
    strb    r5, [r3, r4]
    add     r4, #1
    add     r6, #1
    // arreter a la fin de la chaine
    cmp     r5, #0
    bne     bcl_str2

/* return 0; */	 
	mov     r0,#0  
	pop     {pc}
