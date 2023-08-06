/*****************************************************************************
 *                   SEGGER Microcontroller GmbH & Co. KG                    *
 *            Solutions for real time microcontroller applications           *
 *****************************************************************************
 *                                                                           *
 *               (c) 2017 SEGGER Microcontroller GmbH & Co. KG               *
 *                                                                           *
 *           Internet: www.segger.com   Support: support@segger.com          *
 *                                                                           *
 *****************************************************************************/

/*****************************************************************************
 *                         Preprocessor Definitions                          *
 *                         ------------------------                          *
 * VECTORS_IN_RAM                                                            *
 *                                                                           *
 *   If defined, an area of RAM will large enough to store the vector table  *
 *   will be reserved.                                                       *
 *                                                                           *
 *****************************************************************************/

  .syntax unified
  .code 16

  .section .init, "ax"
  .align 0

/*****************************************************************************
 * Default Exception Handlers                                                *
 *****************************************************************************/

  .thumb_func
  .weak NMI_Handler
NMI_Handler:
  b .

  .thumb_func
  .weak HardFault_Handler
HardFault_Handler:
  b .

  .thumb_func
  .weak SVC_Handler
SVC_Handler:
  b .

  .thumb_func
  .weak PendSV_Handler
PendSV_Handler:
  b .

  .thumb_func
  .weak SysTick_Handler
SysTick_Handler:
  b .

  .thumb_func
Dummy_Handler:
  b .

#if defined(__OPTIMIZATION_SMALL)

  .weak WWDG_IRQHandler
  .thumb_set WWDG_IRQHandler,Dummy_Handler

  .weak PVD_IRQHandler
  .thumb_set PVD_IRQHandler,Dummy_Handler

  .weak RTC_IRQHandler
  .thumb_set RTC_IRQHandler,Dummy_Handler

  .weak FLASH_IRQHandler
  .thumb_set FLASH_IRQHandler,Dummy_Handler

  .weak RCC_IRQHandler
  .thumb_set RCC_IRQHandler,Dummy_Handler

  .weak EXTI0_1_IRQHandler
  .thumb_set EXTI0_1_IRQHandler,Dummy_Handler

  .weak EXTI2_3_IRQHandler
  .thumb_set EXTI2_3_IRQHandler,Dummy_Handler

  .weak EXTI4_15_IRQHandler
  .thumb_set EXTI4_15_IRQHandler,Dummy_Handler

  .weak DMA1_CH1_IRQHandler
  .thumb_set DMA1_CH1_IRQHandler,Dummy_Handler

  .weak DMA1_CH2_3_IRQHandler
  .thumb_set DMA1_CH2_3_IRQHandler,Dummy_Handler

  .weak DMA1_CH4_5_IRQHandler
  .thumb_set DMA1_CH4_5_IRQHandler,Dummy_Handler

  .weak ADC_IRQHandler
  .thumb_set ADC_IRQHandler,Dummy_Handler

  .weak TIM1_BRK_UP_TRG_COM_IRQHandler
  .thumb_set TIM1_BRK_UP_TRG_COM_IRQHandler,Dummy_Handler

  .weak TIM1_CC_IRQHandler
  .thumb_set TIM1_CC_IRQHandler,Dummy_Handler

  .weak TIM3_IRQHandler
  .thumb_set TIM3_IRQHandler,Dummy_Handler

  .weak TIM6_IRQHandler
  .thumb_set TIM6_IRQHandler,Dummy_Handler

  .weak TIM14_IRQHandler
  .thumb_set TIM14_IRQHandler,Dummy_Handler

  .weak TIM15_IRQHandler
  .thumb_set TIM15_IRQHandler,Dummy_Handler

  .weak TIM16_IRQHandler
  .thumb_set TIM16_IRQHandler,Dummy_Handler

  .weak TIM17_IRQHandler
  .thumb_set TIM17_IRQHandler,Dummy_Handler

  .weak I2C1_IRQHandler
  .thumb_set I2C1_IRQHandler,Dummy_Handler

  .weak I2C2_IRQHandler
  .thumb_set I2C2_IRQHandler,Dummy_Handler

  .weak SPI1_IRQHandler
  .thumb_set SPI1_IRQHandler,Dummy_Handler

  .weak SPI2_IRQHandler
  .thumb_set SPI2_IRQHandler,Dummy_Handler

  .weak USART1_IRQHandler
  .thumb_set USART1_IRQHandler,Dummy_Handler

  .weak USART2_IRQHandler
  .thumb_set USART2_IRQHandler,Dummy_Handler

  .weak USART3_4_5_6_IRQHandler
  .thumb_set USART3_4_5_6_IRQHandler,Dummy_Handler

  .weak USB_IRQHandler
  .thumb_set USB_IRQHandler,Dummy_Handler

#else

  .thumb_func
  .weak WWDG_IRQHandler
WWDG_IRQHandler:
  b .

  .thumb_func
  .weak PVD_IRQHandler
PVD_IRQHandler:
  b .

  .thumb_func
  .weak RTC_IRQHandler
RTC_IRQHandler:
  b .

  .thumb_func
  .weak FLASH_IRQHandler
FLASH_IRQHandler:
  b .

  .thumb_func
  .weak RCC_IRQHandler
RCC_IRQHandler:
  b .

  .thumb_func
  .weak EXTI0_1_IRQHandler
EXTI0_1_IRQHandler:
  b .

  .thumb_func
  .weak EXTI2_3_IRQHandler
EXTI2_3_IRQHandler:
  b .

  .thumb_func
  .weak EXTI4_15_IRQHandler
EXTI4_15_IRQHandler:
  b .

  .thumb_func
  .weak DMA1_CH1_IRQHandler
DMA1_CH1_IRQHandler:
  b .

  .thumb_func
  .weak DMA1_CH2_3_IRQHandler
DMA1_CH2_3_IRQHandler:
  b .

  .thumb_func
  .weak DMA1_CH4_5_IRQHandler
DMA1_CH4_5_IRQHandler:
  b .

  .thumb_func
  .weak ADC_IRQHandler
ADC_IRQHandler:
  b .

  .thumb_func
  .weak TIM1_BRK_UP_TRG_COM_IRQHandler
TIM1_BRK_UP_TRG_COM_IRQHandler:
  b .

  .thumb_func
  .weak TIM1_CC_IRQHandler
TIM1_CC_IRQHandler:
  b .

  .thumb_func
  .weak TIM3_IRQHandler
TIM3_IRQHandler:
  b .

  .thumb_func
  .weak TIM6_IRQHandler
TIM6_IRQHandler:
  b .

  .thumb_func
  .weak TIM14_IRQHandler
TIM14_IRQHandler:
  b .

  .thumb_func
  .weak TIM15_IRQHandler
TIM15_IRQHandler:
  b .

  .thumb_func
  .weak TIM16_IRQHandler
TIM16_IRQHandler:
  b .

  .thumb_func
  .weak TIM17_IRQHandler
TIM17_IRQHandler:
  b .

  .thumb_func
  .weak I2C1_IRQHandler
I2C1_IRQHandler:
  b .

  .thumb_func
  .weak I2C2_IRQHandler
I2C2_IRQHandler:
  b .

  .thumb_func
  .weak SPI1_IRQHandler
SPI1_IRQHandler:
  b .

  .thumb_func
  .weak SPI2_IRQHandler
SPI2_IRQHandler:
  b .

  .thumb_func
  .weak USART1_IRQHandler
USART1_IRQHandler:
  b .

  .thumb_func
  .weak USART2_IRQHandler
USART2_IRQHandler:
  b .

  .thumb_func
  .weak USART3_4_5_6_IRQHandler
USART3_4_5_6_IRQHandler:
  b .

  .thumb_func
  .weak USB_IRQHandler
USB_IRQHandler:
  b .

#endif

/*****************************************************************************
 * Vector Table                                                              *
 *****************************************************************************/

  .section .vectors, "ax"
  .align 0
  .global _vectors
  .extern __stack_end__
  .extern Reset_Handler

_vectors:
  .word __stack_end__
  .word Reset_Handler
  .word NMI_Handler
  .word HardFault_Handler
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word SVC_Handler
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word PendSV_Handler
  .word SysTick_Handler
  .word WWDG_IRQHandler
  .word PVD_IRQHandler
  .word RTC_IRQHandler
  .word FLASH_IRQHandler
  .word RCC_IRQHandler
  .word EXTI0_1_IRQHandler
  .word EXTI2_3_IRQHandler
  .word EXTI4_15_IRQHandler
  .word Dummy_Handler /* Reserved */
  .word DMA1_CH1_IRQHandler
  .word DMA1_CH2_3_IRQHandler
  .word DMA1_CH4_5_IRQHandler
  .word ADC_IRQHandler
  .word TIM1_BRK_UP_TRG_COM_IRQHandler
  .word TIM1_CC_IRQHandler
  .word Dummy_Handler /* Reserved */
  .word TIM3_IRQHandler
  .word TIM6_IRQHandler
  .word Dummy_Handler /* Reserved */
  .word TIM14_IRQHandler
  .word TIM15_IRQHandler
  .word TIM16_IRQHandler
  .word TIM17_IRQHandler
  .word I2C1_IRQHandler
  .word I2C2_IRQHandler
  .word SPI1_IRQHandler
  .word SPI2_IRQHandler
  .word USART1_IRQHandler
  .word USART2_IRQHandler
  .word USART3_4_5_6_IRQHandler
  .word Dummy_Handler /* Reserved */
  .word USB_IRQHandler
_vectors_end:

#ifdef VECTORS_IN_RAM
  .section .vectors_ram, "ax"
  .align 0
  .global _vectors_ram

_vectors_ram:
  .space _vectors_end - _vectors, 0
#endif
