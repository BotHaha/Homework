# 41125243 
# 41043146

作業二 (Merge Sort 使用Iterative版本)

## 解題說明

### 問題描述

本題要求使用 Merge Sort 針對指定數量的整數進行排序，並分析其效能。

### 解題策略

1. 使用隨機排列產生器（程式 7.20）產生測試資料。
2. 若前方元素較大則向右移動，直到找到適當位置。
3. 將元素插入正確位置。
4. 從第二個元素開始，逐步與前方元素比較。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace chrono;

// 隨機排列產生器 (程式 7.20)
template <class T>
void Permute(T *a, int n) {
    for (int i = n; i >= 2; i--) {
        int j = rand() % i;
        swap(a[j], a[i - 1]);
    }
}

// 合併兩個已排序子陣列
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Iterative Merge Sort
void mergeSortIterative(vector<int>& arr) {
    int n = arr.size();
    for (int curr_size = 1; curr_size <= n - 1; curr_size *= 2) {
        for (int left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = min(left_start + curr_size - 1, n - 1);
            int right_end = min(left_start + 2 * curr_size - 1, n - 1);
            merge(arr, left_start, mid, right_end);
        }
    }
}

int main() {
    srand(time(0));
    int n = 10;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = i + 1;

    // 測量 timer 精度
    auto timer_start = high_resolution_clock::now();
    auto timer_end = high_resolution_clock::now();
    auto delta = duration_cast<nanoseconds>(timer_end - timer_start).count();
    cout << "Timer precision (delta δ): " << delta << " nanoseconds" << endl;

    Permute(&arr[0], n);

    cout << "Original array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    auto start = high_resolution_clock::now();
    mergeSortIterative(arr);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();

    cout << "Sorted array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    cout << "Sorting time: " << duration << " microseconds" << endl;

    return 0;
}
```

## 效能分析

1. 時間複雜度：最佳情況 $O(n/log/n)$、最壞情況 $O(n/log/n)$、平均情況 $O(n/log/n)$
2. 空間複雜度：空間複雜度為 $O(n)$。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $n$ | Timer 精度（δ) | 排序執行時間 |
|----------|--------------|--------------|-------------|
| 測試一   | $n = 500$    | ns        | ms         |
| 測試二   | $n = 1000$   | ns        | ms        |
| 測試三   | $n = 2000$   | ns        | ms        |
| 測試四   | $n = 3000$   | ns        | ms       |
| 測試五   | $n = 4000$   | ns        | ms        | 
| 測試六   | $n = 5000$   | ns        | ms        | 

### 編譯與執行指令



### 結論

1. 程式能正確計算 Timer 精度和最終排序執行時間。  
2. 在 $n = 3000$ 的情況下，程式 Timer 精度突然上升，導致排序時間異常增加，我認為是當時執行程式時系統背景程序活動增加，影響到測量準確性。
3. 測試案例涵蓋多種不同資料量測試（$n = 500$、$n = 1000$、$n = 2000$、$n = 3000$、$n = 4000$、$n = 5000$），驗證程式能夠執行少量和大量的排序。

## 申論及開發報告

### 使用 Insertion Sort 的理由：
