# 33円 RISC-Vマイコン CH32X033評価F/W開発
1石33円のRISC-Vマイコン CH32X033の評価F/W個人開発リポジトリ

<div align="center">
  <img src="/doc/IMG_20250824_023041.jpg">
</div>

## 開発環境

### H/W

> [!IMPORTANT]
> 外部クロックのHSEはそもそも入力ピンが存在しない。<br>なのでCH32X033、CH32X035は内蔵RCのHSIしかクロック源で使えず、<br>HSIは48MHz ±0.8% ~ ±1.1%(±8000ppm ~ ±11000ppm)で結構厳しい精度のクロック。。。


- 評価基板
  - (TBD)
  - ※基板完成まではブレッドボード

<br>

- マイコン ... 型番:[CH32X033F8P6](https://www.wch.cn/products/CH32X035.html)🔗
  - CPU ... [QingKeV4C (RISC-V RV32IMAC)]
  - ROM ... 62KB
  - RAM ... 20KB
  - Clock ... 48MHz
  - GPIO ... 18本
  - PIOC ... RP2040のPIOみたいな機能
  - DMA ... x8ch
  - タイマー
    - 16bit高機能タイマー ADTM ... TIM1、TIM2
    - 16bit汎用タイマー GPTM ... TIM3
  - WDT ... x2本(IWDG, WWDG)
  - SysTick ... 32bitタイマー
  - I2C ... x1ch
  - SPI ... x1ch
  - USART ... x4ch
  - ADC ... 12bit x10ch
  - オペアンプ ... x2ch
  - コンパレータ ... x2ch
  - USB ... USBFS Device (※Host機能はなし)

### S/W

- IDE/SDK/コンパイラ
  - [MounRiver Studio (MRS) V2.2.0](https://www.mounriver.com/download)🔗

### デバッガ

- [WCH-LinkE Ver1.3](https://akizukidenshi.com/catalog/g/g118065)🔗

### デバッグ

#### SWD

- [WCH-LinkE <--> 評価基板]
  - SWDIO <--> PC18ピン
  - SWCLK <--> PC19ピン
  - GND <--> GND

#### UART

- [WCH-LinkE <--> 評価基板]
  - RX <--> PB10ピン(TX)
  - TX <--> PB11ピン(RX)
  - GND <--> GND
