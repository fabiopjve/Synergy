/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2017 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/**********************************************************************************************************************
 * File Name    : lcd_setup.c
 * Description  : Definition for the SK-S7 LCD Panel setup function through SPI interface
 ***********************************************************************************************************************/

#include "lcd_setup.h"
#include <string.h>

static spi_instance_t * p_spi;
static spi_cfg_t      g_lcd_spi_alt_cfg;
static uint8_t        spi_flag;

void                  g_lcd_spi_callback (spi_callback_args_t * p_args);

static ssp_err_t      lcd_write (uint8_t cmd, uint8_t * data, uint32_t len);

static ssp_err_t      lcd_read (uint8_t cmd, uint8_t * data, uint32_t len);

void g_lcd_spi_callback (spi_callback_args_t * p_args)
{
    if (SPI_EVENT_TRANSFER_COMPLETE == p_args->event)
    {
        spi_flag = 1;
    }
}

ssp_err_t ILI9341V_Init (const spi_instance_t * p_spi_instance)
{
    ssp_err_t err;
    uint8_t   data[8];
    int       i;

    p_spi = (spi_instance_t *) p_spi_instance;
    memcpy(&g_lcd_spi_alt_cfg, p_spi->p_cfg, sizeof(spi_cfg_t));

    g_lcd_spi_alt_cfg.p_callback = &g_lcd_spi_callback;

    // Initialize SPI/I2C Communication
    err                          = p_spi->p_api->open(p_spi->p_ctrl, &g_lcd_spi_alt_cfg);

    g_ioport.p_api->pinWrite(LCD_CS, IOPORT_LEVEL_HIGH);
    g_ioport.p_api->pinWrite(LCD_RESET, IOPORT_LEVEL_HIGH);
    g_ioport.p_api->pinWrite(LCD_RESET, IOPORT_LEVEL_LOW);
    R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);
    g_ioport.p_api->pinWrite(LCD_RESET, IOPORT_LEVEL_HIGH);

    lcd_write(ILI9341_SW_RESET, (uint8_t *) "\x0", 0);
    R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);
    for (i = 0; i < 4; i++)
    {
        data[0] = (uint8_t) (0x10 + i);
        lcd_write(0xD9, data, 1);
        lcd_read(0xD3, data, 1);
    }

    err = lcd_write(ILI9341_POWERB,        (uint8_t *) "\x00\xC1\x30", 3);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    err = lcd_write(ILI9341_DTCA,          (uint8_t *) "\x85\x00\x78", 3);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    err = lcd_write(ILI9341_DTCB,          (uint8_t *) "\x00\x00", 2);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    err = lcd_write(ILI9341_POWERA,        (uint8_t *) "\x39\x2C\x00\x34\x02", 5);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    err = lcd_write(ILI9341_POWER_SEQ,     (uint8_t *) "\x64\x03\x12\x81", 4);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    err = lcd_write(ILI9341_PRC,           (uint8_t *) "\x20", 1);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    err = lcd_write(ILI9341_POWER1,        (uint8_t *) "\x23", 1);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    err = lcd_write(ILI9341_POWER2,        (uint8_t *) "\x10", 1);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    err = lcd_write(ILI9341_VCOM1,         (uint8_t *) "\x3E\x28", 2);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    err = lcd_write(ILI9341_VCOM2,         (uint8_t *) "\x86", 1);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    err = lcd_write(ILI9341_MAC,           (uint8_t *) "\x48", 1);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    err = lcd_write(ILI9341_PIXEL_FORMAT,  (uint8_t *) "\x55", 1);          /* DPI[101]: RGB 16 bits/pixel; DBI[101] MCU
                                                                             * 16 bit/pixel */
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    err = lcd_write(ILI9341_FRM_CTRL1,     (uint8_t *) "\x00\x18", 2);      /* 79 kHz */
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    err = lcd_write(ILI9341_DFC,           (uint8_t *) "\x08\x82\x27", 3);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    err = lcd_write(ILI9341_3GAMMA_EN,     (uint8_t *) "\x00", 1);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    err = lcd_write(ILI9341_RGB_INTERFACE, (uint8_t *) "\xC2", 1);          /* ByPass_Mode =1; RCM[1:0] = 10; VSPL=0;
                                                                             * HSPL = 0; DPL=1; EPL=0 */
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    err = lcd_write(ILI9341_INTERFACE,     (uint8_t *) "\x01\x00\x06", 3);  /* DE pol - high active, DOTCLK Pol = 1 data
                                                                             * latch on falling, HSYNC Pol - High level
                                                                             * Sync, Vsync Low level sync */
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    err = lcd_write(ILI9341_COLUMN_ADDR,   (uint8_t *) "\x00\x00\x00\xEF", 4);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    err = lcd_write(ILI9341_PAGE_ADDR,     (uint8_t *) "\x00\x00\x01\x3F", 4);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    err = lcd_write(ILI9341_GAMMA,         (uint8_t *) "\x01", 1);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    err = lcd_write(ILI9341_PGAMMA,
                    (uint8_t *) "\x0F\x31\x2B\x0C\x0E\x08\x4E\xF1\x37\x07\x10\x03\x0E\x09\x00",
                    15);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    err = lcd_write(ILI9341_NGAMMA,
                    (uint8_t *) "\x00\x0E\x14\x03\x11\x07\x31\xC1\x48\x08\x0F\x0C\x31\x36\x0F",
                    15);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    err = lcd_write(ILI9341_SLEEP_OUT,     (uint8_t *) "\x00", 1);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    R_BSP_SoftwareDelay(20, BSP_DELAY_UNITS_MILLISECONDS);
    err = lcd_write(ILI9341_DISP_ON,       (uint8_t *) "\x00", 1);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    err = lcd_read(ILI9341_READ_DISP_PIXEL, data, 1);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    return SSP_SUCCESS;
}

static ssp_err_t lcd_write (uint8_t cmd, uint8_t * data, uint32_t len)
{
    ssp_err_t err;

    g_ioport.p_api->pinWrite(LCD_CMD, IOPORT_LEVEL_LOW);
    g_ioport.p_api->pinWrite(LCD_CS, IOPORT_LEVEL_LOW);

    err = p_spi->p_api->write(p_spi->p_ctrl, &cmd, 1, SPI_BIT_WIDTH_8_BITS);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    while (!spi_flag)
    {
        R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);
    }

    spi_flag = 0;

    if (len)
    {
        g_ioport.p_api->pinWrite(LCD_CMD, IOPORT_LEVEL_HIGH);

        err = p_spi->p_api->write(p_spi->p_ctrl, data, len, SPI_BIT_WIDTH_8_BITS);
        if (SSP_SUCCESS != err)
        {
            return err;
        }

        while (!spi_flag)
        {
            R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);
        }

        spi_flag = 0;
    }

    g_ioport.p_api->pinWrite(LCD_CS, IOPORT_LEVEL_HIGH);

    return SSP_SUCCESS;
}

static ssp_err_t lcd_read (uint8_t cmd, uint8_t * data, uint32_t len)
{
    ssp_err_t      err;
    static uint8_t dummy_write[] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    g_ioport.p_api->pinWrite(LCD_CMD, IOPORT_LEVEL_LOW);
    g_ioport.p_api->pinWrite(LCD_CS, IOPORT_LEVEL_LOW);

    err = p_spi->p_api->write(p_spi->p_ctrl, &cmd, 1, SPI_BIT_WIDTH_8_BITS);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    while (!spi_flag)
    {
        R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);
    }

    spi_flag = 0;

    g_ioport.p_api->pinWrite(LCD_CMD, IOPORT_LEVEL_HIGH);
    g_ioport.p_api->pinCfg(IOPORT_PORT_01_PIN_02,
                           ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT |
                            ((uint32_t) (p_spi->p_cfg->clk_polarity ==
                                         SPI_CLK_POLARITY_HIGH) ? IOPORT_LEVEL_LOW : IOPORT_LEVEL_HIGH)));
    R_BSP_SoftwareDelay(5, BSP_DELAY_UNITS_MICROSECONDS);
    g_ioport.p_api->pinCfg(IOPORT_PORT_01_PIN_02,
                           ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_SCI0_2_4_6_8));

    err = p_spi->p_api->writeRead(p_spi->p_ctrl, dummy_write, data, len, SPI_BIT_WIDTH_8_BITS);
    if (SSP_SUCCESS != err)
    {
        return err;
    }

    while (!spi_flag)
    {
        R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);
    }

    spi_flag = 0;
    g_ioport.p_api->pinWrite(LCD_CS, IOPORT_LEVEL_HIGH);

    return SSP_SUCCESS;
}
