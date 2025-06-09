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

### 1. 標頭與命名空間
```cpp
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;
```
這部分引入必要的標頭：

<iostream>：輸出輸入功能

<vector>：使用向量作為堆的底層儲存結構

<stdexcept>：提供 runtime_error 例外處理

### 2. 抽象類別 MinPQ
```cpp
template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T&) = 0;
    virtual void Pop() = 0;
};
```
這是一個模板抽象類別（Min Priority Queue），提供四個純虛擬函式，定義了最小優先佇列應有的基本操作介面：

IsEmpty()：檢查是否為空堆

Top()：取得目前堆中最小值

Push()：插入新元素

Pop()：移除最小元素

### 3. 類別 MinHeap（具體實作）
```cpp
template <class T>
class MinHeap : public MinPQ<T> {
    ...
};
```
這個類別繼承自 MinPQ，使用向量 vector<T> 實作最小堆的功能。

成員函式：
HeapifyUp(int index)：插入新元素後，將其「上浮」到正確位置

HeapifyDown(int index)：刪除最小元素後，將新的根節點「下沉」以恢復堆序性

Push(const T& item)：新增元素並執行 HeapifyUp

Pop()：刪除最小元素並執行 HeapifyDown

Top()：回傳堆中最小元素（data[0]）

IsEmpty()：回傳是否為空

### 4. 主程式 main()
```cpp
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
這段程式是為了測試 MinHeap 的功能，操作如下：
插入 4 個元素：5、2、8、1
接著重複印出最小值並刪除，直到堆為空

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
