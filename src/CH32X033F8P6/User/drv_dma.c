/**
 * @file drv_dma.c
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief  CH32X033 DMAドライバ＆ラッパー＆API
 * @version 0.1
 * @date 2025-09-20
 * 
 * @copyright Copyright (c) 2025 Chimipupu All Rights Reserved.
 * 
 */

#include "drv_dma.h"

typedef struct {
    uint8_t ch;             // DMA Ch1~8
    DMA_Channel_TypeDef *p_ch_typedef;
    uint32_t gl_flg;        // DMA global flag
    uint32_t tc_flg;        // DMA transfer complete flag
    uint32_t ht_flg;        // DMA half transfer flag
    uint32_t te_flg;        // DMA transfer error flag
} dma_ch_config_data_t;

const dma_ch_config_data_t g_dma_ch_data[] = {
    {DMA_CH_1, DMA1_Channel1, DMA1_FLAG_GL1, DMA1_FLAG_TC1, DMA1_FLAG_HT1, DMA1_FLAG_TE1},
    {DMA_CH_2, DMA1_Channel2, DMA1_FLAG_GL2, DMA1_FLAG_TC2, DMA1_FLAG_HT2, DMA1_FLAG_TE2},
    {DMA_CH_3, DMA1_Channel3, DMA1_FLAG_GL3, DMA1_FLAG_TC3, DMA1_FLAG_HT3, DMA1_FLAG_TE3},
    {DMA_CH_4, DMA1_Channel4, DMA1_FLAG_GL4, DMA1_FLAG_TC4, DMA1_FLAG_HT4, DMA1_FLAG_TE4},
    {DMA_CH_5, DMA1_Channel5, DMA1_FLAG_GL5, DMA1_FLAG_TC5, DMA1_FLAG_HT5, DMA1_FLAG_TE5},
    {DMA_CH_6, DMA1_Channel6, DMA1_FLAG_GL6, DMA1_FLAG_TC6, DMA1_FLAG_HT6, DMA1_FLAG_TE6},
    {DMA_CH_7, DMA1_Channel7, DMA1_FLAG_GL7, DMA1_FLAG_TC7, DMA1_FLAG_HT7, DMA1_FLAG_TE7},
    {DMA_CH_8, DMA1_Channel8, DMA1_FLAG_GL8, DMA1_FLAG_TC8, DMA1_FLAG_HT8, DMA1_FLAG_TE8},
};

#ifdef DEBUG_DMA_TEST
#define DMA_TEST_BUF_SIZE    32
uint32_t g_dbg_dma_test_src_buf[DMA_TEST_BUF_SIZE] = {
        0x01020304, 0x05060708, 0x090A0B0C, 0x0D0E0F10,
        0x11121314, 0x15161718, 0x191A1B1C, 0x1D1E1F20,
        0x21222324, 0x25262728, 0x292A2B2C, 0x2D2E2F30,
        0x31323334, 0x35363738, 0x393A3B3C, 0x3D3E3F40,
        0x41424344, 0x45464748, 0x494A4B4C, 0x4D4E4F50,
        0x51525354, 0x55565758, 0x595A5B5C, 0x5D5E5F60,
        0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70,
        0x71727374, 0x75767778, 0x797A7B7C, 0x7D7E7F80
        };

uint32_t g_dbg_dma_test_dst_buf[DMA_TEST_BUF_SIZE] = {0};

void dbg_dma_test(void)
{
    memset(&g_dbg_dma_test_dst_buf[0], 0x00, DMA_TEST_BUF_SIZE);

    dma_init_config_t config;

    config.ch = DMA_CH_1;
    config.dir = DMA_MEM_TO_MEM;
    config.mode = DMA_MODE_ONE_SHOT;
    config.transfer_size = DMA_BYTE_TRANSFER;
    config.data_size = DMA_TEST_BUF_SIZE;
    config.p_src_buf = &g_dbg_dma_test_src_buf[0];
    config.p_dst_buf = &g_dbg_dma_test_dst_buf[0];
    drv_dma_init(&config);

    drv_dma_start(DMA_CH_1);
    drv_dma_transfer_check(DMA_CH_1);
}
#endif // DEBUG_DMA_TEST

/**
 * @brief DMA転送開始
 * 
 * @param ch DMA Ch1~8(val = 0~7)
 */
void drv_dma_start(uint8_t ch)
{
    DMA_Cmd(g_dma_ch_data[ch].p_ch_typedef, ENABLE);
}

/**
 * @brief DMA転送状況確認関数
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
    status = DMA_GetFlagStatus(g_dma_ch_data[ch].te_flg);
    if(status != RESET) {
        ret = 0xFF;
    } else {
        // DMA転送完了ステータス確認
        status = DMA_GetFlagStatus(g_dma_ch_data[ch].tc_flg);
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
    DMA_InitTypeDef dma_init_data = {0};

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

    // DMAの転送サイズの設定
    dma_init_data.DMA_BufferSize = p_dma_config->data_size * 4;

    // DMAの転送データ幅と転送元と転送先アドレスの設定
    switch (p_dma_config->transfer_size)
    {
        case DMA_HALF_WORD_TRANSFER:
            dma_init_data.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
            dma_init_data.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
            dma_init_data.DMA_PeripheralBaseAddr = (uint32_t)((uint16_t *)p_src);
            dma_init_data.DMA_MemoryBaseAddr = (uint32_t)((uint16_t *)p_dst);
            break;

        case DMA_WORD_TRANSFER:
            dma_init_data.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
            dma_init_data.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
            dma_init_data.DMA_PeripheralBaseAddr = (uint32_t)((uint32_t *)p_src);
            dma_init_data.DMA_MemoryBaseAddr = (uint32_t)((uint32_t *)p_dst);
            break;

        case DMA_BYTE_TRANSFER:
        default:
            dma_init_data.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
            dma_init_data.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
            dma_init_data.DMA_PeripheralBaseAddr = (uint32_t)((uint8_t *)p_src);
            dma_init_data.DMA_MemoryBaseAddr = (uint32_t)((uint8_t *)p_dst);
            break;
    }
    dma_init_data.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
    dma_init_data.DMA_MemoryInc = DMA_MemoryInc_Enable;

    // DMAの転送モードの設定
    if (p_dma_config->mode == DMA_MODE_ONE_SHOT)
    {
        dma_init_data.DMA_Mode = DMA_Mode_Normal;
    } else {
        dma_init_data.DMA_Mode = DMA_Mode_Circular;
    }

    // DMAのその他設定
    dma_init_data.DMA_Priority = DMA_Priority_VeryHigh;
    dma_init_data.DMA_M2M = DMA_M2M_Enable;
    DMA_Init(g_dma_ch_data[p_dma_config->ch].p_ch_typedef, &dma_init_data);
    DMA_ClearFlag(g_dma_ch_data[p_dma_config->ch].tc_flg);

    // DMA_Cmd(DMA1_Channel3, DISABLE);
}