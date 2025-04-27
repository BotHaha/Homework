#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace chrono;

// 隨機排列器
template <class T>
void Permute(T* a, int n) {
    for (int i = n; i >= 2; i--) {
        int j = rand() % i;
        swap(a[j], a[i - 1]);
    }
}

// Heap Sort 子程序
void maxHeapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void buildMaxHeap(vector<int>& arr) {
    int n = arr.size();
    for (int i = n/2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    buildMaxHeap(arr);
    for (int i = n-1; i > 0; i--) {
        swap(arr[0], arr[i]);
        maxHeapify(arr, i, 0);
    }
}

int main() {
    srand(time(0));
    int n = 10;        // 資料量
    int trials = 30;     // 測試次數

    long long worst_time = 0;
    vector<int> worst_case;

    for (int t = 0; t < trials; t++) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++) arr[i] = i + 1;

        Permute(&arr[0], n);

        vector<int> temp = arr; // 保留一份原資料
        auto start = high_resolution_clock::now();
        heapSort(temp);
        auto end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end - start).count();

        cout << "Trial " << t+1 << " - Sorting time: " << duration << " ms" << endl;

        if (duration > worst_time) {
            worst_time = duration;
            worst_case = arr; // 記錄這組資料
        }
    }

    cout << "Worst case sorting time: " << worst_time << " ms" << endl;

    return 0;
}
