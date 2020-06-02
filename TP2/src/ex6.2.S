	.syntax unified

	.data
tabmois:
	.word m1,m2,m3,m4,m5,m6,m7,m8,m9,m10,m11,m12
m1:
	.string "Janvier"
m2:
	.string "Février"
m3:
	.string "Mars"
m4:
	.string "Avril"
m5:
	.string "Mai"
m6:
	.string "Juin"
m7:
	.string "Juillet"
m8:
	.string "Août"
m9:
	.string "Septembre"
m10:
	.string "Octobre"
m11:
	.string "Novembre"
m12:
	.string "Décembre"
	.align 4
dest:
	.space 20

err:
    .string "Erreur"

	.text

	.globl main
	.thumb_func
main:
	push    {lr}
/* Insert program here */
    bl init_USART2

    bl init_USART2_GPIOA

    mov     r0, #-1          // numero de mois

    ldr     r2, =tabmois    // tableau de mois
    
    cmp     r0, #1
    blt     fail             //si <= 0 fail
    cmp     r0, #12
    bgt     fail             // si > 12 fail

    sub     r0, #1          // conversion numero mois -> rang du tableau
    mov     r1, #4
    mul     r0, r1          //*4 car sizeof(word) = 4
    ldr     r1, [r2, r0]    // chaine nom du mois

    mov     r5, #0          // i = 0
boucle:
    ldrb    r4, [r1, r5]    // charger nom[i]
    cmp     r4, #0
    beq end

    mov     r0, r4
    bl _putch
    
    strb    r4, [r3, r5]    // ecrire dest[i]
    add     r5, #1
    bal boucle

    bal end

fail:
    ldr     r1, =err
    mov     r2, #0
bcl_err:
    ldrb    r0, [r1, r2]
    cmp     r0, #0
    beq end

    bl _putch
    add r2, #1
    bal bcl_err

end:
    mov r0, #'\n'
    bl _putch
    mov r0, #'\r'
    bl _putch
/* return 0; */	 
	mov     r0,#0  
	pop     {pc}
