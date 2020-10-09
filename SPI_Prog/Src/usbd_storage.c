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
  * <h2><center>&copy; Copyright � 2016 STMicroelectronics International N.V. 
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
#include "spi.h"
#include "stm32f4_discovery.h"
#include "ff.h"
#include "Driver_SPI.h"


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
uint32_t SectorError = 0, last_wr_adr=0xffffffff, modulo=0;
/*Variable used for Erase procedure*/
uint8_t flash_eraset = 0, temp=0,Wr_Protect, mod=0;
uint8_t write_started =0;
uint16_t block_num_cnt=0;
//IWDG_HandleTypeDef hiwdg;
extern uint8_t complet, error;
//TIM_HandleTypeDef htim6;
extern uint8_t inter;
volatile uint32_t  ttt=0;
extern __IO uint32_t CRCValue_nominal;
bool backup_mode = false;  //backup firmware first
extern uint32_t spi_speed;
ARM_SPI_STATUS  sts;

uint8_t FAT[STORAGE_BLK_SIZ*26]  __attribute__ ((aligned (4))) = {0};   //__attribute__((section(".ARM.__at_0x20010e39")));//

extern const struct flashchip flashchips[];
extern const struct flashchip * flschip;

FRESULT res;
WCHAR tmp[FF_LFN_BUF];
FRESULT check;
FATFS  * fs;//__attribute__ ((aligned (4)));

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
 
unsigned char backup_fil[28] = {
    0x46, 0x49, 0x52, 0x4D, 0x57, 0x41, 0x52, 0x45, 0x42, 0x49, 0x4E, 0x20, 0x18, 0x7A, 0x62, 0x7F,
    0xB6, 0x4E, 0xB6, 0x4E, 0x00, 0x00, 0x63, 0x7F, 0xB6, 0x4E, 0x02, 0x00 
};



uint8_t a[5];

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
/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DWORD get_fattime (void)
{
	//use the project compilation date
	char  year[5] = {BUILD_YEAR_CH0, BUILD_YEAR_CH1, BUILD_YEAR_CH2, BUILD_YEAR_CH3, 0};
	char month[3] = {BUILD_MONTH_CH0, BUILD_MONTH_CH1, 0};
	char   day[3] = {BUILD_DAY_CH0, BUILD_DAY_CH1, 0};
	
	
	return	 ((atoi(year)-1980) << 25)	// Year = 2006   return	((2019UL-1980) << 25)	   
					| (atoi(month)<< 21)	      // Month = Feb     (5UL << 21)	
					| (atoi(day) << 16)	        // Day = 9         (9UL << 16)	
					| (22U << 11)	              // Hour = 22       (22U << 11)	   
					| (30U << 5)	              // Min = 30        (30U << 5)	
					| (0U >> 1)	                // Sec = 0         (0U >> 1)	
					;
}

int8_t create_fs(void) {   //create fat for backup  flash
	uint8_t i=0;
	uint16_t clusters ;
	FAT12_FAT_TABLE * tbl	= (FAT12_FAT_TABLE*)&FAT[0x200+3];	
	
	for (int k=0;k<2;k++) {
	i=0;
	tbl	= (FAT12_FAT_TABLE*)&FAT[0x203+k*SECTOR_PER_FAT*STORAGE_BLK_SIZ];
	clusters = (*(uint32_t*)&FAT[0x20])/(*(uint8_t*)&FAT[0x0d]);	//cluster cnt;
	while (clusters>1){			
			if (clusters == 1) {tbl->cluster0 = END_OF_CHAIN; break;}
					 else tbl->cluster0 = 3+ i*4;
			clusters--;
			if (clusters == 1) {tbl->cluster1 = END_OF_CHAIN; break;}
					 else tbl->cluster1 = 4+ i*4;
			clusters--;
			if (clusters == 1) {tbl->cluster2 = END_OF_CHAIN; break;}
					 else tbl->cluster2 = 5+ i*4;
			clusters--;
			if (clusters == 1) {tbl->cluster3 = END_OF_CHAIN; break;}
					 else tbl->cluster3 = 6+ i*4;
			clusters--;
			i++;
			tbl++;
	}
 }
	
 
#ifdef USE_LFN	   
    // I use FatFS for long filename 
    fs = (FATFS *)malloc(sizeof(FATFS));
		FIL fil;
//    uint32_t bw;
		char sd_path[4] = "0:/";
    char filename[30] = {0};  
    memcpy (filename, flschip->name, strlen(flschip->name));
	while (strchr (filename, '/') != NULL) {               //replace '/' on '_'
			*strchr (filename, '/') = '_';
		}
	while (strlen(filename) > 22) {
			if (strrchr (filename, '_') > strrchr (filename, ')')) *strrchr (filename, '_') = '\0';
			   else *(strrchr (filename, ')') + 1) = '\0';
		}
	  strcat (filename, ".bin");
		check = f_mount(fs, sd_path, 0);
		check = f_open(&fil, filename, FA_CREATE_ALWAYS);			
	  memcpy(&FAT[0]+STORAGE_BLK_SIZ*FAT_DIRECTORY_BLK ,fs->win, 0x80);
		//check = f_write(&fil, "123456", 6, &bw);	
		check = f_close(&fil);		
		check = f_mount(NULL, sd_path, 0);
		free(fs);
		if (check) return -1;
	  if (strlen(flschip->name) <= 8) {                                                       //SFN
		 *(uint32_t*)&FAT[STORAGE_BLK_SIZ*FAT_DIRECTORY_BLK+0x3c] = flschip->total_size*1024; //set  file size
		 *(uint32_t*)&FAT[STORAGE_BLK_SIZ*FAT_DIRECTORY_BLK+0x38] = 0x20000; //			
	 }
	  else if ((sizeof(filename)-4) > 8) {     //LFN  (strlen(flschip->name) > 8 && strlen(flschip->name) < sizeof(filename)-4)
			if (*(uint32_t*)&FAT[STORAGE_BLK_SIZ*FAT_DIRECTORY_BLK+0x5c] == 0) { 
        //for file names consisting of 9 chars				
				*(uint32_t*)&FAT[STORAGE_BLK_SIZ*FAT_DIRECTORY_BLK+0x5c] = flschip->total_size*1024; //set  file size
				*(uint32_t*)&FAT[STORAGE_BLK_SIZ*FAT_DIRECTORY_BLK+0x58] = 0x20000; 
			}
			   else {     // >9 chars
					 *(uint32_t*)&FAT[STORAGE_BLK_SIZ*FAT_DIRECTORY_BLK+0x7c] = flschip->total_size*1024; //set  file size
		       *(uint32_t*)&FAT[STORAGE_BLK_SIZ*FAT_DIRECTORY_BLK+0x78] = 0x20000; //
				 }
		}
		 else return -1;  //filename leght error
		
		//memset(&FAT[0]+26*STORAGE_BLK_SIZ, 0, STORAGE_BLK_SIZ);
#else	
    memcpy(&FAT[STORAGE_BLK_SIZ*FAT_DIRECTORY_BLK+0x20], backup_fil, sizeof(backup_fil));
		memset(&FAT[STORAGE_BLK_SIZ*FAT_DIRECTORY_BLK+0x20], 0x20, 8);
		memcpy(&FAT[STORAGE_BLK_SIZ*FAT_DIRECTORY_BLK+0x20], flschip->name, strlen(flschip->name) <= 8 ? strlen(flschip->name) : 8);   //copy file name & etc.
  	*(uint32_t*)&FAT[STORAGE_BLK_SIZ*FAT_DIRECTORY_BLK+28+0x20] = flschip->total_size*1024; //set  file size
#endif	 
   return 0;
}

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
  uint16_t n=0;
	uint32_t * buf32 = (uint32_t*)buf;
	
  switch (lun)
  {
    case 0:
				//for backup firmware mode
				if (blk_addr>=FAT_FILE_DATA_BLK && backup_mode) {
					ReadData((blk_addr-FAT_FILE_DATA_BLK)*STORAGE_BLK_SIZ, buf32, STORAGE_BLK_SIZ*blk_len);
				}
				//fill zeros if blk_addr>sizeof(FAT)/STORAGE_BLK_SIZ
				else if (blk_addr>sizeof(FAT)/STORAGE_BLK_SIZ ) memset (buf, 0, STORAGE_BLK_SIZ*blk_len);
					else {
						memcpy(buf, &FAT[0] + (blk_addr+n)*STORAGE_BLK_SIZ, STORAGE_BLK_SIZ*blk_len);
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
	
	  memset(FAT, 0, sizeof(FAT));	
	
		ret =  Write_LL((uint32_t)&FAT[0]                                        , &boot_sec[0], sizeof(boot_sec)- 4*2);
		ret |= Write_LL((uint32_t)&FAT[0]+0x01FC                                 , &boot_sec[sizeof(boot_sec)- 4*1], 4*1);	
		ret |= Write_LL((uint32_t)&FAT[0]+(STORAGE_BLK_SIZ*1)                    , &boot_sec[sizeof(boot_sec)- 4*2], 4*1);  //+0x0200
		ret |= Write_LL((uint32_t)&FAT[0]+(STORAGE_BLK_SIZ*(SECTOR_PER_FAT*1+1)) , &boot_sec[sizeof(boot_sec)- 4*2], 4*1);  //+0x1000
		ret |= Write_LL((uint32_t)&FAT[0]+(STORAGE_BLK_SIZ*FAT_DIRECTORY_BLK)    , &Label_disk[0], sizeof(Label_disk));	    //+0x1E00
	
	  if (backup_mode){ 
			memcpy(&FAT[0]+STORAGE_BLK_SIZ*FAT_DIRECTORY_BLK+4, "BACKUP", 6);		
			if (create_fs()) return -1; 
			//fatfs вешает spi
#ifdef USE_LFN				
//			Initialize(NULL);	
//			PowerControl(ARM_POWER_FULL);		
//			ptrSPI->Control(ARM_SPI_SET_BUS_SPEED, spi_speed);
#endif			
		}

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
	//if the file size is not a multiple of the sector size
	if ((modulo) && ((dest - FAT_OFFSET) == (file_size-modulo))) {	
		len = modulo; 
	}
	
	//if writing data
	if (dest < (flschip->total_size*1024+FAT_OFFSET))	{   
		  if (backup_mode) return 0;
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
           if (blk_addr == FAT_DIRECTORY_BLK && !(backup_mode))  {
						 //0x1C- file_size offset 
						 if (*(uint32_t*)(buf+0x1C+0x20)) {
							 if (*(uint32_t*)(buf+0x40)) {
								 //0x20 - offset for 1 file, 0x00 - offset for disk label, +0x40 for long filename
								 file_size  = *(uint32_t*)(buf+0x1C+0x20+0x40); //LFN
								 if (!(file_size)) {
									 file_size  = *(uint32_t*)(buf+0x1C+0x20+0x20) ; //for 9-character file names
								 }
							 }
							   else file_size = *(uint32_t*)(buf+0x1C+0x20);  //SFN
							 if (file_size) {
									 if (file_size > flschip->total_size*1024) {
										 USBD_UsrLog("\n\r ERROR, file size > flash size!!!");
										 return -1;
									 }
									 modulo = 	file_size % STORAGE_BLK_SIZ;	//chunk of file
									 if (modulo) mod=1;
									   else mod = 0;
									}					
//								printf ("\n\r F_size -> %x", file_size);		
					    }						 
					   }
					 } 
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
//					backup_mode = true;
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
