/***********************************************************************************************************************
* File Name    : blinky_thread_entry.c
* Description  : This is a very simple example application that blinks all the LEDs on a board.
***********************************************************************************************************************/

#include "blinky_thread.h"

/*******************************************************************************************************************//**
 * @brief  Blinky example application
 *
 * Blinks all leds at a rate of 1 second using the the threadx sleep function.
 * Only references two other modules including the BSP, IOPORT.
 *
 **********************************************************************************************************************/
void blinky_thread_entry(void)
{
    /* LED type structure */
    bsp_leds_t leds;
    /* Get LED information for this board */
    R_BSP_LedsGet(&leds);
    while (1)
    {
        //g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_LOW);
        g_ioport.p_api->pinWrite(leds.p_leds[0], IOPORT_LEVEL_LOW);
        tx_thread_sleep (100);
        //g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_HIGH);
        g_ioport.p_api->pinWrite(leds.p_leds[0], IOPORT_LEVEL_HIGH);
        tx_thread_sleep (100);
    }
}
