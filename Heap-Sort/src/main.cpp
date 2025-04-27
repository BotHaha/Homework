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
