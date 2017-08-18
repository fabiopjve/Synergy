#include "new_thread0.h"
#include "hal_data.h"
#include "glcdInit.h"
#include "glcdPrimitives.h"

extern TX_THREAD new_thread1;
extern TX_MUTEX glcdMutex;

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
    tx_thread_resume(&new_thread1);
    while (1)
    {
        for (px = 0; px<240; px+=8) {
            // by using Mutex we can overcome the problem of sharing glcd_printCharXY_TEST
            // between the two threads!
            tx_mutex_get(&glcdMutex,TX_WAIT_FOREVER);
            glcd_setForegroundColor(clGREEN);
            glcd_printCharXY_TEST(px,20,'O');
            tx_mutex_put(&glcdMutex);
        }
        for (px = 0; px<240; px+=8) {
            tx_mutex_get(&glcdMutex,TX_WAIT_FOREVER);
            glcd_setForegroundColor(clGREEN);
            glcd_printCharXY_TEST(px,20,'.');
            tx_mutex_put(&glcdMutex);
        }
    }
}
