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
 * Project:      Flash Device Description for Micron W25Q80BV (SPI)
 * -------------------------------------------------------------------- */
 #include <stdint.h>
 #include "Driver_Flash.h"
 #include "Driver_SPI.h"

#define FLASH_SECTOR_COUNT      ((uint32_t)256)      /* Number of sectors */
#define FLASH_SECTOR_SIZE       ((uint32_t)0x1000)   /* Sector size: 4kB */
#define FLASH_PAGE_SIZE         ((uint32_t)256)      /* Programming page size in bytes */
#define FLASH_PROGRAM_UNIT      ((uint32_t)1)        /* Smallest programmable unit in bytes */
#define FLASH_ERASED_VALUE      ((uint8_t)0xFF)      /* Contents of erased memory */



/* Flash Driver Flags */
#define FLASH_INIT              (0x01U)
#define FLASH_POWER             (0x02U)


typedef struct _JEDEC_ID {
  uint8_t  man_id;            
  uint16_t dev_id; 
} JEDEC_ID;


int32_t ReadData (uint32_t addr, void *data, uint32_t cnt);
int32_t ProgramData (uint32_t addr, const void *data, uint32_t cnt);
int32_t ReadSfdpReg (uint8_t cmd, uint32_t* _size);
int32_t ReadJedecId (uint8_t cmd, JEDEC_ID* jdc_id);
int32_t ReadIdSST ( uint8_t cmd, JEDEC_ID* jdc_id);
int32_t EraseChip (void);
int32_t Initialize (ARM_Flash_SignalEvent_t cb_event);
int32_t Uninitialize (void);
int32_t PowerControl (ARM_POWER_STATE state);
ARM_SPI_STATUS Spi_status(void);



int32_t spi_chip_read         (uint32_t addr, void *data, uint32_t cnt);
int32_t spi_chip_write_256    (uint32_t addr, const void *data, uint32_t cnt);
int32_t spi_chip_write_256_11 (uint32_t addr, const void *data, uint32_t cnt);
int32_t spi_chip_write_af     (uint32_t addr, const void *data, uint32_t cnt);
int32_t spi_chip_write_1      (uint32_t addr, const void *data, uint32_t cnt);
int32_t spi_erase_bulk        (uint8_t cmd); 
int32_t spi_erase_bulk_sec    (uint8_t cmd);

