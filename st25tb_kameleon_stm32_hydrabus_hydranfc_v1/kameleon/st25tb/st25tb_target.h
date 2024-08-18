/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "st25tb.h"

typedef enum __attribute__((__packed__)) _tSt25TbState {
    Invalid,
    PowerOff,
    Ready,
    Inventory,
    Selected,
    Deselected,
    Deactivated,
} tSt25TbState;

void ST25TB_Target_ResetState();
tSt25TbState ST25TB_Target_StateMachine();

/*
 * SRT512
 *  t0 Antenna reversal delay 128/fS  151 µs
 *  t1 Synchronization delay          151 µs
 *  t2 Answer to new request delay >= 132 µs
 *
 * ST25TB512-AT
 *  t0 Antenna reversal delay 128/fS  159 µs
 *  t1 Synchronization delay          151 µs
 *  t2 Answer to new request delay >= 132 µs
 *
 *  -> focus on t0 <= 160 �s ?
 */
#if !defined(DEBUG)
#define ST25TB_TARGET_DELAY_US_GLOBAL  102
#define ST25TB_TARGET_DELAY_US_MEDIUM  7
#define ST25TB_TARGET_DELAY_US_SMALL   2
#else
#define ST25TB_TARGET_DELAY_US_GLOBAL  83
#define ST25TB_TARGET_DELAY_US_MEDIUM  8
#define ST25TB_TARGET_DELAY_US_SMALL   2
#endif
