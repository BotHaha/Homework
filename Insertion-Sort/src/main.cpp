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
