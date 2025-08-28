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
#include "dbg_com.h"

// const uint8_t uart_test_str[] = "CH32X033 Develop by Chimipupu(https://github.com/Chimipupu)\r\n";

// #include "drv_tim.h"
#include "dbg_com.h"

// extern bool g_is_tim_cnt_up;
extern bool g_is_usart_irq_proc_end;

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

#if 0
/**
 * @brief 関数の実行時間を計測する
 * 
 * @param func 計測対象の関数ポインタ
 * @param func_name 関数名（表示用）
 * @param ... 関数に渡す引数（可変長）
 */
void proc_exec_time(void (*func)(void), const char* func_name, ...)
{
    _DI();
    volatile uint16_t start_time = drv_get_tim_cnt();
    _EI();

    func();

    _DI();
    volatile uint16_t end_time = drv_get_tim_cnt();
    _EI();

    printf("proc time %s: %u us\n", func_name, end_time - start_time);
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
#endif

/**
 * @brief アプリメイン初期化
 * 
 */
void app_main_init(void)
{
    // デバッグモニタ初期化
    dbg_com_init();
}

/**
 * @brief アプリメイン
 * 
 */
void app_main(void)
{
    // デバッグモニタ
    dbg_com_main();
}