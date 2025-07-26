/** HL_sys_main.c – LED’leri sırayla yak (125 ms) – saf delay */
/* Generates code‑safe user sections only */

#include "HL_sys_common.h"
/* USER CODE BEGIN (0) */
#include "HL_het.h"
#include "HL_gio.h"
/* USER CODE END */

/* USER CODE BEGIN (1) */
/* Yakılacak NHET1 pinleri */
#define LED_COUNT 8U
static const uint32 ledPins[LED_COUNT] = {0U, 5U, 17U, 18U, 25U, 27U, 29U, 31U};
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    uint32 i;           /* C90 döngü değişkeni      */
    uint32 ledIndex = 0;

    hetInit();          /* NHET modülü başlat */

    /* LED pinlerini çıkış yap */
    gioSetDirection(hetPORT1,
        (1U << 0)  | (1U << 5)  | (1U << 17) | (1U << 18) |
        (1U << 25) | (1U << 27) | (1U << 29) | (1U << 31));

    /* Sonsuz döngü: sırayla yak‑söndür */
    while (1)
    {
        /* Tüm LED’leri kapat */
        for (i = 0U; i < LED_COUNT; i++)
        {
            gioSetBit(hetPORT1, ledPins[i], 0U);
        }

        /* Aktif LED’i yak */
        gioSetBit(hetPORT1, ledPins[ledIndex], 1U);

        /* 125 ms kaba gecikme (150 MHz CPU için yaklaşık) */
        for (i = 0U; i < 18U * 100000U; i++)  /* 18*10^5 döngü ≈125 ms */
        {
            __asm(" nop");
        }

        /* Sonraki LED */
        ledIndex++;
        if (ledIndex >= LED_COUNT)
        {
            ledIndex = 0U;
        }
    }
/* USER CODE END */
    return 0;
}