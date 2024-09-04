/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../USB_DEVICE/App/usbd_cdc_if.h"
#include "../Core/Inc/main.h"

#include "slots.h"
#include "references.h"
#include "leds.h"
#include "trf7970a.h"

extern volatile bool g_irq_TA0, g_irq_SW1, g_irq_SW2, g_irq_TRF;

extern SPI_HandleTypeDef hspi2;
extern TIM_HandleTypeDef htim6;
extern RNG_HandleTypeDef hrng;

#define SPI_INTERNAL_HANDLE		(&hspi2)
#define TIMER_INTERNAL_HANDLE	(&htim6)

#define RAND_Generate() HAL_RNG_GetRandomNumber(&hrng) //rand()

#define TIMER_stop()                      	HAL_TIM_Base_Stop_IT(TIMER_INTERNAL_HANDLE)
#define TIMER_delay_Milliseconds(n_ms)      TIMER_delay_Milliseconds_internal(n_ms * 100)
#define TIMER_start_Milliseconds(n_ms)  	TIMER_start_Milliseconds_internal(n_ms * 100)
#define TIMER_delay_Microseconds(n_us)      TIMER_delay_Microseconds_internal(n_us * 84)

void TIMER_delay_Milliseconds_internal(uint16_t n_unit_ms);
void TIMER_start_Milliseconds_internal(uint16_t n_unit_ms);
void TIMER_delay_Microseconds_internal(uint16_t n_unit_us);

#define IRQ_SOURCE_NONE                 0x00
#define IRQ_SOURCE_TRF7970A             0x01
#define IRQ_SOURCE_SW1                  0x02
#define IRQ_SOURCE_SW2                  0x04
#define IRQ_SOURCE_TIMER                0x08
#define IRQ_SOURCE_ST25TB_PROTOCOL_ERR  0x10

uint8_t IRQ_Wait_for_SW1();
uint8_t IRQ_Wait_for_SW1_or_SW2();
uint8_t IRQ_Wait_for_SW1_or_SW2_or_TRF(uint8_t *pTRF7970A_irqStatus);
uint8_t IRQ_Wait_for_SW1_or_TRF(uint8_t *pTRF7970A_irqStatus);
uint8_t IRQ_Wait_for_SW1_or_SW2_or_Timeout(uint16_t timeout_ms);
uint8_t IRQ_Wait_for_SW1_or_SW2_or_TRF_or_Timeout(uint8_t *pTRF7970A_irqStatus, uint16_t timeout_ms);

#define count_of(a) (sizeof(a)/sizeof((a)[0]))

//#define __low_power_mode_0              tight_loop_contents
#define __no_operation()                __asm__("nop")
//extern int __flash_binary_start, __flash_binary_end;
