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

// Quick Sort（三數取中法 pivot）
int medianOfThree(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[high] < arr[low]) swap(arr[low], arr[high]);
    if (arr[mid] < arr[low]) swap(arr[mid], arr[low]);
    if (arr[high] < arr[mid]) swap(arr[high], arr[mid]);
    swap(arr[mid], arr[high - 1]);
    return arr[high - 1];
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = medianOfThree(arr, low, high);
    int i = low;
    int j = high - 1;

    while (true) {
        while (arr[++i] < pivot) {}
        while (arr[--j] > pivot) {}
        if (i < j) swap(arr[i], arr[j]);
        else break;
    }
    swap(arr[i], arr[high - 1]);
    return i;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low + 10 <= high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
    else {
        // 小陣列用 insertion sort
        for (int p = low + 1; p <= high; p++) {
            int tmp = arr[p];
            int j;
            for (j = p; j > low && arr[j - 1] > tmp; j--)
                arr[j] = arr[j - 1];
            arr[j] = tmp;
        }
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
    
    cout << "Testing Quick Sort (Permute):" << endl;
    for (int t = 0; t < trials; t++) {
        for (int i = 0; i < n; i++) arr[i] = i + 1;
        Permute(arr);

        start = high_resolution_clock::now();
        quickSort(arr, 0, n - 1);
        end = high_resolution_clock::now();

        duration = duration_cast<microseconds>(end - start).count();
        //cout << t + 1 << ": " << duration << " microseconds" << endl;
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
