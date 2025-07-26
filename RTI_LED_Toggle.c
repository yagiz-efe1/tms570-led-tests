/** @file HL_sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   RTI interrupt ile 8 LED toggle eden switch-case yapılı örnek.
*/

#include "HL_sys_common.h"
/* USER CODE BEGIN (0) */
#include "HL_rti.h"
#include "HL_het.h"
#include "HL_gio.h"
/* USER CODE END */

/* USER CODE BEGIN (1) */
bool RTI_COMP0_FLAG = FALSE;
int toggleMode = 0;
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */

    rtiInit();          // RTI modülünü başlat
    hetInit();          // NHET portlarını başlat
    gioSetDirection(hetPORT1, 0xFFFFFFFF); // HET1 pinlerini output yap

    // Açılışta LED'leri yak
    gioSetBit(hetPORT1, 0, 1);
    gioSetBit(hetPORT1, 5, 1);
    gioSetBit(hetPORT1, 17, 1);
    gioSetBit(hetPORT1, 18, 1);
    gioSetBit(hetPORT1, 25, 1);
    gioSetBit(hetPORT1, 27, 1);
    gioSetBit(hetPORT1, 29, 1);
    gioSetBit(hetPORT1, 31, 1);

    rtiEnableNotification(rtiREG1, rtiNOTIFICATION_COMPARE0);
    _enable_IRQ();
    rtiStartCounter(rtiREG1, rtiCOUNTER_BLOCK0);

    while(1)
    {
        if(RTI_COMP0_FLAG == TRUE)
        {
            RTI_COMP0_FLAG = FALSE;

            switch(toggleMode)
            {
                /* USER CODE BEGIN (case-toggle) */
                case 0:
                    gioToggleBit(hetPORT1, 0);
                    gioToggleBit(hetPORT1, 5);
                    gioToggleBit(hetPORT1, 17);
                    gioToggleBit(hetPORT1, 18);
                    gioToggleBit(hetPORT1, 25);
                    gioToggleBit(hetPORT1, 27);
                    gioToggleBit(hetPORT1, 29);
                    gioToggleBit(hetPORT1, 31);
                    break;
                /* USER CODE END */

                default:
                    break;
            }
        }
    }

/* USER CODE END */
    return 0;
}

/* USER CODE BEGIN (4) */
void rtiNotification(rtiBASE_t *rtiREG, uint32 notification)
{
    if(notification == rtiNOTIFICATION_COMPARE0)
    {
        RTI_COMP0_FLAG = TRUE;
    }
}
/* USER CODE END */