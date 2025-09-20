/**
 * @file drv_dma.h
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief CH32X033用DMAドライバのラッパー＆API
 * @version 0.1
 * @date 2025-09-20
 * 
 * @copyright Copyright (c) 2025 Chimipupu All Rights Reserved.
 * 
 */

#ifndef DRV_DMA_H
#define DRV_DMA_H

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include <ch32X035.h>
#include "ch32x035_dma.h"

#define DEBUG_DMA_TEST

#ifdef DEBUG_DMA_TEST
void dbg_dma_test(void);
#endif // DEBUG_DMA_TEST

#define DMA_CH_1    0
#define DMA_CH_2    1
#define DMA_CH_3    2
#define DMA_CH_4    3
#define DMA_CH_5    4
#define DMA_CH_6    5
#define DMA_CH_7    6
#define DMA_CH_8    7

#define DMA_MEM_TO_MEM           0x00 // DMA MEM to MEM
#define DMA_MEM_TO_PERI          0x01 // DMA MEM to ペリフェラル

#define DMA_BYTE_TRANSFER        0x00 // DMA転送データ幅 1Byte
#define DMA_HALF_WORD_TRANSFER   0x01 // DMA転送データ幅 2Byte
#define DMA_WORD_TRANSFER        0x02 // DMA転送データ幅 4Byte

#define DMA_MODE_ONE_SHOT        0x00 // DMA転送 単発モード
#define DMA_MODE_CIRCULAR        0x01 // DMA転送 サーキュラーモード

typedef struct {
    uint8_t ch;             // DMA Ch1~8
    uint8_t dir;            // DMA転送方向
    uint8_t mode;           // DMA転送モード(単発 or サーキュラー)
    uint32_t transfer_size; // DMA転送データ幅(8/16/32bit)
    uint32_t data_size;     // 転送サイズ(Byte数)
    void *p_src_buf;        // DMA転送元バッファポインタ
    void *p_dst_buf;        // DMA転送先バッファポインタ
    bool is_it_use;         // DMA割り込み有効
} dma_init_config_t;

void drv_dma_start(uint8_t ch);
uint8_t drv_dma_transfer_check(uint8_t ch);
void drv_dma_init(dma_init_config_t *p_dma_config);

#endif // DRV_DMA_H