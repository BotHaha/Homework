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
