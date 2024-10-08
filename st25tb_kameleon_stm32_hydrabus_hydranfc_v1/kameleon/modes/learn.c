/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "learn.h"

void MODE_learn()
{
    uint8_t BP_IrqSource, index = FlashStoredData.CurrentSlot;
    bool bNeedToReload = false;

    ST25TB_TRF7970A_Mode(true);
    do
    {
        BP_IrqSource = IRQ_Wait_for_SW1_or_SW2_or_Timeout(ST25TB_INITIATOR_DELAY_BEFORE_RETRY);
        if(BP_IrqSource & IRQ_SOURCE_TIMER)
        {
            LED_ON(LED_INDEX_STATUS_RED);
            BP_IrqSource = ST25TB_Initiator_Read_Card();
            LED_OFF(LED_INDEX_STATUS_RED);

            if(BP_IrqSource == IRQ_SOURCE_NONE)
            {
                //LED_OFF(LED_INDEX_STATUS_RED); IMPLICIT
                SLOTS_Save(index);
                LED_ON(LED_INDEX_STATUS_GREEN);

                BP_IrqSource = IRQ_Wait_for_SW1_or_SW2();
                bNeedToReload = false;
            }
            else if(BP_IrqSource & (IRQ_SOURCE_TRF7970A | IRQ_SOURCE_ST25TB_PROTOCOL_ERR))
            {
                LED_ON(LED_INDEX_STATUS_RED);
                bNeedToReload = true;
            }
        }

        if(BP_IrqSource & IRQ_SOURCE_SW2)
        {
            LEDS_STATUS_Bitmask(0b00);
            index++;
            if(index >= SLOTS_ST25TB_COUNT)
            {
                index = 0;
            }
            SLOTS_Change(index);
            bNeedToReload = false;
        }
    }
    while (!(BP_IrqSource & IRQ_SOURCE_SW1));

    if(bNeedToReload)
    {
        SLOTS_Load_Current();
    }
}
