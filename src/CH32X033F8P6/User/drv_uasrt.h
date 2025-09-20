/**
 * @file drv_uasrt.h
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief CH32X033用USARTドライバのラッパー＆API
 * @version 0.1
 * @date 2025-08-24
 * 
 * @copyright Copyright (c) 2025 Chimipupu All Rights Reserved.
 * 
 */

#ifndef DRV_UASRT_H
#define DRV_UASRT_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include <ch32X035.h>

#define USE_USART_1
#define USE_USART_2
#define USE_USART_3
#define USE_USART_4

#define USART_RX_BUF_SIZE   128

int32_t hw_usart_get_char(void);
void hw_usart_init(void);

#endif // DRV_UASRT_H