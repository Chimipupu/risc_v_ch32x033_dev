/**
 * @file drv_tim.c
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief CH32V006用TIM(タイマー)ドライバのラッパー＆API
 * @version 0.1
 * @date 2025-09-21
 * 
 * @copyright Copyright (c) 2025 Chimipupu All Rights Reserved.
 * 
 */

#include "drv_tim.h"
#include "app_main.h"

bool g_is_tim_cnt_up = false;

void TIM1_UP_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/**
 * @brief TIM1カウントアップ割り込み
 * 
 */
void TIM1_UP_IRQHandler(void)
{
    ITStatus ret;

    ret = TIM_GetITStatus(TIM1, TIM_IT_Update);

    if(ret == SET) {
        g_is_tim_cnt_up = true;
    }

    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
}

/**
 * @brief Initializes TIM1 output compare.
 * 
 * @param arr the period value.
 * @param psc the prescaler value.
 */
void drv_tim_init(uint16_t arr, uint16_t psc)
{
    NVIC_InitTypeDef NVIC_InitStructure = {0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 50;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);

    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

#if 1
    TIM_Cmd(TIM1, ENABLE);
#else
    TIM_GenerateEvent(TIM1, TIM_IT_Update);
#endif
}

// (DEBUG)タイマーデバッグ用
#ifdef DEBUG_TIM_TEST
uint32_t dbg_tim_test(void)
{
    volatile uint32_t start_cnt = (uint32_t)drv_get_tim_cnt();
    Delay_Us(100);
    volatile uint32_t end_cnt = (uint32_t)drv_get_tim_cnt();
    // 期待値は100us
    volatile uint32_t proc_time = get_proc_time(start_cnt, end_cnt);

    return proc_time;
}
#endif // DEBUG_TIM_TEST