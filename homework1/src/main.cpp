#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace chrono;

// Random permutation generator (程式 7.20)
template <class T>
void Permute(T *a, int n) {
    for (int i = n; i >= 2; i--) {
        int j = rand() % i;
        swap(a[j], a[i - 1]);
    }
}

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


int main() {
    srand(time(0));
    int n = 500; //測試 n=500、1000、2000、3000、4000、5000
    vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = i + 1;

    // 測量 timer 精度
    auto timer_start = high_resolution_clock::now();
    auto timer_end = high_resolution_clock::now();
    auto delta = duration_cast<nanoseconds>(timer_end - timer_start).count();
    cout << "Timer precision (delta δ): " << delta << " nanoseconds" << endl;

    // 顯示原始陣列
    Permute(&arr[0], n);
    cout << "Original array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    // 計算排序所需時間
    auto start = high_resolution_clock::now();
    insertionSort(arr);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();

    // 顯示排序後陣列
    cout << "Sorted array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Sorting time: " << duration << " microseconds" << endl;
    return 0;
}
