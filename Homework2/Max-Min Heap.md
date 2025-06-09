# 41125243
# 41043146

作業一 (Max-Min Heap)

## 解題說明
### 問題描述
本題要求實作一個最小優先佇列（Min Priority Queue），需定義一個抽象類別 MinPQ，包含四個基本操作介面：IsEmpty()、Top()、Push()、Pop()。接著，需實作一個具體類別 MinHeap，其操作邏輯需以最小堆積（Min Heap）為基礎，所有操作的時間複雜度需與最大堆（MaxHeap）相同，達到高效處理資料的效果。

### 解題策略
首先定義抽象類別 MinPQ，以泛型支援任意型別元素，並使用純虛擬函式來規範介面。

接著設計 MinHeap 類別，使用 std::vector<T> 作為底層資料容器，實作 array-based binary heap：

Push() 插入資料後進行「上浮」(HeapifyUp)

Pop() 移除頂部元素後進行「下沉」(HeapifyDown)

Top() 回傳堆頂最小元素

IsEmpty() 檢查堆是否為空

此資料結構可應用於許多演算法，例如 Dijkstra、A* 搜尋、模擬系統等。

## 程式實作

以下為主要程式碼 :

```cpp
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
```

## 效能分析
1. 時間複雜度
操作	時間複雜度	說明
Push	O(log n)	插入資料需上浮至正確位置
Pop	O(log n)	移除頂部資料後需下沉重建堆
Top	O(1)	回傳最小值為陣列第 0 項
IsEmpty	O(1)	判斷容器是否為空

2. 空間複雜度
O(n)：使用 std::vector<T> 儲存 n 筆資料

不額外使用遞迴或臨時陣列，額外空間開銷極小

## 測試與驗證
測試輸入程式
```shell
$ g++ main.cpp --std=c++21 -o main.exe
$ .\main.exe
1 2 5 8
```
測試說明
我們先插入數列：5, 2, 8, 1

執行過程中，每次 Top() 皆印出當前最小值

Pop() 後堆仍維持最小堆性質

最終輸出為升冪排序：1 2 5 8

## 申論及開發報告
使用資料結構與原因
Min Heap：選擇最小堆為底層結構，是因為其具備穩定、平衡的二元樹特性，能保證：

插入與刪除時間皆為 O(log n)

查詢最小值為 O(1)

std::vector：方便擴充與動態記憶體管理

利用 HeapifyUp/HeapifyDown 維護堆序性

開發心得
此實作深化了我對 STL 中 priority_queue 底層運作方式的理解。

抽象類別的使用也幫助我熟悉介面導向的程式設計模式（OOP interface design）。

此資料結構能廣泛應用於事件驅動模擬、路徑搜尋、排程器等實務場景。
