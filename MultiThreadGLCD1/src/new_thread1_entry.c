#include "new_thread1.h"
#include "hal_data.h"
#include "glcdInit.h"
#include "glcdPrimitives.h"

/* New Thread entry function */
void new_thread1_entry(void)
{
    /* TODO: add your own code here */
    uint8_t px = 0;
    while (1)
    {
        for (px = 0; px<240; px+=8) {
            glcd_setForegroundColor(clRED);
            glcd_printCharXY_TEST(px,60,'X');
        }
        for (px = 0; px<240; px+=8) {
            glcd_setForegroundColor(clRED);
            glcd_printCharXY_TEST(px,60,' ');
        }
    }
}
