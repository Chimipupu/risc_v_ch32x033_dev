/**
 * @file state_machine.c
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief ステートマシーン (CH32X033用)
 * @version 0.1
 * @date 2025-09-22
 * 
 * @copyright Copyright (c) 2025 Chimipupu All Rights Reserved.
 * 
 */

#include "state_machine.h"
#include "app_main.h"

static e_state_machine s_state = SM_NONE;
static void sm_math_calc(void);

static void sm_math_calc(void)
{
#if 1
    // 円周率の定数をprintf()
    printf("pi = %s\r\n", MATH_PI_STR);
#else
    // 円周率を計算してprintf()
    float pi;

    pi = math_pi_calc(4);
    printf("pi = ");
    print_float_to_u32(pi);
    printf("\r\n");
#endif

    s_state = SM_IDLE;
}

/**
 * @brief ステートマシーン 初期化関数
 * 
 */
void state_machine_init(void)
{
    s_state = SM_MATH_CALC;
}

/**
 * @brief ステートマシーン メイン関数
 * 
 */
void state_machine_main(void)
{
    switch (s_state)
    {
        case SM_MATH_CALC:
            sm_math_calc();
            break;

        case SM_NONE:
        case SM_IDLE:
        default:
            s_state = SM_MATH_CALC;
            break;
    }
}