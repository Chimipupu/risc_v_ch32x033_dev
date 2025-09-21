/**
 * @file drv_dma.c
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief CH32X033用DMAドライバのラッパー＆API
 * @version 0.1
 * @date 2025-09-20
 * 
 * @copyright Copyright (c) 2025 Chimipupu All Rights Reserved.
 * 
 */

#include "drv_dma.h"

void DMA1_Channel1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void DMA1_Channel2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void DMA1_Channel3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void DMA1_Channel4_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void DMA1_Channel5_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void DMA1_Channel6_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void DMA1_Channel7_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void DMA1_Channel8_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

// （ROM）DMAステータスフラグテーブル
const dma_status_flg_t g_dma_status_flg_tbl[] = {
    {DMA1_FLAG_GL1, DMA1_FLAG_TC1, DMA1_FLAG_HT1, DMA1_FLAG_TE1},
    {DMA1_FLAG_GL2, DMA1_FLAG_TC2, DMA1_FLAG_HT2, DMA1_FLAG_TE2},
    {DMA1_FLAG_GL3, DMA1_FLAG_TC3, DMA1_FLAG_HT3, DMA1_FLAG_TE3},
    {DMA1_FLAG_GL4, DMA1_FLAG_TC4, DMA1_FLAG_HT4, DMA1_FLAG_TE4},
    {DMA1_FLAG_GL5, DMA1_FLAG_TC5, DMA1_FLAG_HT5, DMA1_FLAG_TE5},
    {DMA1_FLAG_GL6, DMA1_FLAG_TC6, DMA1_FLAG_HT6, DMA1_FLAG_TE6},
    {DMA1_FLAG_GL7, DMA1_FLAG_TC7, DMA1_FLAG_HT7, DMA1_FLAG_TE7},
    {DMA1_FLAG_GL8, DMA1_FLAG_TC8, DMA1_FLAG_HT8, DMA1_FLAG_TE8},
};

// （ROM）DMA割り込みステータスフラグテーブル
const dma_it_status_flg_t g_dma_it_status_flg_tbl[] = {
    {DMA1_IT_GL1, DMA1_IT_TC1, DMA1_IT_HT1, DMA1_IT_TE1},
    {DMA1_IT_GL2, DMA1_IT_TC2, DMA1_IT_HT2, DMA1_IT_TE2},
    {DMA1_IT_GL3, DMA1_IT_TC3, DMA1_IT_HT3, DMA1_IT_TE3},
    {DMA1_IT_GL4, DMA1_IT_TC4, DMA1_IT_HT4, DMA1_IT_TE4},
    {DMA1_IT_GL5, DMA1_IT_TC5, DMA1_IT_HT5, DMA1_IT_TE5},
    {DMA1_IT_GL6, DMA1_IT_TC6, DMA1_IT_HT6, DMA1_IT_TE6},
    {DMA1_IT_GL7, DMA1_IT_TC7, DMA1_IT_HT7, DMA1_IT_TE7},
    {DMA1_IT_GL8, DMA1_IT_TC8, DMA1_IT_HT8, DMA1_IT_TE8},
};

// （ROM）DMA Ch configデータテーブル
const dma_ch_config_data_t g_dma_ch_config_data_tbl[] = {
    {DMA_CH_1, DMA1_Channel1, DMA1_Channel1_IRQn, &g_dma_status_flg_tbl[0], &g_dma_it_status_flg_tbl[0]},
    {DMA_CH_2, DMA1_Channel2, DMA1_Channel2_IRQn, &g_dma_status_flg_tbl[1], &g_dma_it_status_flg_tbl[1]},
    {DMA_CH_3, DMA1_Channel3, DMA1_Channel3_IRQn, &g_dma_status_flg_tbl[2], &g_dma_it_status_flg_tbl[2]},
    {DMA_CH_4, DMA1_Channel4, DMA1_Channel4_IRQn, &g_dma_status_flg_tbl[3], &g_dma_it_status_flg_tbl[3]},
    {DMA_CH_5, DMA1_Channel5, DMA1_Channel5_IRQn, &g_dma_status_flg_tbl[4], &g_dma_it_status_flg_tbl[4]},
    {DMA_CH_6, DMA1_Channel6, DMA1_Channel6_IRQn, &g_dma_status_flg_tbl[5], &g_dma_it_status_flg_tbl[5]},
    {DMA_CH_7, DMA1_Channel7, DMA1_Channel7_IRQn, &g_dma_status_flg_tbl[6], &g_dma_it_status_flg_tbl[6]},
    {DMA_CH_8, DMA1_Channel8, DMA1_Channel8_IRQn, &g_dma_status_flg_tbl[7], &g_dma_it_status_flg_tbl[7]},
};

dma_init_config_t g_dma_ch_1_init_config;
dma_init_config_t g_dma_ch_2_init_config;
dma_init_config_t g_dma_ch_3_init_config;
dma_init_config_t g_dma_ch_4_init_config;
dma_init_config_t g_dma_ch_5_init_config;
dma_init_config_t g_dma_ch_6_init_config;
dma_init_config_t g_dma_ch_7_init_config;
dma_init_config_t g_dma_ch_8_init_config;

// （ROM）DMA Chデータテーブル
const dma_data_t g_dma_data_tbl[] = {
    {&g_dma_ch_1_init_config, &g_dma_ch_config_data_tbl[0]},
    {&g_dma_ch_2_init_config, &g_dma_ch_config_data_tbl[1]},
    {&g_dma_ch_3_init_config, &g_dma_ch_config_data_tbl[2]},
    {&g_dma_ch_4_init_config, &g_dma_ch_config_data_tbl[3]},
    {&g_dma_ch_5_init_config, &g_dma_ch_config_data_tbl[4]},
    {&g_dma_ch_6_init_config, &g_dma_ch_config_data_tbl[5]},
    {&g_dma_ch_7_init_config, &g_dma_ch_config_data_tbl[6]},
    {&g_dma_ch_8_init_config, &g_dma_ch_config_data_tbl[7]},
};

static void dma_isr(uint8_t ch);

/**
 * @brief DMA割り込みハンドラISR
 * 
 * @param ch DMA Ch1~8
 */
static void dma_isr(uint8_t ch)
{
    ITStatus status;

    status = DMA_GetITStatus(g_dma_ch_config_data_tbl[ch].p_it_status_flg_tbl->tc_it_flg);

    // DMA転送完了割り込み(TC)フラグ確認
    if(status != RESET) {
        // DMAが単発モード時
        if(g_dma_data_tbl[ch].p_init_config->mode == DMA_MODE_ONE_SHOT) {
            DMA_Cmd(g_dma_ch_config_data_tbl[ch].p_ch_typedef, DISABLE);
        }

        DMA_ClearITPendingBit(g_dma_ch_config_data_tbl[ch].p_it_status_flg_tbl->tc_it_flg);
    }
}

/**
 * @brief DMA Ch1 割り込みハンドラ
 * 
 */
void DMA1_Channel1_IRQHandler(void)
{
    dma_isr(DMA_CH_1);
}

/**
 * @brief DMA Ch2 割り込みハンドラ
 * 
 */
void DMA1_Channel2_IRQHandler(void)
{
    dma_isr(DMA_CH_2);
}

/**
 * @brief DMA Ch3 割り込みハンドラ
 * 
 */
void DMA1_Channel3_IRQHandler(void)
{
    dma_isr(DMA_CH_3);
}
#if 0
/**
 * @brief DMA Ch4 割り込みハンドラ
 * 
 */
void DMA1_Channel4_IRQHandler(void)
{
    dma_isr(DMA_CH_4);
}

/**
 * @brief DMA Ch5 割り込みハンドラ
 * 
 */
void DMA1_Channel5_IRQHandler(void)
{
    dma_isr(DMA_CH_5);
}

/**
 * @brief DMA Ch6 割り込みハンドラ
 * 
 */
void DMA1_Channel6_IRQHandler(void)
{
    dma_isr(DMA_CH_6);
}

/**
 * @brief DMA Ch7 割り込みハンドラ
 * 
 */
void DMA1_Channel7_IRQHandler(void)
{
    dma_isr(DMA_CH_7);
}

/**
 * @brief DMA Ch8 割り込みハンドラ
 * 
 */
void DMA1_Channel8_IRQHandler(void)
{
    dma_isr(DMA_CH_8);
}
#endif

/**
 * @brief DMA転送開始
 * 
 * @param ch DMA Ch1~8(val = 0~7)
 */
void drv_dma_start(uint8_t ch)
{
    DMA_Cmd(g_dma_ch_config_data_tbl[ch].p_ch_typedef, ENABLE);
}

/**
 * @brief DMA転送状況確認関数(割り込み未使用時のポーリング用)
 * 
 * @param ch DMA Ch1~8
 * @return 0x00 DMA転送中
 * @return 0x01 DMA転送完了
 * @return 0xFF DMA転送エラー
 */
uint8_t drv_dma_transfer_check(uint8_t ch)
{
    uint8_t ret = 0xFF;
    FlagStatus status;

    // DMA転送エラーステータス確認
    status = DMA_GetFlagStatus(g_dma_ch_config_data_tbl[ch].p_status_flg_tbl->te_flg);
    if(status != RESET) {
        ret = 0xFF;
    } else {
        // DMA転送完了ステータス確認
        status = DMA_GetFlagStatus(g_dma_ch_config_data_tbl[ch].p_status_flg_tbl->tc_flg);
        if(status != RESET) {
            ret = 0x01;
        } else {
            ret = 0x00;
        }
    }

    return ret;
}

/**
 * @brief DMA初期化関数
 * 
 * @param p_dma_config DMA初期化構造体
 */
void drv_dma_init(dma_init_config_t *p_dma_config)
{
    void *p_src;
    void *p_dst;
    uint8_t transfer_byte;
    DMA_InitTypeDef dma_init_data = {0};
	NVIC_InitTypeDef nvic_init_data = {0};

    DMA_StructInit(&dma_init_data);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    // DMAの転送方向の設定
    if(p_dma_config->dir == DMA_MEM_TO_MEM) {
        dma_init_data.DMA_DIR = DMA_DIR_PeripheralSRC;
        p_src = p_dma_config->p_src_buf;
        p_dst = p_dma_config->p_dst_buf;
    } else {
        dma_init_data.DMA_DIR = DMA_DIR_PeripheralDST;
        p_src = p_dma_config->p_dst_buf;
        p_dst = p_dma_config->p_src_buf;
    }

    // DMAの転送データ幅と転送元と転送先アドレスと転送サイズの設定
    switch (p_dma_config->transfer_size)
    {
        // 16bit転送
        case DMA_HALF_WORD_TRANSFER:
            dma_init_data.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
            dma_init_data.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
            dma_init_data.DMA_PeripheralBaseAddr = (uint32_t)((uint16_t *)p_src);
            dma_init_data.DMA_MemoryBaseAddr = (uint32_t)((uint16_t *)p_dst);
            transfer_byte = 2;
            break;

        // 32bit転送
        case DMA_WORD_TRANSFER:
            dma_init_data.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
            dma_init_data.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
            dma_init_data.DMA_PeripheralBaseAddr = (uint32_t)((uint32_t *)p_src);
            dma_init_data.DMA_MemoryBaseAddr = (uint32_t)((uint32_t *)p_dst);
            transfer_byte = 4;
            break;

        // 8bit転送
        case DMA_BYTE_TRANSFER:
        default:
            dma_init_data.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
            dma_init_data.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
            dma_init_data.DMA_PeripheralBaseAddr = (uint32_t)((uint8_t *)p_src);
            dma_init_data.DMA_MemoryBaseAddr = (uint32_t)((uint8_t *)p_dst);
            transfer_byte = 1;
            break;
    }
    dma_init_data.DMA_BufferSize = p_dma_config->data_size * transfer_byte;
    dma_init_data.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
    dma_init_data.DMA_MemoryInc = DMA_MemoryInc_Enable;

    // DMAの転送モードの設定
    if (p_dma_config->mode == DMA_MODE_ONE_SHOT) {
        dma_init_data.DMA_Mode = DMA_Mode_Normal;
    } else {
        dma_init_data.DMA_Mode = DMA_Mode_Circular;
    }

    // DMAのその他設定
    dma_init_data.DMA_Priority = DMA_Priority_VeryHigh;
    dma_init_data.DMA_M2M = DMA_M2M_Enable;
    DMA_Init(g_dma_ch_config_data_tbl[p_dma_config->ch].p_ch_typedef, &dma_init_data);
    DMA_ClearFlag(g_dma_ch_config_data_tbl[p_dma_config->ch].p_status_flg_tbl->tc_flg);

    // DMA割り込み有効
    if(p_dma_config->is_it_use != false) {
        nvic_init_data.NVIC_IRQChannel = g_dma_ch_config_data_tbl[p_dma_config->ch].irq;
        nvic_init_data.NVIC_IRQChannelPreemptionPriority = 1;
        nvic_init_data.NVIC_IRQChannelSubPriority = 0;
        nvic_init_data.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&nvic_init_data);
        DMA_ITConfig(g_dma_ch_config_data_tbl[p_dma_config->ch].p_ch_typedef, DMA_IT_TC, ENABLE);
    }
}

// (DEBUG)DMAデバッグ用
#ifdef DEBUG_DMA_TEST
#define DMA_TEST_BUF_SIZE    3
uint8_t g_dbg_dma_test_src_u8_buf[DMA_TEST_BUF_SIZE]   = {0xAB, 0xCD, 0xEF};
uint16_t g_dbg_dma_test_src_u16_buf[DMA_TEST_BUF_SIZE] = {0xABCD, 0x1234, 0x5678};
uint32_t g_dbg_dma_test_src_u32_buf[DMA_TEST_BUF_SIZE] = {0x12345678, 0x00ABCDEF, 0xAABBCCDD};

uint8_t g_dbg_dma_test_dst_u8_buf[DMA_TEST_BUF_SIZE]   = {0};
uint16_t g_dbg_dma_test_dst_u16_buf[DMA_TEST_BUF_SIZE] = {0};
uint32_t g_dbg_dma_test_dst_u32_buf[DMA_TEST_BUF_SIZE] = {0};

void dbg_dma_test(void)
{
    memset(&g_dbg_dma_test_dst_u8_buf[0], 0, DMA_TEST_BUF_SIZE);
    memset(&g_dbg_dma_test_dst_u16_buf[0], 0, DMA_TEST_BUF_SIZE);
    memset(&g_dbg_dma_test_dst_u32_buf[0], 0, DMA_TEST_BUF_SIZE);

    // DMA Ch1 ... 8bit転送テスト
    g_dma_ch_1_init_config.is_it_use = true;
    g_dma_ch_1_init_config.ch = DMA_CH_1;
    g_dma_ch_1_init_config.dir = DMA_MEM_TO_MEM;
    g_dma_ch_1_init_config.mode = DMA_MODE_ONE_SHOT;
    g_dma_ch_1_init_config.transfer_size = DMA_BYTE_TRANSFER;
    g_dma_ch_1_init_config.data_size = DMA_TEST_BUF_SIZE;
    g_dma_ch_1_init_config.p_src_buf = &g_dbg_dma_test_src_u8_buf[0];
    g_dma_ch_1_init_config.p_dst_buf = &g_dbg_dma_test_dst_u8_buf[0];
    drv_dma_init(&g_dma_ch_1_init_config);

    // DMA Ch2 ... 8bit転送テスト
    g_dma_ch_2_init_config.is_it_use = true;
    g_dma_ch_2_init_config.ch = DMA_CH_2;
    g_dma_ch_2_init_config.dir = DMA_MEM_TO_MEM;
    g_dma_ch_2_init_config.mode = DMA_MODE_ONE_SHOT;
    g_dma_ch_2_init_config.transfer_size = DMA_HALF_WORD_TRANSFER;
    g_dma_ch_2_init_config.data_size = DMA_TEST_BUF_SIZE;
    g_dma_ch_2_init_config.p_src_buf = &g_dbg_dma_test_src_u16_buf[0];
    g_dma_ch_2_init_config.p_dst_buf = &g_dbg_dma_test_dst_u16_buf[0];
    drv_dma_init(&g_dma_ch_2_init_config);

    // DMA Ch3 ... 8bit転送テスト
    g_dma_ch_3_init_config.is_it_use = true;
    g_dma_ch_3_init_config.ch = DMA_CH_3;
    g_dma_ch_3_init_config.dir = DMA_MEM_TO_MEM;
    g_dma_ch_3_init_config.mode = DMA_MODE_ONE_SHOT;
    g_dma_ch_3_init_config.transfer_size = DMA_WORD_TRANSFER;
    g_dma_ch_3_init_config.data_size = DMA_TEST_BUF_SIZE;
    g_dma_ch_3_init_config.p_src_buf = &g_dbg_dma_test_src_u32_buf[0];
    g_dma_ch_3_init_config.p_dst_buf = &g_dbg_dma_test_dst_u32_buf[0];
    drv_dma_init(&g_dma_ch_3_init_config);

    drv_dma_start(DMA_CH_1);
    drv_dma_start(DMA_CH_2);
    drv_dma_start(DMA_CH_3);
    // drv_dma_transfer_check(DMA_CH_1);
    // drv_dma_transfer_check(DMA_CH_2);
    // drv_dma_transfer_check(DMA_CH_3);
}
#endif // DEBUG_DMA_TEST