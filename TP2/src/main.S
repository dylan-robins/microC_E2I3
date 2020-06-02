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

prompt:
    .string "Numero du mois? (1-12)\n\r>"
err:
    .string "Erreur"

	.text

	.globl main
	.thumb_func

// prend une adresse de str dans r0 et l'affiche avec _putch
_puts:
    push    {r1, r2, r3, lr}    // sauver les registres ecrases

    mov     r3, r0              // ptr chaine dans r3
    mov     r2, #0              // i dans r2
bcl_pts:
    ldrb    r0, [r3, r2]        // charger chaine[i] dans r0
    cmp     r0, #0              // si fin de chaine finir
    beq     end_pts

    bl      _putch              // sinon afficher
    add     r2, #1              // i++
    bal     bcl_pts             // boucler

end_pts:
    pop     {r1, r2, r3, lr}    // restaurer les registres
    bx      lr                  // return

_getint:
    push    {r1, r2, r3, r4, lr}

    // lire un 1e caractere
    bl      _getch
    bl      _putch
    cmp     r0, #'\r'
    beq     fail                // si fin de chaine, erreur
    mov     r3, r0              // stockage temporaire

    // lire un 2e caractere
    bl      _getch
    bl      _putch
    cmp     r0, #'\r'
    beq     un_chiffre          //si fin de chqinem ! seul char
    mov     r1, r0              // stockage temporaire

    // lire un 2e caractere
    bl      _getch
    bl      _putch
    cmp     r0, #'\r'
    bne     fail                // si fin de chaine (3 chiffres), erreur

deux_chiffres:
    sub     r1, #'0'
    sub     r3, #'0'

    mov     r4, #10
    mul     r0, r3, r4
    add     r0, r1
    bal fin_geti

un_chiffre:
    sub     r0, r3, #'0'
    
fin_geti:
    // return
    pop     {r1, r2, r3, r4, lr}
    bx      lr


main:
	push    {lr}
/* Insert program here */
    bl      init_USART2

    bl      init_USART2_GPIOA

    ldr     r0, =prompt
    bl      _puts

    bl      _getint

    ldr     r2, =tabmois    // tableau de mois
    
    cmp     r0, #1
    blt     fail             //si <= 0 fail
    cmp     r0, #12
    bgt     fail             // si > 12 fail

    sub     r0, #1          // conversion numero mois -> rang du tableau
    mov     r1, #4
    mul     r0, r1          //*4 car sizeof(word) = 4
    ldr     r0, [r2, r0]    // chaine nom du mois

    bl      _puts

    bal end

fail:
    ldr     r0, =err
    bl      _puts

end:
    mov r0, #'\n'
    bl _putch
    mov r0, #'\r'
    bl _putch

    bal     main

/* return 0; */	 
	mov     r0,#0  
	pop     {pc}
