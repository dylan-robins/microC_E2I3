  .syntax unified 
	
  .section boot , "a"

/* _reset values for SP, PC */

  .word __stack
  .word _start

  .text

  .globl hardware_init_hook 
  .thumb_func
/* we copy data section from rom to ram */

hardware_init_hook:
   push {r0,r1,r2,r3,lr}	
   ldr r0,=__data_start__
   ldr r1,=__data_load__
   ldr r2,=__data_end__
   sub r2,r2,r0
   bl memcpy
   pop {r0,r1,r2,r3,pc}

  .text
	
  .globl _exit 
  .thumb_func
   /* we loop forever */
_exit:
   b _exit
