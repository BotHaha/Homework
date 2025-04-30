# 41125243 
# 41043146

作業一 (Insertion Sort)

## 解題說明

### 問題描述

本題要求使用 Insertion Sort 針對指定數量的整數進行排序，並分析其效能。

### 解題策略

1. 使用隨機排列產生器（程式 7.20）產生測試資料。
2. 使用最壞情況產生器 ReversFill() 函式產生測試資料。
3. 若前方元素較大則向右移動，直到找到適當位置。
4. 將元素插入正確位置。
5. 從第二個元素開始，逐步與前方元素比較。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <Windows.h>
#include <Psapi.h>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace chrono;

// 隨機排列產生器
void Permute(vector<int>& a) {
    int n = a.size();
    for (int i = n; i >= 2; i--) {
        int j = rand() % i;
        swap(a[j], a[i - 1]);
    }
}

// 倒序排列產生器
void ReverseFill(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n; i++)
        a[i] = n - i;
}

// 記憶體使用量測函式
void printMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memInfo;
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
    cout << "------------------------" << endl;
    cout << "Memory Usage:" << endl;
    cout << "Working Set Size: " << memInfo.WorkingSetSize / 1024 << " KB" << endl;
    cout << "Peak Working Set Size: " << memInfo.PeakWorkingSetSize / 1024 << " KB" << endl;
    cout << "Pagefile Usage: " << memInfo.PagefileUsage / 1024 << " KB" << endl;
    cout << "------------------------" << endl;
}

// Insertion Sort 實作
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 主程式
int main() {
    srand(time(0));

    int n = 10; // 資料量大小
    int trials = 30; // 平均情況測試次數

    vector<int> arr(n);
    double total_time = 0;

    //測量時間精度
    auto start = high_resolution_clock::now();
    auto end = high_resolution_clock::now();
    double duration = duration_cast<nanoseconds>(end - start).count();
    cout << "Timer" << ": " << duration << " ms" << endl;

    
    cout << "Average-case testing (Permute):" << endl;
    for (int t = 0; t < trials; t++) {
        for (int i = 0; i < n; i++) arr[i] = i + 1;
        Permute(arr);

        start = high_resolution_clock::now();
        insertionSort(arr);
        end = high_resolution_clock::now();

        duration = duration_cast<microseconds>(end - start).count();
        //cout << t + 1 << ": " << duration << " ms" << endl;  //打印每一次排序所花的時間
        total_time += duration;
    }
    cout << "Average time: " << total_time / trials << " ms" << endl;
    cout << "------------------------" << endl;
    
    
    cout << "Worst-case testing (ReverseFill):" << endl;
    ReverseFill(arr);

    start = high_resolution_clock::now();
    insertionSort(arr);
    end = high_resolution_clock::now();

    duration = duration_cast<microseconds>(end - start).count();
    cout << "Worst-case time: " << duration << " ms" << endl;
    

    // 測試記憶體使用量
    printMemoryUsage();

    return 0;
}


```

## 效能分析

1. 時間複雜度：最佳情況 $O(n)$、最壞情況 $O(n^2)$、平均情況 $O(n^2)$
2. 空間複雜度：空間複雜度為 $O(1)$。

## 測試與驗證

### 平均情況測試案例

使用 Permule() 函式
| 測試案例 | 輸入參數 $n$ | Timer 精度（δ) | 排序執行時間 |
|----------|--------------|--------------|-------------|
| 測試一   | $n = 500$    | 100ns        | 1020ms       |
| 測試二   | $n = 1000$   | 100ns        | 3362ms       |
| 測試三   | $n = 2000$   | 100ns        | 13584ms      |
| 測試四   | $n = 3000$   | 100ns        | 37030ms      |
| 測試五   | $n = 4000$   | 100ns        | 69782ms     | 
| 測試六   | $n = 5000$   | 100ns        | 93997ms     | 

### 最壞情況測試案例

使用 ReverseFill() 函式
| 測試案例 | 輸入參數 $n$ | Timer 精度（δ) | 排序執行時間 |
|----------|--------------|--------------|-------------|
| 測試一   | $n = 500$    | 100ns        | 1422ms       |
| 測試二   | $n = 1000$   | 100ns        | 5603ms       |
| 測試三   | $n = 2000$   | 100ns        | 23661ms      |
| 測試四   | $n = 3000$   | 200ns        | 62580ms      |
| 測試五   | $n = 4000$   | 100ns        | 98040ms      | 
| 測試六   | $n = 5000$   | 100ns        | 145375ms     | 


### 圖表（x 軸為 n，y 軸為時間）

![image](https://github.com/user-attachments/assets/980a860f-d248-4a32-a31b-bd1d83903892)

### 編譯與執行指令
```shell
$ g++ main.cpp --std=c++21 -o main.exe
$ .\main.exe
Timer precision (delta δ): 0 nanoseconds
Original array: 3 10 1 4 6 2 7 5 9 8
Sorted array: 1 2 3 4 5 6 7 8 9 10
Sorting time: 15 microseconds
```

### 結論

1. 程式能正確計算 Timer 精度和最終排序執行時間。  
2. 利用最壞情況資料和平均時間資料測試後，效能分析測試時間最壞情況 $O(n^2)$比平均情況 $O(n^2)$多了快兩倍，我認為跟理論有差是因為測試比數不構造成的。
3. 測試案例涵蓋多種不同資料量測試（$n = 500$、$n = 1000$、$n = 2000$、$n = 3000$、$n = 4000$、$n = 5000$），驗證程式能夠執行少量和大量的排序。

## 申論及開發報告

### 使用 Insertion Sort 的理由：

1. **使用場景與效能觀察**    
   雖然 Insertion Sort 的時間複雜度在平均與最壞情況下為 O(n^2)，    
   但其實在資料量小（如 n < 20）或資料本身接近有序的情況下，    
   Insertion Sort 的效能往往超過其他複雜排序法（如 Merge Sort 或 Heap Sort）。
2. **對於小型或近乎排序的資料有較佳效能**
   Insertion Sort 在資料幾乎已經排序時效能非常高。
   其時間複雜度在最佳情況下為 O(n)，
   遠優於 Merge Sort 與 Heap Sort 的 O(n log n)。以下是一個幾乎排序的例子：
   
   ```cpp
   vector<int> arr = {1, 2, 3, 5, 4, 6, 7};
   ```
   
3. **空間需求小，適合記憶體有限的環境**
   Insertion Sort 不需要額外的記憶體空間，僅使用常數額外空間，
   屬於 in-place 排序法。這對於嵌入式系統或記憶體受限環境特別實用。
   
