#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>  // �ޤJ chrono
using namespace std;
using namespace chrono;

// �~�P�]�üƱƦC�^
template <class T>
void Permute(T *a, int n) {
    for (int i = n; i >= 2; i--) {
        int j = rand() % i;
        swap(a[j], a[i - 1]);
    }
}

// �ֳt�Ƨ� partition
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

// �ֳt�ƧǥD��
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

    // ��J���� 1, 2, ..., n
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    Permute(&arr[0], n); // ��ƦC����

    // �p��ƧǮɶ�
    auto start = high_resolution_clock::now();  // �}�l�p��
    quickSort(arr, 0, n - 1);
    auto end = high_resolution_clock::now();  // �����p��

    // �p��ɶ��t
    auto duration = duration_cast<microseconds>(end - start).count();

    // ��X�Ƨǫ᪺���G�]�i��^
    // for (int i = 0; i < arr.size(); i++) {
    //     cout << arr[i] << " ";
    // }
    // cout << endl;

    cout << "Sorting time: " << duration << " microseconds" << endl;

    return 0;
}

