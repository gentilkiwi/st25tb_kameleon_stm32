/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "leds.h"

const LED LEDS[] = {
    // LEDS_MODES
    /* 0 */ {D2_GPIO_Port, D2_Pin}, // LED_MOD_EMULATE
    /* 1 */ {D3_GPIO_Port, D3_Pin}, // LED_MOD_REWRITE
    /* 2 */ {D4_GPIO_Port, D4_Pin}, // LED_MOD_LEARN
    // LEDS_STATUS
    /* 0 */ {ULED1_GPIO_Port, ULED1_Pin}, // LED_STATUS_GREEN
    /* 1 */ {D5_GPIO_Port, D5_Pin}, // LED_STATUS_RED
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
