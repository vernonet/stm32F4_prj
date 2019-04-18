/*
 * main.h
 *
 *  Created on: 10 jul 2012
 *      Author: BenjaminVe
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include <stdio.h>
#include "stm32f4xx_it.h"
//#include "usb_hcd_int.h"
#include "usbh_diskio_dma.h"
#include "usbh_core.h"
#include "usbh_msc.h"
#include "stm32f4_discovery.h"
//#include "stm32f4_discovery_audio.h"
#include "ff.h"
#include "ff_gen_drv.h"

typedef enum
{
  APPLICATION_IDLE = 0,  
  APPLICATION_START,    
  APPLICATION_RUNNING,
}
MSC_ApplicationTypeDef;
/* You can change the Wave file name as you need, but do not exceed 11 characters */
#define WAVE_NAME "0:1.wav"
#define REC_WAVE_NAME "0:rec.wav"
  
/* State Machine for the USBH_USR_ApplicationState */
#define USBH_USR_FS_INIT    ((uint8_t)0x00)
#define USBH_USR_AUDIO      ((uint8_t)0x01)

/* Defines for the Audio used commands */
#define CMD_PLAY           ((uint32_t)0x00)
#define CMD_RECORD         ((uint32_t)0x01)
#define CMD_STOP           ((uint32_t)0x02)

/* Defines for the Audio playing process */
#define PAUSE_STATUS     ((uint32_t)0x00) /* Audio Player in Pause Status */
#define RESUME_STATUS    ((uint32_t)0x01) /* Audio Player in Resume Status */
#define IDLE_STATUS      ((uint32_t)0x02) /* Audio Player in Idle Status */

/* Defines for MEMS Acclerometer ID Types */
#define MEMS_LIS3DSH     0x3F /* LIS3DSH MEMS Acclerometer ID */
#define MEMS_LIS302DL    0x3B /* LIS302DL MEMS Acclerometer ID */

// Function prototypes
void TimingDelay_Decrement(void);
void Delay(volatile uint32_t nTime);
void Error_Handler(void);

#endif /* MAIN_H_ */
