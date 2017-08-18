#include "new_thread0.h"
#include "hal_data.h"
#include "glcdInit.h"
#include "glcdPrimitives.h"

extern TX_THREAD new_thread1;

/* New Thread entry function */
void new_thread0_entry(void)
{
    uint8_t px = 0;
    glcd_init();
    glcd_setFrameBuffer((uint16_t*)&g_display_fb_background[0]);
    glcd_fillScreen(clBLACK);
    glcd_setFont(BigFont);
    glcd_printStringXY(30,0,"Two threads");
    glcd_setFont(SmallFont);
    // by sharing glcd_printCharXY_TEST (a function with static variables) we
    // can see artifacts on display due to data corruption (both threads use
    // the same resource without any control
    tx_thread_resume(&new_thread1);
    while (1)
    {
        for (px = 0; px<240; px+=8) {
            glcd_setForegroundColor(clGREEN);
            glcd_printCharXY_TEST(px,20,'O');
        }
        for (px = 0; px<240; px+=8) {
            glcd_setForegroundColor(clGREEN);
            glcd_printCharXY_TEST(px,20,'.');
        }
    }
}
