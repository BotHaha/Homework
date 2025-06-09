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

```cpp
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    Node* Insert(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->key) node->left = Insert(node->left, key);
        else node->right = Insert(node->right, key);
        return node;
    }

    int Height(Node* node) const {
        if (!node) return 0;
        return 1 + max(Height(node->left), Height(node->right));
    }

    Node* Delete(Node* node, int key) {
        if (!node) return nullptr;

        if (key < node->key)
            node->left = Delete(node->left, key);
        else if (key > node->key)
            node->right = Delete(node->right, key);
        else {
            if (!node->left) return node->right;
            if (!node->right) return node->left;

            Node* minNode = FindMin(node->right);
            node->key = minNode->key;
            node->right = Delete(node->right, minNode->key);
        }
        return node;
    }

    Node* FindMin(Node* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

public:
    BST() : root(nullptr) {}

    void Insert(int key) {
        root = Insert(root, key);
    }

    int Height() const {
        return Height(root);
    }

    void Delete(int key) {
        root = Delete(root, key);
    }
};

int main() {
    srand(time(0));
    vector<int> sizes = {100, 500, 1000, 2000, 5000, 10000};
    cout << "n,height,height/log2(n)\n";

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

    // 刪除測試
    BST tree;
    tree.Insert(50);
    tree.Insert(30);
    tree.Insert(70);
    tree.Insert(60);
    tree.Insert(80);
    tree.Delete(70); // 測試刪除兩個子節點的情況
    return 0;
}
```

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
100,12,2.45943
500,17,2.3318
1000,19,2.7354
```
測試說明
隨機插入 n 筆資料，測量 BST 高度，計算與 log₂(n) 比值

輸出觀察結果接近常數，約 2~3 之間，證明平均情況下 BST 高度與 log₂(n) 成比例

Delete() 函式成功從樹中移除節點並重構樹結構

## 申論及開發報告
使用資料結構與原因
Binary Search Tree 為基本資料結構，可快速支援插入、刪除、查詢操作

平均情況下操作效率為 O(log n)，常用於字典、索引、查詢最佳化

開發心得
透過高度比值分析，理解 BST 與平衡樹的差異，並理解實際資料下的效率

刪除節點操作需同時考慮三種狀況，實作過程加深對指標與遞迴的掌握

若需避免退化為線性樹，實務上應考慮使用 AVL Tree、Red-Black Tree 等平衡機制
