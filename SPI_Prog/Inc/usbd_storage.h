/**
  ******************************************************************************
  * @file    USB_Device/MSC_Standalone/Inc/usbd_storage.h
  * @author  MCD Application Team
  * @version V1.6.0
  * @date    12-May-2017
  * @brief   Header for usbd_storage.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright © 2016 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_STORAGE_H_
#define __USBD_STORAGE_H_

/* Includes ------------------------------------------------------------------*/
#include "usbd_msc.h"

#define STORAGE_LUN_NBR                  1
#define STORAGE_BLK_NBR                  32797  //32768//640      //32768//    
#define STORAGE_BLK_SIZ                  0x200                               
#define SECTOR_PER_FAT                   07U
#define NUMBER_OF_FAT_TABLES	           02U
#define FAT_DIRECTORY_BLK                (SECTOR_PER_FAT*NUMBER_OF_FAT_TABLES+1)//15U
#define MAX_ROOT_DIR_ENTRIES             0x0EU   //boot_sec[17]
#define FAT_FILE_DATA_BLK                29U //FAT_DIRECTORY_BLK + MAX_ROOT_DIR_ENTRIES/0x10
#define FAT_OFFSET                       FAT_FILE_DATA_BLK*STORAGE_BLK_SIZ  //0A 0x1400   1B 3600
#define END_OF_CHAIN                     (0xfff)



#define FLASH_DISK_START_ADDRESS              0                  
#define FIRMWARE_SIZE
#define FLASH_DISK_SIZE                       STORAGE_BLK_NBR*STORAGE_BLK_SIZ  //0x50000         
//#define FLASH_PAGE_SIZE                     0x200                            /* 2K per page */
#define WAIT_TIMEOUT                		      100000 
#define FLASH_TIMEOUT                         50000U                           /* 50 s */


// __DATE__  __DATE__  __DATE__  __DATE__  __DATE__  __DATE__  __DATE__  __DATE__  __DATE__
// Example of __DATE__ string: "Jul 27 2012"
//                              01234567890

#define BUILD_YEAR_CH0 (__DATE__[ 7])
#define BUILD_YEAR_CH1 (__DATE__[ 8])
#define BUILD_YEAR_CH2 (__DATE__[ 9])
#define BUILD_YEAR_CH3 (__DATE__[10])


#define BUILD_MONTH_IS_JAN (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')
#define BUILD_MONTH_IS_FEB (__DATE__[0] == 'F')
#define BUILD_MONTH_IS_MAR (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
#define BUILD_MONTH_IS_APR (__DATE__[0] == 'A' && __DATE__[1] == 'p')
#define BUILD_MONTH_IS_MAY (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
#define BUILD_MONTH_IS_JUN (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
#define BUILD_MONTH_IS_JUL (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l')
#define BUILD_MONTH_IS_AUG (__DATE__[0] == 'A' && __DATE__[1] == 'u')
#define BUILD_MONTH_IS_SEP (__DATE__[0] == 'S')
#define BUILD_MONTH_IS_OCT (__DATE__[0] == 'O')
#define BUILD_MONTH_IS_NOV (__DATE__[0] == 'N')
#define BUILD_MONTH_IS_DEC (__DATE__[0] == 'D')


#define BUILD_MONTH_CH0 \
    ((BUILD_MONTH_IS_OCT || BUILD_MONTH_IS_NOV || BUILD_MONTH_IS_DEC) ? '1' : '0')

#define BUILD_MONTH_CH1 \
    ( \
        (BUILD_MONTH_IS_JAN) ? '1' : \
        (BUILD_MONTH_IS_FEB) ? '2' : \
        (BUILD_MONTH_IS_MAR) ? '3' : \
        (BUILD_MONTH_IS_APR) ? '4' : \
        (BUILD_MONTH_IS_MAY) ? '5' : \
        (BUILD_MONTH_IS_JUN) ? '6' : \
        (BUILD_MONTH_IS_JUL) ? '7' : \
        (BUILD_MONTH_IS_AUG) ? '8' : \
        (BUILD_MONTH_IS_SEP) ? '9' : \
        (BUILD_MONTH_IS_OCT) ? '0' : \
        (BUILD_MONTH_IS_NOV) ? '1' : \
        (BUILD_MONTH_IS_DEC) ? '2' : \
        /* error default */    '?' \
    )

#define BUILD_DAY_CH0 ((__DATE__[4] >= '0') ? (__DATE__[4]) : '0')
#define BUILD_DAY_CH1 (__DATE__[ 5])



// __DATE__  __DATE__  __DATE__  __DATE__  __DATE__  __DATE__  __DATE__  __DATE__  __DATE__


typedef  struct FAT12_FAT_TABLE {  //struct size  6 bytes for 4 clusters
	uint32_t cluster0:12;
	uint32_t cluster1:12;
	uint32_t cluster2:12;
	uint32_t cluster3:12;
} __attribute__((packed)) FAT12_FAT_TABLE;


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
int8_t STORAGE_Init(uint8_t lun);
int8_t STORAGE_GetCapacity(uint8_t lun, uint32_t * block_num, uint16_t * block_size);
int8_t STORAGE_IsReady(uint8_t lun);
int8_t STORAGE_IsWriteProtected(uint8_t lun);
int8_t STORAGE_Read (uint8_t lun, uint8_t * buf, uint32_t blk_addr, uint16_t blk_len);
int8_t STORAGE_Write(uint8_t lun, uint8_t * buf, uint32_t blk_addr, uint16_t blk_len);
int8_t STORAGE_GetMaxLun(void);
int8_t Prepare_FAT(void);
int8_t create_fs(void);

extern USBD_StorageTypeDef  USBD_DISK_fops;

#endif /* __USBD_STORAGE_H_ */
 
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
