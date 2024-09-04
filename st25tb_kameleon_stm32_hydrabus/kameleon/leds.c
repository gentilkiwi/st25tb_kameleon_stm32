/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "leds.h"

const LED LEDS[] = {
    // LEDS_MODES
    /* 0 */ {LED_MOD_EMULATE_GPIO_Port, LED_MOD_EMULATE_Pin},
    /* 1 */ {LED_MOD_REWRITE_GPIO_Port, LED_MOD_REWRITE_Pin},
    /* 2 */ {LED_MOD_DETECT_GPIO_Port, LED_MOD_DETECT_Pin},
    /* 3 */ {LED_MOD_LEARN_GPIO_Port, LED_MOD_LEARN_Pin},
    /* 4 */ {LED_MOD_UNK_GPIO_Port, LED_MOD_UNK_Pin},
    // LEDS_SLOTS
    /* 0 */ {LED_SLOT0_GPIO_Port, LED_SLOT0_Pin},
    /* 1 */ {LED_SLOT1_GPIO_Port, LED_SLOT1_Pin},
    /* 2 */ {LED_SLOT2_GPIO_Port, LED_SLOT2_Pin},
    /* 3 */ {LED_SLOT3_GPIO_Port, LED_SLOT3_Pin},
    /* 4 */ {LED_SLOT4_GPIO_Port, LED_SLOT4_Pin},
    /* 5 */ {LED_SLOT5_GPIO_Port, LED_SLOT5_Pin},
    /* 6 */ {LED_SLOT6_GPIO_Port, LED_SLOT6_Pin},
    /* 7 */ {LED_SLOT7_GPIO_Port, LED_SLOT7_Pin},
    // LEDS_STATUS
    /* 0 */ {LED_STATUS_BLUE_GPIO_Port, LED_STATUS_BLUE_Pin},
    /* 1 */ {LED_STATUS_GREEN_GPIO_Port, LED_STATUS_GREEN_Pin},
    /* 2 */ {LED_STATUS_RED_GPIO_Port, LED_STATUS_RED_Pin},
};

void LEDS_Bitmask(const LED *LEDS_ARRAY, const uint8_t nbLeds, uint8_t bitmask)
{
    uint8_t i;

    for(i = 0; i < nbLeds; i++, bitmask >>= 1)
    {
    	HAL_GPIO_WritePin(LEDS_ARRAY[i].portOutput, LEDS_ARRAY[i].bit, bitmask & 0b00000001);
    }
}

void LEDS_Animation()
{
    uint8_t i;

    for(i = 0; i < count_of(LEDS); i++)
    {
        LED_ON(i);
        TIMER_delay_Milliseconds(10);
        LED_OFF(i);
    }
}
