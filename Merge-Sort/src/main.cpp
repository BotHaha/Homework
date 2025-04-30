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

// Merge Sort 實作
void merge(vector<int>& arr, int left, int mid, int right, vector<int>& temp) {
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (int l = left; l <= right; l++)
        arr[l] = temp[l];
}

void mergeSort(vector<int>& arr, int left, int right, vector<int>& temp) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, temp);
        mergeSort(arr, mid + 1, right, temp);
        merge(arr, left, mid, right, temp);
    }
}

int main() {
    srand(time(0));

    int n = 5000; // 資料量大小
    int trials = 30; // 平均情況測試次數

    vector<int> arr(n);
    vector<int> temp(n);
    double total_time = 0;

    //測量時間精度
    auto start = high_resolution_clock::now();
    auto end = high_resolution_clock::now();
    double duration = duration_cast<nanoseconds>(end - start).count();
    cout << "Timer" << ": " << duration << " ms" << endl;

    //測試平均時間
    cout << "Average-case testing (Permute):" << endl;
    for (int t = 0; t < trials; t++) {
        for (int i = 0; i < n; i++) arr[i] = i + 1;
        Permute(arr);

        start = high_resolution_clock::now();
        mergeSort(arr, 0, n - 1, temp);
        end = high_resolution_clock::now();

        duration = duration_cast<microseconds>(end - start).count();
        cout << "Trial " << t + 1 << ": " << duration << " microseconds" << endl;
        total_time += duration;
    }
    cout << "Average time: " << total_time / trials << " microseconds" << endl;
    cout << "------------------------" << endl;
    //測試最壞時間
    cout << "Worst-case testing (ReverseFill):" << endl;
    ReverseFill(arr);

    start = high_resolution_clock::now();
    mergeSort(arr, 0, n - 1, temp);
    end = high_resolution_clock::now();

    duration = duration_cast<microseconds>(end - start).count();
    cout << "Worst-case time: " << duration << " microseconds" << endl;


    // 測試記憶體使用量
    printMemoryUsage();

    return 0;
}
