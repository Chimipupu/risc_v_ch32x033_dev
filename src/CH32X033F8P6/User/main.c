/**
 * @file main.c
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief  CH32X033 メイン
 * @version 0.1
 * @date 2025-08-24
 * 
 * @copyright Copyright (c) 2025 Chimipupu All Rights Reserved.
 * 
 */

#include "stdio.h"
#include <ch32X035.h>

#include "debug.h"
#include "drv_uasrt.h"
#include "app_main.h"

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();

    // USRAT初期化 115200 8N1(TX=PA10ピン, RX=PA11ピン)
    hw_usart_init();

    printf("[DEBUG] CH32X0033F8P6 Develop\r\n");
    printf("SystemClk:%d\r\n",SystemCoreClock);
    printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID() );

    // アプリメイン初期化
    app_main_init();

    while(1)
    {
        // アプリメイン
        app_main();
    }

    return 0;
}