	.syntax unified

	.text

	.globl main
	.thumb_func
main:
	push {lr}
/* Insert program here */
//mystere:
//    mov.w   r0, #14
//    mov.w   r1, #5
//    add.w   r2, r1, r0
//    sub.w   r3, r0, r1
//    mul.w   r4, r3, r2
//    and.w   r5, r4, #62

//test:
//    mov.w   r2, #0x42
//    mvn.w   r4, #0xDB
//    movw    r9, #0xDEAF
//    movw    r1, #5678
//    movt    r1, #1234

/* EX 3 */
//   mov     r0, #1
//   mov     r1, #2
//   adds    r2, r0, r1
//
//   // save nzcv in r3
//   mrs     r3, psr
//
//   // put N in r4
//   mov     r4, r3
//   lsr     r4, #31
//
//   // put Z in r5
//   mov     r5, r3
//   lsr     r5, #30
//   and     r5, #1
//
//   // put C in r6
//   mov     r6, r3
//   lsr     r6, #29
//   and     r6, #1
//
//   // put V in r7
//   mov     r7, r3
//   lsr     r7, #28
//   and     r7, #1

/* EX 4 */
//    // control values
//    mov     r10, #0x03b5    // VALC1
//    mov     r11, #30        // TC1
//    mov     r12, #0x04b0    // VALC2
//    mov     r9, #110        // TC2
//
//    // read value
//    mov r1, #0x0396         // VALTS
//
//    // multiply all the things!
//    mov r3, #100
//    mul     r10, r3
//    mul     r11, r3
//    mul     r12, r3
//    mul     r9, r3
//    mul     r1, r3
//    // ==> result in centidegrees
//
//    // TC2 - TC1
//    sub r5, r9, r11
//    // VALC2 - VALC1
//    sub r6, r12, r10
//    // VALTS - VALC1
//    sub r7, r1, r10
//    
//    // (.-.) * (.-.)
//    mul r8, r5, r7
//    // (.-.) * (.-.)) / (.-.) 
//    sdiv r2, r8, r6
//
//    // (.-.) / (.-.) * (.-.) + TC1
//    add r0, r2, r11

/* EX 5 - 1*/
//
//    // n
//    mov     r1, #0
//    // nmax
//    mov     r2, #10
//    // S = u0 = 0
//    mov     r3, #0
//boucle:
//    // S = S + n
//    add     r3, r1
//    // n++
//    add     r1, #1
//    // if n == nmax stop looping
//    cmp r1, r2
//    bne     boucle
//
//    // return un
//    mov r0, r3

/* EX 5 - 2*/
//
//    // n
//    mov     r1, #0
//    // nmax
//    mov     r2, #10
//    // S
//    mov     r3, #0
//    // un
//    mov     r4, #0
//boucle:
//    // n*n
//    mul r4, r1, r1
//    // S = S + n*n
//    add     r3, r4
//    // n++
//    add     r1, #1
//    // if n == nmax stop looping
//    cmp r1, r2
//    bne     boucle
//
//    // return un
//    mov r0, r3

/* EX 5 - 3*/

    // n
    mov     r1, #0
    // nmax
    mov     r2, #10
    // S
    mov     r3, #0
    // un
    mov     r4, #0
boucle:
    // n*n
    mul r4, r1, r1
    sub r4, #3
    // S = S + n*n-3
    add     r3, r4
    // n++
    add     r1, #1
    // if n == nmax stop looping
    cmp r1, r2
    bne     boucle

    // return un
    mov r0, r3

/* return 0; */	 
	mov r0,#0  
	pop {pc}
