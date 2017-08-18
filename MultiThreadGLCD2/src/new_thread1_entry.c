#include "new_thread1.h"
#include "hal_data.h"
#include "glcdInit.h"
#include "glcdPrimitives.h"

extern TX_MUTEX glcdMutex;

/* New Thread entry function */
void new_thread1_entry(void)
{
    /* TODO: add your own code here */
    uint8_t px = 0;
    while (1)
    {
        for (px = 0; px<240; px+=8) {
            tx_mutex_get(&glcdMutex,TX_WAIT_FOREVER);
            glcd_setForegroundColor(clRED);
            glcd_printCharXY_TEST(px,60,'X');
            tx_mutex_put(&glcdMutex);
        }
        for (px = 0; px<240; px+=8) {
            tx_mutex_get(&glcdMutex,TX_WAIT_FOREVER);
            glcd_setForegroundColor(clRED);
            glcd_printCharXY_TEST(px,60,' ');
            tx_mutex_put(&glcdMutex);
        }
    }
}
