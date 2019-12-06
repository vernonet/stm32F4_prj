#include "Driver_SPI.h"

/* SPI Driver */
#define _SPI_Driver_(n)  Driver_SPI##n
#define  SPI_Driver_(n)  _SPI_Driver_(n)
extern ARM_DRIVER_SPI     SPI_Driver_(DRIVER_SPI_NUM);
#define ptrSPI          (&SPI_Driver_(DRIVER_SPI_NUM))

#define NUM_BYTES_CMD                2

/* SPI Data Flash Commands */
#define CMD_READ_DATA           (0x03U)
#define CMD_READ_STATUS         (0x05U)
#define CMD_WRITE_ENABLE        (0x06U)
#define CMD_WRITE_DISABLE       (0x04U)
#define CMD_PAGE_PROGRAM        (0x02U)
#define CMD_PAGE_PROGRAM_11     (0x11U)
#define CMD_PROGRAM_BYTE_AF     (0xAFU)
#define CMD_PROGRAM_BYTE        (0x02U)
#define CMD_READ_FLAG_STATUS    (0x70U)
#define CMD_SECTOR_ERASE        (0x20U)//(0xD8U)
#define CMD_BULK_ERASE          (0xC7U)
#define CMD_BULK_ERASE_SST      (0x60U)
#define CMD_READ_SFDP           (0x5AU) // Read SFDP 
#define CMD_READ_RDID           (0x9fU) // Read Manufacturer and JDEC Device ID 
#define CMD_READ_RDID_SST       (0x90U)
#define CMD_READ_RDID_ATMEL     (0x15U)
#define CMD_READ_RDID_PMC       (0xABU)
#define CMD_EWSR                (0x50U)
#define CMD_WRSR                (0x01U)
#define CMD_READ_CONF_REG       (0x15U)

/* Enter 4-byte Address Mode */
#define JEDEC_ENTER_4_BYTE_ADDR_MODE	0xB7
/* Exit 4-byte Address Mode */
#define JEDEC_EXIT_4_BYTE_ADDR_MODE	0xE9
/* Write Extended Address Register */
#define JEDEC_WRITE_EXT_ADDR_REG	0xC5
/* Read Extended Address Register */
#define JEDEC_READ_EXT_ADDR_REG		0xC8

void delay_mic(void);
int32_t SendCmd (uint8_t * cmd, uint8_t bytes);
int32_t ReadStatusReg (uint8_t cmd, uint8_t *stat);
int32_t ReadConfigReg (uint8_t cmd, uint8_t *stat);
int32_t SetWriteEnable (void);
int32_t SetWriteDisable (void);
int spi_enter_4ba(void);
int spi_exit_4ba(void);
int32_t spi_disable_blockprotect (void);
int32_t spi_disable_blockprotect_at2x_global_unprotect(void);
int32_t spi_disable_blockprotect_at25f512a(void);
int32_t spi_disable_blockprotect_bp1_srwd(void);
int32_t spi_disable_blockprotect_bp3_srwd(void);
int32_t spi_disable_blockprotect_bp4_srwd(void);
int32_t spi_disable_blockprotect_at25f512b(void);
int32_t spi_disable_blockprotect_bp2_srwd(void);
int32_t spi_disable_blockprotect_n25q(void);
int32_t spi_disable_blockprotect_at25f(void);
int32_t spi_disable_blockprotect_at25fs010(void);
int32_t spi_disable_blockprotect_at25fs040(void);

uint32_t CalcCRC32(uint8_t *Buf, uint32_t Len, uint32_t id);
