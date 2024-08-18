/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "board.h"

typedef void (* PMODE_FUNCTION) ();
typedef struct _KAMELEON_MODE {
    const PMODE_FUNCTION function;
    const uint8_t ledsModesBitmask;
    const char* Name;
    const char* Description;
} KAMELEON_MODE, *PKAMELEON_MODE;

#include "st25tb/st25tb.h"

#include "modes/emulate.h"
#include "modes/rewrite.h"
#include "modes/learn.h"
