# 33円 RISC-Vマイコン CH32X033評価F/W開発

1石33円のRISC-Vマイコン CH32X033の評価F/W個人開発リポジトリ

## 重要

### ロット番号問題

> [!CAUTION]
> **ロット番号の最後から5桁目が0** ... **ADC Ch3/7/11/15、I2Cが使えない🪦🪦🪦**<br> 対策 ... I2Cはハードが使えんからソフトでI2Cするしかない！<br>※このロットを引いてしまったのを知っていま絶賛絶望中、、、最悪やけど33円なら安いし我慢😭

<div align="center">
  <img src="/doc/CH32X033_CH32X035のADC4chとI2Cがつかえないロット記載部分.jpg">
  <img src="/doc/CH32X033のADC4chとI2Cがつかえないロット.jpg">
</div>

### 外部クロックHSEの入力ピンが存在しない問題

> [!IMPORTANT]
> 外部クロックのHSEはそもそも入力ピンが存在しない。<br>なのでCH32X033、CH32X035は内蔵RCのHSIしかクロック源で使えず、<br>48MHzのHSIはTYPで±0.8%(±8000ppm)で結構厳しい精度のクロック。。。

## 開発環境

### H/W

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
  - ~~I2C ... x1ch~~ I2Cが使えないロットだった、、、
  - SPI ... x1ch
  - USART ... x4ch
  - ADC ... 12bit ~~x10ch~~ x6ch (ADC Ch3/7/11/15は使えないロットだった)
  - オペアンプ ... x2ch
  - コンパレータ ... x2ch
  - USB ... USBFS Device (※Host機能はなし)

### S/W

- IDE/SDK/コンパイラ
  - [MounRiver Studio (MRS) V2.2.0](https://www.mounriver.com/download)🔗
- 最適化
  - リリース
    - `-O0` ... 最適化なし
    - `-Os` ... サイズ優先
  - デバッグ
    - `-Og`

### デバッガ

- [WCH-LinkE Ver1.3](https://akizukidenshi.com/catalog/g/g118065)🔗

### デバッグ

#### SWD

- [WCH-LinkE <--> マイコン]
  - SWDIO <--> PC18ピン (ICの8ピン)
  - SWCLK <--> PC19ピン (ICの18ピン)
  - GND <--> GND (ICの7ピン)

#### UART

- [WCH-LinkE <--> マイコン]
  - RX <--> PB0ピン(USART4 TX) (IC2のピン)
  - TX <--> PB1ピン(USART4 RX) (IC3のピン)
  - GND <--> GND (ICの7ピン)

<div align="center">
  <img src="/doc/CH32X033F8P6_Debug_Pin.png">
</div>
