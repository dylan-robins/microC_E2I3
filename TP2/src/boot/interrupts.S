
.syntax unified
	
/* We define interrupt handlers as weak aliases to Default_Handler */

  .globl Default_Handler	
  .type Default_Handler,%function	
Default_Handler:
  b .
  .size Default_Handler, . - Default_Handler

  .macro Interrupt_Handler source
  .weak \source\()_Handler
  .thumb_set \source\()_Handler,Default_Handler
  .word \source\()_Handler
  .endm

.section interrupt_vector, "a"

/* ARM Cortex-M4 Interrupts */

Interrupt_Handler NMI
Interrupt_Handler HardFault
Interrupt_Handler MemManage 
Interrupt_Handler BusFault
Interrupt_Handler UsageFault
  .word 0
  .word 0
  .word 0
  .word 0
Interrupt_Handler SVCall
Interrupt_Handler Debug_Monitor
  .word 0
Interrupt_Handler PendSV
Interrupt_Handler SysTick
 
/* STM32F446 specific interrupts */
 
Interrupt_Handler WWDG
Interrupt_Handler PVD
Interrupt_Handler TAMP_STAMP
Interrupt_Handler RTC_WKUP
Interrupt_Handler FLASH
Interrupt_Handler RCC
Interrupt_Handler EXTI0
Interrupt_Handler EXTI1
Interrupt_Handler EXTI2
Interrupt_Handler EXTI3
Interrupt_Handler EXTI4
Interrupt_Handler DMA1_Stream0
Interrupt_Handler DMA1_Stream1
Interrupt_Handler DMA1_Stream2
Interrupt_Handler DMA1_Stream3
Interrupt_Handler DMA1_Stream4
Interrupt_Handler DMA1_Stream5
Interrupt_Handler DMA1_Stream6
Interrupt_Handler ADC
Interrupt_Handler CAN1_TX
Interrupt_Handler CAN1_RX0
Interrupt_Handler CAN1_RX1
Interrupt_Handler CAN1_SCE
Interrupt_Handler EXTI9_5
Interrupt_Handler TIM1_BRK_TIM9
Interrupt_Handler TIM1_UP_TIM10
Interrupt_Handler TIM1_TRG_COM_TIM11
Interrupt_Handler TIM1_CC
Interrupt_Handler TIM2
Interrupt_Handler TIM3
Interrupt_Handler TIM4
Interrupt_Handler I2C1_EV
Interrupt_Handler I2C1_ER
Interrupt_Handler I2C2_EV
Interrupt_Handler I2C2_ER
Interrupt_Handler SPI1
Interrupt_Handler SPI2
Interrupt_Handler USART1
Interrupt_Handler USART2
Interrupt_Handler USART3
Interrupt_Handler EXTI15_10
Interrupt_Handler RTC_Alarm
Interrupt_Handler OTG_FS_WKUP
Interrupt_Handler TIM8_BRK_TIM12
Interrupt_Handler TIM8_UP_TIM13
Interrupt_Handler TIM8_TRG_COM_TIM14
Interrupt_Handler TIM8_CC
Interrupt_Handler DMA1_Stream7
Interrupt_Handler FMC
Interrupt_Handler SDIO
Interrupt_Handler TIM5
Interrupt_Handler SPI3
Interrupt_Handler UART4
Interrupt_Handler UART5
Interrupt_Handler TIM6_DAC
Interrupt_Handler TIM7
Interrupt_Handler DMA2_Stream0
Interrupt_Handler DMA2_Stream1
Interrupt_Handler DMA2_Stream2
Interrupt_Handler DMA2_Stream3
Interrupt_Handler DMA2_Stream4
  .word 0
  .word 0
Interrupt_Handler CAN2_TX
Interrupt_Handler CAN2_RX0
Interrupt_Handler CAN2_RX1
Interrupt_Handler CAN2_SCE
Interrupt_Handler OTG_FS
Interrupt_Handler DMA2_Stream5
Interrupt_Handler DMA2_Stream6
Interrupt_Handler DMA2_Stream7
Interrupt_Handler USART6
Interrupt_Handler I2C3_EV
Interrupt_Handler I2C3_ER
Interrupt_Handler OTG_HS_EP1_OUT
Interrupt_Handler OTG_HS_EP1_IN
Interrupt_Handler OTG_HS_WKUP
Interrupt_Handler OTG_HS
Interrupt_Handler DCMI
  .word 0
  .word 0
Interrupt_Handler FPU
  .word 0
  .word 0
Interrupt_Handler SPI4
  .word 0
  .word 0
Interrupt_Handler SAI1
  .word 0
  .word 0
  .word 0
Interrupt_Handler SAI2
Interrupt_Handler QuadSPI
Interrupt_Handler HDMI_CEC
Interrupt_Handler SPDIF_Rx
Interrupt_Handler FMPI2C1
Interrupt_Handler FMPI2C1_error
