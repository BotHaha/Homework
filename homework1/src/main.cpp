#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

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
    int n = 10;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = i + 1;

    Permute(&arr[0], n);

    cout << "Original array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    insertionSort(arr);

    cout << "Sorted array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
