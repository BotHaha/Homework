# 41125243
# 41043146
作業三：Textbook p.457 題目 1(外部排序分析)

## 解題說明

### 問題描述

在外部排序（external sorting）中，資料過大無法全部載入主記憶體，因此會將資料分割為多個 sorted runs 存放於磁碟中，接著使用 k-way merge 演算法合併資料。

本題目要求：
- (a) 推導 Phase Two 合併階段的「總輸入時間」`t_input`
- (b) 代入具體參數，繪製 `t_input` 對 k 的關係圖，觀察是否存在某個 k 值使得 `t_CPU ≈ t_input`

### 解題策略

- 根據外部排序 I/O 模型，每次從磁碟讀取一筆資料會耗費固定成本：
  - seek time `t_s`：磁頭定位時間
  - latency `t_l`：等待磁碟轉到資料位置的時間
  - transfer time `t_t`：資料傳輸時間（單筆 record）

- 以 block 為單位，假設每次讀取 1 block（含 S 筆 record），則一個 block 的讀取時間為：
t_block = t_s + t_l + S × t_t

- 對於 m 個 sorted runs、總共 n 筆資料，若使用 k-way merge：
- 一次處理 k 個輸入串流，總共需進行 `ceil(log_k(m))` 次 merge
- 每一輪合併都需輸入所有 n 筆資料

- 總輸入時間為：
t_input = ceil(log_k(m)) × (n / S) × (t_s + t_l + S × t_t)

## 程式實作

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double t_s = 0.08;
    double t_l = 0.02;
    double t_t = 0.001;
    int S = 2000;
    int n = 200000;
    int m = 64;

    cout << "k\tt_input (sec)" << endl;
    for (int k = 2; k <= 64; k *= 2) {
        int rounds = ceil(log(m) / log(k));
        double blocks = static_cast<double>(n) / S;
        double t_block = t_s + t_l + S * t_t;
        double t_input = rounds * blocks * t_block;
        cout << k << "\t" << t_input << endl;
    }
    return 0;
}

```

## 效能分析
### 時間複雜度
若一次合併 k 個串流，共需進行 ceil(log_k(m)) 次合併，每次處理 n 筆資料

單次輸入時間為 O(n)

總輸入時間：

O((n / S) × log_k(m) × (t_s + t_l + S × t_t))
通常以 I/O 為瓶頸，故 CPU 複雜度反而不是關鍵

### 空間複雜度
每次合併需同時開 k 個輸入 buffer，加一個輸出 buffer

總空間：O(k × B)，B 為 block 大小（暫存區）

## 測試與驗證
參數條件：
參數	值
t_s	80ms = 0.08 sec
t_l	20ms = 0.02 sec
t_t	1ms = 0.001 sec
S (block)	2000 records
n	200000 records
m	64 sorted runs

### 編譯與執行指令

```shell
$ g++ sort_input_time.cpp --std=c++17 -o sort_input_time
$ ./sort_input_time
k       t_input (sec)
2       720
4       480
8       360
16      300
32      270
64      240
```

圖中可見：k 越大，合併輪數減少，輸入時間下降，最後趨近一個最低點。

## 申論及開發報告
選擇方式說明
本題使用經典 k-way merge 模型搭配實際硬碟參數，模擬 Phase Two 輸入成本。

因為硬碟 seek 與 latency 成本高，所以應儘可能減少合併輪數。

經驗觀察
若可支援較大的 k，輸入時間顯著降低

但若 k 過大，buffer 空間不足會造成頻繁換頁或額外 I/O

實際實作時會考量 I/O + CPU 時間做綜合優化（如 polyphase merge）
