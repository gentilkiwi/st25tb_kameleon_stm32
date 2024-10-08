/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "st25tb_target.h"

const uint8_t st25tb_ui8ChipId = 0x42;
const uint8_t ST25TB_TARGET_KIWI_SPECIAL_RETCODE_OK[] = {0xca, 0xfe, 0xba, 0xbe}, ST25TB_TARGET_KIWI_SPECIAL_RETCODE_KO[] = {0xde, 0xca, 0xfb, 0xad};

volatile tSt25TbState g_eCurrentTargetState;

void ST25TB_Target_ResetState()
{
    g_eCurrentTargetState = PowerOff;
}

uint8_t ST25TB_Target_AdjustIdxForSpecialAddr(uint8_t original)
{
    if(original == 0xff)
    {
        original = SLOTS_ST25TB_INDEX_SYSTEM;
    }

    return original;
}

tSt25TbState ST25TB_Target_StateMachine()
{
    uint8_t cbData = 0, idx, delay;
    const uint8_t *pcbData = 0;

    switch (g_eCurrentTargetState)
    {
    case PowerOff:
    case Ready:

        if ((g_ui8_cbST25TB_Buffer == 2) && (g_ui8_ST25TB_Buffer[0] == ST25TB_CMD_INITIATE))
        {
            g_eCurrentTargetState = Inventory;
            pcbData = &st25tb_ui8ChipId;
            cbData = sizeof(st25tb_ui8ChipId);
            delay = ST25TB_TARGET_DELAY_US_GLOBAL + ST25TB_TARGET_DELAY_US_MEDIUM;
        }
        else
        {
            g_eCurrentTargetState = Invalid;
        }

        break;

    case Inventory:
    case Deselected:

        if ((g_ui8_cbST25TB_Buffer == 2) && (g_ui8_ST25TB_Buffer[0] == ST25TB_CMD_SELECT))
        {
            if (g_ui8_ST25TB_Buffer[1] == st25tb_ui8ChipId)
            {
                g_eCurrentTargetState = Selected;
            }
            pcbData = &st25tb_ui8ChipId;
            cbData = sizeof(st25tb_ui8ChipId);
            delay = ST25TB_TARGET_DELAY_US_GLOBAL + ST25TB_TARGET_DELAY_US_MEDIUM;
        }
        else if ((g_ui8_cbST25TB_Buffer >= 1) && ((g_ui8_ST25TB_Buffer[0] & 0x0f) == ST25TB_CMD_SLOT_MARKER_MASK)) // Slot_marker() mask includes Initiate() and Pcall16()
        {
            pcbData = &st25tb_ui8ChipId;
            cbData = sizeof(st25tb_ui8ChipId);
            delay = ST25TB_TARGET_DELAY_US_GLOBAL + ST25TB_TARGET_DELAY_US_MEDIUM;
        }
        else
        {
            g_eCurrentTargetState = PowerOff;
        }

        break;

    case Selected:

        if (g_ui8_cbST25TB_Buffer == 1)
        {
            if (g_ui8_ST25TB_Buffer[0] == ST25TB_CMD_GET_UID)
            {
                pcbData = SLOTS_ST25TB_Current[SLOTS_ST25TB_INDEX_UID];
                cbData = 2 * sizeof(SLOTS_ST25TB_Current[0]);
                delay = ST25TB_TARGET_DELAY_US_GLOBAL;
            }
            else if (g_ui8_ST25TB_Buffer[0] == ST25TB_CMD_RESET_TO_INVENTORY)
            {
                g_eCurrentTargetState = Inventory;
            }
            else if (g_ui8_ST25TB_Buffer[0] == ST25TB_CMD_COMPLETION)
            {
                g_eCurrentTargetState = Deactivated;
            }
        }
        else if (g_ui8_cbST25TB_Buffer == 2)
        {
            if (g_ui8_ST25TB_Buffer[0] == ST25TB_CMD_READ_BLOCK)
            {
                idx = ST25TB_Target_AdjustIdxForSpecialAddr(g_ui8_ST25TB_Buffer[1]);
                if(idx < SLOTS_ST25TB_SECTORS_INTERNAL)
                {
                    pcbData = SLOTS_ST25TB_Current[idx];
                    cbData = sizeof(SLOTS_ST25TB_Current[0]);
                    delay = ST25TB_TARGET_DELAY_US_GLOBAL + ST25TB_TARGET_DELAY_US_SMALL;
                }
            }
        }
        else if ((g_ui8_cbST25TB_Buffer == 6) && (g_ui8_ST25TB_Buffer[0] == ST25TB_CMD_WRITE_BLOCK))
        {
            idx = ST25TB_Target_AdjustIdxForSpecialAddr(g_ui8_ST25TB_Buffer[1]);
            if(idx < SLOTS_ST25TB_SECTORS_INTERNAL)
            {
                *(uint32_t *) SLOTS_ST25TB_Current[idx] = *(uint32_t *) (g_ui8_ST25TB_Buffer + 2);
            }
            else if(idx == 0xfe)
            {
                SLOTS_Save_Current(); // maybe move at the end for Flash operation ? (slow, even if ret is not really needed)
                pcbData = ST25TB_TARGET_KIWI_SPECIAL_RETCODE_OK;
                cbData = sizeof(ST25TB_TARGET_KIWI_SPECIAL_RETCODE_OK);
                delay = ST25TB_TARGET_DELAY_US_GLOBAL;
            }
        }

        break;

    case Deactivated:
    default:

        g_eCurrentTargetState = PowerOff;

        break;
    }

    if (pcbData && cbData)
    {
        TIMER_delay_Microseconds(delay);
        if(!ST25TB_Send(pcbData, cbData))
        {
            g_eCurrentTargetState = Invalid;
        }
    }
    else if(g_eCurrentTargetState != Invalid)
    {
        TRF7970A_SPI_DirectCommand(TRF79X0_STOP_DECODERS_CMD);
        TRF7970A_SPI_DirectCommand(TRF79X0_RUN_DECODERS_CMD);
    }

    return g_eCurrentTargetState;
}
