#include<iostream>
#include<stack>
#include<algorithm>

using namespace std;

struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;
};

// 1. Tạo node mới
NODE* createNode(int data) {
    NODE* p = new NODE;
    p->key = data;
    p->height = 1;
    p->p_left = nullptr;
    p->p_right = nullptr;
    return p;
}

int height(NODE* p) {
    return (p == nullptr) ? 0 : p->height;
}

int getBalance(NODE* p) {
    return (p == nullptr) ? 0 : height(p->p_left) - height(p->p_right);
}

NODE* rightRotate(NODE* y) {
    NODE* x = y->p_left;
    NODE* T2 = x->p_right;

    x->p_right = y;
    y->p_left = T2;

    y->height = 1 + max(height(y->p_left), height(y->p_right));
    x->height = 1 + max(height(x->p_left), height(x->p_right));

    return x;
}

NODE* leftRotate(NODE* x) {
    NODE* y = x->p_right;
    NODE* T2 = y->p_left;

    y->p_left = x;
    x->p_right = T2;

    x->height = 1 + max(height(x->p_left), height(x->p_right));
    y->height = 1 + max(height(y->p_left), height(y->p_right));

    return y;
}

// 2. Insert node vào AVL
void Insert(NODE*& pRoot, int x) {
    if (pRoot == nullptr) {
        pRoot = createNode(x);
        return;
    }

    if (x < pRoot->key)
        Insert(pRoot->p_left, x);
    else if (x > pRoot->key)
        Insert(pRoot->p_right, x);
    else
        return; // giá trị đã tồn tại, không chèn

    // Cập nhật chiều cao
    pRoot->height = 1 + max(height(pRoot->p_left), height(pRoot->p_right));

    // Cân bằng
    int balance = getBalance(pRoot);

    // 4 trường hợp
    if (balance > 1 && x < pRoot->p_left->key) {
        pRoot = rightRotate(pRoot);
    }
    else if (balance < -1 && x > pRoot->p_right->key) {
        pRoot = leftRotate(pRoot);
    }
    else if (balance > 1 && x > pRoot->p_left->key) {
        pRoot->p_left = leftRotate(pRoot->p_left);
        pRoot = rightRotate(pRoot);
    }
    else if (balance < -1 && x < pRoot->p_right->key) {
        pRoot->p_right = rightRotate(pRoot->p_right);
        pRoot = leftRotate(pRoot);
    }
}

// Hàm phụ: tìm node nhỏ nhất
NODE* minValueNode(NODE* node) {
    NODE* current = node;
    while (current->p_left != nullptr)
        current = current->p_left;
    return current;
}

// 3. Xóa node khỏi AVL
void Remove(NODE*& pRoot, int x) {
    if (pRoot == nullptr) return;

    if (x < pRoot->key)
        Remove(pRoot->p_left, x);
    else if (x > pRoot->key)
        Remove(pRoot->p_right, x);
    else {
        // Node có một hoặc không con
        if (pRoot->p_left == nullptr || pRoot->p_right == nullptr) {
            NODE* temp = (pRoot->p_left) ? pRoot->p_left : pRoot->p_right;
            if (temp == nullptr) {
                temp = pRoot;
                pRoot = nullptr;
            }
            else {
                *pRoot = *temp;
            }
            delete temp;
        }
        else {
            NODE* temp = minValueNode(pRoot->p_right);
            pRoot->key = temp->key;
            Remove(pRoot->p_right, temp->key);
        }
    }

    if (pRoot == nullptr) return;

    // Cập nhật chiều cao
    pRoot->height = 1 + max(height(pRoot->p_left), height(pRoot->p_right));

    // Cân bằng
    int balance = getBalance(pRoot);

    if (balance > 1 && getBalance(pRoot->p_left) >= 0)
        pRoot = rightRotate(pRoot);
    else if (balance > 1 && getBalance(pRoot->p_left) < 0) {
        pRoot->p_left = leftRotate(pRoot->p_left);
        pRoot = rightRotate(pRoot);
    }
    else if (balance < -1 && getBalance(pRoot->p_right) <= 0)
        pRoot = leftRotate(pRoot);
    else if (balance < -1 && getBalance(pRoot->p_right) > 0) {
        pRoot->p_right = rightRotate(pRoot->p_right);
        pRoot = leftRotate(pRoot);
    }
}

// 4. Kiểm tra cây có phải AVL không (không đệ quy)
bool isAVL(NODE* pRoot) {
    if (!pRoot) return true;

    stack<NODE*> s;
    s.push(pRoot);

    while (!s.empty()) {
        NODE* node = s.top(); s.pop();
        int bf = getBalance(node);
        if (abs(bf) > 1)
            return false;
        if (node->p_right) s.push(node->p_right);
        if (node->p_left) s.push(node->p_left);
    }

    return true;
}
