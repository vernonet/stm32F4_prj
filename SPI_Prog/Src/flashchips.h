/*
 * This file is part of the flashrom project.
 *
 * Copyright (C) 2000 Silicon Integrated System Corporation
 * Copyright (C) 2000 Ronald G. Minnich <rminnich@gmail.com>
 * Copyright (C) 2005-2007 coresystems GmbH <stepan@coresystems.de>
 * Copyright (C) 2006-2009 Carl-Daniel Hailfinger
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef __FLASHCHIPS_H__
#define __FLASHCHIPS_H__ 1

/*
 * Please keep this list sorted alphabetically by manufacturer. The first
 * entry of each section should be the manufacturer ID, followed by the
 * list of devices from that manufacturer (sorted by device ID).
 *
 * SPI parts have at least 16-bit device IDs if they support RDID.
 */
 
 #include <stdint.h>
 
 //#include "W25Q80BV.h"
 /*
 * How many different contiguous runs of erase blocks with one size each do
 * we have for a given erase function?
 */
#define NUM_ERASEREGIONS 5
/*
 * How many different erase functions do we have per chip?
 * Atmel AT25FS010 has 6 different functions.
 */
#define NUM_ERASEFUNCTIONS 6


/* Feature bits used for SPI only */
#define FEATURE_WREN	          (1 << 5)      //I added
#define FEATURE_WRSR_EWSR	      (1 << 6)
#define FEATURE_WRSR_WREN	      (1 << 7)
#define FEATURE_WRSR_EITHER	    (FEATURE_WRSR_EWSR | FEATURE_WRSR_WREN)
#define FEATURE_OTP		          (1 << 8)
#define FEATURE_QPI		          (1 << 9)
#define FEATURE_4BA_ENTER	      (1 << 10) /**< Can enter/exit 4BA mode with instructions 0xb7/0xe9 w/o WREN */
#define FEATURE_4BA_ENTER_WREN	(1 << 11) /**< Can enter/exit 4BA mode with instructions 0xb7/0xe9 after WREN */
#define FEATURE_4BA_ENTER_EAR7	(1 << 12) /**< Can enter/exit 4BA mode by setting bit7 of the ext addr reg */
#define FEATURE_4BA_EXT_ADDR	  (1 << 13) /**< Regular 3-byte operations can be used by writing the most
					                                  significant address byte into an extended address register. */
#define FEATURE_4BA_READ	      (1 << 14) /**< Native 4BA read instruction (0x13) is supported. */
#define FEATURE_4BA_FAST_READ	  (1 << 15) /**< Native 4BA fast read instruction (0x0c) is supported. */
#define FEATURE_4BA_WRITE	      (1 << 16) /**< Native 4BA byte program (0x12) is supported. */
/* 4BA Shorthands */
#define FEATURE_4BA_NATIVE	    (FEATURE_4BA_READ | FEATURE_4BA_FAST_READ | FEATURE_4BA_WRITE)
#define FEATURE_4BA		          (FEATURE_4BA_ENTER | FEATURE_4BA_EXT_ADDR | FEATURE_4BA_NATIVE)
#define FEATURE_4BA_WREN	      (FEATURE_4BA_ENTER_WREN | FEATURE_4BA_EXT_ADDR | FEATURE_4BA_NATIVE)
#define FEATURE_4BA_EAR7	      (FEATURE_4BA_ENTER_EAR7 | FEATURE_4BA_EXT_ADDR | FEATURE_4BA_NATIVE)




#define SPI_BLOCK_ERASE_81      (0x81U)
#define SPI_BLOCK_ERASE_50      (0x50U)
#define SPI_BLOCK_ERASE_20      (0x20U)
#define SPI_BLOCK_ERASE_52      (0x52U)
#define SPI_BLOCK_ERASE_62      (0x62U)
#define SPI_BLOCK_ERASE_D8      (0xD8U)
#define SPI_BLOCK_ERASE_60      (0x60U)
#define SPI_BLOCK_ERASE_C7      (0xC7U)
#define SPI_BLOCK_ERASE_D7      (0xD7U)




#define TEST_UNTESTED	(struct tested){ .probe = NT, .read = NT, .erase = NT, .write = NT }

#define TEST_OK_PROBE	(struct tested){ .probe = OK, .read = NT, .erase = NT, .write = NT }
#define TEST_OK_PR	(struct tested){ .probe = OK, .read = OK, .erase = NT, .write = NT }
#define TEST_OK_PRE	(struct tested){ .probe = OK, .read = OK, .erase = OK, .write = NT }
#define TEST_OK_PRU	(struct tested){ .probe = OK, .read = OK, .erase = NT, .write = NT }
#define TEST_OK_PREU	(struct tested){ .probe = OK, .read = OK, .erase = OK, .write = NT }
#define TEST_OK_PREW	(struct tested){ .probe = OK, .read = OK, .erase = OK, .write = OK }
#define TEST_OK_PREWU	(struct tested){ .probe = OK, .read = OK, .erase = OK, .write = OK }

#define TEST_BAD_PROBE	(struct tested){ .probe = BAD, .read = NT, .erase = NT, .write = NT }
#define TEST_BAD_PR	(struct tested){ .probe = BAD, .read = BAD, .erase = NT, .write = NT }
#define TEST_BAD_PRE	(struct tested){ .probe = BAD, .read = BAD, .erase = BAD, .write = NT }
#define TEST_BAD_PREW	(struct tested){ .probe = BAD, .read = BAD, .erase = BAD, .write = BAD }
#define TEST_BAD_PREWU	(struct tested){ .probe = BAD, .read = BAD, .erase = BAD, .write = BAD }

#define GENERIC_MANUF_ID	0xFF	/* Check if there is a vendor ID */
#define GENERIC_DEVICE_ID	0xFFFF	/* Only match the vendor ID */
#define SFDP_DEVICE_ID		0xFFFE
#define PROGMANUF_ID		0xFFFE	/* dummy ID for opaque chips behind a programmer */
#define PROGDEV_ID		0x01	/* dummy ID for opaque chips behind a programmer */

#define VARIABLE_SIZE_MANUF_ID 0x3eaf
#define VARIABLE_SIZE_DEVICE_ID 0x10af


#define AMIC_ID			      0x7F37	/* AMIC */
#define AMIC_ID_NOPREFIX	0x37	/* AMIC */
#define AMIC_A25L05PT		0x2020
#define AMIC_A25L05PU		0x2010
#define AMIC_A25L10PT		0x2021
#define AMIC_A25L10PU		0x2011
#define AMIC_A25L20PT		0x2022
#define AMIC_A25L20PU		0x2012
#define AMIC_A25L40PT		0x2013	/* Datasheet says T and U have
					   same device ID. Confirmed by
					   hardware testing. */
#define AMIC_A25L40PU		0x2013
#define AMIC_A25L80P		0x2014	/* Seems that no A25L80PT exists */
#define AMIC_A25L16PT		0x2025
#define AMIC_A25L16PU		0x2015
#define AMIC_A25L512		0x3010
#define AMIC_A25L010		0x3011
#define AMIC_A25L020		0x3012
#define AMIC_A25L040		0x3013
#define AMIC_A25L080		0x3014
#define AMIC_A25L016		0x3015
#define AMIC_A25L032		0x3016
#define AMIC_A25LQ16		0x4015
#define AMIC_A25LQ032		0x4016	/* Same as A25LQ32A, but the latter supports SFDP */
#define AMIC_A25LQ64		0x4017

#define ATMEL_ID		      0x1F	/* Atmel (now used by Adesto) */
#define ATMEL_AT25DF021		0x4300
#define ATMEL_AT25DF041A	0x4401
#define ATMEL_AT25DF081		0x4502	/* EDI 0x00. AT25DL081 has same ID + EDI 0x0100 */
#define ATMEL_AT25DF081A	0x4501	/* Yes, 81A has a lower number than 81 */
#define ATMEL_AT25DF161		0x4602
#define ATMEL_AT25DF321		0x4700	/* Same as 26DF321 */
#define ATMEL_AT25DF321A	0x4701
#define ATMEL_AT25DF641		0x4800
#define ATMEL_AT25DL161		0x4603	/* EDI 0x0100 */
#define ATMEL_AT25DQ161		0x8600	/* EDI 0x0100 */
#define ATMEL_AT25DQ321		0x8700	/* EDI 0x0100 */
#define ATMEL_AT25F512		0x60	/* Needs AT25F_RDID. ID from PCN and actual HW. Seems to be a relabeled AT25F1024. */
#define ATMEL_AT25F512A		0x6565	/* Needs AT25F_RDID */
#define ATMEL_AT25F512B		0x6500
#define ATMEL_AT25F1024		0x6060	/* Needs AT25F_RDID */
#define ATMEL_AT25F2048		0x63	/* Needs AT25F_RDID */
#define ATMEL_AT25F4096		0x64	/* Needs AT25F_RDID */
#define ATMEL_AT25FS010		0x6601
#define ATMEL_AT25FS040		0x6604
#define ATMEL_AT25SF041		0x8401
#define ATMEL_AT25SF081		0x8501
#define ATMEL_AT25SF161		0x8601
#define ATMEL_AT25SL128A	0x4218
#define ATMEL_AT26DF041		0x4400
#define ATMEL_AT26DF081		0x4500	/* guessed, no datasheet available */
#define ATMEL_AT26DF081A	0x4501
#define ATMEL_AT26DF161		0x4600
#define ATMEL_AT26DF161A	0x4601
#define ATMEL_AT26DF321		0x4700	/* Same as 25DF321 */
#define ATMEL_AT26F004		0x0400

#define ATMEL_AT45BR3214B	/* No ID available */
#define ATMEL_AT45CS1282	0x2920
#define ATMEL_AT45D011		/* No ID available */
#define ATMEL_AT45D021A		/* No ID available */
#define ATMEL_AT45D041A		/* No ID available */
#define ATMEL_AT45D081A		/* No ID available */
#define ATMEL_AT45D161		/* No ID available */
#define ATMEL_AT45DB011		/* No ID (opcode) available for AT45DB011, AT45DB011B */
#define ATMEL_AT45DB011D	0x2200
#define ATMEL_AT45DB021		/* No ID (opcode) available for AT45DB021, AT45DB021A, AT45DB021B */
#define ATMEL_AT45DB021D	0x2300
#define ATMEL_AT45DB021E	/* same as above but with EDI 0x0100 */
#define ATMEL_AT45DB041		/* No ID (opcode) available for AT45DB041, AT45DB041A, AT45DB041B */
#define ATMEL_AT45DB041D	0x2400
#define ATMEL_AT45DB041E	/* same as above but with EDI 0x0100 */
#define ATMEL_AT45DB081		/* No ID (opcode) available for AT45DB081, AT45DB081A, AT45DB081B */
#define ATMEL_AT45DB081D	0x2500
#define ATMEL_AT45DB081E	/* same as above but with EDI 0x0100 */
#define ATMEL_AT45DB161		/* No ID (opcode) available for AT45DB161, AT45DB161B */
#define ATMEL_AT45DB161D	0x2600
#define ATMEL_AT45DB161E	/* same as above but with EDI 0x0100 */
#define ATMEL_AT45DB321		/* No ID (opcode) available for AT45DB321, AT45DB321B */
#define ATMEL_AT45DB321C	0x2700
#define ATMEL_AT45DB321E	/* same as above but with EDI 0x0100 */
#define ATMEL_AT45DB321D	0x2701 /* Buggy data sheet */
#define ATMEL_AT45DB642		/* No ID (opcode) available for AT45DB642 */

/*
 * EN25 chips are SPI, first byte of device ID is memory type,
 * second byte of device ID is log(bitsize)-9.
 * Vendor and device ID of EN29 series are both prefixed with 0x7F, which
 * is the continuation code for IDs in bank 2.
 * Vendor ID of EN25 series is NOT prefixed with 0x7F, this results in
 * a collision with Mitsubishi. Mitsubishi once manufactured flash chips.
 * Let's hope they are not manufacturing SPI flash chips as well.
 */
#define EON_ID			0x7F1C	/* EON Silicon Devices */
#define EON_ID_NOPREFIX		0x1C	/* EON, missing 0x7F prefix */
#define EON_EN25B05		0x2010	/* Same as EN25P05, can be distinguished by RES/REMS: */
#define EON_EN25P05		0x05
#define EON_EN25B05T		0x25
#define EON_EN25B05B		0x95
#define EON_EN25B10		0x2011	/* Same as EN25P10, can be distinguished by RES/REMS: */
#define EON_EN25P10		0x10
#define EON_EN25B10T		0x40
#define EON_EN25B10B		0x30
#define EON_EN25B20		0x2012	/* Same as EN25P20, can be distinguished by RES/REMS: */
#define EON_EN25P20		0x11
#define EON_EN25B20T		0x41
#define EON_EN25B20B		0x31
#define EON_EN25B40		0x2013	/* Same as EN25P40, can be distinguished by RES/REMS: */
#define EON_EN25P40		0x12
#define EON_EN25B40T		0x42
#define EON_EN25B40B		0x32
#define EON_EN25B80		0x2014	/* Same as EN25P80, can be distinguished by RES/REMS: */
#define EON_EN25P80		0x13
#define EON_EN25B80T		0x43
#define EON_EN25B80B		0x33
#define EON_EN25B16		0x2015	/* Same as EN25P16, can be distinguished by RES/REMS: */
#define EON_EN25P16		0x14
#define EON_EN25B16T		0x44
#define EON_EN25B16B		0x34
#define EON_EN25B32		0x2016	/* Same as EN25P32, can be distinguished by RES/REMS: */
#define EON_EN25P32		0x15
#define EON_EN25B32T		0x45
#define EON_EN25B32B		0x35
#define EON_EN25B64		0x2017	/* Same as EN25P64, can be distinguished by RES/REMS: */
#define EON_EN25P64		0x16
#define EON_EN25B64T		0x46
#define EON_EN25B64B		0x36
#define EON_EN25D16		0x3015
#define EON_EN25Q40		0x3013
#define EON_EN25Q80		0x3014
#define EON_EN25D16		0x3015	/* Same as Q16 */
#define EON_EN25Q32		0x3016
#define EON_EN25Q64		0x3017
#define EON_EN25Q128		0x3018
#define EON_EN25F05		0x3110
#define EON_EN25F10		0x3111
#define EON_EN25F20		0x3112
#define EON_EN25F40		0x3113
#define EON_EN25F80		0x3114
#define EON_EN25F16		0x3115
#define EON_EN25F32		0x3116
#define EON_EN25F64		0x3117
#define EON_EN25Q40		0x3013
#define EON_EN25Q80		0x3014
#define EON_EN25Q16		0x3015	/* Same as EN25D16 */
#define EON_EN25Q32		0x3016	/* Same as EN25Q32A and EN25Q32B */
#define EON_EN25Q64		0x3017
#define EON_EN25Q128		0x3018
#define EON_EN25QH16		0x7015
#define EON_EN25QH32		0x7016
#define EON_EN25QH64		0x7017
#define EON_EN25QH128		0x7018
#define EON_EN25QH256		0x7019
#define EON_EN25S10		0x3811
#define EON_EN25S20		0x3812
#define EON_EN25S40		0x3813
#define EON_EN25S80		0x3814
#define EON_EN25S16		0x3815
#define EON_EN25S32		0x3816
#define EON_EN25S64		0x3817
#define EON_EN25T80		0x5114
#define EON_EN25T16		0x5115
#define EON_EN29F512		0x7F21
#define EON_EN29F010		0x20
#define EON_EN29F040A		0x7F04
#define EON_EN29LV010		0x7F6E
#define EON_EN29LV040A		0x7F4F	/* EN29LV040(A) */
#define EON_EN29LV040		0x4F	/* Same as EN29LV040A */
#define EON_EN29LV640B		0xCB
#define EON_EN29LV640T		0xC9
#define EON_EN29LV640U		0x7E
#define EON_EN29F002T		0x7F92	/* Same as EN29F002A */
#define EON_EN29F002B		0x7F97	/* Same as EN29F002AN */
#define EON_EN29GL064HL		0x7E0C01	/* Uniform Sectors, WP protects Top OR Bottom sector */
#define EON_EN29GL064T		0x7E1001	/* Same ID as EN29GL064AT */
#define EON_EN29GL064B		0x7E1000	/* Same ID as EN29GL064AB */
#define EON_EN29GL128HL		0x7F2101	/* Uniform Sectors, WP protects Top OR Bottom sector */
#define EON_EN29GL256HL		0x7F2201	/* Uniform Sectors, WP protects Top OR Bottom sector */


#define MACRONIX_ID		0xC2	/* Macronix (MX) */
/* Mask ROMs */
#define MACRONIX_MX23L1654	0x0515
#define MACRONIX_MX23L3254	0x0516
#define MACRONIX_MX23L6454	0x0517
#define MACRONIX_MX23L12854	0x0518
/* MX25 chips are SPI, first byte of device ID is memory type,
 * second byte of device ID is log(bitsize)-9.
 * Generalplus SPI chips seem to be compatible with Macronix
 * and use the same set of IDs. */
#define MACRONIX_MX25L512	0x2010	/* Same as MX25L512E, MX25V512, MX25V512C */
#define MACRONIX_MX25L1005	0x2011	/* Same as MX25L1005C, MX25L1006E */
#define MACRONIX_MX25L2005	0x2012	/* Same as MX25L2005C, MX25L2006E */
#define MACRONIX_MX25L4005	0x2013	/* Same as MX25L4005A, MX25L4005C, MX25L4006E */
#define MACRONIX_MX25L8005	0x2014	/* Same as MX25V8005, MX25L8006E, MX25L8008E, FIXME: MX25L8073E (4k 0x20) */
#define MACRONIX_MX25L1605	0x2015	/* MX25L1605 (64k 0x20); MX25L1605A/MX25L1606E/MX25L1608E (4k 0x20, 64k 0x52); MX25L1605D/MX25L1608D/MX25L1673E (4k 0x20) */
#define MACRONIX_MX25L3205	0x2016	/* MX25L3205, MX25L3205A (64k 0x20); MX25L3205D/MX25L3208D (4k 0x20); MX25L3206E/MX25L3208E (4k 0x20, 64k 0x52); MX25L3273E (4k 0x20, 32k 0x52) */
#define MACRONIX_MX25L6405	0x2017	/* MX25L6405, MX25L6405D (64k 0x20); MX25L6406E/MX25L6408E (4k 0x20); MX25L6436E/MX25L6445E/MX25L6465E/MX25L6473E (4k 0x20, 32k 0x52) */
#define MACRONIX_MX25L12805D	0x2018	/* MX25L12805D (no 32k); MX25L12865E, MX25L12835F, MX25L12845E (32k 0x52) */
#define MACRONIX_MX25L25635F	0x2019	/* Same as MX25L25639F, but the latter seems to not support REMS */
#define MACRONIX_MX25L1635D	0x2415
#define MACRONIX_MX25L1635E	0x2515	/* MX25L1635{E} */
#define MACRONIX_MX66L51235F	0x201a	/* MX66L51235F */
#define MACRONIX_MX25U8032E	0x2534
#define MACRONIX_MX25U1635E	0x2535
#define MACRONIX_MX25U3235E	0x2536	/* Same as MX25U6435F */
#define MACRONIX_MX25U6435E	0x2537	/* Same as MX25U6435F */
#define MACRONIX_MX25U12835E	0x2538	/* Same as MX25U12835F */
#define MACRONIX_MX25U25635F	0x2539
#define MACRONIX_MX25U51245G	0x253a
#define MACRONIX_MX25L3235D	0x5E16	/* MX25L3225D/MX25L3235D/MX25L3237D */
#define MACRONIX_MX25L6495F	0x9517

#define MACRONIX_MX25R6435F	0x2817
/*
 * Programmable Micro Corp is listed in JEP106W in bank 2, so it should
 * have a 0x7F continuation code prefix.
 * Apparently PMC was renamed to "Chingis Technology Corporation" http://www.chingistek.com which is now a
 * subsidiary of ISSI. They continue to use the PMC manufacturer ID (instead of ISSI's) nevertheless, even for
 * new chips with IS* model numbers.
 */
#define PMC_ID			    0x7F	/* PMC */
#define PMC_ID_NOPREFIX	0x9D	/* PMC, missing 0x7F prefix */
#define PMC_PM25LD256C	0x2F
#define PMC_PM25LD512		0x9d20	/* Same as Pm25LD512C, but the latter has more locking options. */
#define PMC_PM25LD010		0x9d21	/* Same as Pm25LD010C, but the latter has more locking options. */
#define PMC_PM25LD020		0x9d22	/* Same as Pm25LD020C, but the latter has more locking options. */
#define PMC_PM25LQ020		0x42
#define PMC_PM25LQ040		0x43
#define PMC_PM25LQ080		0x44
#define PMC_PM25LQ016		0x45
#define PMC_PM25LQ032C		0x46
#define PMC_PM25LV512		0x7B	/* Same as Pm25LV512A */
#define PMC_PM25LV010		0x7C	/* Same as Pm25LV010A, but the former does not support RDID but RES3 only. */
#define PMC_PM25LV020		0x7D
#define PMC_PM25LV040		0x7E	/* Same as PM25LD040(C), but the latter supports more features. */
#define PMC_PM25LV080B		0x13
#define PMC_PM25LV016B		0x14

/* 
 * The Sanyo chip found so far uses SPI, first byte is manufacture code,
 * second byte is the device code,
 * third byte is a dummy byte.
 */
#define SANYO_ID		0x62	/* Sanyo */
#define SANYO_LE25FW203A	0x1600
#define SANYO_LE25FW403A	0x1100
#define SANYO_LE25FW106		0x15
#define SANYO_LE25FW406		0x07	/* RES2 */
#define SANYO_LE25FW418A	0x10	/* RES2 and some weird 1 byte RDID variant */
#define SANYO_LE25FW406A	0x1A	/* RES2, no datasheet */
#define SANYO_LE25FU406B	0x1E	/* LE25FW418A without HD_READ mode option variant */
#define SANYO_LE25FU406C	0x0613	/* Also known as LE25U40CMC apparently */
#define SANYO_LE25FW806		0x26	/* RES2 and some weird 1 byte RDID variant */
#define SANYO_LE25FW808		0x20	/* RES2 and some weird 1 byte RDID variant */



/* Spansion was previously a joint venture of AMD and Fujitsu. */
#define SPANSION_ID		0x01	/* Spansion, same ID as AMD */
/* S25 chips are SPI. The first device ID byte is memory type and
 * the second device ID byte is memory capacity. */
#define SPANSION_S25FL004A	0x0212
#define SPANSION_S25FL008A	0x0213
#define SPANSION_S25FL016A	0x0214
#define SPANSION_S25FL032A	0x0215	/* Same as S25FL032P, but the latter supports EDI and CFI */
#define SPANSION_S25FL064A	0x0216	/* Same as S25FL064P, but the latter supports EDI and CFI */
#define SPANSION_S25FL128	0x2018	/* Same ID for various S25FL127S, S25FL128P, S25FL128S and S25FL129P (including dual-die S70FL256P) variants (EDI supported) */
#define SPANSION_S25FL256	0x0219
#define SPANSION_S25FL512	0x0220
#define SPANSION_S25FL204	0x4013
#define SPANSION_S25FL208	0x4014
#define SPANSION_S25FL216	0x4015	/* Same as S25FL216K, but the latter supports OTP, 3 status regs, quad I/O, SFDP etc. */
#define SPANSION_S25FL116K	0x4015
#define SPANSION_S25FL132K	0x4016
#define SPANSION_S25FL164K	0x4017
#define SPANSION_S25FS128S_L	0x20180081  /* Large sectors. */
#define SPANSION_S25FS128S_S	0x20180181  /* Small sectors. */
#define SPANSION_S25FS256S_L	0x02190081  /* Large sectors. */
#define SPANSION_S25FS256S_S	0x02190181  /* Small sectors. */
#define SPANSION_S25FL128S_UL	0x20180080  /* Uniform Large (128kB) sectors */
#define SPANSION_S25FL128S_US	0x20180180  /* Uniform Small (64kB) sectors */
#define SPANSION_S25FL256S_UL	0x02190080  /* Uniform Large (128kB) sectors */
#define SPANSION_S25FL256S_US	0x02190180  /* Uniform Small (64kB) sectors */


/*
 * SST25 chips are SPI, first byte of device ID is memory type, second
 * byte of device ID is related to log(bitsize) at least for some chips.
 */
#define SST_ID			0xBF	/* SST */
#define SST_SST25LF020_REMS	0x43	/* REMS or RES opcode */
#define SST_SST25VF040_REMS	0x44	/* REMS or RES opcode, same as SST25LF040A */
#define SST_SST25VF512_REMS	0x48	/* REMS or RES opcode, same as SST25VF512A */
#define SST_SST25VF010_REMS	0x49	/* REMS or RES opcode, same as SST25VF010A */
#define SST_SST25VF020_REMS	0x43	/* REMS or RES opcode, same as SST25LF020A */

#define SST_SST25WF512		0x2501
#define SST_SST25WF010		0x2502
#define SST_SST25WF020		0x2503
#define SST_SST25WF040		0x2504
#define SST_SST25WF080		0x2505


/*
 * ST25P chips are SPI, first byte of device ID is memory type, second
 * byte of device ID is related to log(bitsize) at least for some chips.
 */
#define ST_ID			0x20	/* ST / SGS/Thomson / Numonyx (later acquired by Micron) */
#define ST_M25P05A		0x2010
#define ST_M25P05_RES		0x10	/* Same code as M25P10. */
#define ST_M25P10A		0x2011
#define ST_M25P10_RES		0x10	/* Same code as M25P05. */
#define ST_M25P20		0x2012
#define ST_M25P20_RES		0x11
#define ST_M25P40		0x2013
#define ST_M25P40_RES		0x12
#define ST_M25P80		0x2014
#define ST_M25P16		0x2015
#define ST_M25P32		0x2016
#define ST_M25P64		0x2017
#define ST_M25P128		0x2018
#define ST_M45PE10		0x4011
#define ST_M45PE20		0x4012
#define ST_M45PE40		0x4013
#define ST_M45PE80		0x4014
#define ST_M45PE16		0x4015
#define ST_M25PX80		0x7114
#define ST_M25PX16		0x7115
#define ST_M25PX32		0x7116
#define ST_M25PX64		0x7117
#define ST_M25PE10		0x8011
#define ST_M25PE20		0x8012
#define ST_M25PE40		0x8013
#define ST_M25PE80		0x8014
#define ST_M25PE16		0x8015

#define ST_N25Q016__1E		0xBB15	/* N25Q016, 1.8V, (uniform sectors expected) */
#define ST_N25Q032__3E		0xBA16	/* N25Q032, 3.0V, (uniform sectors expected) */
#define ST_N25Q032__1E		0xBB16	/* N25Q032, 1.8V, (uniform sectors expected) */
#define ST_N25Q064__3E		0xBA17	/* N25Q064, 3.0V, (uniform sectors expected) */
#define ST_N25Q064__1E		0xBB17	/* N25Q064, 1.8V, (uniform sectors expected) */
#define ST_N25Q128__3E		0xBA18	/* N25Q128, 3.0V, (uniform sectors expected) */
#define ST_N25Q128__1E		0xBB18	/* N25Q128, 1.8V, (uniform sectors expected) */
#define ST_N25Q256__3E		0xBA19	/* N25Q256, 3.0V, (uniform sectors expected) */
#define ST_N25Q256__1E		0xBB19	/* N25Q256, 1.8V, (uniform sectors expected) */
#define ST_N25Q512__3E		0xBA20	/* N25Q512, 3.0V, (uniform sectors expected) */
#define ST_N25Q512__1E		0xBB20	/* N25Q512, 1.8V, (uniform sectors expected) */
#define ST_N25Q00A__3E		0xBA21	/* N25Q00A, 3.0V, (uniform sectors expected) */

/*
 * W25X chips are SPI, first byte of device ID is memory type, second
 * byte of device ID is related to log(bitsize).
 */
#define WINBOND_NEX_ID		0xEF	/* Winbond (ex Nexcom) serial flashes */
#define WINBOND_NEX_W25X10	0x3011
#define WINBOND_NEX_W25X20	0x3012
#define WINBOND_NEX_W25X40	0x3013
#define WINBOND_NEX_W25X80	0x3014
#define WINBOND_NEX_W25X16	0x3015
#define WINBOND_NEX_W25X32	0x3016
#define WINBOND_NEX_W25X64	0x3017
#define WINBOND_NEX_W25Q40_V	0x4013	/* W25Q40BV; W25Q40BL (2.3-3.6V) */
#define WINBOND_NEX_W25Q80_V	0x4014	/* W25Q80BV */
#define WINBOND_NEX_W25Q16_V	0x4015	/* W25Q16CV; W25Q16DV */
#define WINBOND_NEX_W25Q32_V	0x4016	/* W25Q32BV; W25Q32FV in SPI mode (default) */
#define WINBOND_NEX_W25Q64_V	0x4017	/* W25Q64BV, W25Q64CV; W25Q64FV in SPI mode (default) */

/*
 * W25Q128 has several variants. Currently all are 3.3V except for the W25Q128FW
 * which is 1.8V. Otherwise they should behave the same...
 */
#define WINBOND_NEX_W25Q128_V	0x4018	/* W25Q128BV, W25Q128FV (SPI mode), W25Q128JV */
#define WINBOND_NEX_W25Q256_V	0x4019	/* W25Q256FV */
#define WINBOND_NEX_W25Q20_W	0x5012	/* W25Q20BW */
#define WINBOND_NEX_W25Q40_W	0x5013	/* W25Q40BW */
#define WINBOND_NEX_W25Q80_W	0x5014	/* W25Q80BW */
#define WINBOND_NEX_W25Q40EW	0x6013
#define WINBOND_NEX_W25Q16_W	0x6015	/* W25Q16DW */
#define WINBOND_NEX_W25Q32_W	0x6016	/* W25Q32DW; W25Q32FV in QPI mode */
#define WINBOND_NEX_W25Q64_W	0x6017	/* W25Q64DW; W25Q64FV in QPI mode */
#define WINBOND_NEX_W25Q128_W	0x6018	/* Same as W25Q128FV (QPI mode), W25R128FV */
#define WINBOND_NEX_W25Q128FW	0x6018	/* Same as W25Q128FV (QPI mode), W25R128FV */
#define WINBOND_NEX_W25Q128J	0x7018
#define WINBOND_NEX_W25Q256JV	0x7019



typedef unsigned long chipaddr;

struct voltage_range {
	uint16_t min, max;
};

enum chipbustype {
	BUS_NONE	= 0,
	BUS_PARALLEL	= 1 << 0,
	BUS_LPC		= 1 << 1,
	BUS_FWH		= 1 << 2,
	BUS_SPI		= 1 << 3,
	BUS_PROG	= 1 << 4,
	BUS_NONSPI	= BUS_PARALLEL | BUS_LPC | BUS_FWH,
};

	/* struct flashctx must always contain struct flashchip at the beginning. */
//struct flashctx {
//	struct flashchip *chip;

//	chipaddr virtual_memory;
//	/* Some flash devices have an additional register space. */
//	chipaddr virtual_registers;
//}_flashctx;

enum test_state {
	OK = 0,
	NT = 1,	/* Not tested */
	BAD,	/* Known to not work */
	DEP,	/* Support depends on configuration (e.g. Intel flash descriptor) */
	NA,	/* Not applicable (e.g. write support on ROM chips) */
};



//struct tested {
//		enum test_state probe;
//		enum test_state read;
//		enum test_state erase;
//		enum test_state write;
//	} ;

struct flashchip {
	const char *vendor;
	const char *name;

	enum chipbustype bustype;

	/*
	 * With 32bit manufacture_id and model_id we can cover IDs up to
	 * (including) the 4th bank of JEDEC JEP106W Standard Manufacturer's
	 * Identification code.
	 */
	uint32_t manufacture_id;
	uint32_t model_id;

	/* Total chip size in kilobytes */
	unsigned int total_size;
	/* Chip page size in bytes */
	unsigned int page_size;
	int feature_bits;

	/* Indicate how well flashrom supports different operations of this flash chip. */
	struct tested {
		enum test_state probe;
		enum test_state read;
		enum test_state erase;
		enum test_state write;
	} tested;

	/*
	 * Erase blocks and associated erase function. Any chip erase function
	 * is stored as chip-sized virtual block together with said function.
	 * The first one that fits will be chosen. There is currently no way to
	 * influence that behaviour. For testing just comment out the other
	 * elements or set the function pointer to NULL.
	 */
	struct block_eraser {
		struct eraseblock {
			unsigned int size; /* Eraseblock size in bytes */
			unsigned int count; /* Number of contiguous blocks with that size */
		} eraseblocks[NUM_ERASEREGIONS];
		/* a block_erase function should try to erase one block of size
		 * 'blocklen' at address 'blockaddr' and return 0 on success. */
		uint8_t block_erase;//int (*block_erase) (struct flashctx *flash, unsigned int blockaddr, unsigned int blocklen);
	} block_erasers[NUM_ERASEFUNCTIONS];

	//int (*printlock) (struct flashctx *flash);
	int (*unlock) (void);
	int (*write) (unsigned int start, const void *data,  unsigned int len);
	int (*read) (unsigned int start, void *data,  unsigned int len);
	int (*erase) (uint8_t cmd);
	uint8_t (*read_status) (void);
	int (*write_status) ( int status);
	struct voltage {
		uint16_t min;
		uint16_t max;
	} voltage;
	//struct wp *wp;
} ;//__attribute__((packed));

const struct flashchip *flash_id_to_entry(uint8_t mfg_id, uint32_t model_id);
unsigned int flashchips_in_base(void);


#endif /* !FLASHCHIPS_H */
