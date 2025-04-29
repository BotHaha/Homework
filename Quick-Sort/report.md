# 41125243 
# 41043146

作業二 Quick Sort

## 解題說明

### 問題描述

本題要求使用 Quick Sort 針對指定數量的整數進行排序，並分析其效能。

### 解題策略

1. 使用隨機排列產生器（程式 7.20）產生測試資料。
2. 使用快速排序（Quick Sort）方法進行排序：
   每次選取最後一個元素作為 pivot。
   將小於等於 pivot 的元素移到左邊，大於 pivot 的移到右邊。
   分別對左右子陣列遞迴排序。
3. 在排序過程前後顯示數列內容，確認排序正確性。
4. 使用 chrono 函式庫測量 Quick Sort 執行所需的時間，並輸出效能結果。
## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>  // 引入 chrono
using namespace std;
using namespace chrono;

// 洗牌（亂數排列）
template <class T>
void Permute(T *a, int n) {
    for (int i = n; i >= 2; i--) {
        int j = rand() % i;
        swap(a[j], a[i - 1]);
    }
}

// 快速排序 partition
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    int j;
    for (j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// 快速排序主體
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    srand(time(0));

    int n = 2000;
    vector<int> arr(n);

    // 填入順序 1, 2, ..., n
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    Permute(&arr[0], n); // 把數列打亂

    // 計算排序時間
    auto start = high_resolution_clock::now();  // 開始計時
    quickSort(arr, 0, n - 1);
    auto end = high_resolution_clock::now();  // 結束計時

    // 計算時間差
    auto duration = duration_cast<microseconds>(end - start).count();

    // 輸出排序後的結果（可選）
    // for (int i = 0; i < arr.size(); i++) {
    //     cout << arr[i] << " ";
    // }
    // cout << endl;

    cout << "Sorting time: " << duration << " microseconds" << endl;

    return 0;
}

```

## 效能分析

1. 時間複雜度：最佳情況 $O(nlogn)$、最壞情況 $O(n^2)$、平均情況 $O(nlogn)$
2. 空間複雜度：空間複雜度為 $O(logn)$ ~ $O(n)$。

## 測試與驗證

### 平均測試案例

使用 Permute() 函式

| 測試案例 | 輸入參數 $n$ | Timer 精度（δ) | 排序執行時間 |
|----------|--------------|--------------|-------------|
| 測試一   | $n = 500$    | 100ns        | 53ms       |
| 測試二   | $n = 1000$   | 100ns        | 115ms      |
| 測試三   | $n = 2000$   | 100ns        | 262ms      |
| 測試四   | $n = 3000$   | 100ns        | 402ms      |
| 測試五   | $n = 4000$   | 100ns        | 599ms      | 
| 測試六   | $n = 5000$   | 100ns        | 789ms      | 

### 圖表（x 軸為 n，y 軸為時間）



### 編譯與執行指令

```shell
g++ quicksort.cpp -o quicksort
./quicksort
```

### 結論

1. Quick Sort 能有效率地將亂序的整數數列進行排序。
2. 使用遞迴及分割策略，使得大部分情況下排序時間接近 O(n log n)。
3. 透過 chrono 測量顯示，排序的時間隨著資料量大小變化，但在小型資料下仍能快速完成。

## 申論及開發報告

### 使用 Quick Sort 的理由：

1. Quick Sort 平均時間複雜度為 O(n log n)，在實際應用中表現優異。
2. 實作簡單，且能直接就地排序（in-place），不需額外大量記憶體空間。
3. 對隨機排列的資料（本題使用 Permute 隨機排列）排序效果特別好，符合本題要求。


