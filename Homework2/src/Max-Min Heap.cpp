#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}

    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T&) = 0;
    virtual void Pop() = 0;
};

template <class T>
class MinHeap : public MinPQ<T> {
private:
    vector<T> data;

    void HeapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (data[index] < data[parent]) {
                swap(data[index], data[parent]);
                index = parent;
            } else break;
        }
    }

    void HeapifyDown(int index) {
        int n = data.size();
        while (2 * index + 1 < n) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < n && data[left] < data[smallest]) smallest = left;
            if (right < n && data[right] < data[smallest]) smallest = right;

            if (smallest != index) {
                swap(data[index], data[smallest]);
                index = smallest;
            } else break;
        }
    }

public:
    bool IsEmpty() const override {
        return data.empty();
    }

    const T& Top() const override {
        if (IsEmpty()) throw runtime_error("Heap is empty");
        return data[0];
    }

    void Push(const T& item) override {
        data.push_back(item);
        HeapifyUp(data.size() - 1);
    }

    void Pop() override {
        if (IsEmpty()) throw runtime_error("Heap is empty");
        data[0] = data.back();
        data.pop_back();
        if (!IsEmpty()) HeapifyDown(0);
    }
};

int main() {
    MinHeap<int> heap;

    heap.Push(5);
    heap.Push(2);
    heap.Push(8);
    heap.Push(1);

    while (!heap.IsEmpty()) {
        cout << heap.Top() << " ";
        heap.Pop();
    }

    return 0;
}
