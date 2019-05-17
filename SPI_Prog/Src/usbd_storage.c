/**
  ******************************************************************************
  * @file    USB_Device/MSC_Standalone/Src/usbd_storage.c
  * @author  MCD Application Team
  * @version V1.6.0
  * @date    12-May-2017
  * @brief   Memory management layer
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

/* Includes ------------------------------------------------------------------ */
#include "usbd_storage.h"
#include "usb_device.h"
#include "flashchips.h"
#include "chip_drv.h"
#include "stm32f4_discovery.h"


/* Private typedef ----------------------------------------------------------- */
/* Private define ------------------------------------------------------------ */
//#define STORAGE_LUN_NBR                  1
//#define STORAGE_BLK_NBR                  0x10000
//#define STORAGE_BLK_SIZ                  0x200

/* Private macro ------------------------------------------------------------- */
/* Private variables --------------------------------------------------------- */
/* USB Mass storage Standard Inquiry Data */
extern int8_t STORAGE_Inquirydata_FS[];

/* Private function prototypes ----------------------------------------------- */
int8_t STORAGE_Init(uint8_t lun);
int8_t STORAGE_GetCapacity(uint8_t lun, uint32_t * block_num,
                           uint16_t * block_size);
int8_t STORAGE_IsReady(uint8_t lun);
int8_t STORAGE_IsWriteProtected(uint8_t lun);
int8_t STORAGE_Read(uint8_t lun, uint8_t * buf, uint32_t blk_addr,
                    uint16_t blk_len);
int8_t STORAGE_Write(uint8_t lun, uint8_t * buf, uint32_t blk_addr,
                     uint16_t blk_len);
int8_t STORAGE_GetMaxLun(void);
//static uint32_t GetSector(uint32_t Address);
//static uint32_t GetSectorSize(uint32_t Sector);
static int8_t Write_LL(uint32_t  dest, uint8_t * buf, uint16_t len);
int8_t Sector_Erase(void);
//static void MX_TIM6_Init(void);

uint32_t FirstSector = 0, NbOfSectors = 0, Address = 0, Sector = 0;
uint32_t SectorError = 0, last_wr_adr=0xffffffff;
/*Variable used for Erase procedure*/
uint8_t flash_eraset = 0, temp=0,Wr_Protect, first=1, mod=0;
uint8_t write_started =0;
uint16_t block_num_cnt=0, modulo=0;
IWDG_HandleTypeDef hiwdg;
extern uint8_t complet, error;
//TIM_HandleTypeDef htim6;
extern uint8_t inter;
volatile uint32_t  ttt=0;
extern __IO uint32_t CRCValue_nominal;


uint8_t FAT[STORAGE_BLK_SIZ*26]  __attribute__ ((aligned (4))) = {0};   //__attribute__((section(".ARM.__at_0x20010e39")));//

extern const struct flashchip flashchips[];
extern const struct flashchip * flschip;

 unsigned char boot_sec[] = { //188
 
    0xEB, 0x3C, 0x90, 0x4D, 0x53, 0x44, 0x4F, 0x53, 0x35, 0x2E, 0x30, 0x00, 0x02, 0x40, 0x01, 0x00,
    0x02, 0xE0, 0x00, 0x00, 0x00, 0xF8, 0x07, 0x00, 0x11, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1D, 0x00, 0x02, 0x00, 0x80, 0x00, 0x29, 0xFC, 0xEE, 0xCB, 0x4C, 0x53, 0x50, 0x49, 0x2D, 0x50,
    0x52, 0x4F, 0x47, 0x20, 0x20, 0x20, 0x46, 0x41, 0x54, 0x31, 0x32, 0x20, 0x20, 0x20,
	  0xF0, 0xFF, 0xFF, 0x00, 
	  0x00, 0x00, 0x55, 0xAA 
};
 unsigned char Label_disk[32] = {
    0x53, 0x50, 0x49, 0x2D, 0x50, 0x52, 0x4F, 0x47, 0x20, 0x20, 0x20, 0x08, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x53, 0xA8, 0x4E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

 int32_t file_size = 0;


USBD_StorageTypeDef USBD_DISK_fops = {
  STORAGE_Init,
  STORAGE_GetCapacity,
  STORAGE_IsReady,
  STORAGE_IsWriteProtected,
  STORAGE_Read,
  STORAGE_Write,
  STORAGE_GetMaxLun,
  STORAGE_Inquirydata_FS,
};

/* Private functions --------------------------------------------------------- */



/**
  * @brief  Initailizes the storage unit (medium)       
  * @param  lun: Logical unit number
  * @retval Status (0 : Ok / -1 : Error)
  */
int8_t STORAGE_Init(uint8_t lun)
{
  switch (lun)
  {
    case 0:
      //HAL_FLASH_Unlock(); 
      break;
    case 1:
      return 1;
    default:
      return 1;
  }
  return 0;
}

/**
  * @brief  Returns the medium capacity.      
  * @param  lun: Logical unit number
  * @param  block_num: Number of total block number
  * @param  block_size: Block size
  * @retval Status (0: Ok / -1: Error)
  */
int8_t STORAGE_GetCapacity(uint8_t lun, uint32_t * block_num,
                           uint16_t * block_size)
{
  switch (lun)
  {
    case 0:
      *block_num  = flschip->total_size*1024/STORAGE_BLK_SIZ + FAT_FILE_DATA_BLK ;//0x1D;   //STORAGE_BLK_NBR;
      *block_size = STORAGE_BLK_SIZ;
      break;
    case 1:
      return 1;
    default:
      return 1;
  
  }
  return 0;
}

/**
  * @brief  Checks whether the medium is ready.  
  * @param  lun: Logical unit number
  * @retval Status (0: Ok / -1: Error)
  */
int8_t STORAGE_IsReady(uint8_t lun)
{
   switch (lun)
  {
    case 0:
      return 0;
//      break;
    case 1:
      return 1;
    default:
      return 1;
  }
}

/**
  * @brief  Checks whether the medium is write protected.
  * @param  lun: Logical unit number
  * @retval Status (0: write enabled / -1: otherwise)
  */
int8_t STORAGE_IsWriteProtected(uint8_t lun)
{
	if (Wr_Protect) return -1;
    else return 0;
}

/**
  * @brief  Reads data from the medium.
  * @param  lun: Logical unit number
  * @param  blk_addr: Logical block address
  * @param  blk_len: Blocks number
  * @retval Status (0: Ok / -1: Error)
  */
int8_t STORAGE_Read(uint8_t lun, uint8_t * buf, uint32_t blk_addr,
                    uint16_t blk_len)
{
//  int8_t ret = -1;
  uint16_t i,n;
	uint32_t * buf32 = (uint32_t*)buf;
	
  switch (lun)
  {
    case 0:
  	  for(n = 0; n < blk_len; n++)
			{ 
				//fill zeros if blk_addr>sizeof(FAT)/STORAGE_BLK_SIZ
				if (blk_addr>sizeof(FAT)/STORAGE_BLK_SIZ ) memset (buf, 0, STORAGE_BLK_SIZ);
					else {
						for(i = 0; i < STORAGE_BLK_SIZ; i+=4) {
								*buf32 = *(__IO uint32_t*)(&FAT[0] + (blk_addr+n)*STORAGE_BLK_SIZ+i);  
								buf32++;
						}
			   }
			}
			USBD_UsrLog("\n\r RD blk_addr-> %d blk_len-> %d", blk_addr,blk_len);
      break;
    case 1:
      break;
    default:
      return 1;
  }
  return 0;
}

int8_t Sector_Erase(void)
{		
        if  (EraseChip ()) return 1;
				flash_eraset = 1; 
	      //printf ("\n Sector erase run");
        //MX_TIM6_Init();					
			
	return 0;
}

 int8_t Prepare_FAT(void)
{
	int8_t ret=0;
	
		ret =  Write_LL((uint32_t)&FAT[0]                                        , &boot_sec[0], sizeof(boot_sec)- 4*2);
		ret |= Write_LL((uint32_t)&FAT[0]+0x01FC                                 , &boot_sec[sizeof(boot_sec)- 4*1], 4*1);	
		ret |= Write_LL((uint32_t)&FAT[0]+(STORAGE_BLK_SIZ*1)                    , &boot_sec[sizeof(boot_sec)- 4*2], 4*1);  //+0x0200
		ret |= Write_LL((uint32_t)&FAT[0]+(STORAGE_BLK_SIZ*(SECTOR_PER_FAT*1+1)) , &boot_sec[sizeof(boot_sec)- 4*2], 4*1);  //+0x1000
		ret |= Write_LL((uint32_t)&FAT[0]+(STORAGE_BLK_SIZ*FAT_DIRECTORY_BLK)    , &Label_disk[0], sizeof(Label_disk));	    //+0x1E00

		//if (ret) Error_Handler();				
			
	return ret;
}

/**
  * @brief  LL Writes data into the medium.
  * @param  dest: Destination addres
  * @param  src: Pointer to source data
  * @param  len: number byte for writing
  * @retval Status (0 : Ok / 1 : Error)
  */
static int8_t Write_LL(uint32_t  dest, uint8_t * src, uint16_t len)
{	
	//indicate writing
	if ((dest & 0x0fff)  == 0) BSP_LED_Toggle(LED3);                         
	//if the file size is not a multiple of the sector size
	if ((modulo) && ((dest - FAT_OFFSET) == (file_size-modulo))) {	
		len = modulo; 
	}
	
	//if writing data
	if (dest < (flschip->total_size*1024+FAT_OFFSET))	{   
		  //if (Wr_Protect) return -1;
			if (ProgramData (dest - FAT_OFFSET, src, len) != ARM_DRIVER_OK) return ARM_DRIVER_ERROR;							
	}				 				 			 
	 //else writing  FAT
	 else  if ((dest <= ((uint32_t)&FAT[0] + sizeof(FAT))) && (dest >= ((uint32_t)&FAT[0]))) memcpy ((uint8_t*)dest, src, len);
		   else return 1;
			 
	return ARM_DRIVER_OK;
 
}

/**
  * @brief  Writes data into the medium.
  * @param  lun: Logical unit number
  * @param  blk_addr: Logical block address
  * @param  blk_len: Blocks number
  * @retval Status (0 : Ok / -1 : Error)
  */
int8_t STORAGE_Write(uint8_t lun, uint8_t * buf, uint32_t blk_addr,
                     uint16_t blk_len)
{                       
  uint32_t adr=0;

	
  switch (lun)
  {
    case 0:	
     USBD_UsrLog("\n\r WR blk_addr-> %d blk_len-> %d", blk_addr, blk_len);
		 if (!(error)) {                                      //
			 if (blk_addr >= FAT_FILE_DATA_BLK) {                             //0x3a00 file body
				 if ((modulo)&&(blk_addr == (FAT_FILE_DATA_BLK+file_size/STORAGE_BLK_SIZ))) {
					 //last block && not aligned 
					 CRCValue_nominal = CalcCRC32(buf, modulo, CRCValue_nominal);                       
					 }
				   //standart
					 else CRCValue_nominal = CalcCRC32(buf, blk_len*STORAGE_BLK_SIZ, CRCValue_nominal);							
				 }
         if (blk_addr < FAT_FILE_DATA_BLK) {
           if (blk_addr == FAT_DIRECTORY_BLK)  {
             //write_started =1;						 
//						 if (*(uint8_t*)(buf+0x20)) {
//						 if (((*(uint8_t*)(buf+0x20) == 0x46)) | ((*(uint8_t*)(buf+0x20) == 0x66))) {
//								 if (memcmp(( char*)(buf+0x20), "FIRMWAREBIN", 11)) {error = 1; Wr_Protect = 1;return -1;}
//								    else Wr_Protect = 0;
//							 }
//							  else {error = 1; Wr_Protect = 1;return -1;}
//						 }
						 //28- file_size offset 
						 if (*(uint32_t*)(buf+28+0x20)) {
							 //0x20 - offset for 1 file, 0x00 - offset for disk label, +0x40 for long filename
							 file_size  = (*(uint32_t*)(buf+28+0x20)== 0xFFFFFFFF)?  *(uint32_t*)(buf+28+0x20+0x40):\
																																			 *(uint32_t*)(buf+28+0x20);
								 if (file_size) {
									 if (file_size > flschip->total_size*1024) {
										 USBD_UsrLog("\n\r ERROR, file size > flash size!!!");
										 return -1;
									 }
									 modulo = 	file_size % STORAGE_BLK_SIZ;	//chunk of file
									 if (modulo) mod=1;
									}					
								//printf ("\n\r F_size -> %x", file_size);		
					    }						 
					   }
					 }
//        if (!(write_started))  	{Wr_Protect = 1;return -1;}			 
				if (blk_addr < FAT_FILE_DATA_BLK) adr = (uint32_t)&FAT[0];            //writing FAT
					  else adr = FLASH_DISK_START_ADDRESS;                              //else writing data
				//if block number >FAT_DIRECTORY_BLK & <FAT_FILE_DATA_BLK -> skip writing 	 
				if (!(blk_addr < FAT_FILE_DATA_BLK & blk_addr > FAT_DIRECTORY_BLK)){  
				if (Write_LL((adr) +blk_addr*STORAGE_BLK_SIZ, buf, blk_len*STORAGE_BLK_SIZ) == HAL_ERROR) 
							 { 
								Error_Handler();
							 }	 
				}
				
			if (file_size>0) {
	      if (blk_addr == (29-1) + mod + file_size/STORAGE_BLK_SIZ){       //If the file is recorded fully
				  Wr_Protect = 1;
					complet = 1;
				 } 
			 }

		}
		 else return -1;
     break;
   case 1:
     break;
   default:
     return 1;
  }
  return 0;
}

/**
  * @brief  Returns the Max Supported LUNs.   
  * @param  None
  * @retval Lun(s) number
  */
int8_t STORAGE_GetMaxLun(void)
{
  return (STORAGE_LUN_NBR - 1);
}



///* TIM6 init function */
//static void MX_TIM6_Init(void)
//{

//  TIM_MasterConfigTypeDef sMasterConfig;

//  htim6.Instance = TIM6;
//  htim6.Init.Prescaler = 16800*2;
//  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
//  htim6.Init.Period = 1000;
//  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
//  {
//    _Error_Handler(__FILE__, __LINE__);
//  }

//  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
//  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
//  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
//  {
//    _Error_Handler(__FILE__, __LINE__);
//  }

//}
/**********************************END OF FILE**************************************/
