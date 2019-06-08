
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_IT_H
#define __STM32F4xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define VOLUME_DEFAULT	50
#define VOLUME_MIN		0
#define VOLUME_MAX		100
#define VOLUME_STEP		10

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void OTG_FS_IRQHandler(void);
void I2S2_IRQHandler(void);
void I2S3_IRQHandler(void);
void TIM4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_IT_H */

