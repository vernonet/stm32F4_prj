/*
 * Copyright (c) 2017-2018 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * -----------------------------------------------------------------------
 *
 * $Date:        19. April 2018
 * $Revision:    V1.1
 *
 * Driver:       Driver_Flash# (default: Driver_Flash0)
 * Project:      Flash Device Driver for Micron W25Q80BV (SPI)
 * -----------------------------------------------------------------------
 * Use the following configuration settings in the middleware component
 * to connect to this driver.
 *
 *   Configuration Setting                   Value
 *   ---------------------                   -----
 *   Connect to hardware via Driver_Flash# = n (default: 0)
 * -------------------------------------------------------------------- */

/* Note:
    Use the following definitions to customize this driver:

    #define DRIVER_FLASH_NUM   #
    Replace symbol # with any integer to customize the number of exported
    driver (i.e. Driver_Flash#) Default setting is 0.
    
    #define DRIVER_SPI_NUM     #
    Replace symbol # with any integer to customize the number of SPI driver
    (i.e. Driver_SPI#) used to communicate with Flash device.
    Default setting is 0.
    
    #define DRIVER_SPI_BUS_SPEED #
    Replace symbol # with any integer to customize the SPI bus frequency.
    Default setting is 36000000 (36MHz).
*/

#include "Driver_SPI.h"
#include "chip_drv.h"
#include "spi.h"
#include "string.h"
#include "stm32f4xx_hal.h"
#include "stm32f4_discovery.h"
#include "usbd_conf.h"


#include "flashchips.h"

#define ARM_FLASH_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1,1) /* driver version */


#ifndef DRIVER_FLASH_NUM
#define DRIVER_FLASH_NUM        0         /* Default driver number */
#endif

#ifndef DRIVER_SPI_NUM
#define DRIVER_SPI_NUM          0         /* Default SPI driver number */
#endif

#ifndef DRIVER_SPI_BUS_SPEED
#define DRIVER_SPI_BUS_SPEED    24000000  /* Default SPI bus speed */
#endif




/* SPI Driver */
#define _SPI_Driver_(n)  Driver_SPI##n
#define  SPI_Driver_(n)  _SPI_Driver_(n)
extern ARM_DRIVER_SPI     SPI_Driver_(DRIVER_SPI_NUM);
#define ptrSPI          (&SPI_Driver_(DRIVER_SPI_NUM))

/* SPI Bus Speed */
#define SPI_BUS_SPEED   ((uint32_t)DRIVER_SPI_BUS_SPEED)

//uint16_t fl_sec_cnt = FLASH_SECTOR_COUNT;

/* Flash Information */
 ARM_FLASH_INFO FlashInfo = {
  NULL,
  FLASH_SECTOR_COUNT,
  FLASH_SECTOR_SIZE,
  FLASH_PAGE_SIZE,
  FLASH_PROGRAM_UNIT,
  FLASH_ERASED_VALUE,
#if (ARM_FLASH_API_VERSION > 0x201U)
  { 0U, 0U, 0U }
#endif
};

/* Flash Status */
static ARM_FLASH_STATUS FlashStatus;
static uint8_t Flags;
    


/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
  ARM_FLASH_API_VERSION,
  ARM_FLASH_DRV_VERSION
};

/* Driver Capabilities */
static const ARM_FLASH_CAPABILITIES DriverCapabilities = {
  0U,   /* event_ready */
  0U,   /* data_width = 0:8-bit, 1:16-bit, 2:32-bit */
  1U,   /* erase_chip */
#if (ARM_FLASH_API_VERSION > 0x200U)
  0U    /* reserved */
#endif
};

//extern const struct flashchip flashchips[];
const struct flashchip * flschip = NULL; //&flashchips[0];
JEDEC_ID jdc_id_ = {0};






/* Read SFDP register */
//uint32_t* _size - size of flash in bytes
 int32_t ReadSfdpReg (uint8_t cmd, uint32_t* _size) {  
  int32_t status; /* driver execution status */
  uint8_t buf_rec[20];  //20
	uint8_t buf_tra[20] = {0};

  /* Select Slave */
  status = ptrSPI->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_ACTIVE);

  if (status == ARM_DRIVER_OK) {
    /* Set command */
    buf_tra[0] = cmd;

    /* Send command and receive register value */
    status = ptrSPI->Transfer (&buf_tra[0], &buf_rec[0], 20U); //20

    if (status == ARM_DRIVER_OK) {
      /* Wait till transfer done */
      while (ptrSPI->GetDataCount() != 20U) {__asm("nop");};
    }
  }
  /* Deselect Slave */
  ptrSPI->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_INACTIVE);
	
	  // Verify SFDP signature for sanity
    // Also check that major/minor version is acceptable
    if (!(memcmp(&buf_rec[5], "SFDP", 4) == 0 && buf_rec[10] == 1)) {
        return ARM_DRIVER_ERROR_UNSUPPORTED;
		}
		// The SFDP spec indicates the standard table is always at offset 0
    // in the parameter headers, we check just to be safe
    if (!((buf_rec[13] == 0xEF || buf_rec[13] == 0x00)&& buf_rec[15] == 1)) {
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    // Parameter table pointer, spi commands are BE, SFDP is LE,
    // also sfdp command expects extra read wait byte
		buf_tra[0] = cmd;
		buf_tra[1] = buf_rec[19];
		buf_tra[2] = buf_rec[18];
		buf_tra[3] = buf_rec[17] ;
		/* Send command and receive register value */
		/* Select Slave */
    status = ptrSPI->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_ACTIVE);
    status = ptrSPI->Transfer (&buf_tra[0], &buf_rec[0], 13U);
		if (status == ARM_DRIVER_OK) {
      /* Wait till transfer done */
      while (ptrSPI->GetDataCount() != 13U) {__asm("nop");};
    }
		/* Deselect Slave */
    ptrSPI->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_INACTIVE);
		// Check erase size, currently only supports 4kbytes
    // TODO support erase size != 4kbytes?
    // TODO support other erase opcodes from the sector descriptions
    if ((buf_rec[5] & 0x3) != 0x1 || buf_rec[6] != CMD_SECTOR_ERASE) {
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    // Check address size, currently only supports 3byte addresses
    // TODO support address > 3bytes?
		//00: 3-Byte only addressing
    //01: 3- or 4-Byte addressing (e.g. defaults to 3-Byte mode; enters 4-Byte mode on command)
    //10: 4-Byte only addressing
    //11: Reserved
		//
    // TODO check for devices larger than 2Gbits?
		//For densities 2 gigabits or less, bit-31 is set to 0b. 
    if (((buf_rec[7] >> 1) & 0x3) != 0 || (buf_rec[12] & 0x80) != 0) {
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    // Get device density, stored as size in bits - 1
		//3-Byte only addressing,   
    uint32_t density = ( 
        (buf_rec[12] << 24) |		
        (buf_rec[11] << 16) |   
        (buf_rec[10] << 8 ) |
        (buf_rec[9]  << 0 ));
    *_size = (density/8) + 1;
  
  return (status);
}
 
/* Read JEDEC ID */
 int32_t ReadJedecId (uint8_t cmd, JEDEC_ID* jdc_id) {
  int32_t status; /* driver execution status */
  uint8_t buf[8]= {0};

  /* Select Slave */
  status = ptrSPI->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_ACTIVE);

  if (status == ARM_DRIVER_OK) {
    /* Set command */
    //buf[0] = CMD_READ_RDID_SST;
		buf[0] = cmd;
		//buf[3] = 1;

    /* Send command and receive register value */
    status = ptrSPI->Transfer (&buf[0], &buf[4], 4U);

    if (status == ARM_DRIVER_OK) {
      /* Wait till transfer done */
      while (ptrSPI->GetDataCount() != 4U) {
				__asm("nop"); 
			};

      jdc_id->man_id = buf[5];
			jdc_id->dev_id = (buf[6] << 8) | buf[7];
    }
  }
  /* Deselect Slave */
  ptrSPI->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_INACTIVE);
  
  return (status);
}
 
/* Read JEDEC ID */
 int32_t ReadIdSST ( uint8_t cmd, JEDEC_ID* jdc_id) {
  int32_t status; /* driver execution status */
  uint8_t buf[12] = {0};

  /* Select Slave */
  status = ptrSPI->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_ACTIVE);

  if (status == ARM_DRIVER_OK) {
    /* Set command */
		buf[0] = cmd;//CMD_READ_RDID_SST;
		//buf[3] = 1;

    /* Send command and receive register value */
    status = ptrSPI->Transfer (&buf[0], &buf[6], 6U);

    if (status == ARM_DRIVER_OK) {
      /* Wait till transfer done */
      while (ptrSPI->GetDataCount() != 6U){
				__asm("nop");
			};

      jdc_id->man_id = buf[10];
			jdc_id->dev_id = buf[11];
    }
  }
  /* Deselect Slave */
  ptrSPI->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_INACTIVE);
  
  return (status);
}



/**
  \fn          ARM_DRIVER_VERSION ARM_Flash_GetVersion (void)
  \brief       Get driver version.
  \return      \ref ARM_DRIVER_VERSION
*/
static ARM_DRIVER_VERSION GetVersion (void) {
  return DriverVersion;
}

/**
  \fn          ARM_FLASH_CAPABILITIES ARM_Flash_GetCapabilities (void)
  \brief       Get driver capabilities.
  \return      \ref ARM_FLASH_CAPABILITIES
*/
static ARM_FLASH_CAPABILITIES GetCapabilities (void) {
  return DriverCapabilities;
}

/**
  \fn          int32_t ARM_Flash_Initialize (ARM_Flash_SignalEvent_t cb_event)
  \brief       Initialize the Flash Interface.
  \param[in]   cb_event  Pointer to \ref ARM_Flash_SignalEvent
  \return      \ref execution_status
*/
 int32_t Initialize (ARM_Flash_SignalEvent_t cb_event) {
  int32_t status;
  (void)cb_event;

  FlashStatus.busy  = 0U;
  FlashStatus.error = 0U;

  status = ptrSPI->Initialize(NULL);
  if (status != ARM_DRIVER_OK) { return ARM_DRIVER_ERROR; }

  Flags = FLASH_INIT;
	
	

  return ARM_DRIVER_OK;
}

/**
  \fn          int32_t ARM_Flash_Uninitialize (void)
  \brief       De-initialize the Flash Interface.
  \return      \ref execution_status
*/
static int32_t Uninitialize (void) {

  Flags = 0U;
  return ptrSPI->Uninitialize();
} 

/**
  \fn          int32_t ARM_Flash_PowerControl (ARM_POWER_STATE state)
  \brief       Control the Flash interface power.
  \param[in]   state  Power state
  \return      \ref execution_status
*/
 int32_t PowerControl (ARM_POWER_STATE state) {
  int32_t status;

  switch ((int32_t)state) {
    case ARM_POWER_OFF:
      Flags &= ~FLASH_POWER;

      FlashStatus.busy  = 0U;
      FlashStatus.error = 0U;

      return ptrSPI->PowerControl(ARM_POWER_FULL);

    case ARM_POWER_FULL:
      if ((Flags & FLASH_INIT) == 0U) {
        return ARM_DRIVER_ERROR;
      }

      if ((Flags & FLASH_POWER) == 0U) {
        status = ptrSPI->PowerControl(ARM_POWER_FULL);
        if (status != ARM_DRIVER_OK) {
          return ARM_DRIVER_ERROR;
        }
        status = ptrSPI->Control(ARM_SPI_MODE_MASTER | ARM_SPI_CPOL0_CPHA0  |
                                                       ARM_SPI_DATA_BITS(8) |
                                                       ARM_SPI_MSB_LSB      |
                                                       ARM_SPI_SS_MASTER_SW,
                                                       SPI_BUS_SPEED);
        if (status != ARM_DRIVER_OK) {
          return ARM_DRIVER_ERROR;
        }

        FlashStatus.busy  = 0U;
        FlashStatus.error = 0U;

        Flags |= FLASH_POWER;
				
//--------------------------------------------------------------------------------				
				volatile uint32_t i=0x03; 
				while(i-->0) {
					ReadJedecId (CMD_READ_RDID, &jdc_id_) ; 
					delay_mic();	
			  }
				if (jdc_id_.man_id == 0xFF && (jdc_id_.dev_id == 0xFFFF | jdc_id_.dev_id == 0xFF)) {
				i = 1;
				while(i-->0) {
					ReadIdSST (CMD_READ_RDID_SST, &jdc_id_);
					delay_mic();
					}		  
			 }
				if (jdc_id_.man_id == 0xFF && (jdc_id_.dev_id == 0xFFFF | jdc_id_.dev_id == 0xFF | jdc_id_.dev_id == 0x00)) {
				i = 1;
				while(i-->0) {
					ReadIdSST (CMD_READ_RDID_PMC, &jdc_id_);
					delay_mic();
					}		  
			 }
				if (jdc_id_.man_id == 0xFF && (jdc_id_.dev_id == 0xFFFF | jdc_id_.dev_id == 0xFF | jdc_id_.dev_id == 0x00)) {
				i = 1;
				while(i-->0) {
					ReadJedecId (CMD_READ_RDID_ATMEL, &jdc_id_);
					delay_mic();
					}		  
			 }
				 if (!(jdc_id_.man_id == GENERIC_MANUF_ID && (jdc_id_.dev_id == GENERIC_DEVICE_ID ))){
				 flschip = flash_id_to_entry(jdc_id_.man_id, jdc_id_.dev_id);
				 }
				 if (flschip == NULL) {
					 SPI_UsrLog ("\n Flash not supported\n\n");
				 }
				    else {
							//SPI_UsrLog ("\n Flash supported");
							SPI_UsrLog ("\n Vendor - %s\n Chip   - %s\n Size   - %d Kbytes\n\n\n",\
							flschip->vendor, flschip->name, flschip->total_size);
							FlashInfo.sector_count = flschip->block_erasers->eraseblocks[0].count;
						}
//-----------------------------------------------------------------------------------				
      }
      return ARM_DRIVER_OK;

    case ARM_POWER_LOW:
      return ARM_DRIVER_ERROR_UNSUPPORTED;

    default:
      return ARM_DRIVER_ERROR;
  }
}

/**
  \fn          int32_t ARM_Flash_ReadData (uint32_t addr, void *data, uint32_t cnt)
  \brief       Read data from Flash.
  \param[in]   addr  Data address.
  \param[out]  data  Pointer to a buffer storing the data read from Flash.
  \param[in]   cnt   Number of data items to read.
  \return      number of data items read or \ref execution_status
*/
 int32_t ReadData (uint32_t addr, void *data, uint32_t cnt) {
  
  return (flschip->read(addr, data, cnt));
}
 
/**
  \fn          int32_t ARM_Flash_ReadData (uint32_t addr, void *data, uint32_t cnt)
  \brief       Read data from Flash.
  \param[in]   addr  Data address.
  \param[out]  data  Pointer to a buffer storing the data read from Flash.
  \param[in]   cnt   Number of data items to read.
  \return      number of data items read or \ref execution_status
*/
  int32_t spi_chip_read (uint32_t addr, void *data, uint32_t cnt) {
  uint8_t  buf[8];
  int32_t  status;

  if ((addr > (flschip->total_size*1024)) || (data == NULL)) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }
	
	if ((addr & 0x3fff)  == 0) BSP_LED_Toggle(LED3);                //indicate reading

  /* Prepare Command with address */
  buf[0] = CMD_READ_DATA;
  buf[1] = (uint8_t)(addr >> 16);
  buf[2] = (uint8_t)(addr >>  8);
  buf[3] = (uint8_t)(addr >>  0);

  /* Select Slave */
  status = ptrSPI->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_ACTIVE);

  if (status == ARM_DRIVER_OK) {
    /* Send Command with Address */
    status = ptrSPI->Send(buf, 4U);

    if (status == ARM_DRIVER_OK) {
      while (ptrSPI->GetDataCount() != 4U) {
				__asm("nop");
			};

      status = ptrSPI->Receive(data, cnt);

      if (status == ARM_DRIVER_OK) {
        while (ptrSPI->GetDataCount() != cnt) {
				__asm("nop");
			};
        
        /* Number of data items read */
        status = (int32_t)cnt;
      }
    }
  }
  ptrSPI->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_INACTIVE);

  return (status);
}
	


/**
  \fn          int32_t ARM_Flash_ProgramData (uint32_t addr, const void *data, uint32_t cnt)
  \brief       Program data to Flash.
  \param[in]   addr  Data address.
  \param[in]   data  Pointer to a buffer containing the data to be programmed to Flash.
  \param[in]   cnt   Number of data items to program.
  \return      number of data items programmed or \ref execution_status
*/
 int32_t ProgramData (uint32_t addr, const void *data, uint32_t cnt) {
	 int32_t sts;
	 int32_t  status;
	 
	 if (flschip->unlock) {
		status = flschip->unlock(); // 
		if (status) return status;
		}
	 
	 SPI_UsrLog ("\n pd_addr -> 0x%05x   cnt -> 0x%03x", addr, cnt);
		
	 /* Enable/disable 4-byte addressing mode if flash chip supports it */
	 if (flschip->feature_bits & (FEATURE_4BA_ENTER | FEATURE_4BA_ENTER_WREN | FEATURE_4BA_ENTER_EAR7)) {
		int ret;
		
		ret = spi_enter_4ba();
		
		if (ret) {
			SPI_UsrLog ("Failed to set correct 4BA mode! Aborting.\n");
			return 1;
		}
	}	
	 
	 sts = flschip->write(addr, data, cnt);
	 if (sts < 0) {
		 SPI_UsrLog("\n ProgramData error -> %d", sts);
	 }
  
  return (sts);
}
 
/**
  \fn          int32_t ARM_Flash_ProgramData (uint32_t addr, const void *data, uint32_t cnt)
  \brief       Program data to Flash.
  \param[in]   addr  Data address.
  \param[in]   data  Pointer to a buffer containing the data to be programmed to Flash.
  \param[in]   cnt   Number of data items to program.
  \return      number of data items programmed or \ref execution_status
*/
 int32_t spi_chip_write_256 (uint32_t addr, const void *data, uint32_t cnt) {
  const uint8_t *buf;
        uint8_t  cmd[4];
        int32_t  status;
        uint32_t num, n;
	      uint16_t flash_page_size = flschip->page_size;

  if ((addr > (flschip->total_size*1024)) || (data == NULL)) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  status = ARM_DRIVER_OK;

  num = 0U;
  buf = data;

  while (cnt) {
    /* Enable data write */
    status = SetWriteEnable();
    
    if (status == ARM_DRIVER_OK) {
      /* Select Slave */
      status = ptrSPI->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_ACTIVE);
      
      if (status == ARM_DRIVER_OK) {
        /* Prepare command with address */
        cmd[0] = CMD_PAGE_PROGRAM;
        cmd[1] = (uint8_t)(addr >> 16U);
        cmd[2] = (uint8_t)(addr >>  8U);
        cmd[3] = (uint8_t)(addr >>  0U);

        status = ptrSPI->Send(cmd, 4U);

        if (status == ARM_DRIVER_OK) {
          /* Wait until command and address are sent */
          while (ptrSPI->GetDataCount() != 4U){
				  __asm("nop");
			    };

          n = flash_page_size - (addr % flash_page_size);

          if (n > cnt) {
            n = cnt;
          }

          status = ptrSPI->Send(&buf[num], n);

          if (status == ARM_DRIVER_OK) {
            /* Wait until data sent */
            while (ptrSPI->GetDataCount() != n){
				     __asm("nop");
			      };

            addr += n;
            num  += n;
            cnt  -= n;
          }
        }
      }
      /* Deselect Slave */
      ptrSPI->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_INACTIVE);

      if (status == ARM_DRIVER_OK) {
        /* Read status until device ready */
        do {
          status = ReadStatusReg(CMD_READ_STATUS, &cmd[0]);  //CMD_READ_FLAG_STATUS
          if (status != ARM_DRIVER_OK) {
            break;
          }

          /* Check Flags Status register value */
          if ((cmd[0] & 0x1U) != 1U) {
            FlashStatus.busy = 0U;
          }

        }
        while ((cmd[0] & 0x1U) == 0x1U);
      }
    }

    if (status != ARM_DRIVER_OK) {
      break;
    }
    /* Number of data items programmed */
    status = (int32_t)num;
  }

  return status;
}
 
/**
  \fn          int32_t ARM_Flash_ProgramData (uint32_t addr, const void *data, uint32_t cnt)
  \brief       Program data to Flash.
  \param[in]   addr  Data address.
  \param[in]   data  Pointer to a buffer containing the data to be programmed to Flash.
  \param[in]   cnt   Number of data items to program.
  \return      number of data items programmed or \ref execution_status
*/
 int32_t spi_chip_write_256_11 (uint32_t addr, const void *data, uint32_t cnt) {   //CMD_PAGE_PROGRAM_11 
  const uint8_t *buf;
        uint8_t  cmd[4];
        int32_t  status;
        uint32_t num, n;
	      uint16_t flash_page_size = flschip->page_size;

  if ((addr > (flschip->total_size*1024)) || (data == NULL)) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }
	
	//printf ("\n addr -> 0x%05x   cnt -> 0x%03x", addr, cnt);

  status = ARM_DRIVER_OK;

  num = 0U;
  buf = data;

  while (cnt) {
//    /* Enable data write */
    status = ARM_DRIVER_OK;
    
    if (status == ARM_DRIVER_OK) {
      /* Select Slave */
      status = ptrSPI->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_ACTIVE);
      
      if (status == ARM_DRIVER_OK) {
        /* Prepare command with address */
        cmd[0] = CMD_PAGE_PROGRAM_11;
        cmd[1] = (uint8_t)(addr >> 16U);
        cmd[2] = (uint8_t)(addr >>  8U);
        cmd[3] = (uint8_t)(addr >>  0U);

        status = ptrSPI->Send(cmd, 4U);

        if (status == ARM_DRIVER_OK) {
          /* Wait until command and address are sent */
          while (ptrSPI->GetDataCount() != 4U) {__asm("nop");};

          n = flash_page_size - (addr % flash_page_size);

          if (n > cnt) {
            n = cnt;
          }

          status = ptrSPI->Send(&buf[num], n);

          if (status == ARM_DRIVER_OK) {
            /* Wait until data sent */
            while (ptrSPI->GetDataCount() != n) {__asm("nop");};

            addr += n;
            num  += n;
            cnt  -= n;
          }
        }
      }
      /* Deselect Slave */
      ptrSPI->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_INACTIVE);

      if (status == ARM_DRIVER_OK) {
        /* Read status until device ready */
        do {
          status = ReadStatusReg(CMD_READ_STATUS, &cmd[0]);  //CMD_READ_FLAG_STATUS
          if (status != ARM_DRIVER_OK) {
            break;
          }

          /* Check Flags Status register value */
//          if ((cmd[0] & 0x1U) != 1U) {
//            FlashStatus.busy = 0U;
//          }

        }
        while ((cmd[0] & 0x1U) == 0x1U);
				FlashStatus.busy = 0U;
      }
    }

    if (status != ARM_DRIVER_OK) {
      break;
    }
    /* Number of data items programmed */
    status = (int32_t)num;
  }

  return status;
}
 
/**
  \fn          int32_t ARM_Flash_ProgramData (uint32_t addr, const void *data, uint32_t cnt)
  \brief       Program data to Flash.
  \param[in]   addr  Data address.
  \param[in]   data  Pointer to a buffer containing the data to be programmed to Flash.
  \param[in]   cnt   Number of data items to program.
  \return      number of data items programmed or \ref execution_status
*/
 int32_t spi_chip_write_af(uint32_t addr, const void *data, uint32_t cnt) {
  const uint8_t *buf;
        uint8_t  cmd[4], first = 1, bytes;
        int32_t  status;
        uint32_t num;//, n;
	  

  if ((addr > (flschip->total_size*1024)) || (data == NULL)) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }
	
	SPI_UsrLog (" addr -> 0x%05x   cnt -> 0x%03x", addr, cnt);

  status = ARM_DRIVER_OK;

  num = 0U;
  buf = data;
	
  while (cnt) {
    /* Enable data write */
    if (first) status = SetWriteEnable();
		   else status = ARM_DRIVER_OK;
    
    if (status == ARM_DRIVER_OK) {
      /* Select Slave */
      status = ptrSPI->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_ACTIVE);
      
      if (status == ARM_DRIVER_OK) {
        /* Prepare command with address */
        cmd[0] = CMD_PROGRAM_BYTE_AF;
        cmd[1] = (uint8_t)(addr >> 16U);
        cmd[2] = (uint8_t)(addr >>  8U);
        cmd[3] = (uint8_t)(addr >>  0U);

        if (first) bytes = 4;
				    else bytes = 1;
				status = ptrSPI->Send(cmd, bytes);

        if (status == ARM_DRIVER_OK) {
          /* Wait until command and address are sent */
          while (ptrSPI->GetDataCount() != bytes) {__asm("nop"); };
					 

          status = ptrSPI->Send(&buf[num], 1U);

          if (status == ARM_DRIVER_OK) {
            /* Wait until data sent */
            while (ptrSPI->GetDataCount() != 1U){__asm("nop"); };
						delay_mic();

            //addr += 1;
            num  += 1;
            cnt  -= 1;
          }
					else break;
        }
				else break;
      }
      /* Deselect Slave */
      ptrSPI->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_INACTIVE);

      if (status == ARM_DRIVER_OK) {
        /* Read status until device ready */
        do {
          status = ReadStatusReg(CMD_READ_STATUS, &cmd[0]);  //CMD_READ_FLAG_STATUS
          if (status != ARM_DRIVER_OK) {
            break;
          }

          /* Check Flags Status register value */
          if ((cmd[0] & 0x1U) != 1U) {
            FlashStatus.busy = 0U;
          }

        }
        while ((cmd[0] & 0x1U) == 0x1U);
      }
    }

    if (status != ARM_DRIVER_OK) {
      break;
    }
    /* Number of data items programmed */
    status = (int32_t)num;
		if (first) {
			first = 0;
			addr = 0;
		}
  }
	
	
	if (SetWriteDisable()!= ARM_DRIVER_OK) {
	    return ARM_DRIVER_ERROR;
	}
	ReadStatusReg(CMD_READ_STATUS, &cmd[0]);  //CMD_READ_FLAG_STATUS
   
		/* Check Flags Status register value */
		if ((cmd[0] & 0x40U) != 0U) {
			return ARM_DRIVER_ERROR;
		}

  return status;
}
 
int32_t spi_chip_write_1 (uint32_t addr, const void *data, uint32_t cnt) {  // one byte write
  const uint8_t *buf;
        uint8_t  cmd[4];
        int32_t  status;
        uint32_t num;

  if ((addr > (flschip->total_size*1024)) || (data == NULL)) {
    return ARM_DRIVER_ERROR_PARAMETER;
  }
	
	SPI_UsrLog ("\n addr -> 0x%05x   cnt -> 0x%03x", addr, cnt);

  status = ARM_DRIVER_OK;

  num = 0U;
  buf = data;

  while (cnt) {
    /* Enable data write */
    if (flschip->feature_bits	& (FEATURE_WRSR_WREN | FEATURE_WREN)) status = SetWriteEnable();
		   else status = ARM_DRIVER_OK;
    
    if (status == ARM_DRIVER_OK) {
      /* Select Slave */
      status = ptrSPI->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_ACTIVE);
      
      if (status == ARM_DRIVER_OK) {
        /* Prepare command with address */
        cmd[0] = CMD_PROGRAM_BYTE;
        cmd[1] = (uint8_t)(addr >> 16U);
        cmd[2] = (uint8_t)(addr >>  8U);
        cmd[3] = (uint8_t)(addr >>  0U);

        status = ptrSPI->Send(cmd, 4U);

        if (status == ARM_DRIVER_OK) {
          /* Wait until command and address are sent */
          while (ptrSPI->GetDataCount() != 4U) {__asm("nop");};

          status = ptrSPI->Send(&buf[num], 1);

          if (status == ARM_DRIVER_OK) {
            /* Wait until data sent */
            while (ptrSPI->GetDataCount() != 1) {__asm("nop");};

            addr ++;
            num  ++;
            cnt  --;
          }
        }
      }
      /* Deselect Slave */
      ptrSPI->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_INACTIVE);

      if (status == ARM_DRIVER_OK) {
        /* Read status until device ready */
        do {
          status = ReadStatusReg(CMD_READ_STATUS, &cmd[0]);  //CMD_READ_FLAG_STATUS
          if (status != ARM_DRIVER_OK) {
            break;
          }

          /* Check Flags Status register value */
          if ((cmd[0] & 0x1U) != 1U) {
            FlashStatus.busy = 0U;
          }

        }
        while ((cmd[0] & 0x1U) == 0x1U);
      }
    }

    if (status != ARM_DRIVER_OK) {
      break;
    }
    /* Number of data items programmed */
    status = (int32_t)num;
  }

  return status;
}

/**
  \fn          int32_t ARM_Flash_EraseSector (uint32_t addr)
  \brief       Erase Flash Sector.
  \param[in]   addr  Sector address
  \return      \ref execution_status
*/
static int32_t EraseSector (uint32_t addr) {
  uint8_t buf[4];
  int32_t status;
	uint8_t i;
	
	for (i = 0; i < NUM_ERASEFUNCTIONS; i++) {
		 if (flschip->block_erasers[i].eraseblocks->size == 4 * 1024) break;
	 }
	if (i == NUM_ERASEFUNCTIONS) return ARM_DRIVER_ERROR_PARAMETER;  //not find

  if (flschip->feature_bits & FEATURE_WRSR_WREN) status = SetWriteEnable();
	   else status = ARM_DRIVER_OK;

  if (status == ARM_DRIVER_OK) {
    FlashStatus.busy  = 1U;
    FlashStatus.error = 0U;

		buf[0] = flschip->block_erasers[i].block_erase ;//CMD_SECTOR_ERASE;
    buf[1] = (uint8_t)(addr >> 16U);
    buf[2] = (uint8_t)(addr >>  8U);
    buf[3] = (uint8_t)(addr >>  0U);
		
    status = SendCmd(buf, 4U);
  }

  return status;
}
//static int32_t memcmp_(uint32_t * buf, uint32_t val,  uint32_t word_cnt){
//	
//  int32_t status = 0;
//	uint32_t addr;
//	
//	while (word_cnt){
//		if (*buf != val) return 1;
//		buf++;
//		word_cnt =-4;
//	}
//	return 0;
//}

static int32_t isErased (void) {
  uint32_t buf[0x40], buf_[0x40];
  int32_t status = 0;
	uint32_t addr;
	
	memset(buf_, 0xff, sizeof(buf_));
	for (addr=0; addr<flschip->total_size*1024;) {
		//if ((addr & 0x3fff)  == 0) BSP_LED_Toggle(LED3);
		ReadData(addr, (uint32_t *)&buf[0], sizeof(buf));
		status += memcmp(buf, buf_, sizeof(buf));
		//status += memcmp_(buf, 0xffffffff, sizeof(buf));
		if (status) break;
		addr += sizeof(buf)*4;
	}
	return status;
}

//static int32_t isLocked(void) {
//  uint8_t cmd[4];
//  int32_t status;
//	 
//	status = ReadStatusReg(CMD_READ_STATUS, &cmd[0]);  //
//          if (status == ARM_DRIVER_OK) {
//						if (cmd[0] & 0x0CU) {
//							 printf("\n Flash is locked for writing!!!");	
//							 return 1;
//						}	
//            else return ARM_DRIVER_OK;						
//					}
//					else return ARM_DRIVER_ERROR; 

//}

//int32_t spi_disable_blockprotect (void) {
//	uint8_t cmd[4], stat;
//  int32_t status;
//	 
//	if (isLocked() == 1){
//		if (WriteStatusReg(0)) return ARM_DRIVER_ERROR;
//		status = ReadStatusReg(CMD_READ_STATUS, &cmd[0]);  //CMD_READ_FLAG_STATUS
//          if (status != ARM_DRIVER_OK) {
//            return ARM_DRIVER_ERROR;
//          }
//          /* Check Flags Status register value */
//          if (cmd[0] & 0x0CU) {
//            return 1;
//          }
//					 else return ARM_DRIVER_OK;
//		
//	} 
//    else  if (isLocked() == ARM_DRIVER_OK) return ARM_DRIVER_OK;
//	      else return ARM_DRIVER_ERROR;
//}





/**
  \fn          int32_t ARM_Flash_EraseChip (void)
  \brief       Erase complete Flash.
               Optional function for faster full chip erase.
  \return      \ref execution_status
*/
 int32_t EraseChip (void) {
	 uint8_t i;
	 for (i = 0; i < NUM_ERASEFUNCTIONS; i++) {
		 //search for a command to erase the entire chip,  not individual sectors
		 if (flschip->block_erasers[i].eraseblocks->count == 1 && flschip->block_erasers[i].eraseblocks[1].size == 0) break;
	 }
	 
	 return flschip->erase(flschip->block_erasers[i].block_erase);
 }
 
int32_t spi_erase_bulk (uint8_t cmd) {
  //uint8_t cmd[4];
  int32_t status;
	uint8_t buf[4];
	volatile int32_t led_tgl=30;
	
	 
	if (isErased() == 0) return ARM_DRIVER_OK; //no need execute erase
	 
	if (flschip->unlock) {  //(flschip->unlock == spi_disable_blockprotect)
		status = flschip->unlock();//spi_disable_blockprotect(); // 
		if (status) return status;
		}

  FlashStatus.busy  = 1U;
  FlashStatus.error = 0U;

	if (flschip->feature_bits & (FEATURE_WRSR_WREN | FEATURE_WREN)) {   //flschip->write != spi_chip_write_256_11
  status = SetWriteEnable();

  if (status == ARM_DRIVER_OK) {
    
		status = SendCmd(&cmd, 1U);
		
		do {
          status = ReadStatusReg(CMD_READ_STATUS, &buf[0]);  //CMD_READ_FLAG_STATUS
          if (status != ARM_DRIVER_OK) {
            break;
          }
					if (led_tgl-- == 0) {BSP_LED_Toggle(LED3); led_tgl = 10;}
		      HAL_Delay(1);
          /* Check Flags Status register value */
          if ((buf[0] & 0x1U) != 1U) {
            FlashStatus.busy = 0U;
          }

        }
        while ((buf[0] & 0x1U) == 0x1U);
  }
 }
	 if (isErased()){ 
	   SPI_UsrLog ("\n Flash not erased!!!\n");
		 return ARM_DRIVER_ERROR;
	 }
	   else SPI_UsrLog ("\n Flash erased!!!, all 0xFF\n");
   BSP_LED_Off(LED3);
   return status;
 
}


 int32_t spi_erase_bulk_sec (uint8_t cmd) {     //bulk erase on sectors
  int32_t status, addr;
	uint8_t buf[4];
	 
	if (isErased() == 0) return ARM_DRIVER_OK; //no need execute erase
	 	

  FlashStatus.busy  = 1U;
  FlashStatus.error = 0U;


	for(addr=0; addr<(flschip->total_size*1024); )  {

		buf[0] = CMD_SECTOR_ERASE;
		buf[1] = (uint8_t)(addr >> 16U);
		buf[2] = (uint8_t)(addr >>  8U);
		buf[3] = (uint8_t)(addr >>  0U);
		
		status = SendCmd(buf, 4U);
		
		do {
          status = ReadStatusReg(CMD_READ_STATUS, &buf[0]);  //CMD_READ_FLAG_STATUS
          if (status != ARM_DRIVER_OK) {
            break;
          }

          /* Check Flags Status register value */
          if ((buf[0] & 0x1U) != 1U) {
            FlashStatus.busy = 0U;
          }

        }
        while ((buf[0] & 0x1U) == 0x1U);
				addr += 4096;
			}
	
	
  if (isErased()) {
	   SPI_UsrLog("\n Flash not erased!!!\n")
	}
	   else SPI_UsrLog ("\n Flash erased!!!, all 0xFF\n");
  return status;
}

/**
  \fn          ARM_FLASH_STATUS ARM_Flash_GetStatus (void)
  \brief       Get Flash status.
  \return      Flash status \ref ARM_FLASH_STATUS
*/
static ARM_FLASH_STATUS GetStatus (void) {
  uint8_t val;

  if (FlashStatus.busy == 1U) {
    /* Read flag status register */
    if (ReadStatusReg (CMD_READ_STATUS, &val) == ARM_DRIVER_OK) {
      /* Check "Program or erase controller" bit */
      if ((val & 0x1U) != 0U) {
        FlashStatus.busy = 1U;
      }
			else {
				FlashStatus.busy = 0U;
				FlashStatus.error = 0U;
			}

    }
    else {
      FlashStatus.error = 1U;
    }
  }

  return FlashStatus;
}

/**
  \fn          ARM_FLASH_INFO * ARM_Flash_GetInfo (void)
  \brief       Get Flash information.
  \return      Pointer to Flash information \ref ARM_FLASH_INFO
*/
static ARM_FLASH_INFO * GetInfo (void) {
	//FlashInfo.sector_count = fl_sec_cnt;
  return &FlashInfo;
}


/* Flash Driver Control Block */
extern
ARM_DRIVER_FLASH ARM_Driver_Flash_(DRIVER_FLASH_NUM);
ARM_DRIVER_FLASH ARM_Driver_Flash_(DRIVER_FLASH_NUM) = {
  GetVersion,
  GetCapabilities,
  Initialize,
  Uninitialize,
  PowerControl,
  ReadData,
  ProgramData,
  EraseSector,
  EraseChip,
  GetStatus,
  GetInfo
};
