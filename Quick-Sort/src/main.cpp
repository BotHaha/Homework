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

