/**
 * @file drv_tim.h
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief CH32V006用TIM(タイマー)ドライバのラッパー＆API
 * @version 0.1
 * @date 2025-09-21
 * 
 * @copyright Copyright (c) 2025 Chimipupu All Rights Reserved.
 * 
 */

#ifndef DRV_TIM_H
#define DRV_TIM_H

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include <ch32X035.h>
#include "ch32x035_tim.h"

// (DEBUG)タイマーデバッグ用
#define DEBUG_TIM_TEST

#ifdef DEBUG_TIM_TEST
uint32_t dbg_tim_test(void);
#endif // DEBUG_TIM_TEST

inline __attribute__((always_inline)) uint16_t drv_get_tim_cnt(void)
{
    uint16_t cnt;

    cnt = TIM_GetCounter(TIM3);

    return cnt;
}

void drv_tim_init(uint16_t arr, uint16_t psc);

#endif // DRV_TIM_H