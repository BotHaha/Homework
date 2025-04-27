# 41125243 
# 41043146

作業四 (Heap Sort)

## 解題說明

Heap Sort 是一種基於堆積資料結構設計的排序演算法，
具有良好的時間複雜度 ，且能在不需要額外大量記憶體的情況下完成排序。

### 問題描述

本題要求使用 Heap Sort 針對指定數量的整數進行排序，並分析其效能。

### 解題策略

1. 使用隨機排列產生器（程式 7.20）產生測試資料。
2. 將原始資料轉換成最大堆積（Max Heap）。
3. 重複將堆積頂端（最大值）取出，移到陣列末尾，並重新調整剩餘元素成為新的 Max Heap。

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

// 隨機排列產生器
template <class T>
void Permute(T* a, int n) {
    for (int i = n; i >= 2; i--) {
        int j = rand() % i;
        swap(a[j], a[i - 1]);
    }
}

// 維護最大堆積性質
void maxHeapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

// 建立最大堆積
template <class T>
void buildMaxHeap(vector<T>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
}

// Heap Sort 主程式
template <class T>
void heapSort(vector<T>& arr) {
    int n = arr.size();
    buildMaxHeap(arr);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        maxHeapify(arr, i, 0);
    }
}

int main() {
    srand(time(0));
    int n = 10;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = i + 1;

    auto timer_start = high_resolution_clock::now();
    auto timer_end = high_resolution_clock::now();
    auto delta = duration_cast<nanoseconds>(timer_end - timer_start).count();
    cout << "Timer precision (delta δ): " << delta << " nanoseconds" << endl;

    Permute(&arr[0], n);
    /*
    cout << "Original array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;
    */
    auto start = high_resolution_clock::now();
    heapSort(arr);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    /*
    cout << "Sorted array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;
    */
    cout << "Sorting time: " << duration << " microseconds" << endl;
    return 0;
}
```

## 效能分析

1. 時間複雜度：最佳情況 $O(n)$、最壞情況 $O(nlogn)$、平均情況 $O(nlogn)$
2. 空間複雜度：空間複雜度為 $O(n)$ + $O(1)$。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $n$ | Timer 精度（δ) | 排序執行時間 |
|----------|--------------|--------------|-------------|
| 測試一   | $n = 500$    | 100ns        | 197ms         |
| 測試二   | $n = 1000$   | 100ns        | 463ms        |
| 測試三   | $n = 2000$   | 100ns        | 871ms        |
| 測試四   | $n = 3000$   | 100ns        | 1313ms       |
| 測試五   | $n = 4000$   | 100ns        | 1730ms        | 
| 測試六   | $n = 5000$   | 100ns        | 3067ms        | 

### 編譯與執行指令

```shell
$ g++ main.cpp --std=c++21 -o main.exe
$ .\main.exe
Timer precision (delta δ): 0 nanoseconds
Original array: 7 2 5 10 4 8 6 1 9 3
Sorted array: 1 2 3 4 5 6 7 8 9 10
Sorting time: 50 microseconds
```

### 結論

1. 透過測試，可以確認 Heap Sort 能正確地將隨機排列的資料排序完成，且在小型資料上具備穩定且快速的效能。
2. 測試案例涵蓋多種不同資料量測試（$n = 500$、$n = 1000$、$n = 2000$、$n = 3000$、$n = 4000$、$n = 5000$），驗證程式能夠執行少量和大量的排序。

## 申論及開發報告

### 使用 Heap Sort 的理由：

1. Heap Sort 透過最大堆積的結構進行排序，具有$O(nlogn)$的穩定時間複雜度，不受初始資料排列影響。
2. 相比 Quick Sort 可能退化成  的情況，Heap Sort 提供了更可靠的性能保障。
3. 在記憶體空間有限、需要 in-place 排序時，Heap Sort 是一個理想選擇，因為它不需要額外的輔助陣列。

### 測試設計與開發經驗

本次作業中，使用隨機排列器產生不同初始排列，並測試 Heap Sort 的正確性與效能。
開發過程中特別注意了 maxHeapify 遞迴調整過程中邊界條件的處理，確保每次調整能維持最大堆積性質，最終成功完成資料排序。
透過這些設計，Heap Sort 展現了即使在隨機資料情境下也能保持良好效能的特性，為組合排序函式提供了穩固的支持。
