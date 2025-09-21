/**
 * @file app_main.c
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief アプリメイン
 * @version 0.1
 * @date 2025-08-24
 * 
 * @copyright Copyright (c) 2025 Chimipupu All Rights Reserved.
 * 
 */
#include "app_main.h"
#include "drv_tim.h"
#include "state_machine.h"
#include <math.h>

#ifdef DBG_COM_USE
#include "dbg_com.h"
#endif // DBG_COM_USE

// extern bool g_is_tim_cnt_up;
extern bool g_is_usart_irq_proc_end;

/**
 * @brief floatをuint32_tでprintf()する関数
 * loatのprintf()は容量を食うから整数でprintf()
 * @param value 
 */
void print_float_to_u32(float value)
{
    uint32_t ip = (uint32_t)value;
    uint32_t frac = (uint32_t)((value - (float)ip) * 1000000.0f + 0.5f);

    if (frac >= 1000000U) {
        ip += 1;
        frac -= 1000000U;
    }

    // %lu を使って符号なしを明示（環境に合わせてキャスト）
    printf("%lu.%06lu", (unsigned long)ip, (unsigned long)frac);
}

/**
 * @brief メモリダンプ(16進HEX & Ascii)
 * 
 * @param dump_addr ダンプするメモリの32bitアドレス
 * @param dump_size ダンプするサイズ(Byte)
 */
void show_mem_dump(uint32_t dump_addr, uint32_t dump_size)
{
    printf("\n[Memory Dump '(addr:0x%04X)]\n", dump_addr);

    // ヘッダー行を表示
    printf("Address  ");
    for (int i = 0; i < 16; i++)
    {
        printf("%02X ", i);
    }
    printf("| ASCII\n");
    printf("-------- ");
    for (int i = 0; i < 16; i++)
    {
        printf("---");
    }
    printf("| ------\n");

    // 16バイトずつダンプ
    for (uint32_t offset = 0; offset < dump_size; offset += 16)
    {
        printf("%08X: ", dump_addr + offset);

        // 16バイト分のデータを表示
        for (int i = 0; i < 16; i++)
        {
            if (offset + i < dump_size) {
                uint8_t data = *((volatile uint8_t*)(dump_addr + offset + i));
                printf("%02X ", data);
            } else {
                printf("   ");
            }
        }

        // ASCII表示
        printf("| ");
        for (int i = 0; i < 16; i++)
        {
            if (offset + i < dump_size) {
                uint8_t data = *((volatile uint8_t*)(dump_addr + offset + i));
                // 表示可能なASCII文字のみ表示
                printf("%c", (data >= 32 && data <= 126) ? data : '.');
            } else {
                printf(" ");  // データがない場合は空白を表示
            }
        }
        printf("\n");
    }
}

// ガウス・ルジャンドル法による円周率の計算
float math_pi_calc(uint8_t cnt)
{
    uint8_t i;
    float a = 1.0;
    float b = 1.0 / sqrt(2);
    float t = 1.0 / 4.0;
    float p = 1.0;

    for (i = 0; i < cnt; i++)
    {
        float an = (a + b) / 2.0;
        float bn = sqrt(a * b);
        float tn = t - p * pow(a - an, 2);
        float pn = 2.0 * p;

        a = an;
        b = bn;
        t = tn;
        p = pn;
    }

    float pi = pow(a + b, 2) / (4.0 * t);

    return pi;
}

/**
 * @brief 処理時間取得関数(単位:us)
 * 
 * @param start_us_cnt 計測開始時の1usタイマーのカウント
 * @param end_us_cnt 計測終了時の1usタイマーのカウント
 * @return uint32_t 処理時間 us
 */
uint32_t get_proc_time(uint32_t start_us_cnt, uint32_t end_us_cnt)
{
    uint32_t proc_time_us;

    if(end_us_cnt < start_us_cnt) {
        end_us_cnt += 65535;
    }

    proc_time_us = end_us_cnt - start_us_cnt;

    return proc_time_us;
}

/**
 * @brief アプリメイン初期化
 * 
 */
void app_main_init(void)
{
#ifdef DBG_COM_USE
    // デバッグモニタ初期化
    dbg_com_init();
#endif // DBG_COM_USE

    // ステートマシーン初期化
    state_machine_init();
}

/**
 * @brief アプリメイン
 * 
 */
void app_main(void)
{
#ifdef DBG_COM_USE
    // デバッグモニタ
    dbg_com_main();
#else
    // ステートマシーン
    state_machine_main();
    Delay_Ms(1000);
#endif // DBG_COM_USE
}