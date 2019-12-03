/**
  ******************************************************************************
  * @file    Audio_playback_and_record/inc/main.h 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    28-October-2011
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_audio_codec.h"
#include <stdio.h>
//#include "stm32f4xx_it.h"
#include "Interrupts.h"
#include "waveplayer.h"


#define UART_BUF1_SIZE 200//размер буфера, в который будут записываться команды и данные от UART

typedef enum
{
  ABUF_P1_COMPLETE = 0,//заполнена 1 половина буфера
  ABUF_P2_COMPLETE,//заполнена 2 половина буфера
  ABUF_NONE,
} abuf_status_type;

typedef enum
{
  ABUF_STOP,//заполнение буфера остановлено
  ABUF_RUN,//разрешено заполнение буфера
} abuf_run_type;

typedef enum
{
  MAIN_STAT_START = 0,
  MAIN_STAT_CMD,
  MAIN_STAT_CONF,//переконфигурировать
  MAIN_STAT_DATA,//отправлен запрос аудиоданных
  MAIN_STAT_DATAREADY,//первая половина аудиобуфера заполнилась
  MAIN_STAT_PLAY,
} main_status_type;

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void TimingDelay_Decrement(void);
void Delay(__IO uint32_t nTime);

#endif /* __MAIN_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
