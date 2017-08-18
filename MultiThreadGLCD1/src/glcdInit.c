/*
 * glcdInit.c
 *
 *  Created on: 08/15/2017
 *      Author: Fabio Pereira
 */
#include "hal_data.h"
#include "lcd_setup/lcd_setup.h"
#include "glcdInit.h"

void glcd_init(void){
    ssp_err_t err;
    // Configure LCD controller registers
    // Setup the ILI9341V
    err = ILI9341V_Init(&g_lcd_spi);
    if (err){
        while (1);
    }
    // Initialize the Display Driver
    err = g_display.p_api->open(g_display.p_ctrl, g_display.p_cfg);
    if (SSP_SUCCESS != err){
        while (1);
    }
    // Start displaying the content
    err = g_display.p_api->start(g_display.p_ctrl);
    if (SSP_SUCCESS != err){
        while (1);
    }
}


