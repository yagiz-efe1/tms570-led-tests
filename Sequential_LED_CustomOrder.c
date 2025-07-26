/** @file HL_sys_main.c
 *  @brief Sequential LED demo (custom order, 1 s delay)
 */

#include "HL_sys_common.h"
/* USER CODE BEGIN (0) */
#include "HL_het.h"
#include "HL_gio.h"
/* USER CODE END */

/* USER CODE BEGIN (1) */
/* İstenen sıra: D7, D8, LED1, D3, D4, D5, LED2, D6
 * Pin eşleşmeleri:
 *   D7   → NHET1[18]
 *   D8   → NHET1[29]
 *   LED1 → NHET1[27]
 *   D3   → NHET1[17]
 *   D4   → NHET1[31]
 *   D5   → NHET1[0]
 *   LED2 → NHET1[5]
 *   D6   → NHET1[25]
 */
#define LED_COUNT 8U
static const uint32 ledPins[LED_COUNT] = {18U, 29U, 27U, 17U, 31U, 0U, 5U, 25U};
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    uint32 i;
    uint32 ledIndex = 0U;

    hetInit();

    /* İlgili NHET1 pinlerini çıkış yap */
    gioSetDirection(hetPORT1,
        (1U << 0)  | (1U << 5)  | (1U << 17) | (1U << 18) |
        (1U << 25) | (1U << 27) | (1U << 29) | (1U << 31));

    while (1)
    {
        /* Tüm LED’leri kapat */
        for (i = 0U; i < LED_COUNT; i++)
        {
            gioSetBit(hetPORT1, ledPins[i], 0U);
        }

        /* Seçili LED’i yak */
        gioSetBit(hetPORT1, ledPins[ledIndex], 1U);

        /* ≈1 s gecikme (150 MHz CPU ≈ 15 000 000 NOP) */
        for (i = 0U; i < 15000000U; i++)
        {
            __asm(" nop");
        }

        /* Sonraki LED’e geç */
        ledIndex++;
        if (ledIndex >= LED_COUNT)
        {
            ledIndex = 0U;
        }
    }
/* USER CODE END */
    return 0;
}