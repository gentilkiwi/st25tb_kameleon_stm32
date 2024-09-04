/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "board.h"

volatile bool g_irq_TA0, g_irq_SW1, g_irq_SW2, g_irq_TRF;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin)
	{
	case TRF_IRQ_Pin:
		g_irq_TRF = true;
		break;
	case K1_Pin:
		g_irq_SW1 = true;
		break;
	case UBTN_Pin:
		g_irq_SW2 = true;
		break;
	/*
	 * No K3 nor K4
	 */
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIMER_INTERNAL_HANDLE->Instance)
	{
		TIMER_stop();
		g_irq_TA0 = true;
	}
}

void TIMER_delay_Milliseconds_internal(uint16_t n_unit_ms) {
	__HAL_TIM_SET_AUTORELOAD(TIMER_INTERNAL_HANDLE, n_unit_ms);
	__HAL_TIM_SET_PRESCALER(TIMER_INTERNAL_HANDLE, 839);
	TIMER_INTERNAL_HANDLE->Instance->EGR = TIM_EGR_UG;
	CLEAR_BIT(TIMER_INTERNAL_HANDLE->Instance->SR, TIM_FLAG_UPDATE); // even TIM_Base_SetConfig needed it
	g_irq_TA0 = false;
	if (HAL_TIM_Base_Start_IT(TIMER_INTERNAL_HANDLE) == HAL_OK) {
		while (!g_irq_TA0)
			;
	} else {
		Error_Handler();
	}
}

void TIMER_start_Milliseconds_internal(uint16_t n_unit_ms) {
	__HAL_TIM_SET_AUTORELOAD(TIMER_INTERNAL_HANDLE, n_unit_ms);
	__HAL_TIM_SET_PRESCALER(TIMER_INTERNAL_HANDLE, 839);
	TIMER_INTERNAL_HANDLE->Instance->EGR = TIM_EGR_UG;
	CLEAR_BIT(TIMER_INTERNAL_HANDLE->Instance->SR, TIM_FLAG_UPDATE); // even TIM_Base_SetConfig needed it
	g_irq_TA0 = false;
	if (HAL_TIM_Base_Start_IT(TIMER_INTERNAL_HANDLE) == HAL_OK) {

	} else {
		Error_Handler();
	}
}

void TIMER_delay_Microseconds_internal(uint16_t n_unit_us) {
	__HAL_TIM_SET_AUTORELOAD(TIMER_INTERNAL_HANDLE, n_unit_us);
	__HAL_TIM_SET_PRESCALER(TIMER_INTERNAL_HANDLE, 0);
	TIMER_INTERNAL_HANDLE->Instance->EGR = TIM_EGR_UG;
	CLEAR_BIT(TIMER_INTERNAL_HANDLE->Instance->SR, TIM_FLAG_UPDATE); // even TIM_Base_SetConfig needed it after, too fast ?
	g_irq_TA0 = false;
	if (HAL_TIM_Base_Start_IT(TIMER_INTERNAL_HANDLE) == HAL_OK) {
		while (!g_irq_TA0)
			;
	} else {
		Error_Handler();
	}
}

/*
 * TODO: Can be interesting to see a generic function with a bitmask of what is wanted instead of multiple functions
 */
uint8_t IRQ_Wait_for_SW1()
{
    g_irq_SW1 = false;
    while(!g_irq_SW1)
    {
       //__low_power_mode_0();
    }
    g_irq_SW1 = false;

    return IRQ_SOURCE_SW1;
}

uint8_t IRQ_Wait_for_SW1_or_SW2()
{
    uint8_t ret = IRQ_SOURCE_NONE;

    g_irq_SW1 = false;
    g_irq_SW2 = false;
    while(!g_irq_SW1 && !g_irq_SW2)
    {
       //__low_power_mode_0();
    }

    if(g_irq_SW1)
    {
        g_irq_SW1 = false;
        ret |= IRQ_SOURCE_SW1;
    }

    if(g_irq_SW2)
    {
        g_irq_SW2 = false;
        ret |= IRQ_SOURCE_SW2;
    }

    return ret;
}

uint8_t IRQ_Wait_for_SW1_or_SW2_or_TRF(uint8_t *pTRF7970A_irqStatus)
{
    uint8_t ret = IRQ_SOURCE_NONE;

    g_irq_SW1 = false;
    g_irq_SW2 = false;
    g_irq_TRF = TRF_IRQ_READ();
    while(!g_irq_TRF && !g_irq_SW1 && !g_irq_SW2)
    {
        //__low_power_mode_0();
    }

    if(g_irq_TRF)
    {
        *pTRF7970A_irqStatus = TRF7970A_getIrqStatus();
        g_irq_TRF = false;
        ret |= IRQ_SOURCE_TRF7970A;
    }

    if(g_irq_SW1)
    {
        g_irq_SW1 = false;
        ret |= IRQ_SOURCE_SW1;
    }

    if(g_irq_SW2)
    {
        g_irq_SW2 = false;
        ret |= IRQ_SOURCE_SW2;
    }

    return ret;
}

uint8_t IRQ_Wait_for_SW1_or_TRF(uint8_t *pTRF7970A_irqStatus)
{
    uint8_t ret = IRQ_SOURCE_NONE;

    g_irq_SW1 = false;
    g_irq_TRF = TRF_IRQ_READ();
    while(!g_irq_TRF && !g_irq_SW1)
    {
        //__low_power_mode_0();
    }

    if(g_irq_TRF)
    {
        *pTRF7970A_irqStatus = TRF7970A_getIrqStatus();
        g_irq_TRF = false;
        ret |= IRQ_SOURCE_TRF7970A;
    }

    if(g_irq_SW1)
    {
        g_irq_SW1 = false;
        ret |= IRQ_SOURCE_SW1;
    }

    return ret;
}

uint8_t IRQ_Wait_for_SW1_or_SW2_or_Timeout(uint16_t timeout_ms)
{
    uint8_t ret = IRQ_SOURCE_NONE;

    g_irq_SW1 = false;
    g_irq_SW2 = false;
    TIMER_start_Milliseconds(timeout_ms);
    while(!g_irq_TA0 && !g_irq_SW1 && !g_irq_SW2)
    {
        //__low_power_mode_0();
    }
    TIMER_stop();

    if(g_irq_SW1)
    {
        g_irq_SW1 = false;
        ret |= IRQ_SOURCE_SW1;
    }

    if(g_irq_SW2)
    {
        g_irq_SW2 = false;
        ret |= IRQ_SOURCE_SW2;
    }

    if(g_irq_TA0)
    {
        ret |= IRQ_SOURCE_TIMER;
    }

    return ret;
}

uint8_t IRQ_Wait_for_SW1_or_SW2_or_TRF_or_Timeout(uint8_t *pTRF7970A_irqStatus, uint16_t timeout_ms)
{
    uint8_t ret = IRQ_SOURCE_NONE;
    
    g_irq_SW1 = false;
    g_irq_SW2 = false;
    TIMER_start_Milliseconds(timeout_ms);
    g_irq_TRF = TRF_IRQ_READ();
    while(!g_irq_TRF && !g_irq_TA0 && !g_irq_SW1 && !g_irq_SW2)
    {
        //__low_power_mode_0();
    }
    TIMER_stop();

    if(g_irq_TRF)
    {
        *pTRF7970A_irqStatus = TRF7970A_getIrqStatus();
        g_irq_TRF = false;
        ret |= IRQ_SOURCE_TRF7970A;
    }

    if(g_irq_SW1)
    {
        g_irq_SW1 = false;
        ret |= IRQ_SOURCE_SW1;
    }

    if(g_irq_SW2)
    {
        g_irq_SW2 = false;
        ret |= IRQ_SOURCE_SW2;
    }

    if(g_irq_TA0)
    {
        ret |= IRQ_SOURCE_TIMER;
    }

    return ret;
}
