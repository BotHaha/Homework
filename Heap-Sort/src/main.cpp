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

// Heapify 子函式
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

// Heap Sort 實作
void heapSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        maxHeapify(arr, i, 0);
    }
}

int main() {
    srand(time(0));

    int n = 500; // 資料量大小
    int trials = 30; // 平均情況測試次數

    vector<int> arr(n);
    double total_time = 0;
    double worst_time = 0;

    //測量時間精度
    auto start = high_resolution_clock::now();
    auto end = high_resolution_clock::now();
    double duration = duration_cast<nanoseconds>(end - start).count();
    cout << "Timer" << ": " << duration << " ms" << endl;
    cout << "Testing Heap Sort (Permute):" << endl;
    for (int t = 0; t < trials; t++) {
        for (int i = 0; i < n; i++) arr[i] = i + 1;
        Permute(arr);

        start = high_resolution_clock::now();
        heapSort(arr);
        end = high_resolution_clock::now();

        duration = duration_cast<microseconds>(end - start).count();
        //cout << "Trial " << t + 1 << ": " << duration << " microseconds" << endl;
        total_time += duration;
        worst_time = max(worst_time, duration);
    }
    cout << "Average time: " << total_time / trials << " microseconds" << endl;
    cout << "------------------------" << endl;
    cout << "Worst-case time: " << worst_time << " microseconds" << endl;

    // 測試記憶體使用量
    printMemoryUsage();

    return 0;
}
