/*
 * arch/arm/plat-omap/include/mach/mux.h
 *
 * Table of the Omap register configurations for the FUNC_MUX and
 * PULL_DWN combinations.
 *
 * Copyright (C) 2004 - 2008 Texas Instruments Inc.
 * Copyright (C) 2003 - 2008 Nokia Corporation
 *
 * Written by Tony Lindgren
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * NOTE: Please use the following naming style for new pin entries.
 *	 For example, W8_1610_MMC2_DAT0, where:
 *	 - W8	     = ball
 *	 - 1610	     = 1510 or 1610, none if common for both 1510 and 1610
 *	 - MMC2_DAT0 = function
 */

#ifndef __ASM_ARCH_MUX_H
#define __ASM_ARCH_MUX_H

#define PU_PD_SEL_NA		0	/* No pu_pd reg available */
#define PULL_DWN_CTRL_NA	0	/* No pull-down control needed */

#ifdef	CONFIG_OMAP_MUX_DEBUG
#define MUX_REG(reg, mode_offset, mode) .mux_reg_name = "FUNC_MUX_CTRL_"#reg, \
					.mux_reg = FUNC_MUX_CTRL_##reg, \
					.mask_offset = mode_offset, \
					.mask = mode,

#define PULL_REG(reg, bit, status)	.pull_name = "PULL_DWN_CTRL_"#reg, \
					.pull_reg = PULL_DWN_CTRL_##reg, \
					.pull_bit = bit, \
					.pull_val = status,

#define PU_PD_REG(reg, status)		.pu_pd_name = "PU_PD_SEL_"#reg, \
					.pu_pd_reg = PU_PD_SEL_##reg, \
					.pu_pd_val = status,

#define MUX_REG_730(reg, mode_offset, mode) .mux_reg_name = "OMAP730_IO_CONF_"#reg, \
					.mux_reg = OMAP730_IO_CONF_##reg, \
					.mask_offset = mode_offset, \
					.mask = mode,

#define PULL_REG_730(reg, bit, status)	.pull_name = "OMAP730_IO_CONF_"#reg, \
					.pull_reg = OMAP730_IO_CONF_##reg, \
					.pull_bit = bit, \
					.pull_val = status,

#else

#define MUX_REG(reg, mode_offset, mode) .mux_reg = FUNC_MUX_CTRL_##reg, \
					.mask_offset = mode_offset, \
					.mask = mode,

#define PULL_REG(reg, bit, status)	.pull_reg = PULL_DWN_CTRL_##reg, \
					.pull_bit = bit, \
					.pull_val = status,

#define PU_PD_REG(reg, status)		.pu_pd_reg = PU_PD_SEL_##reg, \
					.pu_pd_val = status,

#define MUX_REG_730(reg, mode_offset, mode) \
					.mux_reg = OMAP730_IO_CONF_##reg, \
					.mask_offset = mode_offset, \
					.mask = mode,

#define PULL_REG_730(reg, bit, status)	.pull_reg = OMAP730_IO_CONF_##reg, \
					.pull_bit = bit, \
					.pull_val = status,

#endif /* CONFIG_OMAP_MUX_DEBUG */

#define MUX_CFG(desc, mux_reg, mode_offset, mode,	\
		pull_reg, pull_bit, pull_status,	\
		pu_pd_reg, pu_pd_status, debug_status)	\
{							\
	.name =	 desc,					\
	.debug = debug_status,				\
	MUX_REG(mux_reg, mode_offset, mode)		\
	PULL_REG(pull_reg, pull_bit, pull_status)	\
	PU_PD_REG(pu_pd_reg, pu_pd_status)		\
},


/*
 * OMAP730 has a slightly different config for the pin mux.
 * - config regs are the OMAP730_IO_CONF_x regs (see omap730.h) regs and
 *   not the FUNC_MUX_CTRL_x regs from hardware.h
 * - for pull-up/down, only has one enable bit which is is in the same register
 *   as mux config
 */
#define MUX_CFG_730(desc, mux_reg, mode_offset, mode,	\
		   pull_bit, pull_status, debug_status)\
{							\
	.name =	 desc,					\
	.debug = debug_status,				\
	MUX_REG_730(mux_reg, mode_offset, mode)		\
	PULL_REG_730(mux_reg, pull_bit, pull_status)	\
	PU_PD_REG(NA, 0)		\
},

#define MUX_CFG_24XX(desc, reg_offset, mode,			\
				pull_en, pull_mode, dbg)	\
{								\
	.name		= desc,					\
	.debug		= dbg,					\
	.mux_reg	= reg_offset,				\
	.mask		= mode,					\
	.pull_val	= pull_en,				\
	.pu_pd_val	= pull_mode,				\
},

/* 24xx/34xx mux bit defines */
#define OMAP2_PULL_ENA		(1 << 3)
#define OMAP2_PULL_UP		(1 << 4)
#define OMAP2_ALTELECTRICALSEL	(1 << 5)

/* 34xx specific mux bit defines */
#define OMAP3_INPUT_EN		(1 << 8)
#define OMAP3_OFF_EN		(1 << 9)
#define OMAP3_OFFIN_EN		(1 << 10)
#define OMAP3_OFFOUT_VAL	(1 << 11)
#define OMAP3_OFF_PULL_EN	(1 << 12)
#define OMAP3_OFF_PULL_UP	(1 << 13)
#define OMAP3_WAKEUP_EN		(1 << 14)

/* 34xx mux mode options for each pin. See TRM for options */
#define	OMAP34XX_MUX_MODE0	0
#define	OMAP34XX_MUX_MODE1	1
#define	OMAP34XX_MUX_MODE2	2
#define	OMAP34XX_MUX_MODE3	3
#define	OMAP34XX_MUX_MODE4	4
#define	OMAP34XX_MUX_MODE5	5
#define	OMAP34XX_MUX_MODE6	6
#define	OMAP34XX_MUX_MODE7	7

/* 34xx active pin states */
#define OMAP34XX_PIN_OUTPUT		0
#define OMAP34XX_PIN_INPUT		OMAP3_INPUT_EN
#define OMAP34XX_PIN_INPUT_PULLUP	(OMAP2_PULL_ENA | OMAP3_INPUT_EN \
						| OMAP2_PULL_UP)
#define OMAP34XX_PIN_INPUT_PULLDOWN	(OMAP2_PULL_ENA | OMAP3_INPUT_EN)

/* 34xx off mode states */
#define OMAP34XX_PIN_OFF_NONE           0
#define OMAP34XX_PIN_OFF_OUTPUT_HIGH	(OMAP3_OFF_EN | OMAP3_OFFOUT_VAL)
#define OMAP34XX_PIN_OFF_OUTPUT_LOW	(OMAP3_OFF_EN)
#define OMAP34XX_PIN_OFF_INPUT_PULLUP	(OMAP3_OFF_EN | OMAP3_OFFIN_EN \
						| OMAP3_OFF_PULL_EN \
						| OMAP3_OFF_PULL_UP)
#define OMAP34XX_PIN_OFF_INPUT_PULLDOWN	(OMAP3_OFF_EN | OMAP3_OFFIN_EN \
						| OMAP3_OFF_PULL_EN)
#define OMAP34XX_PIN_OFF_WAKEUPENABLE	OMAP3_WAKEUP_EN

#define MUX_CFG_34XX(desc, reg_offset, mux_value) {		\
	.name		= desc,					\
	.debug		= 0,					\
	.mux_reg	= reg_offset,				\
	.mux_val	= mux_value				\
},

#define MUX_INITIALIZE	"MUX_INITIALIZE"

struct pin_config {
	char 			*name;
	const unsigned int 	mux_reg;
	unsigned char		debug;

#if	defined(CONFIG_ARCH_OMAP34XX)
	u16			mux_val; /* Wake-up, off mode, pull, mux mode */
#endif

#if	defined(CONFIG_ARCH_OMAP1) || defined(CONFIG_ARCH_OMAP24XX)
	const unsigned char mask_offset;
	const unsigned char mask;

	const char *pull_name;
	const unsigned int pull_reg;
	const unsigned char pull_val;
	const unsigned char pull_bit;

	const char *pu_pd_name;
	const unsigned int pu_pd_reg;
	const unsigned char pu_pd_val;
#endif

#if	defined(CONFIG_OMAP_MUX_DEBUG) || defined(CONFIG_OMAP_MUX_WARNINGS)
	const char *mux_reg_name;
#endif

};

enum omap730_index {
	/* OMAP 730 keyboard */
	E2_730_KBR0,
	J7_730_KBR1,
	E1_730_KBR2,
	F3_730_KBR3,
	D2_730_KBR4,
	C2_730_KBC0,
	D3_730_KBC1,
	E4_730_KBC2,
	F4_730_KBC3,
	E3_730_KBC4,

	/* USB */
	AA17_730_USB_DM,
	W16_730_USB_PU_EN,
	W17_730_USB_VBUSI,
};

enum omap1xxx_index {
	/* UART1 (BT_UART_GATING)*/
	UART1_TX = 0,
	UART1_RTS,

	/* UART2 (COM_UART_GATING)*/
	UART2_TX,
	UART2_RX,
	UART2_CTS,
	UART2_RTS,

	/* UART3 (GIGA_UART_GATING) */
	UART3_TX,
	UART3_RX,
	UART3_CTS,
	UART3_RTS,
	UART3_CLKREQ,
	UART3_BCLK,	/* 12MHz clock out */
	Y15_1610_UART3_RTS,

	/* PWT & PWL */
	PWT,
	PWL,

	/* USB master generic */
	R18_USB_VBUS,
	R18_1510_USB_GPIO0,
	W4_USB_PUEN,
	W4_USB_CLKO,
	W4_USB_HIGHZ,
	W4_GPIO58,

	/* USB1 master */
	USB1_SUSP,
	USB1_SEO,
	W13_1610_USB1_SE0,
	USB1_TXEN,
	USB1_TXD,
	USB1_VP,
	USB1_VM,
	USB1_RCV,
	USB1_SPEED,
	R13_1610_USB1_SPEED,
	R13_1710_USB1_SE0,

	/* USB2 master */
	USB2_SUSP,
	USB2_VP,
	USB2_TXEN,
	USB2_VM,
	USB2_RCV,
	USB2_SEO,
	USB2_TXD,

	/* OMAP-1510 GPIO */
	R18_1510_GPIO0,
	R19_1510_GPIO1,
	M14_1510_GPIO2,

	/* OMAP1610 GPIO */
	P18_1610_GPIO3,
	Y15_1610_GPIO17,

	/* OMAP-1710 GPIO */
	R18_1710_GPIO0,
	V2_1710_GPIO10,
	N21_1710_GPIO14,
	W15_1710_GPIO40,

	/* MPUIO */
	MPUIO2,
	N15_1610_MPUIO2,
	MPUIO4,
	MPUIO5,
	T20_1610_MPUIO5,
	W11_1610_MPUIO6,
	V10_1610_MPUIO7,
	W11_1610_MPUIO9,
	V10_1610_MPUIO10,
	W10_1610_MPUIO11,
	E20_1610_MPUIO13,
	U20_1610_MPUIO14,
	E19_1610_MPUIO15,

	/* MCBSP2 */
	MCBSP2_CLKR,
	MCBSP2_CLKX,
	MCBSP2_DR,
	MCBSP2_DX,
	MCBSP2_FSR,
	MCBSP2_FSX,

	/* MCBSP3 */
	MCBSP3_CLKX,

	/* Misc ballouts */
	BALLOUT_V8_ARMIO3,
	N20_HDQ,

	/* OMAP-1610 MMC2 */
	W8_1610_MMC2_DAT0,
	V8_1610_MMC2_DAT1,
	W15_1610_MMC2_DAT2,
	R10_1610_MMC2_DAT3,
	Y10_1610_MMC2_CLK,
	Y8_1610_MMC2_CMD,
	V9_1610_MMC2_CMDDIR,
	V5_1610_MMC2_DATDIR0,
	W19_1610_MMC2_DATDIR1,
	R18_1610_MMC2_CLKIN,

	/* OMAP-1610 External Trace Interface */
	M19_1610_ETM_PSTAT0,
	L15_1610_ETM_PSTAT1,
	L18_1610_ETM_PSTAT2,
	L19_1610_ETM_D0,
	J19_1610_ETM_D6,
	J18_1610_ETM_D7,

	/* OMAP16XX GPIO */
	P20_1610_GPIO4,
	V9_1610_GPIO7,
	W8_1610_GPIO9,
	N20_1610_GPIO11,
	N19_1610_GPIO13,
	P10_1610_GPIO22,
	V5_1610_GPIO24,
	AA20_1610_GPIO_41,
	W19_1610_GPIO48,
	M7_1610_GPIO62,
	V14_16XX_GPIO37,
	R9_16XX_GPIO18,
	L14_16XX_GPIO49,

	/* OMAP-1610 uWire */
	V19_1610_UWIRE_SCLK,
	U18_1610_UWIRE_SDI,
	W21_1610_UWIRE_SDO,
	N14_1610_UWIRE_CS0,
	P15_1610_UWIRE_CS3,
	N15_1610_UWIRE_CS1,

	/* OMAP-1610 SPI */
	U19_1610_SPIF_SCK,
	U18_1610_SPIF_DIN,
	P20_1610_SPIF_DIN,
	W21_1610_SPIF_DOUT,
	R18_1610_SPIF_DOUT,
	N14_1610_SPIF_CS0,
	N15_1610_SPIF_CS1,
	T19_1610_SPIF_CS2,
	P15_1610_SPIF_CS3,

	/* OMAP-1610 Flash */
	L3_1610_FLASH_CS2B_OE,
	M8_1610_FLASH_CS2B_WE,

	/* First MMC */
	MMC_CMD,
	MMC_DAT1,
	MMC_DAT2,
	MMC_DAT0,
	MMC_CLK,
	MMC_DAT3,

	/* OMAP-1710 MMC CMDDIR and DATDIR0 */
	M15_1710_MMC_CLKI,
	P19_1710_MMC_CMDDIR,
	P20_1710_MMC_DATDIR0,

	/* OMAP-1610 USB0 alternate pin configuration */
	W9_USB0_TXEN,
	AA9_USB0_VP,
	Y5_USB0_RCV,
	R9_USB0_VM,
	V6_USB0_TXD,
	W5_USB0_SE0,
	V9_USB0_SPEED,
	V9_USB0_SUSP,

	/* USB2 */
	W9_USB2_TXEN,
	AA9_USB2_VP,
	Y5_USB2_RCV,
	R9_USB2_VM,
	V6_USB2_TXD,
	W5_USB2_SE0,

	/* 16XX UART */
	R13_1610_UART1_TX,
	V14_16XX_UART1_RX,
	R14_1610_UART1_CTS,
	AA15_1610_UART1_RTS,
	R9_16XX_UART2_RX,
	L14_16XX_UART3_RX,

	/* I2C OMAP-1610 */
	I2C_SCL,
	I2C_SDA,

	/* Keypad */
	F18_1610_KBC0,
	D20_1610_KBC1,
	D19_1610_KBC2,
	E18_1610_KBC3,
	C21_1610_KBC4,
	G18_1610_KBR0,
	F19_1610_KBR1,
	H14_1610_KBR2,
	E20_1610_KBR3,
	E19_1610_KBR4,
	N19_1610_KBR5,

	/* Power management */
	T20_1610_LOW_PWR,

	/* MCLK Settings */
	V5_1710_MCLK_ON,
	V5_1710_MCLK_OFF,
	R10_1610_MCLK_ON,
	R10_1610_MCLK_OFF,

	/* CompactFlash controller */
	P11_1610_CF_CD2,
	R11_1610_CF_IOIS16,
	V10_1610_CF_IREQ,
	W10_1610_CF_RESET,
	W11_1610_CF_CD1,

	/* parallel camera */
	J15_1610_CAM_LCLK,
	J18_1610_CAM_D7,
	J19_1610_CAM_D6,
	J14_1610_CAM_D5,
	K18_1610_CAM_D4,
	K19_1610_CAM_D3,
	K15_1610_CAM_D2,
	K14_1610_CAM_D1,
	L19_1610_CAM_D0,
	L18_1610_CAM_VS,
	L15_1610_CAM_HS,
	M19_1610_CAM_RSTZ,
	Y15_1610_CAM_OUTCLK,

	/* serial camera */
	H19_1610_CAM_EXCLK,
	Y12_1610_CCP_CLKP,
	W13_1610_CCP_CLKM,
	W14_1610_CCP_DATAP,
	Y14_1610_CCP_DATAM,

};

enum omap24xx_index {
	/* 24xx I2C */
	M19_24XX_I2C1_SCL,
	L15_24XX_I2C1_SDA,
	J15_24XX_I2C2_SCL,
	H19_24XX_I2C2_SDA,

	/* 24xx Menelaus interrupt */
	W19_24XX_SYS_NIRQ,

	/* 24xx clock */
	W14_24XX_SYS_CLKOUT,

	/* 24xx GPMC chipselects, wait pin monitoring */
	E2_GPMC_NCS2,
	L2_GPMC_NCS7,
	L3_GPMC_WAIT0,
	N7_GPMC_WAIT1,
	M1_GPMC_WAIT2,
	P1_GPMC_WAIT3,

	/* 242X McBSP */
	Y15_24XX_MCBSP2_CLKX,
	R14_24XX_MCBSP2_FSX,
	W15_24XX_MCBSP2_DR,
	V15_24XX_MCBSP2_DX,

	/* 24xx GPIO */
	M21_242X_GPIO11,
	P21_242X_GPIO12,
	AA10_242X_GPIO13,
	AA6_242X_GPIO14,
	AA4_242X_GPIO15,
	Y11_242X_GPIO16,
	AA12_242X_GPIO17,
	AA8_242X_GPIO58,
	Y20_24XX_GPIO60,
	W4__24XX_GPIO74,
	N15_24XX_GPIO85,
	M15_24XX_GPIO92,
	P20_24XX_GPIO93,
	P18_24XX_GPIO95,
	M18_24XX_GPIO96,
	L14_24XX_GPIO97,
	J15_24XX_GPIO99,
	V14_24XX_GPIO117,
	P14_24XX_GPIO125,

	/* 242x DBG GPIO */
	V4_242X_GPIO49,
	W2_242X_GPIO50,
	U4_242X_GPIO51,
	V3_242X_GPIO52,
	V2_242X_GPIO53,
	V6_242X_GPIO53,
	T4_242X_GPIO54,
	Y4_242X_GPIO54,
	T3_242X_GPIO55,
	U2_242X_GPIO56,

	/* 24xx external DMA requests */
	AA10_242X_DMAREQ0,
	AA6_242X_DMAREQ1,
	E4_242X_DMAREQ2,
	G4_242X_DMAREQ3,
	D3_242X_DMAREQ4,
	E3_242X_DMAREQ5,

	/* UART3 */
	K15_24XX_UART3_TX,
	K14_24XX_UART3_RX,

	/* MMC/SDIO */
	G19_24XX_MMC_CLKO,
	H18_24XX_MMC_CMD,
	F20_24XX_MMC_DAT0,
	H14_24XX_MMC_DAT1,
	E19_24XX_MMC_DAT2,
	D19_24XX_MMC_DAT3,
	F19_24XX_MMC_DAT_DIR0,
	E20_24XX_MMC_DAT_DIR1,
	F18_24XX_MMC_DAT_DIR2,
	E18_24XX_MMC_DAT_DIR3,
	G18_24XX_MMC_CMD_DIR,
	H15_24XX_MMC_CLKI,

	/* Full speed USB */
	J20_24XX_USB0_PUEN,
	J19_24XX_USB0_VP,
	K20_24XX_USB0_VM,
	J18_24XX_USB0_RCV,
	K19_24XX_USB0_TXEN,
	J14_24XX_USB0_SE0,
	K18_24XX_USB0_DAT,

	N14_24XX_USB1_SE0,
	W12_24XX_USB1_SE0,
	P15_24XX_USB1_DAT,
	R13_24XX_USB1_DAT,
	W20_24XX_USB1_TXEN,
	P13_24XX_USB1_TXEN,
	V19_24XX_USB1_RCV,
	V12_24XX_USB1_RCV,

	AA10_24XX_USB2_SE0,
	Y11_24XX_USB2_DAT,
	AA12_24XX_USB2_TXEN,
	AA6_24XX_USB2_RCV,
	AA4_24XX_USB2_TLLSE0,

	/* Keypad GPIO*/
	T19_24XX_KBR0,
	R19_24XX_KBR1,
	V18_24XX_KBR2,
	M21_24XX_KBR3,
	E5__24XX_KBR4,
	M18_24XX_KBR5,
	R20_24XX_KBC0,
	M14_24XX_KBC1,
	H19_24XX_KBC2,
	V17_24XX_KBC3,
	P21_24XX_KBC4,
	L14_24XX_KBC5,
	N19_24XX_KBC6,

	/* 24xx Menelaus Keypad GPIO */
	B3__24XX_KBR5,
	AA4_24XX_KBC2,
	B13_24XX_KBC6,

	/* 2430 USB */
	AD9_2430_USB0_PUEN,
	Y11_2430_USB0_VP,
	AD7_2430_USB0_VM,
	AE7_2430_USB0_RCV,
	AD4_2430_USB0_TXEN,
	AF9_2430_USB0_SE0,
	AE6_2430_USB0_DAT,
	AD24_2430_USB1_SE0,
	AB24_2430_USB1_RCV,
	Y25_2430_USB1_TXEN,
	AA26_2430_USB1_DAT,

	/* 2430 HS-USB */
	AD9_2430_USB0HS_DATA3,
	Y11_2430_USB0HS_DATA4,
	AD7_2430_USB0HS_DATA5,
	AE7_2430_USB0HS_DATA6,
	AD4_2430_USB0HS_DATA2,
	AF9_2430_USB0HS_DATA0,
	AE6_2430_USB0HS_DATA1,
	AE8_2430_USB0HS_CLK,
	AD8_2430_USB0HS_DIR,
	AE5_2430_USB0HS_STP,
	AE9_2430_USB0HS_NXT,
	AC7_2430_USB0HS_DATA7,

	/* 2430 McBSP */
	AD6_2430_MCBSP_CLKS,

	AB2_2430_MCBSP1_CLKR,
	AD5_2430_MCBSP1_FSR,
	AA1_2430_MCBSP1_DX,
	AF3_2430_MCBSP1_DR,
	AB3_2430_MCBSP1_FSX,
	Y9_2430_MCBSP1_CLKX,

	AC10_2430_MCBSP2_FSX,
	AD16_2430_MCBSP2_CLX,
	AE13_2430_MCBSP2_DX,
	AD13_2430_MCBSP2_DR,
	AC10_2430_MCBSP2_FSX_OFF,
	AD16_2430_MCBSP2_CLX_OFF,
	AE13_2430_MCBSP2_DX_OFF,
	AD13_2430_MCBSP2_DR_OFF,

	AC9_2430_MCBSP3_CLKX,
	AE4_2430_MCBSP3_FSX,
	AE2_2430_MCBSP3_DR,
	AF4_2430_MCBSP3_DX,

	N3_2430_MCBSP4_CLKX,
	AD23_2430_MCBSP4_DR,
	AB25_2430_MCBSP4_DX,
	AC25_2430_MCBSP4_FSX,

	AE16_2430_MCBSP5_CLKX,
	AF12_2430_MCBSP5_FSX,
	K7_2430_MCBSP5_DX,
	M1_2430_MCBSP5_DR,

	/* 2430 McSPI*/
	Y18_2430_MCSPI1_CLK,
	AD15_2430_MCSPI1_SIMO,
	AE17_2430_MCSPI1_SOMI,
	U1_2430_MCSPI1_CS0,

	/* Touchscreen GPIO */
	AF19_2430_GPIO_85,

};

enum omap34xx_index {
	/* 34xx I2C */
	K21_34XX_I2C1_SCL,
	J21_34XX_I2C1_SDA,
	AF15_34XX_I2C2_SCL,
	AE15_34XX_I2C2_SDA,
	AF14_34XX_I2C3_SCL,
	AG14_34XX_I2C3_SDA,
	AD26_34XX_I2C4_SCL,
	AE26_34XX_I2C4_SDA,

	/* PHY - HSUSB: 12-pin ULPI PHY: Port 1*/
	AE10_3430_USB1HS_PHY_CLK,
	AF10_3430_USB1HS_PHY_STP,
	AF9_3430_USB1HS_PHY_DIR,
	AG9_3430_USB1HS_PHY_NXT,
	AF11_3430_USB1HS_PHY_DATA0,
	AG12_3430_USB1HS_PHY_DATA1,
	AH12_3430_USB1HS_PHY_DATA2,
	AH14_3430_USB1HS_PHY_DATA3,
	AE11_3430_USB1HS_PHY_DATA4,
	AH9_3430_USB1HS_PHY_DATA5,
	AF13_3430_USB1HS_PHY_DATA6,
	AE13_3430_USB1HS_PHY_DATA7,

	/* PHY - HSUSB: 12-pin ULPI PHY: Port 2*/
	AE7_3430_USB2HS_PHY_CLK,
	AF7_3430_USB2HS_PHY_STP,
	AG7_3430_USB2HS_PHY_DIR,
	AH7_3430_USB2HS_PHY_NXT,
	AG8_3430_USB2HS_PHY_DATA0,
	AH8_3430_USB2HS_PHY_DATA1,
	AB2_3430_USB2HS_PHY_DATA2,
	V3_3430_USB2HS_PHY_DATA3,
	Y2_3430_USB2HS_PHY_DATA4,
	Y3_3430_USB2HS_PHY_DATA5,
	Y4_3430_USB2HS_PHY_DATA6,
	AA3_3430_USB2HS_PHY_DATA7,

	/* PHY FSUSB: FS Serial for Port 1 (multiple PHY modes supported) */
	AF10_3430_USB1FS_PHY_MM1_RXDP,
	AG9_3430_USB1FS_PHY_MM1_RXDM,
	W13_3430_USB1FS_PHY_MM1_RXRCV,
	W12_3430_USB1FS_PHY_MM1_TXSE0,
	W11_3430_USB1FS_PHY_MM1_TXDAT,
	Y11_3430_USB1FS_PHY_MM1_TXEN_N,

	/* PHY FSUSB: FS Serial for Port 2 (multiple PHY modes supported) */
	AF7_3430_USB2FS_PHY_MM2_RXDP,
	AH7_3430_USB2FS_PHY_MM2_RXDM,
	AB10_3430_USB2FS_PHY_MM2_RXRCV,
	AB9_3430_USB2FS_PHY_MM2_TXSE0,
	W3_3430_USB2FS_PHY_MM2_TXDAT,
	T4_3430_USB2FS_PHY_MM2_TXEN_N,

	/* PHY FSUSB: FS Serial for Port 3 (multiple PHY modes supported) */
	AH3_3430_USB3FS_PHY_MM3_RXDP,
	AE3_3430_USB3FS_PHY_MM3_RXDM,
	AD1_3430_USB3FS_PHY_MM3_RXRCV,
	AE1_3430_USB3FS_PHY_MM3_TXSE0,
	AD2_3430_USB3FS_PHY_MM3_TXDAT,
	AC1_3430_USB3FS_PHY_MM3_TXEN_N,

	/* 34xx GPIO
	 *  - normally these are bidirectional, no internal pullup/pulldown
	 *  - "_UP" suffix (GPIO3_UP) if internal pullup is configured
	 *  - "_DOWN" suffix (GPIO3_DOWN) with internal pulldown
	 *  - "_OUT" suffix (GPIO3_OUT) for output-only pins (unlike 24xx)
	 */
	AF26_34XX_GPIO0,
	AF21_34XX_GPIO8,
	AF22_34XX_GPIO9,
	AG25_34XX_GPIO10,
	AB10_34XX_GPIO28_OUT,
	AH8_34XX_GPIO29,
	N4_34XX_GPIO34,
	M4_34XX_GPIO35,
	L4_34XX_GPIO36,
	K4_34XX_GPIO37,
	T3_34XX_GPIO38,
	R3_34XX_GPIO39,
	N3_34XX_GPIO40,
	M3_34XX_GPIO41,
	K3_34XX_GPIO43_OUT,
	V8_34XX_GPIO53_OUT,
	U8_34XX_GPIO54_OUT,
	U8_34XX_GPIO54_DOWN,
	T8_34XX_GPIO55,
	T8_34XX_GPIO55_OUT,
	R8_34XX_GPIO56_OUT,
	P8_34XX_GPIO57_OFF_LOW,
	P8_34XX_GPIO57,
	N8_34XX_GPIO58_OUT,
	T4_34XX_GPIO59_DOWN,
	L8_34XX_GPIO63,
	L8_34XX_GPIO63_OUT,
	J8_3430_GPIO65,
	G25_34XX_GPIO86_OUT,
	AC27_34XX_GPIO92,
	A24_34XX_GPIO94,
	C25_34XX_GPIO96,
	AG17_34XX_GPIO99,
	AH17_34XX_GPIO100,
	B24_34XX_GPIO101,
	B24_34XX_GPIO101_OUT,
	B25_34XX_GPIO109,
	B26_34XX_GPIO111,
	AG4_34XX_GPIO134_OUT,
	AE4_34XX_GPIO136_OUT,
	AH3_34XX_GPIO137_OUT,
	AF3_34XX_GPIO138_OUT,
	AE3_34XX_GPIO139_DOWN,
	AF6_34XX_GPIO140_UP,
	AE6_34XX_GPIO141_DOWN,
	AF5_34XX_GPIO142,
	AE5_34XX_GPIO143,
	AA21_34XX_GPIO157_OUT,
	W1_34XX_GPIO49_OUT,
	W21_34XX_GPIO162,
	H18_34XX_GPIO163,
	H19_34XX_GPIO164_OUT,
	B23_34XX_GPIO167,
	J25_34XX_GPIO170,
	AC3_34XX_GPIO175,
	AB1_34XX_GPIO176_OUT,
	AB2_34XX_GPIO177,
	W7_34XX_GPIO178_DOWN,
	T3_34XX_GPIO_179,
	Y3_34XX_GPIO180,
	Y4_34XX_GPIO181,
	AE22_34XX_GPIO186,
	AE22_34XX_GPIO186_OUT,

	/* MMC1 */
	N28_3430_MMC1_CLK,
	M27_3430_MMC1_CMD,
	N27_3430_MMC1_DAT0,
	N26_3430_MMC1_DAT1,
	N25_3430_MMC1_DAT2,
	P28_3430_MMC1_DAT3,
	P27_3430_MMC1_DAT4,
	P26_3430_MMC1_DAT5,
	R27_3430_MMC1_DAT6,
	R25_3430_MMC1_DAT7,

	/* MMC2 */
	AE2_3430_MMC2_CLK,
	AG5_3430_MMC2_CMD,
	AH5_3430_MMC2_DAT0,
	AH4_3430_MMC2_DAT1,
	AG4_3430_MMC2_DAT2,
	AF4_3430_MMC2_DAT3,
	AE4_3430_MMC2_DAT4,
	AH3_3430_MMC2_DAT5,
	AF3_3430_MMC2_DAT6,
	AE3_3430_MMC2_DAT7,

	/* MMC3 */
	AF10_3430_MMC3_CLK,
	AC3_3430_MMC3_CMD,
	AE11_3430_MMC3_DAT0,
	AH9_3430_MMC3_DAT1,
	AF13_3430_MMC3_DAT2,
	AE13_3430_MMC3_DAT3,

	/* UART1 */
	AA8_34XX_UART1_TX,
	Y8_34XX_UART1_RX,
	AA9_34XX_UART1_RTS,
	W8_34XX_UART1_CTS,

	/* McSPI */
	AB1_34XX_McSPI1_CS2,

	/* DSI */
	AG22_34XX_DSI_DX0,
	AH22_34XX_DSI_DY0,
	AG23_34XX_DSI_DX1,
	AH23_34XX_DSI_DY1,
	AG24_34XX_DSI_DX2,
	AH24_34XX_DSI_DY2,

	H16_34XX_SDRC_CKE0,
	H17_34XX_SDRC_CKE1,

	/* UART2 */
	AA25_34XX_UART2_TX,
	AD25_34XX_UART2_RX,
	AB25_34XX_UART2_RTS,
	AB26_34XX_UART2_CTS,
	
	AB26_34XX_GPIO144,
	
	/* McBSP */
	P21_OMAP34XX_MCBSP2_FSX,
	N21_OMAP34XX_MCBSP2_CLKX,
	R21_OMAP34XX_MCBSP2_DR,
	M21_OMAP34XX_MCBSP2_DX,
	K26_OMAP34XX_MCBSP3_FSX,
	W21_OMAP34XX_MCBSP3_CLKX,
	U21_OMAP34XX_MCBSP3_DR,
	V21_OMAP34XX_MCBSP3_DX,

	/* HDQ */
	J25_34XX_HDQ_SIO,

	/* Camera */
	A24_34XX_CAM_HS,
	A23_34XX_CAM_VS,
	C25_34XX_CAM_XCLKA,
	C27_34XX_CAM_PCLK,
	C23_34XX_CAM_FLD,
	AG17_34XX_CAM_D0,
	AH17_34XX_CAM_D1,
	B24_34XX_CAM_D2,
	C24_34XX_CAM_D3,
	D24_34XX_CAM_D4,
	A25_34XX_CAM_D5,
	K28_34XX_CAM_D6,
	L28_34XX_CAM_D7,
	K27_34XX_CAM_D8,
	L27_34XX_CAM_D9,
	B25_34XX_CAM_D10,
	C26_34XX_CAM_D11,
	B26_34XX_CAM_XCLKB,
	B23_34XX_CAM_WEN,
	D25_34XX_CAM_STROBE,
	K8_34XX_GPMC_WAIT2,

	/* SYS_NIRQ T2 INT1 */
	AF26_34XX_SYS_NIRQ,

	AE7_3430_GPIO24,
	AF7_3430_GPIO25_OUT,
	V3_3430_GPT08,
	AA3_3430_GPIO178,
	Y2_3430_GPIO179,

	AH7_3430_GPIO27,
	AG8_3430_GPIO28,
	AF9_3430_GPIO22,
	B25_3430_GPIO109,
	B26_3430_GPIO111,
	B26_3430_SAFE_UP,
	B26_3430_SAFE_DOWN,
	AG18_3430_GPIO114_UP,
	W21_3430_GPIO162,
	AH18_3430_GPIO115,

	AA8_3430_UART1_TX,
	AA9_3430_UART1_RTS,
	W8_3430_UART1_CTS,
	Y8_3430_UART1_RX,

	AE2_3430_SAFE,
	AG5_3430_SAFE,
	AH5_3430_SAFE,
	AH4_3430_SAFE,
	AG4_3430_SAFE,
	AF4_3430_SAFE,

	W21_3430_SAFE_PULLUP,
	W21_3430_SAFE_PULLDOWN,

	AG9_3430_GPIO23,
	AG7_3430_GPIO26,
	K8_3430_GPIO64,
	P26_3430_GPIO127,
	K26_3430_GPIO161,
	U21_3430_GPIO159,

	AA3_3430_MCSPI2_CLK,
	Y2_3430_MCSPI2_SIMO,
	Y3_3430_MCSPI2_SOMI,
	Y4_3430_MCSPI2_CS0,

	C26_3430_GPIO110,
	R25_3430_GPIO129,
	R27_3430_GPIO128,
	V21_3430_GPIO158,
	N8_3430_GPIO58_IN,
	
	/* Alternative MMC3_CMD on ETK_CTL pad */
	AE10_3430_MMC3_CMD,
	
	D25_34XX_GPIO126,
	R8_34XX_GPIO56_TRISTATE,
	
	/* Alternative DSS_DATA0 - DSS_DATA5 */
	H26_3630_DSS_DATA0,
	H25_3630_DSS_DATA1,
	E28_3630_DSS_DATA2,
	J26_3630_DSS_DATA3,
	AC27_3630_DSS_DATA4,
	AC28_3630_DSS_DATA5,
	
	/* Alternative DSS_DATA0 - DSS_DATA5 in safe mode -> pins not used for A28 */
	H26_3630_SAFE,
	H25_3630_SAFE,
	E28_3630_SAFE,
	J26_3630_SAFE,
	AC27_3630_SAFE,
	AC28_3630_SAFE,

	/* native dss data lines */
	AG22_3630_DSS_DATA0,
	AH22_3630_DSS_DATA1,
	AG23_3630_DSS_DATA2,
	AH23_3630_DSS_DATA3,
	AG24_3630_DSS_DATA4,
	AH24_3630_DSS_DATA5,

	/* DSS functions on default pins */
	D26_3630_DSS_HSYNC,
	D27_3630_DSS_VSYNC,
	D28_3630_DSS_PCLK,
	E27_3630_DSS_ACBIAS,
	E26_3630_DSS_DATA6,
	F28_3630_DSS_DATA7,
	F27_3630_DSS_DATA8,
	G26_3630_DSS_DATA9,
	AD28_3630_DSS_DATA10,
	AD27_3630_DSS_DATA11,
	AB28_3630_DSS_DATA12,
	AB27_3630_DSS_DATA13,
	AA28_3630_DSS_DATA14,
	AA27_3630_DSS_DATA15,
	G25_3630_DSS_DATA16,
	H27_3630_DSS_DATA17,
	
	/* DSS functions on sysboot pins */
	AH26_3630_DSS_DATA18,
	AG26_3630_DSS_DATA19,
	AF18_3630_DSS_DATA20,
	AF19_3630_DSS_DATA21,
	AE21_3630_DSS_DATA22,
	AF21_3630_DSS_DATA23,
	
	N8_3630_GPT08,
	N8_3630_GPT08_OFF_HIGH,
	AD25_3630_GPT08,
	AF11_3630_GPIO14,
	AH14_3630_GPIO21,
	T21_3630_GPIO160,
	Y21_3630_GPIO156,
	AG12_3630_GPIO15,
	AH12_3630_GPIO16,

	W13_3611_CLKOUT2,
	AE22_3430_CLKOUT2,

	N28_3630_GPIO120,
	M27_3430_GPIO121,
 	N27_3630_GPIO122,
	N26_3630_GPIO123,
	N25_3630_GPIO124,
	P28_3630_GPIO125,

	AF6_OMAP34XX_MCBSP3_DX,
	AE6_OMAP34XX_MCBSP3_DR,
	AF5_OMAP34XX_MCBSP3_CLX,
	AE5_OMAP34XX_MCBSP3_FSX,
	
	AD2_OMAP34XX_MCBSP4_DX,
	AD1_OMAP34XX_MCBSP4_DR,
	AE1_OMAP34XX_MCBSP4_CLX,
	AC1_OMAP34XX_MCBSP4_FSX,

	/* 3611 GPIO */
	N20_3611_GPIO157,

	V1_3611_GPIO49,
	D4_3611_GPT08,
	P4_3611_GPIO24,
	L2_3611_GPIO51,
	J22_3611_GPIO111,
	W6_3611_GPIO27,
	Y6_3611_GPIO28,
	T4_3611_GPIO22,
	H20_3611_GPIO96,
	W16_3611_GPIO114,
	U21_3611_GPIO156,
	Y16_3611_GPIO115,
	K2_3611_GPIO50,
	P3_3611_UART2_TX,
	R3_3611_UART2_RX,
	T1_3611_GPIO47,
	AA5_3611_GPIO25,
	AB5_3611_GPIO26,

	U3_3611_MCBSP3_DX,
	T3_3611_MCBSP3_DR,
	P3_3611_MCBSP3_CLK,
	R3_3611_MCBSP3_FSX,

	AA25_3630_GPIO146,
	AB25_3630_GPIO145,

	AG8_3430_USB2FS_RCV,
	AH8_3430_USB2FS_VM,
	AB2_3430_USB2FS_VP,
	V3_3430_USB2FS_EN,
	H20_3430_UART3_RX_IRRX,
	
	K26_OMAP34XX_GPIO161_OFF_IPU,
	Y3_3611_UART1_RX,
	AA2_3611_UART1_CTS,
	G25_3630_RFBI_TE,
	AB26_3630_GPT09,
	AB25_3630_GPT10,
	AD25_3630_GPIO147,

};

struct omap_mux_cfg {
	struct list_head	list;
	struct pin_config	*pins;
	unsigned long		size;
	unsigned int		legacy;
	int			(*cfg_reg)(const struct pin_config *cfg);
};

#ifdef	CONFIG_OMAP_MUX
/* setup pin muxing in Linux */
extern int omap1_mux_init(void);
extern int omap2_mux_init(void);
extern int omap_mux_register(struct omap_mux_cfg *);
extern int omap2_mux_register(struct omap_mux_cfg *);
extern int omap_cfg_reg(unsigned long reg_cfg);
extern int omap_mux_config(const char *group);
#else
/* boot loader does it all (no warnings from CONFIG_OMAP_MUX_WARNINGS) */
static inline int omap1_mux_init(void) { return 0; }
static inline int omap2_mux_init(void) { return 0; }
static inline int omap2_mux_register(struct omap_mux_cfg *) { return 0; }
static inline int omap_cfg_reg(unsigned long reg_cfg) { return 0; }
static inline int omap_mux_config(const char *group) { return 0; }
#endif

#endif
