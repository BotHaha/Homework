# 41125243
# 41043146

作業二：Binary Search Tree 

## 解題說明

### 問題描述

本題包含兩個部分：

(a) 隨機產生 n 筆資料建立 Binary Search Tree（BST），測量其高度與 log₂(n) 的比值，並重複實驗繪製關係圖。

(b) 實作一個從 BST 中刪除 key 為 k 的節點之函式，並分析其時間複雜度。

### 解題策略

- (a) 使用遞迴插入亂數資料至 BST，並定義函式計算樹高。
- 記錄 height / log₂(n) 的比值，驗證 BST 對平均資料是否趨近平衡。
- (b) 遞迴實作 BST 刪除節點操作，涵蓋三種情況：
  - 無子節點
  - 一個子節點
  - 兩個子節點（使用中序繼承者）


## 程式實作

### 1. 標頭與基本設定

```cpp
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;
```
這部分引入了 C++ 中必要的標頭檔，包含輸出輸入、數學函式、隨機數、時間控制與向量容器，並使用 std 命名空間簡化程式撰寫。

### 2. 結構定義：Node

```cpp
struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};
```
這是 BST 的基本節點結構。每個節點包含：

一個整數鍵值 key

指向左子節點與右子節點的指標

建構子初始化節點資料與左右節點為空指標

### 3. 類別定義：BST

```cpp
class BST {
    ...
};
```
這是整棵 Binary Search Tree 的類別定義。包含了 BST 的基本操作，分成私有與公開兩部分：

Insert(Node*, int)：遞迴將 key 插入適當位置

Height(Node*)：遞迴計算從某節點開始的最大高度

Delete(Node*, int)：刪除節點，並根據其子節點情況進行對應處理

FindMin(Node*)：尋找一棵子樹中最小值的節點（用於刪除時替代）

公開部分的函式是對外接口：

Insert(int)：插入節點（呼叫私有的遞迴實作）

Delete(int)：刪除節點

Height()：回傳整棵樹的高度

### 4. 主程式：隨機插入與高度測試

```cpp
vector<int> sizes = {100, 500, 1000, 2000, 5000, 10000};
for (int n : sizes) {
    BST tree;
    for (int i = 0; i < n; ++i) {
        int x = rand();
        tree.Insert(x);
    }
    int h = tree.Height();
    double ratio = h / log2(n);
    cout << n << "," << h << "," << ratio << "\n";
}
```
這段程式進行 BST 的實驗操作：

依序測試不同筆數 n 的資料量（從 100 到 10000）

對每一組 n 筆資料，產生隨機亂數並插入 BST

計算該樹的高度，並與理論的 log₂(n) 做比值比較

最後印出每組資料的結果

### 5. 節點刪除功能測試

```cpp
BST tree;
tree.Insert(50);
tree.Insert(30);
tree.Insert(70);
tree.Insert(60);
tree.Insert(80);
tree.Delete(70);
```
這段程式是用來測試 Delete() 函式：

建立一棵小型 BST

刪除具有兩個子節點的節點（key 為 70）

用以驗證刪除邏輯是否能正確處理中序繼承者的替換與重建子樹

## 效能分析
### 時間複雜度
操作	最佳情況	最差情況
插入	O(log n)	O(n)
查找高度	O(n)	O(n)
刪除節點	O(log n)	O(n)

說明：若 BST 平衡則為 log n，高度不平衡則最差退化為線性。

### 空間複雜度
O(n)：所有節點需佔用 n 個記憶體空間

額外遞迴堆疊最差為 O(n)，平均 O(log n)

## 測試與驗證
### 編譯與執行
```shell
$ g++ bst.cpp --std=c++21 -o bst.exe
$ ./bst.exe
n,height,height/log2(n)
100,14,2.10721
500,17,1.8961
1000,21,2.10721
2000,26,2.37101
5000,27,2.19732
10000,30,2.25772
```

測試說明
隨機插入 n 筆資料，測量 BST 高度，計算與 log₂(n) 比值

輸出觀察結果接近常數，約 2~3 之間，證明平均情況下 BST 高度與 log₂(n) 成比例

Delete() 函式成功從樹中移除節點並重構樹結構

### 測試輸出結果（BST 高度實驗）

| n     | height | height / log₂(n) |
|--------|--------|-------------------|
| 100    | 14     | 2.10721           |
| 500    | 17     | 1.8961            |
| 1000   | 21     | 2.10721           |
| 2000   | 26     | 2.37101           |
| 5000   | 27     | 2.19732           |
| 10000  | 30     | 2.25772           |

## 申論及開發報告
使用資料結構與原因
Binary Search Tree 為基本資料結構，可快速支援插入、刪除、查詢操作

平均情況下操作效率為 O(log n)，常用於字典、索引、查詢最佳化

開發心得
透過高度比值分析，理解 BST 與平衡樹的差異，並理解實際資料下的效率

刪除節點操作需同時考慮三種狀況，實作過程加深對指標與遞迴的掌握

若需避免退化為線性樹，實務上應考慮使用 AVL Tree、Red-Black Tree 等平衡機制
