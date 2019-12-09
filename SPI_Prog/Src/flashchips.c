/*
 * This file is part of the flashrom project.
 *
 * Copyright (C) 2000 Silicon Integrated System Corporation
 * Copyright (C) 2004 Tyan Corp
 * Copyright (C) 2005-2008 coresystems GmbH <stepan@openbios.org>
 * Copyright (C) 2006-2009 Carl-Daniel Hailfinger
 * Copyright (C) 2009 Sean Nelson <audiohacked@gmail.com>
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

#include <stdlib.h>
#include <string.h>

#include "flashchips.h"
#include "chip_drv.h"
#include "spi.h"




/**
 * List of supported flash chips.
 *
 * Please keep the list sorted by vendor name and chip name, so that
 * the output of 'flashrom -L' is alphabetically sorted.
 */
const struct flashchip flashchips[] = {

	/*
	 * .vendor		= Vendor name
	 * .name		= Chip name
	 * .bustype		= Supported flash bus types (Parallel, SPI, LPC...)
	 * .manufacture_id	= Manufacturer chip ID
	 * .model_id		= Model chip ID
	 * .total_size		= Total size in (binary) kbytes
	 * .page_size		= Page or eraseblock(?) size in bytes
	 * .tested		= Test status
	 * .probe		= Probe function
	 * .probe_timing	= Probe function delay
	 * .block_erasers[]	= Array of erase layouts and erase functions
	 * {
	 *	.eraseblocks[]	= Array of { blocksize, blockcount }
	 *	.block_erase	= Block erase function
	 * }
	 * .printlock		= Chip lock status function
	 * .unlock		= Chip unlock function
	 * .write		= Chip write function
	 * .read		= Chip read function
	 * .voltage		= Voltage range in millivolt
	 */

	

//	{
//		.vendor		= "AMIC",
//		.name		= "A25L05PT",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= AMIC_ID,
//		.model_id	= AMIC_A25L05PT,
//		.total_size	= 64,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = {
//					{32 * 1024, 1},
//					{16 * 1024, 1},
//					{8 * 1024, 1},
//					{4 * 1024, 2},
//				},
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {64 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//	},

//	{
//		.vendor		= "AMIC",
//		.name		= "A25L05PU",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= AMIC_ID,
//		.model_id	= AMIC_A25L05PU,
//		.total_size	= 64,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = {
//					{4 * 1024, 2},
//					{8 * 1024, 1},
//					{16 * 1024, 1},
//					{32 * 1024, 1},
//				},
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {64 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//	},

//	{
//		.vendor		= "AMIC",
//		.name		= "A25L10PT",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= AMIC_ID,
//		.model_id	= AMIC_A25L10PT,
//		.total_size	= 128,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid4,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = {
//					{64 * 1024, 1},
//					{32 * 1024, 1},
//					{16 * 1024, 1},
//					{8 * 1024, 1},
//					{4 * 1024, 2},
//				},
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {128 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.printlock	= spi_prettyprint_status_register_amic_a25l05p,
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "AMIC",
//		.name		= "A25L10PU",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= AMIC_ID,
//		.model_id	= AMIC_A25L10PU,
//		.total_size	= 128,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid4,    //PROBE_SPI_RDID4,probe_spi_rdid4
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = {
//					{4 * 1024, 2},
//					{8 * 1024, 1},
//					{16 * 1024, 1},
//					{32 * 1024, 1},
//					{64 * 1024, 1},
//				},
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {128 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.printlock	= spi_prettyprint_status_register_amic_a25l05p,
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "AMIC",
//		.name		= "A25L20PT",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= AMIC_ID,
//		.model_id	= AMIC_A25L20PT,
//		.total_size	= 256,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid4,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = {
//					{64 * 1024, 3},
//					{32 * 1024, 1},
//					{16 * 1024, 1},
//					{8 * 1024, 1},
//					{4 * 1024, 2},
//				},
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {256 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.printlock	= spi_prettyprint_status_register_amic_a25l05p,
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "AMIC",
//		.name		= "A25L20PU",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= AMIC_ID,
//		.model_id	= AMIC_A25L20PU,
//		.total_size	= 256,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid4,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = {
//					{4 * 1024, 2},
//					{8 * 1024, 1},
//					{16 * 1024, 1},
//					{32 * 1024, 1},
//					{64 * 1024, 3},
//				},
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {256 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.printlock	= spi_prettyprint_status_register_amic_a25l05p,
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	/* The A25L40P{T,U} chips are distinguished by their
//	 * erase block layouts, but without any distinction in RDID.
//	 * This inexplicable quirk was verified by Rudolf Marek
//	 * and discussed on the flashrom mailing list on 2010-07-12.
//	 */
//	{
//		.vendor		= "AMIC",
//		.name		= "A25L40PT",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= AMIC_ID,
//		.model_id	= AMIC_A25L40PT,
//		.total_size	= 512,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_OK_PRU,
//		.probe		= probe_spi_rdid4,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = {
//					{64 * 1024, 7},
//					{32 * 1024, 1},
//					{16 * 1024, 1},
//					{8 * 1024, 1},
//					{4 * 1024, 2},
//				},
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {512 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.printlock	= spi_prettyprint_status_register_amic_a25l40p,
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "AMIC",
//		.name		= "A25L40PU",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= AMIC_ID,
//		.model_id	= AMIC_A25L40PU,
//		.total_size	= 512,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_OK_PRU,
//		.probe		= probe_spi_rdid4,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = {
//					{4 * 1024, 2},
//					{8 * 1024, 1},
//					{16 * 1024, 1},
//					{32 * 1024, 1},
//					{64 * 1024, 7},
//				},
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {512 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.printlock	= spi_prettyprint_status_register_amic_a25l40p,
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "AMIC",
//		.name		= "A25L80P",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= AMIC_ID,
//		.model_id	= AMIC_A25L80P,
//		.total_size	= 1024,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_OK_PREU,
//		.probe		= probe_spi_rdid4,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = {
//					{4 * 1024, 2},
//					{8 * 1024, 1},
//					{16 * 1024, 1},
//					{32 * 1024, 1},
//					{64 * 1024, 15},
//				},
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.printlock	= spi_prettyprint_status_register_amic_a25l40p,
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "AMIC",
//		.name		= "A25L16PT",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= AMIC_ID,
//		.model_id	= AMIC_A25L16PT,
//		.total_size	= 2048,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid4,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = {
//					{64 * 1024, 31},
//					{32 * 1024, 1},
//					{16 * 1024, 1},
//					{8 * 1024, 1},
//					{4 * 1024, 2},
//				},
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {2048 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {2048 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.printlock	= spi_prettyprint_status_register_amic_a25l40p,
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "AMIC",
//		.name		= "A25L16PU",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= AMIC_ID,
//		.model_id	= AMIC_A25L16PU,
//		.total_size	= 2048,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_OK_PRU,
//		.probe		= probe_spi_rdid4,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = {
//					{4 * 1024, 2},
//					{8 * 1024, 1},
//					{16 * 1024, 1},
//					{32 * 1024, 1},
//					{64 * 1024, 31},
//				},
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {2048 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {2048 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.printlock	= spi_prettyprint_status_register_amic_a25l40p,
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

	{
		.vendor		= "AMIC",
		.name		= "A25L512",
		.bustype	= BUS_SPI,
		.manufacture_id	= AMIC_ID_NOPREFIX,
		.model_id	= AMIC_A25L512,
		.total_size	= 64,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { { 4 * 1024, 16 } },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { { 64 * 1024, 1 } },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { { 64 * 1024, 1 } },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_amic_a25l40p,
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "AMIC",
		.name		= "A25L010",
		.bustype	= BUS_SPI,
		.manufacture_id	= AMIC_ID_NOPREFIX,
		.model_id	= AMIC_A25L010,
		.total_size	= 128,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { { 4 * 1024, 32 } },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { { 64 * 1024, 2 } },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { { 128 * 1024, 1 } },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_amic_a25l40p,
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "AMIC",
		.name		= "A25L020",
		.bustype	= BUS_SPI,
		.manufacture_id	= AMIC_ID_NOPREFIX,
		.model_id	= AMIC_A25L020,
		.total_size	= 256,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { { 4 * 1024, 64 } },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { { 64 * 1024, 4 } },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { { 256 * 1024, 1 } },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_amic_a25l40p,
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "AMIC",
		.name		= "A25L040",
		.bustype	= BUS_SPI,
		.manufacture_id	= AMIC_ID_NOPREFIX,
		.model_id	= AMIC_A25L040,
		.total_size	= 512,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { { 4 * 1024, 128 } },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { { 64 * 1024, 8 } },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { { 512 * 1024, 1 } },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_amic_a25l40p,
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "AMIC",
		.name		= "A25L080",
		.bustype	= BUS_SPI,
		.manufacture_id	= AMIC_ID_NOPREFIX,
		.model_id	= AMIC_A25L080,
		.total_size	= 1024,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { { 4 * 1024, 256 } },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { { 64 * 1024, 16 } },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { { 1024 * 1024, 1 } },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_amic_a25l40p,
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "AMIC",
		.name		= "A25L016",
		.bustype	= BUS_SPI,
		.manufacture_id	= AMIC_ID_NOPREFIX,
		.model_id	= AMIC_A25L016,
		.total_size	= 2048,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { { 4 * 1024, 512 } },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { { 64 * 1024, 32 } },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { { 2048 * 1024, 1 } },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_amic_a25l40p,
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "AMIC",
		.name		= "A25L032",
		.bustype	= BUS_SPI,
		.manufacture_id	= AMIC_ID_NOPREFIX,
		.model_id	= AMIC_A25L032,
		.total_size	= 4096,
		.page_size	= 256,
		/* OTP: 64B total; read 0x4B, 0x48; write 0x42 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { { 4 * 1024, 1024 } },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { { 64 * 1024, 64 } },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { { 64 * 1024, 64 } },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { { 4096 * 1024, 1 } },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { { 4096 * 1024, 1 } },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_amic_a25l032,
		.unlock		= NULL, /* Two status reg bytes (read with 0x35 and 0x05) */
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "AMIC",
		.name		= "A25LQ032",
		.bustype	= BUS_SPI,
		.manufacture_id	= AMIC_ID_NOPREFIX,
		.model_id	= AMIC_A25LQ032,
		.total_size	= 4096,
		.page_size	= 256,
		/* OTP: 64B total; read 0x4B, 0x48; write 0x42 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { { 4 * 1024, 1024 } },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { { 64 * 1024, 64 } },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { { 64 * 1024, 64 } },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { { 4096 * 1024, 1 } },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { { 4096 * 1024, 1 } },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_amic_a25lq032,
		.unlock		= NULL, /* Two status reg bytes (read with 0x35 and 0x05) */
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},


{
		.vendor		= "ATMEL",
		.name		= "AT25SL128A",
		.bustype	= BUS_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= ATMEL_AT25SL128A,
		.total_size	= 16384,
		.page_size	= 256,
		/* supports SFDP */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP | FEATURE_QPI,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 4096} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 512} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {16 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {16 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		  = spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {1700, 2000},
	},

//	{
//		.vendor		= "Atmel",
//		.name		= "AT25DF021",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ATMEL_ID,
//		.model_id	= ATMEL_AT25DF021,
//		.total_size	= 256,
//		.page_size	= 256,
//		/* OTP: 128B total, 64B pre-programmed; read 0x77; write 0x9B */
//		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 64} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 8} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 4} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {256 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {256 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.printlock	= spi_prettyprint_status_register_at25df,
//		.unlock		= spi_disable_blockprotect_at25df,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600}, /* 2.3-3.6V & 2.7-3.6V models available */
//	},

//	{
//		.vendor		= "Atmel",
//		.name		= "AT25DF041A",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ATMEL_ID,
//		.model_id	= ATMEL_AT25DF041A,
//		.total_size	= 512,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_WRSR_WREN,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 16} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 8} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {512 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {512 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.printlock	= spi_prettyprint_status_register_at25df,
//		.unlock		= spi_disable_blockprotect_at25df,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600}, /* 2.3-3.6V & 2.7-3.6V models available */
//	},

//	{
//		.vendor		= "Atmel",
//		.name		= "AT25DF081",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ATMEL_ID,
//		.model_id	= ATMEL_AT25DF081,
//		.total_size	= 1024,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_WRSR_WREN,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 256} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 32} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 16} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.printlock	= spi_prettyprint_status_register_at25df,
//		.unlock		= spi_disable_blockprotect_at25df,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {1600, 2000}, /* Datasheet says range is 1.65-1.95 V */
//	},

//	{
//		.vendor		= "Atmel",
//		.name		= "AT25DF081A",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ATMEL_ID,
//		.model_id	= ATMEL_AT25DF081A,
//		.total_size	= 1024,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_WRSR_WREN,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 256} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 32} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 16} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.printlock	= spi_prettyprint_status_register_at25df_sec,
//		.unlock		= spi_disable_blockprotect_at25df_sec,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "Atmel",
//		.name		= "AT25DF161",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ATMEL_ID,
//		.model_id	= ATMEL_AT25DF161,
//		.total_size	= 2048,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_WRSR_WREN,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 512} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 64} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 32} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {2 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {2 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.printlock	= spi_prettyprint_status_register_at25df_sec,
//		.unlock		= spi_disable_blockprotect_at25df_sec,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "Atmel",
//		.name		= "AT25DF321",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ATMEL_ID,
//		.model_id	= ATMEL_AT25DF321,
//		.total_size	= 4096,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_WRSR_WREN,
//		.tested		= TEST_OK_PREU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 1024} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 64} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {4 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {4 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.printlock	= spi_prettyprint_status_register_at25df,
//		.unlock		= spi_disable_blockprotect_at25df,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "Atmel",
//		.name		= "AT25DF321A",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ATMEL_ID,
//		.model_id	= ATMEL_AT25DF321A,
//		.total_size	= 4096,
//		.page_size	= 256,
//		/* OTP: 128B total, 64B pre-programmed; read 0x77; write 0x9B */
//		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
//		.tested		= TEST_OK_PROBE,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 1024} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 64} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {4 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {4 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.printlock	= spi_prettyprint_status_register_at25df_sec,
//		.unlock		= spi_disable_blockprotect_at25df_sec,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "Atmel",
//		.name		= "AT25DF641(A)",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ATMEL_ID,
//		.model_id	= ATMEL_AT25DF641,
//		.total_size	= 8192,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_WRSR_WREN,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 2048} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 256} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {8 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {8 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.printlock	= spi_prettyprint_status_register_at25df_sec,
//		.unlock		= spi_disable_blockprotect_at25df_sec,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "Atmel",
//		.name		= "AT25DQ161",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ATMEL_ID,
//		.model_id	= ATMEL_AT25DQ161,
//		.total_size	= 2048,
//		.page_size	= 256,
//		/* OTP: 128B total, 64B pre-programmed; read 0x77; write 0x9B */
//		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 512} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 64} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 32} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {2 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {2 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.printlock	= spi_prettyprint_status_register_at25df_sec,
//		.unlock		= spi_disable_blockprotect_at25df_sec,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//{
//		.vendor		= "Atmel",
//		.name		= "AT25F512",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ATMEL_ID,
//		.model_id	= ATMEL_AT25F512,
//		.total_size	= 64,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_WRSR_WREN,
//		.tested		= TEST_OK_PREW,
////		.probe		= probe_spi_at25f,
////		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {32 * 1024, 2} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_62,
//			}
//		},
////		.printlock	= spi_prettyprint_status_register_at25f,
////		.unlock		= spi_disable_blockprotect_at25f,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

	{
		.vendor		= "Atmel",
		.name		= "AT25F512A",
		.bustype	= BUS_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= ATMEL_AT25F512A,
		.total_size	= 64,
		.page_size	= 128,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_at25f,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {32 * 1024, 2} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_62,
			}
		},
//		.printlock	= spi_prettyprint_status_register_at25f512a,
		/* FIXME: It is not correct to use this one, because the BP1 bit is N/A. */
		.unlock		= spi_disable_blockprotect_at25f512a,
		.write		= spi_chip_write_256,
		.read		  = spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Atmel",
		.name		= "AT25F512B",
		.bustype	= BUS_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= ATMEL_AT25F512B,
		.total_size	= 64,
		.page_size	= 256,
		/* OTP: 128B total, 64B pre-programmed; read 0x77; write 0x9B */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 2} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {32 * 1024, 2} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_62,
			}
		},
//		.printlock	= spi_prettyprint_status_register_at25f512b,
		.unlock		= spi_disable_blockprotect_at25f512b,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},
	
	
		{
		.vendor		= "Atmel",
		/* The A suffix indicates 33MHz instead of 20MHz clock rate.
		 * All other properties seem to be the same.*/
		.name		= "AT25F1024(A)",
		.bustype	= BUS_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= ATMEL_AT25F1024,
		.total_size	= 128,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_at25f,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {32 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_62,
			}
		},
//		.printlock	= spi_prettyprint_status_register_at25f,
		.unlock		= spi_disable_blockprotect_at25f,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Atmel",
		.name		= "AT25F2048",
		.bustype	= BUS_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= ATMEL_AT25F2048,
		.total_size	= 256,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_at25f,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_62,
			}
		},
//		.printlock	= spi_prettyprint_status_register_at25f,
		.unlock		= spi_disable_blockprotect_at25f,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Atmel",
		.name		= "AT25F4096",
		.bustype	= BUS_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= ATMEL_AT25F4096,
		.total_size	= 512,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_at25f,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_62,
			}
		},
//		.printlock	= spi_prettyprint_status_register_at25f4096,
		/* "Bits 5-6 are 0s when device is not in an internal write cycle." Better leave them alone: */
		.unlock		= spi_disable_blockprotect_bp2_srwd,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

{
		.vendor		= "Atmel",
		.name		= "AT25FS010",
		.bustype	= BUS_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= ATMEL_AT25FS010,
		.total_size	= 128,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {4 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_D7,
			}, {
				.eraseblocks = { {32 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {32 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_at25fs010,
		.unlock		= spi_disable_blockprotect_at25fs010,
		.write		= spi_chip_write_256,
		.read		  = spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Atmel",
		.name		= "AT25FS040",
		.bustype	= BUS_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= ATMEL_AT25FS040,
		.total_size	= 512,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_at25fs040,
		.unlock		= spi_disable_blockprotect_at25fs040,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Atmel",
		.name		= "AT25SF041",
		.bustype	= BUS_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= ATMEL_AT25SF041,
		.total_size	= 512,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain,
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2500, 3600},
	},

	{
		.vendor		= "Atmel",
		.name		= "AT25SF081",
		.bustype	= BUS_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= ATMEL_AT25SF081,
		.total_size	= 1024,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain,
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2300, 3600},
	},

	{
		.vendor		= "Atmel",
		.name		= "AT25SF161",
		.bustype	= BUS_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= ATMEL_AT25SF161,
		.total_size	= 2048,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 512} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {2048 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {2048 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain,
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2500, 3600},
	},

	{
		.vendor		= "ATMEL",
		.name		= "AT25SL128A",
		.bustype	= BUS_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= ATMEL_AT25SL128A,
		.total_size	= 16384,
		.page_size	= 256,
		/* supports SFDP */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP | FEATURE_QPI,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 4096} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 512} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {16 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {16 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {1700, 2000},
	},

	{
		.vendor		= "Atmel",
		.name		= "AT26DF041",
		.bustype	= BUS_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= ATMEL_AT26DF041,
		.total_size	= 512,
		.page_size	= 256,
		/* does not support EWSR nor WREN and has no writable status register bits whatsoever */
		.tested		= TEST_OK_PREW,
		//.probe		= probe_spi_rdid,
		//.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {			
				.eraseblocks = { {256, 2048} },
				.block_erase = SPI_BLOCK_ERASE_81,   //spi_block_erase_81
			}, {
				.eraseblocks = { {2 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_50,
			}
		},
		//.printlock	= spi_prettyprint_status_register_plain,
		/* Supports also an incompatible page write (of exactly 256 B) and an auto-erasing write. */
		.write	= spi_chip_write_1,//spi_chip_write_256_11,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase  = spi_erase_bulk_sec,
		.voltage	= {2700, 3600}, /* 3.0-3.6V for higher speed, 2.7-3.6V normal */
	},

	{
		.vendor		= "Atmel",
		.name		= "AT26DF081A",
		.bustype	= BUS_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= ATMEL_AT26DF081A,
		.total_size	= 1024,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
		//.probe		= probe_spi_rdid,
		//.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		//.printlock	= spi_prettyprint_status_register_at26df081a,
		.unlock		= spi_disable_blockprotect_at2x_global_unprotect,
		.write		= spi_chip_write_256,//spi_chip_write_256,
		.read		  = spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

{
		.vendor		= "Atmel",
		.name		= "AT26DF161",
		.bustype	= BUS_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= ATMEL_AT26DF161,
		.total_size	= 2048,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 512} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_at25df,
		.unlock		= spi_disable_blockprotect_at2x_global_unprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Atmel",
		.name		= "AT26DF161A",
		.bustype	= BUS_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= ATMEL_AT26DF161A,
		.total_size	= 2048,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 512} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_at26df081a,
		.unlock		= spi_disable_blockprotect_at2x_global_unprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	/*The AT26DF321 has the same ID as the AT25DF321. */
	/*{
		.vendor		= "Atmel",
		.name		= "AT26DF321",
		.bustype	= BUS_SPI,
		.manufacture_id	= ATMEL_ID,
		.model_id	= ATMEL_AT26DF321,
		.total_size	= 4096,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
		.probe		= probe_spi_rdid,
		.probe_timing	= TIMING_ZERO,
		.printlock	= spi_prettyprint_status_register_at26df081a,
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
	  },*/

//	{
//		.vendor		= "Atmel",
//		.name		= "AT26F004",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ATMEL_ID,
//		.model_id	= ATMEL_AT26F004,
//		.total_size	= 512,
//		.page_size	= 256,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 16} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 8} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {512 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {512 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.write		= NULL /* Incompatible Page write */,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	
//	{
//		.vendor		= "Atmel",
//		.name		= "AT45CS1282",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ATMEL_ID,
//		.model_id	= ATMEL_AT45CS1282,
//		.total_size	= 16896 /* No power of two sizes */,
//		.page_size	= 1056 /* No power of two sizes */,
//		.tested		= { .probe = NT, .read = BAD, .erase = NT, .write = NT, .uread = NT },
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.write		= NULL /* Incompatible Page write */,
//		.read		= NULL /* Incompatible read */,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "Atmel",
//		.name		= "AT45DB011D",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ATMEL_ID,
//		.model_id	= ATMEL_AT45DB011D,
//		.total_size	= 128 /* Size can only be determined from status register */,
//		.page_size	= 256 /* Size can only be determined from status register */,
//		.tested		= { .probe = NT, .read = BAD, .erase = NT, .write = NT, .uread = NT },
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.write		= NULL,
//		.read		= NULL,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "Atmel",
//		.name		= "AT45DB021D",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ATMEL_ID,
//		.model_id	= ATMEL_AT45DB021D,
//		.total_size	= 256 /* Size can only be determined from status register */,
//		.page_size	= 256 /* Size can only be determined from status register */,
//		.tested		= { .probe = NT, .read = BAD, .erase = NT, .write = NT, .uread = NT },
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.write		= NULL,
//		.read		= NULL,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "Atmel",
//		.name		= "AT45DB041D",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ATMEL_ID,
//		.model_id	= ATMEL_AT45DB041D,
//		.total_size	= 512 /* Size can only be determined from status register */,
//		.page_size	= 256 /* Size can only be determined from status register */,
//		.tested		= { .probe = NT, .read = BAD, .erase = NT, .write = NT, .uread = NT },
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.write		= NULL,
//		.read		= NULL,
//		.voltage	= {2500, 3600}, /* 2.5-3.6V & 2.7-3.6V models available */
//	},

//	{
//		.vendor		= "Atmel",
//		.name		= "AT45DB081D",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ATMEL_ID,
//		.model_id	= ATMEL_AT45DB081D,
//		.total_size	= 1024 /* Size can only be determined from status register */,
//		.page_size	= 256 /* Size can only be determined from status register */,
//		.tested		= { .probe = NT, .read = BAD, .erase = NT, .write = NT, .uread = NT },
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.write		= NULL,
//		.read		= NULL,
//		.voltage	= {2700, 3600}, /* 2.5-3.6V & 2.7-3.6V models available */
//	},

//{
//		.vendor		= "Atmel",
//		.name		= "AT45DB161D",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ATMEL_ID,
//		.model_id	= ATMEL_AT45DB161D,
//		.total_size	= 2048 /* or 2112, determined from status register */,
//		.page_size	= 512 /* or 528, determined from status register */,
//		/* does not support EWSR nor WREN and has no writable status register bits whatsoever */
//		/* OTP: 128B total, 64B pre-programmed; read 0x77; write 0x9B */
//		.feature_bits	= FEATURE_OTP,
//		.tested		= TEST_OK_PREW,
////		.probe		= probe_spi_at45db,
////		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {512, 4096} },
//				.block_erase = spi_erase_at45db_page,
//			}, {
//				.eraseblocks = { {8 * 512, 4096/8} },
//				.block_erase = spi_erase_at45db_block,
//			}, {
//				.eraseblocks = {
//					{8 * 512, 1},
//					{248 * 512, 1},
//					{256 * 512, 15},
//				},
//				.block_erase = spi_erase_at45db_sector
//			}, {
//				.eraseblocks = { {2048 * 1024, 1} },
//				.block_erase = spi_erase_at45db_chip,
//			}
//		},
//		.unlock		= spi_disable_blockprotect_at45db, /* Impossible if locked down or #WP is low */
//		//.printlock	= spi_prettyprint_status_register_at45db,
//		/* granularity will be set by the probing function. */
//		.write		= spi_write_at45db,
//		.read		= spi_read_at45db, /* Fast read (0x0B) supported */
//		.voltage	= {2700, 3600}, /* 2.5-3.6V & 2.7-3.6V models available */
//	},

//	{
//		.vendor		= "Atmel",
//		.name		= "AT45DB321C",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ATMEL_ID,
//		.model_id	= ATMEL_AT45DB321C,
//		.total_size	= 4224 /* No power of two sizes */,
//		.page_size	= 528 /* No power of two sizes */,
//		.tested		= { .probe = NT, .read = BAD, .erase = NT, .write = NT, .uread = NT },
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.write		= NULL,
//		.read		= NULL /* Incompatible read */,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "Atmel",
//		.name		= "AT45DB321D",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ATMEL_ID,
//		.model_id	= ATMEL_AT45DB321D,
//		.total_size	= 4096 /* Size can only be determined from status register */,
//		.page_size	= 512 /* Size can only be determined from status register */,
//		/* OTP: 128B total, 64B pre-programmed; read 0x77; write 0x9B */
//		.feature_bits	= FEATURE_OTP,
//		.tested		= { .probe = NT, .read = BAD, .erase = NT, .write = NT, .uread = NT },
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.write		= NULL,
//		.read		= NULL,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "Atmel",
//		.name		= "AT45DB642D",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ATMEL_ID,
//		.model_id	= ATMEL_AT45DB642D,
//		.total_size	= 8192 /* Size can only be determined from status register */,
//		.page_size	= 1024 /* Size can only be determined from status register */,
//		.tested		= { .probe = NT, .read = BAD, .erase = NT, .write = NT, .uread = NT },
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.write		= NULL,
//		.read		= NULL,
//		.voltage	= {2700, 3600},
//	},

//	

//	{
//		.vendor		= "EMST",
//		.name		= "F25L008A",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ESMT_ID,
//		.model_id	= ESMT_F25L008A,
//		.total_size	= 1024,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 256} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {64 * 1024, 16} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_1,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

{
		.vendor		= "Eon",
		.name		= "EN25B05",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B05,
		.total_size	= 64,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{4 * 1024, 2},
					{8 * 1024, 1},
					{16 * 1024, 1},
					{32 * 1024, 1},
				},
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

{
		.vendor		= "Eon",
		.name		= "EN25B05",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B05,
		.total_size	= 64,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{4 * 1024, 2},
					{8 * 1024, 1},
					{16 * 1024, 1},
					{32 * 1024, 1},
				},
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B05T",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B05,
		.total_size	= 64,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{32 * 1024, 1},
					{16 * 1024, 1},
					{8 * 1024, 1},
					{4 * 1024, 2},
				},
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25P05",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B05,
		.total_size	= 64,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{32 * 1024, 2} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B10",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B10,
		.total_size	= 128,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{4 * 1024, 2},
					{8 * 1024, 1},
					{16 * 1024, 1},
					{32 * 1024, 3},
				},
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B10T",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B10,
		.total_size	= 128,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{32 * 1024, 3},
					{16 * 1024, 1},
					{8 * 1024, 1},
					{4 * 1024, 2},
				},
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25P10",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B10,
		.total_size	= 128,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {32 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B20",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B20,
		.total_size	= 256,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{4 * 1024, 2},
					{8 * 1024, 1},
					{16 * 1024, 1},
					{32 * 1024, 1},
					{64 * 1024, 3}
				},
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B20T",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B20,
		.total_size	= 256,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{64 * 1024, 3},
					{32 * 1024, 1},
					{16 * 1024, 1},
					{8 * 1024, 1},
					{4 * 1024, 2},
				},
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25P20",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B20,
		.total_size	= 256,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B40",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B40,
		.total_size	= 512,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{4 * 1024, 2},
					{8 * 1024, 1},
					{16 * 1024, 1},
					{32 * 1024, 1},
					{64 * 1024, 7}
				},
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B40T",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B40,
		.total_size	= 512,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{64 * 1024, 7},
					{32 * 1024, 1},
					{16 * 1024, 1},
					{8 * 1024, 1},
					{4 * 1024, 2},
				},
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25P40",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B40,
		.total_size	= 512,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B80",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B80,
		.total_size	= 1024,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{4 * 1024, 2},
					{8 * 1024, 1},
					{16 * 1024, 1},
					{32 * 1024, 1},
					{64 * 1024, 15}
				},
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B80T",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B80,
		.total_size	= 1024,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{64 * 1024, 15},
					{32 * 1024, 1},
					{16 * 1024, 1},
					{8 * 1024, 1},
					{4 * 1024, 2},
				},
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25P80",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B80,
		.total_size	= 1024,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B16",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B16,
		.total_size	= 2048,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{4 * 1024, 2},
					{8 * 1024, 1},
					{16 * 1024, 1},
					{32 * 1024, 1},
					{64 * 1024, 31},
				},
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B16T",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B16,
		.total_size	= 2048,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{64 * 1024, 31},
					{32 * 1024, 1},
					{16 * 1024, 1},
					{8 * 1024, 1},
					{4 * 1024, 2},
				},
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25P16",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B16,
		.total_size	= 2048,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B32",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B32,
		.total_size	= 4096,
		.page_size	= 256,
		/* OTP: 512B total; enter 0x3A */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{4 * 1024, 2},
					{8 * 1024, 1},
					{16 * 1024, 1},
					{32 * 1024, 1},
					{64 * 1024, 63},
				},
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B32T",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B32,
		.total_size	= 4096,
		.page_size	= 256,
		/* OTP: 512B total; enter 0x3A */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{64 * 1024, 63},
					{32 * 1024, 1},
					{16 * 1024, 1},
					{8 * 1024, 1},
					{4 * 1024, 2},
				},
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25P32", /* Uniform version of EN25B32 */
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B32,
		.total_size	= 4096,
		.page_size	= 256,
		/* OTP: 512B total; enter 0x3A */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B64",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B64,
		.total_size	= 8192,
		.page_size	= 256,
		/* OTP: 512B total; enter 0x3A */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{4 * 1024, 2},
					{8 * 1024, 1},
					{16 * 1024, 1},
					{32 * 1024, 1},
					{64 * 1024, 127},
				},
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25B64T",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B64,
		.total_size	= 8192,
		.page_size	= 256,
		/* OTP: 512B total; enter 0x3A */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{64 * 1024, 127},
					{32 * 1024, 1},
					{16 * 1024, 1},
					{8 * 1024, 1},
					{4 * 1024, 2},
				},
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25P64",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25B64,
		.total_size	= 8192,
		.page_size	= 256,
		/* OTP: 512B total; enter 0x3A */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25F05",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25F05,
		.total_size	= 64,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 2} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {32 * 1024, 2} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		  = spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25F10",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25F10,
		.total_size	= 128,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {32 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
	//	.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25F20",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25F20,
		.total_size	= 256,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {64 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25F40",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25F40,
		.total_size	= 512,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PROBE,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			},
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		  = spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
		//.wp		= &wp_w25,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25F80",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25F80,
		.total_size	= 1024,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		  = spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25F16",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25F16,
		.total_size	= 2048,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 512} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25F32",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25F32,
		.total_size	= 4096,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 1024} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
	},
	
//	{  //analog EN25Q32(A)(B)
//		.vendor		= "cFeon",   
//		.name		= "Q32B104",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= EON_ID_NOPREFIX,
//		.model_id	= EON_EN25Q32,
//		.total_size	= 4096,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_WRSR_WREN,
////		.tested		= TEST_UNTESTED,
////		.probe		= probe_spi_rdid,
////		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 1024} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {64 * 1024, 64} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {4 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {4 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.erase    = spi_erase_bulk,
//	},

	{
		.vendor		= "Eon",
		.name		= "EN25Q40",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25Q40,
		.total_size	= 512,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		//.wp		= &wp_w25,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25Q80(A)",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25Q80,
		.total_size	= 1024,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		  = spi_chip_read,
		.erase    = spi_erase_bulk,
		//.wp		= &wp_w25,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25Q32(A)(B)",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25Q32,
		.total_size	= 4096,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 1024} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		  = spi_chip_read,
		.voltage	= {2700, 3600},
		.erase    = spi_erase_bulk,
		//.wp		= &wp_w25,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25Q64",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25Q64,
		.total_size	= 8192,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 2048} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		  = spi_chip_read,
		.erase    = spi_erase_bulk,
		//.wp		= &wp_w25,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25Q128",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25Q128,
		.total_size	= 16384,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 4096} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {16 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {16 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		//.wp		= &wp_w25,
	},

	{
		.vendor		= "Eon",
		.name		= "EN25Q40",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25Q40,
		.total_size	= 512,
		.page_size	= 256,
		/* OTP: 256B total; enter 0x3A */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage        = {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25Q80(A)",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25Q80,
		.total_size	= 1024,
		.page_size	= 256,
		/* OTP: 256B total; enter 0x3A */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage        = {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25Q32(A/B)",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25Q32,
		.total_size	= 4096,
		.page_size	= 256,
		/* OTP: 512B total; enter 0x3A */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 1024} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage        = {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25Q64",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25Q64,
		.total_size	= 8192,
		.page_size	= 256,
		/* OTP: 512B total; enter 0x3A */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 2048} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage        = {2700, 3600},
	},

	{
		.vendor		= "Eon",
		.name		= "EN25Q128",
		.bustype	= BUS_SPI,
		.manufacture_id	= EON_ID_NOPREFIX,
		.model_id	= EON_EN25Q128,
		.total_size	= 16384,
		.page_size	= 256,
		/* OTP: 512B total; enter 0x3A */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 4096} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {16 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {16 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
	},

//	{
//		.vendor		= "Eon",
//		.name		= "EN25QH16",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= EON_ID_NOPREFIX,
//		.model_id	= EON_EN25QH16,
//		.total_size	= 2048,
//		.page_size	= 256,
//		/* supports SFDP */
//		/* OTP: 512B total; enter 0x3A */
//		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 512} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {64 * 1024, 32} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {1024 * 2048, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {1024 * 2048, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage        = {2700, 3600},
//	},
//	{
//		.vendor		= "Eon",
//		.name		= "EN25S64",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= EON_ID_NOPREFIX,
//		.model_id	= EON_EN25S64,
//		.total_size	= 8192,
//		.page_size	= 256,
//		/* FIXME: add FEATURE_QPI removed */
//		/* OTP: 512B total; enter 0x3A */
//		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	= {
//			{
//				.eraseblocks = { {4 * 1024, 2048} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {64 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {8192 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {8192 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {1650, 1950},
//		.wp		= &wp_w25,
//	},

//	
//	{
//		.vendor		= "GigaDevice",
//		.name		= "GD25Q20",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= GIGADEVICE_ID,
//		.model_id	= GIGADEVICE_GD25Q20,
//		.total_size	= 256,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_WRSR_WREN,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 64} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 8} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 4} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {256 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {256 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage        = {2700, 3600},
//	},

//	{
//		.vendor		= "GigaDevice",
//		.name		= "GD25Q40",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= GIGADEVICE_ID,
//		.model_id	= GIGADEVICE_GD25Q40,
//		.total_size	= 512,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_WRSR_WREN,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 16} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 8} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {512 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {512 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage        = {2700, 3600},
//	},

//	{
//		.vendor		= "GigaDevice",
//		.name		= "GD25LQ40",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= GIGADEVICE_ID,
//		.model_id	= GIGADEVICE_GD25LQ40,
//		.total_size	= 512,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_WRSR_WREN,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 16} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 8} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {512 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {512 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage        = {1650, 1950},
//	},

//	{
//		.vendor		= "GigaDevice",
//		.name		= "GD25Q80",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= GIGADEVICE_ID,
//		.model_id	= GIGADEVICE_GD25Q80,
//		.total_size	= 1024,
//		.page_size	= 256,
//		/* OTP: 1024B total, 256B reserved; read 0x48; write 0x42 */
//		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 256} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 32} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 16} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "GigaDevice",
//		.name		= "GD25Q16",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= GIGADEVICE_ID,
//		.model_id	= GIGADEVICE_GD25Q16,
//		.total_size	= 2048,
//		.page_size	= 256,
//		/* OTP: 1024B total, 256B reserved; read 0x48; write 0x42 */
//		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 512} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 64} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 32} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {2 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {2 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "GigaDevice",
//		.name		= "GD25Q32",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= GIGADEVICE_ID,
//		.model_id	= GIGADEVICE_GD25Q32,
//		.total_size	= 4096,
//		.page_size	= 256,
//		/* OTP: 1024B total, 256B reserved; read 0x48; write 0x42 */
//		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 1024} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 64} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {4 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {4 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.wp		= &wp_generic,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "GigaDevice",
//		.name		= "GD25Q64",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= GIGADEVICE_ID,
//		.model_id	= GIGADEVICE_GD25Q64,
//		.total_size	= 8192,
//		.page_size	= 256,
//		/* OTP: 1024B total, 256B reserved; read 0x48; write 0x42 */
//		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 2048} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 256} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {8 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {8 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.wp		= &wp_w25,
//	},

//	{
//		/*
//		 * TODO: There is a GD25Q128B without QPI support which can
//		 * be differentiated using SFDP, but for now we only care
//		 * about the GD25Q128C.
//		 */
//		.vendor		= "GigaDevice",
//		.name		= "GD25Q127C/GD25Q128C",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= GIGADEVICE_ID,
//		.model_id	= GIGADEVICE_GD25Q128,
//		.total_size	= 16384,
//		.page_size	= 256,
//		/* OTP: 1024B total, 256B reserved; read 0x48; write 0x42 */
//		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 4096} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 512} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 256} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {16 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {16 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.wp		= &wp_w25,
//	},

//	{
//		.vendor		= "GigaDevice",
//		.name		= "GD25Q256D",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= GIGADEVICE_ID,
//		.model_id	= GIGADEVICE_GD25Q256D,
//		.total_size	= 32768,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP | FEATURE_4BA_SUPPORT,
//		.four_bytes_addr_funcs =
//		{
//			.set_4ba = spi_enter_4ba_b7_we, /* enter 4-bytes addressing mode by CMD B7 + WREN */
//			.read_nbyte = spi_nbyte_read_4ba_direct, /* read directly from any mode, no need to enter 4ba */
//			.program_byte = spi_byte_program_4ba, /* write from 4-bytes addressing mode */
//			.program_nbyte = spi_nbyte_program_4ba /* write from 4-bytes addressing mode */
//		},
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 8192} },
//				.block_erase = SPI_BLOCK_ERASE_20_4ba, /* erases 4k from 4-bytes addressing mode */
//			}, {
//				.eraseblocks = { {32 * 1024, 1024} },
//				.block_erase = SPI_BLOCK_ERASE_52_4ba, /* erases 32k from 4-bytes addressing mode */
//			}, {
//				.eraseblocks = { {64 * 1024, 512} },
//				.block_erase = SPI_BLOCK_ERASE_D8_4ba, /* erases 64k from 4-bytes addressing mode */
//			}, {
//				.eraseblocks = { {32 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {32 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//		.wp		= &wp_w25q_large,
//	},

//	

//	{
//		.vendor		= "GigaDevice",
//		.name		= "GD25LQ32",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= GIGADEVICE_ID,
//		.model_id	= GIGADEVICE_GD25LQ32,
//		.total_size	= 4096,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_WRSR_WREN,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 1024} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 64} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {4 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {4 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {1700, 1950},
//		.wp		= &wp_w25,
//	},

//	{
//			.vendor		= "GigaDevice",
//			.name		= "GD25LQ64",
//			.bustype	= BUS_SPI,
//			.manufacture_id	= GIGADEVICE_ID,
//			.model_id	= GIGADEVICE_GD25LQ64,
//			.total_size	= 8192,
//			.page_size	= 256,
//			/* OTP: 1024B total, 256B reserved; read 0x48; write 0x42 */
//			.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
//			.tested		= TEST_OK_PREWU,
//			.probe		= probe_spi_rdid,
//			.probe_timing	= TIMING_ZERO,
//			.block_erasers	=
//			{
//				{
//					.eraseblocks = { {4 * 1024, 2048} },
//					.block_erase = SPI_BLOCK_ERASE_20,
//				}, {
//					.eraseblocks = { {32 * 1024, 256} },
//					.block_erase = SPI_BLOCK_ERASE_52,
//				}, {
//					.eraseblocks = { {64 * 1024, 128} },
//					.block_erase = SPI_BLOCK_ERASE_D8,
//				}, {
//					.eraseblocks = { {8 * 1024 * 1024, 1} },
//					.block_erase = SPI_BLOCK_ERASE_60,
//				}, {
//					.eraseblocks = { {8 * 1024 * 1024, 1} },
//					.block_erase = SPI_BLOCK_ERASE_C7,
//				}
//			},
//			.unlock		= spi_disable_blockprotect,
//			.write		= spi_chip_write_256,
//			.read		= spi_chip_read,
//			.wp		= &wp_w25,
//		},

//		{
//			.vendor		= "GigaDevice",
//			.name		= "GD25LQ128C/GD25LQ128D",
//			.bustype	= BUS_SPI,
//			.manufacture_id	= GIGADEVICE_ID,
//			.model_id	= GIGADEVICE_GD25LQ128CD,
//			.total_size	= 16384,
//			.page_size	= 256,
//			.feature_bits	= FEATURE_WRSR_WREN,
//			.tested		= TEST_OK_PREWU,
//			.probe		= probe_spi_rdid,
//			.probe_timing	= TIMING_ZERO,
//			.block_erasers	=
//			{
//				{
//					.eraseblocks = { {4 * 1024, 4096} },
//					.block_erase = SPI_BLOCK_ERASE_20,
//				}, {
//					.eraseblocks = { {32 * 1024, 512} },
//					.block_erase = SPI_BLOCK_ERASE_52,
//				}, {
//					.eraseblocks = { {64 * 1024, 256} },
//					.block_erase = SPI_BLOCK_ERASE_D8,
//				}, {
//					.eraseblocks = { {16 * 1024 * 1024, 1} },
//					.block_erase = SPI_BLOCK_ERASE_60,
//				}, {
//					.eraseblocks = { {16 * 1024 * 1024, 1} },
//					.block_erase = SPI_BLOCK_ERASE_C7,
//				}
//			},
//			.unlock		= spi_disable_blockprotect,
//			.write		= spi_chip_write_256,
//			.read		= spi_chip_read,
//			.wp		= &wp_generic,
//		},

{
		.vendor		= "Macronix",
		.name		= "MX25L25645G",
		.bustype	= BUS_SPI,
		.manufacture_id	= MACRONIX_ID,
		.model_id	= MACRONIX_MX25L25645G,  //==MACRONIX_MX25L25635F
		.total_size	= 32768,
		.page_size	= 256,
		/* OTP: 512B total; enter 0xB1, exit 0xC1 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP | FEATURE_4BA,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 8192} },
				.block_erase = SPI_BLOCK_ERASE_21,
			}, {
				.eraseblocks = { {4 * 1024, 8192} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 1024} },
				.block_erase = SPI_BLOCK_ERASE_5C,
			}, {
				.eraseblocks = { {32 * 1024, 1024} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 512} },
				.block_erase = SPI_BLOCK_ERASE_DC,
			}, {
				.eraseblocks = { {64 * 1024, 512} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {32 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {32 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		/* TODO: security register and SBLK/SBULK; MX25L12835F: configuration register */
//		.printlock	= spi_prettyprint_status_register_bp3_srwd, /* bit6 is quad enable */
		.unlock		= spi_disable_blockprotect_bp3_srwd,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

{
		.vendor		= "Macronix",
		.name		= "MX23L1654",
		.bustype	= BUS_SPI,
		.manufacture_id	= MACRONIX_ID,
		.model_id	= MACRONIX_MX23L1654,
		.total_size	= 2048,
		.page_size	= 256,
		.tested		= {.probe = NT, .read = NT, .erase = NA, .write = NA},
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.write		= NULL, /* MX23L1654 is a mask ROM, so it is read-only */
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.voltage	= {3000, 3600},
	},

	{
		.vendor		= "Macronix",
		.name		= "MX23L3254",
		.bustype	= BUS_SPI,
		.manufacture_id	= MACRONIX_ID,
		.model_id	= MACRONIX_MX23L3254,
		.total_size	= 4096,
		.page_size	= 256,
		.tested		= {.probe = OK, .read = OK, .erase = NA, .write = NA},
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.write		= NULL, /* MX23L3254 is a mask ROM, so it is read-only */
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.voltage	= {3000, 3600},
	},

	{
		.vendor		= "Macronix",
		.name		= "MX23L6454",
		.bustype	= BUS_SPI,
		.manufacture_id	= MACRONIX_ID,
		.model_id	= MACRONIX_MX23L6454,
		.total_size	= 8192,
		.page_size	= 256,
		.tested		= {.probe = OK, .read = OK, .erase = NA, .write = NA},
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.write		= NULL, /* MX23L6454 is a mask ROM, so it is read-only */
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.voltage	= {3000, 3600},
	},

	{
		.vendor		= "Macronix",
		.name		= "MX23L12854",
		.bustype	= BUS_SPI,
		.manufacture_id	= MACRONIX_ID,
		.model_id	= MACRONIX_MX23L12854,
		.total_size	= 16384,
		.page_size	= 256,
		.tested		= {.probe = NT, .read = NT, .erase = NA, .write = NA},
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.write		= NULL, /* MX23L12854 is a mask ROM, so it is read-only */
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.voltage	= {3000, 3600},
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L512(E)/MX25V512(C)",
		.bustype	= BUS_SPI,
		.manufacture_id	= MACRONIX_ID,
		.model_id	= MACRONIX_MX25L512,
		.total_size	= 64,
		.page_size	= 256,
		/* MX25L512E supports SFDP */
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			},
		},
//		.printlock	= spi_prettyprint_status_register_bp1_srwd,
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported, MX25L512E supports dual I/O */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600}, /* 2.35-3.6V for MX25V512(C) */
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L1005(C)/MX25L1006E",
		.bustype	= BUS_SPI,
		.manufacture_id	= MACRONIX_ID,
		.model_id	= MACRONIX_MX25L1005,
		.total_size	= 128,
		.page_size	= 256,
		/* MX25L1006E supports SFDP */
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 2} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			},
		},
//		.printlock	= spi_prettyprint_status_register_bp1_srwd,
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported, MX25L1006E supports dual I/O */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L2005(C)/MX25L2006E",
		.bustype	= BUS_SPI,
		.manufacture_id	= MACRONIX_ID,
		.model_id	= MACRONIX_MX25L2005,
		.total_size	= 256,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			},
		},
//		.printlock	= spi_prettyprint_status_register_bp1_srwd,
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L4005(A/C)/MX25L4006E",
		.bustype	= BUS_SPI,
		.manufacture_id	= MACRONIX_ID,
		.model_id	= MACRONIX_MX25L4005,
		.total_size	= 512,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			},
		},
//		.printlock	= spi_prettyprint_status_register_bp2_srwd,
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L8005/MX25L8006E/MX25L8008E/MX25V8005",
		.bustype	= BUS_SPI,
		.manufacture_id	= MACRONIX_ID,
		.model_id	= MACRONIX_MX25L8005,
		.total_size	= 1024,
		.page_size	= 256,
		/* MX25L8006E, MX25L8008E support SFDP */
		/* OTP: 64B total; enter 0xB1, exit 0xC1 (MX25L8006E, MX25L8008E only) */
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			},
		},
//		.printlock	= spi_prettyprint_status_register_bp2_srwd,
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600}, /* 2.35-3.6V for MX25V8005 */
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L1605",
		.bustype	= BUS_SPI,
		.manufacture_id	= MACRONIX_ID,
		.model_id	= MACRONIX_MX25L1605,
		.total_size	= 2048,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			},
		},
//		.printlock	= spi_prettyprint_status_register_bp2_srwd, /* bit6: error flag */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L1605A/MX25L1606E/MX25L1608E",
		.bustype	= BUS_SPI,
		.manufacture_id	= MACRONIX_ID,
		.model_id	= MACRONIX_MX25L1605,
		.total_size	= 2048,
		.page_size	= 256,
		/* OTP: 64B total; enter 0xB1, exit 0xC1 (MX25L1606E and MX25L1608E only) */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 512} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			},
		},
//		.printlock	= spi_prettyprint_status_register_bp3_srwd, /* MX25L1605A bp2 only */
		.unlock		= spi_disable_blockprotect_bp3_srwd,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported (MX25L1608E supports dual-I/O read) */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L1605D/MX25L1608D/MX25L1673E",
		.bustype	= BUS_SPI,
		.manufacture_id	= MACRONIX_ID,
		.model_id	= MACRONIX_MX25L1605,
		.total_size	= 2048,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 512} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			},
		},
//		.printlock	= spi_prettyprint_status_register_bp3_srwd, /* bit6: Continuously Program (CP) mode, for 73E is quad enable */
		.unlock		= spi_disable_blockprotect_bp3_srwd,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B), dual I/O supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L1635D",
		.bustype	= BUS_SPI,
		.manufacture_id	= MACRONIX_ID,
		.model_id	= MACRONIX_MX25L1635D,
		.total_size	= 2048,
		.page_size	= 256,
		/* OTP: 64B total; enter 0xB1, exit 0xC1 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 512} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp3_srwd, /* bit6 is quad enable */
		.unlock		= spi_disable_blockprotect_bp3_srwd,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) and multi I/O supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L1635E",
		.bustype	= BUS_SPI,
		.manufacture_id	= MACRONIX_ID,
		.model_id	= MACRONIX_MX25L1635E,
		.total_size	= 2048,
		.page_size	= 256,
		/* OTP: 64B total; enter 0xB1, exit 0xC1 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 512} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp3_srwd, /* bit6 is quad enable */
		.unlock		= spi_disable_blockprotect_bp3_srwd,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) and multi I/O supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L3205(A)",
		.bustype	= BUS_SPI,
		.manufacture_id	= MACRONIX_ID,
		.model_id	= MACRONIX_MX25L3205,
		.total_size	= 4096,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			},
		},
//		.printlock	= spi_prettyprint_status_register_bp2_srwd, /* bit6: error flag */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L3205D/MX25L3208D",
		.bustype	= BUS_SPI,
		.manufacture_id	= MACRONIX_ID,
		.model_id	= MACRONIX_MX25L3205,
		.total_size	= 4096,
		.page_size	= 256,
		/* OTP: 64B total; enter 0xB1, exit 0xC1 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 1024} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			},
		},
//		.printlock	= spi_prettyprint_status_register_bp3_srwd, /* bit6: continuously program mode */
		.unlock		= spi_disable_blockprotect_bp3_srwd,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) and dual I/O supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L3206E/MX25L3208E",
		.bustype	= BUS_SPI,
		.manufacture_id	= MACRONIX_ID,
		.model_id	= MACRONIX_MX25L3205,
		.total_size	= 4096,
		.page_size	= 256,
		/* OTP: 64B total; enter 0xB1, exit 0xC1 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 1024} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {64 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			},
		},
//		.printlock	= spi_prettyprint_status_register_bp3_srwd,
		.unlock		= spi_disable_blockprotect_bp3_srwd,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) and dual I/O supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L3273E",
		.bustype	= BUS_SPI,
		.manufacture_id	= MACRONIX_ID,
		.model_id	= MACRONIX_MX25L3205,
		.total_size	= 4096,
		.page_size	= 256,
		/* OTP: 64B total; enter 0xB1, exit 0xC1 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 1024} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			},
		},
//		.printlock	= spi_prettyprint_status_register_bp3_srwd,
		.unlock		= spi_disable_blockprotect_bp3_srwd,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) and dual I/O supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25L3235D",
		.bustype	= BUS_SPI,
		.manufacture_id	= MACRONIX_ID,
		.model_id	= MACRONIX_MX25L3235D,
		.total_size	= 4096,
		.page_size	= 256,
		/* OTP: 256B total; enter 0xB1, exit 0xC1 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 1024} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp3_srwd, /* bit6 is quad enable */
		.unlock		= spi_disable_blockprotect_bp3_srwd,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},
	{
		.vendor		= "Macronix",
		.name		= "MX25L6406E_MX25L6408E",
		.bustype	= BUS_SPI,
		.manufacture_id	= MACRONIX_ID,
		.model_id	= MACRONIX_MX25L6405,
		.total_size	= 8192,
		.page_size	= 256,
		/* MX25L6406E supports SFDP */
		/* OTP: 06E 64B total; enter 0xB1, exit 0xC1 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 2048} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp3_srwd,
		.unlock		= spi_disable_blockprotect_bp3_srwd,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B), dual I/O read supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

{
		.vendor		= "Macronix",
		.name		= "MX25L6495F",
		.bustype	= BUS_SPI,
		.manufacture_id	= MACRONIX_ID,
		.model_id	= MACRONIX_MX25L6495F,
		.total_size	= 8192,
		.page_size	= 256,
		/* OTP: 1024B total; enter 0xB1, exit 0xC1 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 2048} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {32 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) and multi I/O supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Macronix",
		.name		= "MX25R6435F",
		.bustype	= BUS_SPI,
		.manufacture_id	= MACRONIX_ID,
		.model_id	= MACRONIX_MX25R6435F,
		.total_size	= 8192,
		.page_size	= 256,
		/* OTP: 1024B total; enter 0xB1, exit 0xC1 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 2048} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {32 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp3_srwd, /* bit6 is quad enable */
		.unlock		= spi_disable_blockprotect_bp3_srwd,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) and multi I/O supported */
		.erase    = spi_erase_bulk,
		.voltage	= {1650, 3600},
	},


//	{
//		.vendor		= "Macronix",
//		.name		= "MX25L12805",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= MACRONIX_ID,
//		.model_id	= MACRONIX_MX25L12805,
//		.total_size	= 16384,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_WRSR_WREN,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 4096} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {64 * 1024, 256} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {16 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {16 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

{
		.vendor		= "NextFlash",
		.name		= "NX25B40",
		.bustype	= BUS_SPI,
		.manufacture_id	= NF_ID,
		.model_id	= NF_NX25B40,
		.total_size	= 512,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = {
					{4 * 1024, 2},
					{8 * 1024, 1},
					{16 * 1024, 1},
					{32 * 1024, 1},
					{64 * 1024, 7}
				},
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

//	{
//		.vendor		= "Numonyx",
//		.name		= "M25PE10",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ST_ID,
//		.model_id	= ST_M25PE10,
//		.total_size	= 128,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 32} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {64 * 1024, 2} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {128 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "Numonyx",
//		.name		= "M25PE20",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ST_ID,
//		.model_id	= ST_M25PE20,
//		.total_size	= 256,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 64} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {64 * 1024, 4} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {256 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "Numonyx",
//		.name		= "M25PE40",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ST_ID,
//		.model_id	= ST_M25PE40,
//		.total_size	= 512,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {64 * 1024, 8} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {512 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "Numonyx",
//		.name		= "M25PE80",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ST_ID,
//		.model_id	= ST_M25PE80,
//		.total_size	= 1024,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 256} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {64 * 1024, 16} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "Numonyx",
//		.name		= "M25PE16",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ST_ID,
//		.model_id	= ST_M25PE16,
//		.total_size	= 2048,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 512} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {64 * 1024, 32} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {2 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "Numonyx",
//		/* ..1E = 1.8V, uniform 64KB/4KB blocks/sectors */
//		.name		= "N25Q064..1E",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ST_ID,
//		.model_id	= ST_N25Q064__1E,
//		.total_size	= 8192,
//		.page_size	= 256,
//		/* supports SFDP */
//		/* OTP: 64B total; read 0x4B, write 0x42 */
//		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 2048 } },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {64 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {8 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {1700, 2000},
//		.wp		= &wp_w25,
//	},

//	{
//		.vendor		= "Numonyx",
//		/* ..3E = 3V, uniform 64KB/4KB blocks/sectors */
//		.name		= "N25Q064..3E",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ST_ID,
//		.model_id	= ST_N25Q064__3E,
//		.total_size	= 8192,
//		.page_size	= 256,
//		/* supports SFDP */
//		/* OTP: 64B total; read 0x4B, write 0x42 */
//		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 2048 } },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {64 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {8 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//		.wp		= &wp_w25,
//	},

//	{
//		.vendor		= "Numonyx",
//		.name		= "N25Q256..3E/MT25QL256", /* ..3E/L = 3V, uniform 64KB/4KB blocks/sectors */
//		.bustype	= BUS_SPI,
//		.manufacture_id = ST_ID,
//		.model_id	= ST_N25Q256__3E,
//		.total_size	= 32768,
//		.page_size	= 256,
//		/* supports SFDP */
//		/* OTP: 64B total; read 0x4B, write 0x42 */
//		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP | FEATURE_4BA_SUPPORT,
//		.four_bytes_addr_funcs =
//		{
//			.read_nbyte = spi_nbyte_read_4ba_direct,
//			.program_byte = spi_byte_program_4ba_direct,
//			.program_nbyte = spi_nbyte_program_4ba_direct
//		},
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	= {
//			{
//				.eraseblocks = { {4 * 1024, 8192} },
//				.block_erase = spi_block_erase_21_4ba_direct,
//			}, {
//				.eraseblocks = { {64 * 1024, 512} },
//				.block_erase = spi_block_erase_dc_4ba_direct,
//			}, {
//				.eraseblocks = { {32768 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect, /* TODO: per 64kB sector lock registers */
//		.write		= spi_chip_write_256, /* Multi I/O supported */
//		.read		= spi_chip_read, /* Fast read (0x0B) and multi I/O supported */
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "Micron",
//		.name		= "N25Q512..3E/MT25QL512", /* ..3E/L = 3V, uniform 64KB/4KB blocks/sectors */
//		.bustype	= BUS_SPI,
//		.manufacture_id = ST_ID,
//		.model_id	= ST_N25Q512__3E,
//		.total_size	= 65536,
//		.page_size	= 256,
//		/* supports SFDP */
//		/* OTP: 64B total; read 0x4B, write 0x42 */
//		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP | FEATURE_4BA_SUPPORT,
//		.four_bytes_addr_funcs =
//		{
//			.read_nbyte = spi_nbyte_read_4ba_direct,
//			.program_byte = spi_byte_program_4ba_direct,
//			.program_nbyte = spi_nbyte_program_4ba_direct
//		},
//		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	= {
//			{
//				.eraseblocks = { {4 * 1024, 16384} },
//				.block_erase = spi_block_erase_21_4ba_direct,
//			}, {
//				.eraseblocks = { {64 * 1024, 1024} },
//				.block_erase = spi_block_erase_dc_4ba_direct,
//			}, {
//				.eraseblocks = { {65536 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect, /* TODO: per 64kB sector lock registers */
//		.write		= spi_chip_write_256, /* Multi I/O supported */
//		.read		= spi_chip_read, /* Fast read (0x0B) and multi I/O supported */
//		.voltage	= {2700, 3600},
//	},

{
		.vendor		= "PMC",
		.name		= "Pm25LD010(C)",
		.bustype	= BUS_SPI,
		.manufacture_id	= PMC_ID,
		.model_id	= PMC_PM25LD010,
		.total_size	= 128,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {4 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_D7,
			}, {
				.eraseblocks = { {32 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp2_srwd,
		.unlock		= spi_disable_blockprotect, /* FIXME: C version supports "Safe Guard" */
		.write		= spi_chip_write_256,
		.read		  = spi_chip_read, /* Fast read (0x0B), dual I/O supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600}, /* 2.3-3.6V for Pm25LD010 */
	},

	{
		.vendor		= "PMC",
		.name		= "Pm25LD020(C)",
		.bustype	= BUS_SPI,
		.manufacture_id	= PMC_ID,
		.model_id	= PMC_PM25LD020,
		.total_size	= 256,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {4 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_D7,
			}, {
				.eraseblocks = { {64 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp2_srwd,
		.unlock		= spi_disable_blockprotect, /* FIXME: C version supports "Safe Guard" */
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B), dual I/O supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600}, /* 2.3-3.6V for Pm25LD020 */
	},

	{
		.vendor		= "PMC",
		.name		= "Pm25LD040(C)",
		.bustype	= BUS_SPI,
		.manufacture_id	= PMC_ID,
		.model_id	= PMC_PM25LV040,
		.total_size	= 512,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_D7,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp2_srwd,
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B), dual I/O supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600}, /* 2.3-3.6V for Pm25LD040 */
	},

//	{
//		.vendor		= "PMC",
//		.name		= "Pm25LQ020",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= PMC_ID,
//		.model_id	= PMC_PM25LQ020,
//		.total_size	= 256,
//		.page_size	= 256,
//		/* OTP: 256B total; read 0x4B, write 0xB1 */
//		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 64} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {4 * 1024, 64} },
//				.block_erase = SPI_BLOCK_ERASE_D7,
//			}, {
//				.eraseblocks = { {64 * 1024, 4} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {256 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {256 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.printlock	= spi_prettyprint_status_register_bp3_srwd, /* bit6 is quad enable */
//		.unlock		= spi_disable_blockprotect_bp3_srwd,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2300, 3600},
//	},

//	{
//		.vendor		= "PMC",
//		.name		= "Pm25LQ040",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= PMC_ID,
//		.model_id	= PMC_PM25LQ040,
//		.total_size	= 512,
//		.page_size	= 256,
//		/* OTP: 256B total; read 0x4B, write 0xB1 */
//		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {4 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_D7,
//			}, {
//				.eraseblocks = { {64 * 1024, 8} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {512 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {512 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.printlock	= spi_prettyprint_status_register_bp3_srwd, /* bit6 is quad enable */
//		.unlock		= spi_disable_blockprotect_bp3_srwd,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read, /* Fast read (0x0B) and multi I/O supported */
//		.voltage	= {2300, 3600},
//	},

//	{
//		.vendor		= "PMC",
//		.name		= "Pm25LQ080",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= PMC_ID,
//		.model_id	= PMC_PM25LQ080,
//		.total_size	= 1024,
//		.page_size	= 256,
//		/* OTP: 64B total; read 0x4B, write 0xB1 */
//		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 256} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {4 * 1024, 256} },
//				.block_erase = SPI_BLOCK_ERASE_D7,
//			}, {
//				.eraseblocks = { {64 * 1024, 16} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.printlock	= spi_prettyprint_status_register_bp3_srwd, /* bit6 is quad enable */
//		.unlock		= spi_disable_blockprotect_bp3_srwd,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read, /* Fast read (0x0B) and multi I/O supported */
//		.voltage	= {2300, 3600},
//	},

//	{
//		.vendor		= "PMC",
//		.name		= "Pm25LQ016",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= PMC_ID,
//		.model_id	= PMC_PM25LQ016,
//		.total_size	= 2048,
//		.page_size	= 256,
//		/* OTP: 256B total; read 0x4B, write 0xB1 */
//		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 512} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {4 * 1024, 512} },
//				.block_erase = SPI_BLOCK_ERASE_D7,
//			}, {
//				.eraseblocks = { {64 * 1024, 32} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {2048 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {2048 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.printlock	= spi_prettyprint_status_register_bp3_srwd, /* bit6 is quad enable */
//		.unlock		= spi_disable_blockprotect_bp3_srwd,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read, /* Fast read (0x0B) and multi I/O supported */
//		.voltage	= {2300, 3600},
//	},

//	{
//		.vendor		= "PMC",
//		.name		= "Pm25LQ032C",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= PMC_ID,
//		.model_id	= PMC_PM25LQ032C,
//		.total_size	= 4096,
//		.page_size	= 256,
//		/* OTP: 64B total; read 0x4B, write 0xB1 */
//		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
//		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 1024} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {4 * 1024, 1024} },
//				.block_erase = SPI_BLOCK_ERASE_D7,
//			}, {
//				.eraseblocks = { {64 * 1024, 64} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {4096 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {4096 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.printlock	= spi_prettyprint_status_register_bp3_srwd, /* bit6 is quad enable */
//		.unlock		= spi_disable_blockprotect_bp3_srwd,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read, /* Fast read (0x0B) and multi I/O supported */
//		.voltage	= {2700, 3600},
//	},

{
		.vendor		= "PMC",
		.name		= "Pm25LV010",
		.bustype	= BUS_SPI,
		.manufacture_id	= PMC_ID_NOPREFIX,
		.model_id	= PMC_PM25LV010,
		.total_size	= 128,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_res2, /* The continuation code is transferred as the 3rd byte m( */
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_D7,
			}, {
				.eraseblocks = { {32 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp1_srwd,
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read	  	= spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

//	{
//		.vendor		= "PMC",
//		.name		= "Pm25LV016B",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= PMC_ID,
//		.model_id	= PMC_PM25LV016B,
//		.total_size	= 2048,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 512} },
//				.block_erase = SPI_BLOCK_ERASE_D7,
//			}, {
//				.eraseblocks = { {4 * 1024, 512} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {64 * 1024, 32} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {2 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {2 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "PMC",
//		.name		= "Pm25LV020",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= PMC_ID,
//		.model_id	= PMC_PM25LV020,
//		.total_size	= 256,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 64} },
//				.block_erase = SPI_BLOCK_ERASE_D7,
//			}, {
//				.eraseblocks = { {64 * 1024, 4} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {256 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "PMC",
//		.name		= "Pm25LV040",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= PMC_ID,
//		.model_id	= PMC_PM25LV040,
//		.total_size	= 512,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_D7,
//			}, {
//				.eraseblocks = { {64 * 1024, 8} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {512 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "PMC",
//		.name		= "Pm25LV080B",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= PMC_ID,
//		.model_id	= PMC_PM25LV080B,
//		.total_size	= 1024,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 256} },
//				.block_erase = SPI_BLOCK_ERASE_D7,
//			}, {
//				.eraseblocks = { {4 * 1024, 256} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {64 * 1024, 16} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

{
		.vendor		= "PMC",
		.name		= "Pm25LV512(A)",
		.bustype	= BUS_SPI,
		.manufacture_id	= PMC_ID_NOPREFIX,
		.model_id	= PMC_PM25LV512,
		.total_size	= 64,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_res2, /* The continuation code is transferred as the 3rd byte m( */
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_D7,
			}, {
				.eraseblocks = { {32 * 1024, 2} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp1_srwd,
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		  = spi_chip_read, /* Fast read (0x0B) supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},
//	
//	{
//		.vendor		= "Sanyo",
//		.name		= "LF25FW203A",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SANYO_ID,
//		.model_id	= SANYO_LE25FW203A,
//		.total_size	= 2048,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {64 * 1024, 32} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			},	{
//				.eraseblocks = { {2 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//	},

{
		.vendor		= "Sanyo",
		.name		= "LE25FU106B",
		.bustype	= BUS_SPI,
		.manufacture_id	= SANYO_ID,
		.model_id	= SANYO_LE25FU106B,
		.total_size	= 128,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_res2,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	= {
			/* FIXME: Is this correct?
			{
				.eraseblocks = { {2 * 1024, 64} },
				.block_erase = spi_block_erase_d7,
			},*/
			{
				.eraseblocks = { {32 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp1_srwd,
		.unlock		= spi_disable_blockprotect_bp1_srwd,
		.write		= spi_chip_write_256,
		.read	  	= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2300, 3600},
	},

	{
		.vendor		= "Sanyo",
		.name		= "LE25FU206",
		.bustype	= BUS_SPI,
		.manufacture_id	= SANYO_ID,
		.model_id	= SANYO_LE25FU206,
		.total_size	= 256,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_res2,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	= {
			{
				.eraseblocks = { {4 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_D7,
			}, {
				.eraseblocks = { {64 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp1_srwd,
		.unlock		= spi_disable_blockprotect_bp1_srwd,
		.write		= spi_chip_write_256,
		.read		  = spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2300, 3600},
	},
	
	{
		.vendor		= "Sanyo",
		.name		= "LE25FU206A",
		.bustype	= BUS_SPI,
		.manufacture_id	= SANYO_ID,
		.model_id	= SANYO_LE25FU206A,
		.total_size	= 256,
		.page_size	= 256,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	= {
			{
				.eraseblocks = { {4 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {4 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_D7,
			}, {
				.eraseblocks = { {64 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp2_srwd,
		.unlock		= spi_disable_blockprotect, /* #WP pin write-protects SRWP bit. */
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2300, 3600},
	},

	{
		.vendor		= "Sanyo",
		.name		= "LE25FU406B",
		.bustype	= BUS_SPI,
		.manufacture_id	= SANYO_ID,
		.model_id	= SANYO_LE25FU406B,
		.total_size	= 512,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_res2,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	= {
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_D7,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
				}
			},
//		.printlock	= spi_prettyprint_status_register_bp2_srwd,
		.unlock		= spi_disable_blockprotect, /* #WP pin write-protects SRWP bit. */
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,	
		.voltage	= {2300, 3600},
	},

	{
		.vendor		= "Sanyo",
		.name		= "LE25FU406C/LE25U40CMC",
		.bustype	= BUS_SPI,
		.manufacture_id	= SANYO_ID,
		.model_id	= SANYO_LE25FU406C,
		.total_size	= 512,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	= {
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_D7,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
				}
			},
//		.printlock	= spi_prettyprint_status_register_bp2_srwd,
		.unlock		= spi_disable_blockprotect_bp2_srwd,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* Fast read (0x0B), dual read (0x3B) and dual I/O (0xBB) supported */
		.erase    = spi_erase_bulk,	
		.voltage	= {2300, 3600},
	},
	
	{
		.vendor		= "Sanyo",
		.name		= "LE25FW406A",
		.bustype	= BUS_SPI,
		.manufacture_id	= SANYO_ID,
		.model_id	= SANYO_LE25FW406A,
		.total_size	= 512,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_res2,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_D7,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain,
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,	
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Sanyo",
		.name		= "LE25FW418A",
		.bustype	= BUS_SPI,
		.manufacture_id	= SANYO_ID,
		.model_id	= SANYO_LE25FW418A,
		.total_size	= 512,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_res2,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_D7,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp2_srwd,
		.unlock		= spi_disable_blockprotect, /* #WP pin write-protects SRWP bit. */
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* some quad-read supported ("HD_READ mode") */
		.erase    = spi_erase_bulk,	
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Sanyo",
		.name		= "LE25FW806",
		.bustype	= BUS_SPI,
		.manufacture_id	= SANYO_ID,
		.model_id	= SANYO_LE25FW806,
		.total_size	= 1024,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_res2,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {4 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_D7,
			}, {
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp2_srwd,
		.unlock		= spi_disable_blockprotect, /* #WP pin write-protects SRWP bit. */
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,	
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Sanyo",
		.name		= "LE25FW808",
		.bustype	= BUS_SPI,
		.manufacture_id	= SANYO_ID,
		.model_id	= SANYO_LE25FW808,
		.total_size	= 1024,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_res2,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {8 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_D7,
			}, {
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp2_srwd,
		.unlock		= spi_disable_blockprotect, /* #WP pin write-protects SRWP bit. */
		.write		= spi_chip_write_256,
		.read		= spi_chip_read, /* some quad-read supported ("HD_READ mode") */
		.erase    = spi_erase_bulk,	
		.voltage	= {2700, 3600},
	},

//	
//	{
//		.vendor		= "Spansion",
//		.name		= "S25FL004A",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SPANSION_ID,
//		.model_id	= SPANSION_S25FL004A,
//		.total_size	= 512,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {64 * 1024, 8} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {512 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "Spansion",
//		.name		= "S25FL004A",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SPANSION_ID,
//		.model_id	= SPANSION_S25FL004A,
//		.total_size	= 512,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {64 * 1024, 8} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {512 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//	},

//	{
//		.vendor		= "Spansion",
//		.name		= "S25FL008A",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SPANSION_ID,
//		.model_id	= SPANSION_S25FL008A,
//		.total_size	= 1024,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_OK_PREU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {64 * 1024, 16} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "Spansion",
//		.name		= "S25FL016A",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SPANSION_ID,
//		.model_id	= SPANSION_S25FL016A,
//		.total_size	= 2048,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_OK_PRU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {64 * 1024, 32} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {2 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "Spansion",
//		.name		= "S25FL032A",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SPANSION_ID,
//		.model_id	= SPANSION_S25FL032A,
//		.total_size	= 4096,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {64 * 1024, 64} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {4 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "Spansion",
//		.name		= "S25FL064A",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SPANSION_ID,
//		.model_id	= SPANSION_S25FL064A,
//		.total_size	= 8192,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {64 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {8 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "Spansion",
//		.name		= "S25FL116K",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SPANSION_ID,
//		.model_id	= SPANSION_S25FL116K,
//		.total_size	= 2048,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 512} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {64 * 1024, 32} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {2 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//		/* TODO: write-protection */
//	},

//	{
//		.vendor		= "Spansion",
//		.name		= "S25FS128S Large Sectors",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SPANSION_ID,
//		.model_id	= SPANSION_S25FS128S_L,
//		.total_size	= 16384,
//		.page_size	= 256,
//		.feature_bits   = FEATURE_WRSR_WREN,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_big_spansion,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {64 * 1024, 256} },
//				.block_erase = s25fs_block_erase_d8,
//			}, {
//				.eraseblocks = { {16 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {16 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			},
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {1700, 2000},
//		.wp		= &wp_generic,
//	},

//	{
//		.vendor		= "Spansion",
//		.name		= "S25FS128S Small Sectors",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SPANSION_ID,
//		.model_id	= SPANSION_S25FS128S_S,
//		.total_size	= 16384,
//		.page_size	= 256,
//		.feature_bits   = FEATURE_WRSR_WREN,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_big_spansion,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {64 * 1024, 256} },
//				.block_erase = s25fs_block_erase_d8,
//			}, {
//				.eraseblocks = { {16 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {16 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			},
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {1700, 2000},
//		.wp		= &wp_generic,
//	},

//	{
//		.vendor		= "Spansion",
//		.name		= "S25FL256S Large Sectors",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SPANSION_ID,
//		.model_id	= SPANSION_S25FL256S_UL,
//		.total_size	= 16384,  /* This is just half the size.... */
//		.page_size	= 256,
//		.feature_bits   = FEATURE_WRSR_WREN,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_big_spansion,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {256 * 1024, 64} },
//				.block_erase = s25fl_block_erase,
//			}, {
//				.eraseblocks = { {16 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			},
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {1700, 2000},
//		.wp		= &wp_generic,
//	},

//	{
//		.vendor		= "Spansion",
//		.name		= "S25FL256S Small Sectors",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SPANSION_ID,
//		.model_id	= SPANSION_S25FL256S_US,
//		.total_size	= 16384,   /* This is just half the size.... */
//		.page_size	= 256,
//		.feature_bits   = FEATURE_WRSR_WREN,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_big_spansion,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {64 * 1024, 256} },
//				.block_erase = s25fl_block_erase,
//			}, {
//				.eraseblocks = { {16 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			},
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {1700, 2000},
//		.wp		= &wp_generic,
//	},

//	{
//		.vendor		= "Spansion",
//		.name		= "S25FL128S_UL Uniform 128 kB Sectors",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SPANSION_ID,
//		.model_id	= SPANSION_S25FL128S_UL,
//		.total_size	= 16384,
//		.page_size	= 256,
//		.feature_bits   = FEATURE_WRSR_WREN,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_big_spansion,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {128 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {16 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {16 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			},
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {1700, 2000},
//		.wp		= &wp_generic,
//	},

//	{
//		.vendor		= "Spansion",
//		.name		= "S25FL128S_US Uniform 64 kB Sectors",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SPANSION_ID,
//		.model_id	= SPANSION_S25FL128S_US,
//		.total_size	= 16384,
//		.page_size	= 256,
//		.feature_bits   = FEATURE_WRSR_WREN,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_big_spansion,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {64 * 1024, 256} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {16 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {16 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			},
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {1700, 2000},
//		.wp		= &wp_generic,
//	},

	{
		.vendor		= "SST",
		.name		= "SST25LF040A",
		.bustype	= BUS_SPI,
		.manufacture_id	= SST_ID,
		.model_id	= SST_SST25VF040_REMS,
		.total_size	= 512,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_EWSR | FEATURE_WREN,
//		.tested		= TEST_OK_PREWU,
		//.probe		= probe_spi_res2,
		//.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			},
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_af,//spi_chip_write_1, /* AAI supported, but opcode is 0xAF */
		.read		= spi_chip_read,
		.erase  = spi_erase_bulk,
		.voltage	= {3000, 3600},
	},

//	{
//		.vendor		= "SST",
//		.name		= "SST25LF080A",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SST_ID,
//		.model_id	= SST_SST25VF080_REMS,
//		.total_size	= 1024,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_res2,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 256} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 32} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			},
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_1, /* AAI supported, but opcode is 0xAF */
//		.read		= spi_chip_read,
//		.voltage	= {3000, 3600},
//	},

//	{
//		.vendor		= "SST",
//		.name		= "SST25VF010",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SST_ID,
//		.model_id	= SST_SST25VF010_REMS,
//		.total_size	= 128,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rems,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 32} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 4} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {128 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			},
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_aai_write,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "Spansion",
//		.name		= "S25FL032A",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SPANSION_ID,
//		.model_id	= SPANSION_S25FL032A,
//		.total_size	= 4096,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {64 * 1024, 64} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {4 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//	},

//	{
//		.vendor		= "Spansion",
//		.name		= "S25FL064A",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SPANSION_ID,
//		.model_id	= SPANSION_S25FL064A,
//		.total_size	= 8192,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {64 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {8 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//	},

//	{
//		.vendor		= "SST",
//		.name		= "SST25VF010.REMS",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SST_ID,
//		.model_id	= SST_SST25VF010_REMS,
//		.total_size	= 128,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rems,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 32} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 4} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {128 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			},
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_1,
//		.read		= spi_chip_read,
//	},

//	{
//		.vendor		= "SST",
//		.name		= "SST25VF016B",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SST_ID,
//		.model_id	= SST_SST25VF016B,
//		.total_size	= 2048,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 512} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 64} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 32} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {2 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {2 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			},
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_1, /* AAI supported, but opcode is 0xAF */
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "SST",
//		.name		= "SST25VF032B",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SST_ID,
//		.model_id	= SST_SST25VF032B,
//		.total_size	= 4096,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 1024} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 64} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {4 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {4 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			},
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_aai_write,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "SST",
//		.name		= "SST25VF064C",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SST_ID,
//		.model_id	= SST_SST25VF064C,
//		.total_size	= 8192,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_OK_PREU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 2048} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 256} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {8 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {8 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			},
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "SST",
//		.name		= "SST25VF040",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SST_ID,
//		.model_id	= SST_SST25VF040_REMS,
//		.total_size	= 512,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_OK_PRU,
//		.probe		= probe_spi_rems,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 16} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {512 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			},
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_aai_write,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "SST",
//		.name		= "SST25VF040B",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SST_ID,
//		.model_id	= SST_SST25VF040B,
//		.total_size	= 512,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 16} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 8} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {512 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {512 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			},
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_aai_write,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "SST",
//		.name		= "SST25VF040B.REMS",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SST_ID,
//		.model_id	= SST_SST25VF040B_REMS,
//		.total_size	= 512,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_OK_PRU,
//		.probe		= probe_spi_rems,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 128} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 16} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 8} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {512 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {512 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			},
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_aai_write,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

//	{
//		.vendor		= "SST",
//		.name		= "SST25VF080B",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SST_ID,
//		.model_id	= SST_SST25VF080B,
//		.total_size	= 1024,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_OK_PREU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 256} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 32} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 16} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			},
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_1,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

{
		.vendor		= "SST",
		.name		= "SST25VF512(A)",
		.bustype	= BUS_SPI,
		.manufacture_id	= SST_ID,
		.model_id	= SST_SST25VF512_REMS,
		.total_size	= 64,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_EWSR | FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rems,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 2} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {32 * 1024, 2} },
				.block_erase = SPI_BLOCK_ERASE_D8, /* Supported by SST25VF512A only */
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7, /* Supported by SST25VF512A only */
			},
		},
//		.printlock	= spi_prettyprint_status_register_sst25, /* FIXME: No BP2 & 3 */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_1, /* AAI supported, but opcode is 0xAF */ //or spi_chip_write_af
		.read		  = spi_chip_read, /* Fast read (0x0B) supported by SST25VF512A only */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "SST",
		.name		= "SST25VF010(A)",
		.bustype	= BUS_SPI,
		.manufacture_id	= SST_ID,
		.model_id	= SST_SST25VF010_REMS,
		.total_size	= 128,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_EWSR | FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rems,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {32 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_D8, /* Supported by SST25VF010A only */
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7, /* Supported by SST25VF010A only */
			},
		},
//		.printlock	= spi_prettyprint_status_register_sst25, /* FIXME: No BP2 & 3 */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_1, /* AAI supported, but opcode is 0xAF */
		.read		  = spi_chip_read, /* Fast read (0x0B) supported by SST25VF010A only */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "SST",
		.name		= "SST25VF020",
		.bustype	= BUS_SPI,
		.manufacture_id	= SST_ID,
		.model_id	= SST_SST25VF020_REMS,
		.total_size	= 256,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_EWSR,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rems,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 8} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			},
		},
//		.printlock	= spi_prettyprint_status_register_sst25, /* FIXME: No BP2 & 3 */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_1, /* AAI supported, but opcode is 0xAF */
		.read		  = spi_chip_read, /* only */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},
	
	{
		.vendor		= "ST",
		.name		= "M25P05-A",
		.bustype	= BUS_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25P05A,
		.total_size	= 64,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {32 * 1024, 2} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		  = spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

//	/* The ST M25P05 is a bit of a problem. It has the same ID as the
//	 * ST M25P05-A in RES mode, but supports only 128 byte writes instead
//	 * of 256 byte writes. We rely heavily on the fact that probe_spi_res1
//	 * only is successful if RDID does not work.
//	 */
//	{
//		.vendor		= "ST",
//		.name		= "M25P05",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= 0, /* Not used. */
//		.model_id	= ST_M25P05_RES,
//		.total_size	= 64,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_res1,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {32 * 1024, 2} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {64 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_1, /* 128 */
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

	{
		.vendor		= "ST",
		.name		= "M25P10-A",
		.bustype	= BUS_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25P10A,
		.total_size	= 128,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {32 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		  = spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	/* The ST M25P10 has the same problem as the M25P05. */
//	{
//		.vendor		= "ST",
//		.name		= "M25P10",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= 0, /* Not used. */
//		.model_id	= ST_M25P10_RES,
//		.total_size	= 128,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_UNBOUND_READ,
//		.tested		= TEST_UNTESTED,
////		.probe		= probe_spi_res1,
////		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {32 * 1024, 4} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {128 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_1, /* 128 */
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//	},

	{
		.vendor		= "ST",
		.name		= "M25P20",
		.bustype	= BUS_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25P20,
		.total_size	= 256,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		  = spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "ST", /* Numonyx */
		.name		= "M25P40",
		.bustype	= BUS_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25P40,
		.total_size	= 512,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		  = spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

{
		.vendor		= "Micron/Numonyx/ST", /* Numonyx */
		.name		= "M25P40",
		.bustype	= BUS_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25P40,
		.total_size	= 512,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp3_srwd, /* TODO: check */
		.unlock		= spi_disable_blockprotect_bp3_srwd,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Micron/Numonyx/ST",
		.name		= "M25P40-old",
		.bustype	= BUS_SPI,
		.manufacture_id	= 0, /* Not used. */
		.model_id	= ST_M25P40_RES,
		.total_size	= 512,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_res1,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp3_srwd, /* TODO: check */
		.unlock		= spi_disable_blockprotect_bp3_srwd,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
	},

	{
		.vendor		= "Micron/Numonyx/ST",
		.name		= "M25P80",
		.bustype	= BUS_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25P80,
		.total_size	= 1024,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp3_srwd, /* TODO: check */
		.unlock		= spi_disable_blockprotect_bp3_srwd,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Micron/Numonyx/ST",
		.name		= "M25P16",
		.bustype	= BUS_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25P16,
		.total_size	= 2048,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp3_srwd, /* TODO: check */
		.unlock		= spi_disable_blockprotect_bp3_srwd,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Micron/Numonyx/ST",
		.name		= "M25P32",
		.bustype	= BUS_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25P32,
		.total_size	= 4096,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp3_srwd, /* TODO: check */
		.unlock		= spi_disable_blockprotect_bp3_srwd,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Micron/Numonyx/ST",
		.name		= "M25P64",
		.bustype	= BUS_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25P64,
		.total_size	= 8192,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {64 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp3_srwd, /* TODO: check */
		.unlock		= spi_disable_blockprotect_bp3_srwd,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Micron/Numonyx/ST",
		.name		= "M25P128",
		.bustype	= BUS_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25P128,
		.total_size	= 16384,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {256 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {16 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
	//	.printlock	= spi_prettyprint_status_register_bp3_srwd, /* TODO: check */
		.unlock		= spi_disable_blockprotect_bp3_srwd,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Micron/Numonyx/ST",
		.name		= "M25PE10",
		.bustype	= BUS_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25PE10,
		.total_size	= 128,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 2} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Micron/Numonyx/ST",
		.name		= "M25PE20",
		.bustype	= BUS_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25PE20,
		.total_size	= 256,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Micron/Numonyx/ST",
		.name		= "M25PE40",
		.bustype	= BUS_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25PE40,
		.total_size	= 512,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Micron/Numonyx/ST",
		.name		= "M25PE80",
		.bustype	= BUS_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25PE80,
		.total_size	= 1024,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Micron/Numonyx/ST",
		.name		= "M25PE16",
		.bustype	= BUS_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25PE16,
		.total_size	= 2048,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 512} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Micron/Numonyx/ST",
		.name		= "M25PX80",
		.bustype	= BUS_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25PX80,
		.total_size	= 1024,
		.page_size	= 256,
		/* OTP: 64B total; read 0x4B, write 0x42 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	= {
			{
				.eraseblocks = { { 4 * 1024, 256 } },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp2_srwd, /* bit5: T/B */
		.unlock		= spi_disable_blockprotect_bp2_srwd, /* TODO: per 64kB sector lock registers */
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Micron/Numonyx/ST",
		.name		= "M25PX16",
		.bustype	= BUS_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25PX16,
		.total_size	= 2048,
		.page_size	= 256,
		/* OTP: 64B total; read 0x4B; write 0x42 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { { 4 * 1024, 512 } },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp2_srwd, /* bit5: T/B */
		.unlock		= spi_disable_blockprotect_bp2_srwd, /* TODO: per 64kB sector lock registers */
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2300, 3600},
	},

	{
		.vendor		= "Micron/Numonyx/ST",
		.name		= "M25PX32",
		.bustype	= BUS_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25PX32,
		.total_size	= 4096,
		.page_size	= 256,
		/* OTP: 64B total; read 0x4B; write 0x42 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_OK_PRE,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { { 4 * 1024, 1024 } },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp2_srwd, /* bit5: T/B */
		.unlock		= spi_disable_blockprotect_bp2_srwd, /* TODO: per 64kB sector lock registers */
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Micron/Numonyx/ST",
		.name		= "M25PX64",
		.bustype	= BUS_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_M25PX64,
		.total_size	= 8192,
		.page_size	= 256,
		/* OTP: 64B total; read 0x4B; write 0x42 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { { 4 * 1024, 2048 } },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_bp2_srwd, /* bit5: T/B */
		.unlock		= spi_disable_blockprotect_bp2_srwd, /* TODO: per 64kB sector lock registers */
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},
	


	{
		.vendor		= "Micron/Numonyx/ST",
		.name		= "N25Q032..3E",
		.bustype	= BUS_SPI,
		.manufacture_id	= ST_ID,
		.model_id	= ST_N25Q032__3E,
		.total_size	= 4096,
		.page_size	= 256,
		/* supports SFDP */
		/* OTP: 64B total; read 0x4B, write 0x42 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 1024} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_n25q, /* TODO: config, lock, flag regs */
		.unlock		= spi_disable_blockprotect_n25q, /* TODO: per 64kB sector lock registers */
		.write		= spi_chip_write_256, /* Multi I/O supported */
		.read		= spi_chip_read, /* Fast read (0x0B) and multi I/O supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},



	{
		.vendor		= "Micron/Numonyx/ST",
		.name		= "N25Q064..3E", /* ..3E = 3V, uniform 64KB/4KB blocks/sectors */
		.bustype	= BUS_SPI,
		.manufacture_id = ST_ID,
		.model_id	= ST_N25Q064__3E,
		.total_size	= 8192,
		.page_size	= 256,
		/* supports SFDP */
		/* OTP: 64B total; read 0x4B, write 0x42 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 2048 } },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_n25q, /* TODO: config, lock, flag regs */
		.unlock		= spi_disable_blockprotect_n25q, /* TODO: per 64kB sector lock registers */
		.write		= spi_chip_write_256, /* Multi I/O supported */
		.read		= spi_chip_read, /* Fast read (0x0B) and multi I/O supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},



	{
		.vendor		= "Micron/Numonyx/ST",
		.name		= "N25Q128..3E", /* ..3E = 3V, uniform 64KB/4KB blocks/sectors */
		.bustype	= BUS_SPI,
		.manufacture_id = ST_ID,
		.model_id	= ST_N25Q128__3E,
		.total_size	= 16384,
		.page_size	= 256,
		/* supports SFDP */
		/* OTP: 64B total; read 0x4B, write 0x42 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	= {
			{
				.eraseblocks = { {4 * 1024, 4096 } },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {16384 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_n25q, /* TODO: config, lock, flag regs */
		.unlock		= spi_disable_blockprotect_n25q, /* TODO: per 64kB sector lock registers */
		.write		= spi_chip_write_256, /* Multi I/O supported */
		.read		= spi_chip_read, /* Fast read (0x0B) and multi I/O supported */
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},


{
		.vendor		= "Winbond",
		.name		= "W25Q256BV",
		.bustype	= BUS_SPI,
		.manufacture_id	= WINBOND_NEX_ID,
		.model_id	= WINBOND_NEX_W25Q256_V,
		.total_size	= 32768,
		.page_size	= 256,
		/* supports SFDP */
		/* OTP: 1024B total, 256B reserved; read 0x48; write 0x42, erase 0x44, read ID 0x4B */
		/* FOUR_BYTE_ADDR: supports 4-bytes addressing mode */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP | FEATURE_4BA_ENTER_WREN
			| FEATURE_4BA_EXT_ADDR | FEATURE_4BA_READ | FEATURE_4BA_FAST_READ,
		.tested		= TEST_OK_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 8192} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 1024} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 512} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {32 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {32 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
//		.printlock	= spi_prettyprint_status_register_plain, /* TODO: improve */
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Winbond",
		.name		= "W25Q40EW",
		.bustype	= BUS_SPI,
		.manufacture_id	= WINBOND_NEX_ID,
		.model_id	= WINBOND_NEX_W25Q40EW,
		.total_size	= 512,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {1024 * 512, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {1024 * 512, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		  = spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {1650, 1950},
		/* FIXME(dhendrix): Add write-protection support */
	},

	{
		.vendor		= "Winbond",
		.name		= "W25Q80",
		.bustype	= BUS_SPI,
		.manufacture_id	= WINBOND_NEX_ID,
		.model_id	= WINBOND_NEX_W25Q80_V,
		.total_size	= 1024,
		.page_size	= 256,
		/* OTP: 1024B total, 256B reserved; read 0x48; write 0x42 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
//		.tested		= TEST_OK_PREWU,
		//.probe		= probe_spi_rdid,
		//.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		  = spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
		//.wp		= &wp_w25q,
	},

	{
		.vendor		= "Winbond",
		.name		= "W25Q16",
		.bustype	= BUS_SPI,
		.manufacture_id	= WINBOND_NEX_ID,
		.model_id	= WINBOND_NEX_W25Q16_V,
		.total_size	= 2048,
		.page_size	= 256,
		/* OTP: 1024B total, 256B reserved; read 0x48; write 0x42 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 512} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
		//.wp		= &wp_w25q,
	},

	{
		.vendor		= "Winbond",
		.name		= "W25Q32",
		.bustype	= BUS_SPI,
		.manufacture_id	= WINBOND_NEX_ID,
		.model_id	= WINBOND_NEX_W25Q32_V,
		.total_size	= 4096,
		.page_size	= 256,
		/* OTP: 1024B total, 256B reserved; read 0x48; write 0x42 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 1024} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
		//.wp		= &wp_w25q,
	},

	{
		.vendor		= "Winbond",
		.name		= "W25Q32DW",
		.bustype	= BUS_SPI,
		.manufacture_id	= WINBOND_NEX_ID,
		.model_id	= WINBOND_NEX_W25Q32_W,
		.total_size	= 4096,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 1024} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.voltage	= {1700, 1950},
		.erase    = spi_erase_bulk,
		//.wp		= &wp_w25q,
	},

	{
		.vendor		= "Winbond",
		.name		= "W25Q64",
		.bustype	= BUS_SPI,
		.manufacture_id	= WINBOND_NEX_ID,
		.model_id	= WINBOND_NEX_W25Q64_V,
		.total_size	= 8192,
		.page_size	= 256,
		/* OTP: 1024B total, 256B reserved; read 0x48; write 0x42 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 2048} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		=   spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
		//.wp		= &wp_w25q,
	},

	{
		.vendor		= "Winbond",
		.name		= "W25Q64DW",
		.bustype	= BUS_SPI,
		.manufacture_id	= WINBOND_NEX_ID,
		.model_id	= WINBOND_NEX_W25Q64_W,
		.total_size	= 8192,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 2048} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {1700, 1950},
		//.wp		= &wp_w25q,
	},

	{
		.vendor		= "Winbond",
		.name		= "W25Q128BV", //W25Q128.V
		.bustype	= BUS_SPI,
		.manufacture_id	= WINBOND_NEX_ID,
		.model_id	= WINBOND_NEX_W25Q128_V,
		.total_size	= 16384,
		.page_size	= 256,
		/* OTP: 1024B total, 256B reserved; read 0x48; write 0x42 */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 4096} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 512} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {16 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {16 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		  = spi_chip_read,
		.erase    = spi_erase_bulk,
//		.wp		= &wp_w25q,
	},

//	{
//		.vendor		= "Winbond",
//		.name		= "W25Q128FW",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= WINBOND_NEX_ID,
//		.model_id	= WINBOND_NEX_W25Q128_W,
//		.total_size	= 16384,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 4096} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {32 * 1024, 512} },
//				.block_erase = SPI_BLOCK_ERASE_52,
//			}, {
//				.eraseblocks = { {64 * 1024, 256} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {16 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {16 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		/*
//		 * W25Q128FW is a 1.8V chip, however 3.3V variants with the same
//		 * model ID exist. We'll err on the side of caution here. A user
//		 * with a 3.3V chip sharing the model ID will need to either
//		 * specify voltage on the command line or duplicate this struct
//		 * with a different name/voltage and specify it with "-c".
//		 */
//		.voltage	= {1650, 1950},
//		.wp		= &wp_w25q,
//	},

	{
		.vendor		= "Winbond",
		.name		= "W25Q128J",
		.bustype	= BUS_SPI,
		.manufacture_id	= WINBOND_NEX_ID,
		.model_id	= WINBOND_NEX_W25Q128J,
		.total_size	= 16384,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 4096} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 512} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {16 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {16 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		  = spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
		//.wp		= &wp_w25,
	},
	
//	{
//		.vendor		= "Winbond",
//		.name		= "W25Q256JV",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= WINBOND_NEX_ID,
//		.model_id	= WINBOND_NEX_W25Q256JV,
//		.total_size	= 32768,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP | FEATURE_4BA_SUPPORT,
//		.four_bytes_addr_funcs =
//		{
//			.set_4ba = spi_enter_4ba_b7_we, /* enter 4-bytes addressing mode by CMD B7 + WREN */
//			.read_nbyte = spi_nbyte_read_4ba_direct, /* read directly from any mode, no need to enter 4ba */
//			.program_byte = spi_byte_program_4ba, /* write from 4-bytes addressing mode */
//			.program_nbyte = spi_nbyte_program_4ba /* write from 4-bytes addressing mode */
//		},
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 8192} },
//				.block_erase = SPI_BLOCK_ERASE_20_4ba, /* erases 4k from 4-bytes addressing mode */
//			}, {
//				.eraseblocks = { {32 * 1024, 1024} },
//				.block_erase = SPI_BLOCK_ERASE_52_4ba, /* erases 32k from 4-bytes addressing mode */
//			}, {
//				.eraseblocks = { {64 * 1024, 512} },
//				.block_erase = SPI_BLOCK_ERASE_D8_4ba, /* erases 64k from 4-bytes addressing mode */
//			}, {
//				.eraseblocks = { {32 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_60,
//			}, {
//				.eraseblocks = { {32 * 1024 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//		.wp		= &wp_w25q_large,
//	},
//	{
//		.vendor		= "Winbond",
//		.name		= "W25X10",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= WINBOND_NEX_ID,
//		.model_id	= WINBOND_NEX_W25X10,
//		.total_size	= 128,
//		.page_size	= 256,
//		.feature_bits	= FEATURE_WRSR_WREN,
//		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 32} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {64 * 1024, 2} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}, {
//				.eraseblocks = { {128 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_C7,
//			}
//		},
//		.unlock		= spi_disable_blockprotect,
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//		.voltage	= {2700, 3600},
//		.wp		= &wp_w25,
//	},

	{
		.vendor		= "Winbond",
		.name		= "W25X20",
		.bustype	= BUS_SPI,
		.manufacture_id	= WINBOND_NEX_ID,
		.model_id	= WINBOND_NEX_W25X20,
		.total_size	= 256,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_UNTESTED,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
		//.wp		= &wp_w25,
	},

	{
		.vendor		= "Winbond",
		.name		= "W25X40",
		.bustype	= BUS_SPI,
		.manufacture_id	= WINBOND_NEX_ID,
		.model_id	= WINBOND_NEX_W25X40,
		.total_size	= 512,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 8} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {512 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.voltage	= {2700, 3600},
		.erase    = spi_erase_bulk,
		//.wp		= &wp_w25,
	},

	{
		.vendor		= "Winbond",
		.name		= "W25X80",
		.bustype	= BUS_SPI,
		.manufacture_id	= WINBOND_NEX_ID,
		.model_id	= WINBOND_NEX_W25X80,
		.total_size	= 1024,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREWU,
		//.probe		= probe_spi_rdid,
		//.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {64 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		//.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		  = spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
		//.wp		= &wp_w25,
	},

	{
		.vendor		= "Winbond",
		.name		= "W25X16",
		.bustype	= BUS_SPI,
		.manufacture_id	= WINBOND_NEX_ID,
		.model_id	= WINBOND_NEX_W25X16,
		.total_size	= 2048,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PREWU,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 512} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {2 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.voltage	= {2700, 3600},
		.erase    = spi_erase_bulk,
	},

	{
		.vendor		= "Winbond",
		.name		= "W25X32",
		.bustype	= BUS_SPI,
		.manufacture_id	= WINBOND_NEX_ID,
		.model_id	= WINBOND_NEX_W25X32,
		.total_size	= 4096,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PROBE,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 1024} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {4 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

	{
		.vendor		= "Winbond",
		.name		= "W25X64",
		.bustype	= BUS_SPI,
		.manufacture_id	= WINBOND_NEX_ID,
		.model_id	= WINBOND_NEX_W25X64,
		.total_size	= 8192,
		.page_size	= 256,
		.feature_bits	= FEATURE_WRSR_WREN,
		.tested		= TEST_OK_PROBE,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {4 * 1024, 2048} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 256} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 128} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {8 * 1024 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.unlock		= spi_disable_blockprotect,
		.write		= spi_chip_write_256,
		.read		= spi_chip_read,
		.erase    = spi_erase_bulk,
		.voltage	= {2700, 3600},
	},

//	

//	{
//		.vendor		= "AMIC",
//		.name		= "unknown AMIC SPI chip",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= AMIC_ID,
//		.model_id	= GENERIC_DEVICE_ID,
//		.total_size	= 0,
//		.page_size	= 256,
//		.tested		= TEST_BAD_PREW,
//		.probe		= probe_spi_rdid4,
//		.probe_timing	= TIMING_ZERO,
//		.write		= NULL,
//		.read		= NULL,
//	},

//	{
//		.vendor		= "Atmel",
//		.name		= "unknown Atmel SPI chip",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ATMEL_ID,
//		.model_id	= GENERIC_DEVICE_ID,
//		.total_size	= 0,
//		.page_size	= 256,
//		.tested		= TEST_BAD_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.write		= NULL,
//		.read		= NULL,
//	},

//	{
//		.vendor		= "Eon",
//		.name		= "unknown Eon SPI chip",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= EON_ID_NOPREFIX,
//		.model_id	= GENERIC_DEVICE_ID,
//		.total_size	= 0,
//		.page_size	= 256,
//		.tested		= TEST_BAD_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.write		= NULL,
//		.read		= NULL,
//	},

//	{
//		.vendor		= "Macronix",
//		.name		= "unknown Macronix SPI chip",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= MACRONIX_ID,
//		.model_id	= GENERIC_DEVICE_ID,
//		.total_size	= 0,
//		.page_size	= 256,
//		.tested		= TEST_BAD_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.write		= NULL,
//		.read		= NULL,
//	},

//	{
//		.vendor		= "PMC",
//		.name		= "unknown PMC SPI chip",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= PMC_ID,
//		.model_id	= GENERIC_DEVICE_ID,
//		.total_size	= 0,
//		.page_size	= 256,
//		.tested		= TEST_BAD_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.write		= NULL,
//		.read		= NULL,
//	},

//	{
//		.vendor		= "SST",
//		.name		= "unknown SST SPI chip",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SST_ID,
//		.model_id	= GENERIC_DEVICE_ID,
//		.total_size	= 0,
//		.page_size	= 256,
//		.tested		= TEST_BAD_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.write		= NULL,
//		.read		= NULL,
//	},

//	{
//		.vendor		= "ST",
//		.name		= "unknown ST SPI chip",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= ST_ID,
//		.model_id	= GENERIC_DEVICE_ID,
//		.total_size	= 0,
//		.page_size	= 256,
//		.tested		= TEST_BAD_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.write		= NULL,
//		.read		= NULL,
//	},

//	{
//		.vendor		= "Sanyo",
//		.name		= "unknown Sanyo SPI chip",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= SANYO_ID,
//		.model_id	= GENERIC_DEVICE_ID,
//		.total_size	= 0,
//		.page_size	= 256,
//		.tested		= TEST_BAD_PREW,
//		.probe		= probe_spi_rdid,
//		.probe_timing	= TIMING_ZERO,
//		.write		= NULL,
//		.read		= NULL,
//	},

//	{
//		.vendor		= "Generic",
//		.name		= "Variable Size SPI chip",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= VARIABLE_SIZE_MANUF_ID,
//		.model_id	= VARIABLE_SIZE_DEVICE_ID,
//		.total_size	= 64,  /* This size is set temporarily */
//		.page_size	= 256,
//		.tested		= TEST_OK_PREW,
//		.probe		= probe_variable_size,
//		.block_erasers	=
//		{
//			{
//				.eraseblocks = { {4 * 1024, 16} },
//				.block_erase = SPI_BLOCK_ERASE_20,
//			}, {
//				.eraseblocks = { {64 * 1024, 1} },
//				.block_erase = SPI_BLOCK_ERASE_D8,
//			}
//		},
//		.write		= spi_chip_write_256,
//		.read		= spi_chip_read,
//	},

//	{
//		.vendor		= "Generic",
//		.name		= "unknown SPI chip (RDID)",
//		.bustype	= BUS_SPI,
//		.manufacture_id	= GENERIC_MANUF_ID,
//		.model_id	= GENERIC_DEVICE_ID,
//		.total_size	= 0,
//		.page_size	= 256,
//		.tested		= TEST_BAD_PREW,
//		.probe		= probe_spi_rdid,
//		.write		= NULL,
//	},

	{
		.vendor		= "Generic",
		.name		= "unknown SPI chip (REMS)",
		.bustype	= BUS_SPI,
		.manufacture_id	= GENERIC_MANUF_ID,
		.model_id	= GENERIC_DEVICE_ID,
		.total_size	= 0,
		.page_size	= 256,
		.tested		= TEST_BAD_PREW,
		//.probe		= probe_spi_rems,
		.write		= NULL,
	},

	{ NULL 	}
};



//int flash_erase_value(struct flashctx *flash)
//{
//	return flash->chip->feature_bits & FEATURE_ERASE_TO_ZERO ? 0 : 0xff;
//}

//int flash_unerased_value(struct flashctx *flash)
//{
//	return flash->chip->feature_bits & FEATURE_ERASE_TO_ZERO ? 0xff : 0;
//}

const struct flashchip *flash_id_to_entry(uint8_t mfg_id, uint32_t model_id)
{
	const struct flashchip *chip;

	for (chip = &flashchips[0]; chip->vendor; chip++) {
		if ((chip->manufacture_id == mfg_id) &&
			(chip->model_id == model_id))
			return chip;
	}

	return NULL;
}

unsigned int flashchips_in_base(void){
	return (sizeof(flashchips)/sizeof(flashchips[0]));
}

//struct voltage_range voltage_ranges[NUM_VOLTAGE_RANGES];

//static int compar(const void *_x, const void *_y)
//{
//	const struct voltage_range *x = _x;
//	const struct voltage_range *y = _y;

//	/*
//	 * qsort() places entries in ascending order. We will sort by minimum
//	 * voltage primarily and max voltage secondarily, and move empty sets
//	 * to the end of array.
//	 */
//	if (x->min == 0)
//		return 1;
//	if (y->min == 0)
//		return -1;

//	if (x->min < y->min)
//		return -1;
//	if (x->min > y->min)
//		return 1;

//	if (x->min == y->min) {
//		if (x->max < y->max)
//			return -1;
//		if (x->max > y->max)
//			return 1;
//	}

//	return 0;
//}

