#include "red_thread.h"

/* Red Thread entry function */
void red_thread_entry(void)
{
    /* LED type structure */
    bsp_leds_t leds;
    /* Get LED information for this board */
    R_BSP_LedsGet(&leds);
    while (1)
    {
        g_ioport.p_api->pinWrite(leds.p_leds[1], IOPORT_LEVEL_LOW);
        tx_thread_sleep(100);
        g_ioport.p_api->pinWrite(leds.p_leds[1], IOPORT_LEVEL_HIGH);
        tx_thread_sleep(100);
    }
}
