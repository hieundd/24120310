#include <iostream>
#include<stack>
#include<queue>
#include<climits>

using namespace std;

struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
};

NODE* createNode(int data) {
    NODE* p = new NODE;
    p->key = data;
    p->p_left = nullptr;
    p->p_right = nullptr;
    return p;
}

NODE* Search(NODE* pRoot, int x) {
    NODE* curr = pRoot;
    while (curr != nullptr) {
        if (curr->key == x)
            return curr;

        else if (curr->key < x)
            curr = curr->p_right;
        else
            curr = curr->p_left;
    }
    return NULL;
}

void Insert(NODE*& pRoot, int x) {
    NODE* tmp = createNode(x);
    if (!pRoot) {
        pRoot = tmp;
        return;
    }
    NODE* parent = nullptr;
    NODE* curr = pRoot;
    while (curr) {
        parent = curr;
        if (x < curr->key) curr = curr->p_left;
        else if (x > curr->key) curr = curr->p_right;
        else return;
    }
    if (x < parent->key) parent->p_left = tmp;
    else parent->p_right = tmp;
}


void Remove(NODE* &pRoot, int x) {
    NODE* par = nullptr;
    NODE* curr = pRoot;

    while (curr && curr->key != x) {
        par = curr;
        if (x < curr->key) curr = curr->p_left;
        else curr = curr->p_right;
    }
    if (!curr) return;

    if (!curr->p_left || !curr->p_right) {
        NODE* child = curr->p_left ? curr->p_left : curr->p_right;
        if (!par) pRoot = child;
        else if (par->p_left == curr) par->p_left = child;
        else par->p_right = child;
        delete curr;
    }
    else {
        NODE* succParent = curr;
        NODE* succ = curr->p_right;
        while (succ->p_left) {
            succParent = succ;
            succ = succ->p_left;
        }
        curr->key = succ->key;
        if (succParent->p_left == succ)
            succParent->p_left = succ->p_right;
        else
            succParent->p_right = succ->p_right;
        delete succ;
    }
}

NODE* createTree(int a[], int n) {
    NODE* root = nullptr;
    for (int i = 0; i < n; ++i)
        Insert(root, a[i]);
    return root;
}

void removeTree(NODE* &pRoot) {
    if (!pRoot) return;
    stack<NODE*> s;
    s.push(pRoot);
    while (!s.empty()) {
        NODE* p = s.top();
        s.pop();
        if (p->p_left != nullptr) {
            s.push(p->p_left);
        }
        if (p->p_right != nullptr) {
            s.push(p->p_right);
        }
        delete p;
    }
    pRoot = nullptr;
}

int Height(NODE* pRoot) {
    if (!pRoot) return -1;
    int height = -1;
    queue<NODE*> q;
    q.push(pRoot);
    while (!q.empty()) {
        int levelSize = q.size();
        height++;
        for (int i = 0; i < levelSize; ++i) {
            NODE* p = q.front();
            q.pop();
            if (p->p_left != nullptr) {
                q.push(p->p_left);
            }
            if (p->p_right != nullptr) {
                q.push(p->p_right);
            }
        }
    }
    return height;
}

int countLess(NODE* pRoot, int x) {
    int count = 0;
    stack<NODE*> s;
    NODE* curr = pRoot;
    while (curr || !s.empty()) {
        while (curr) {
            s.push(curr);
            curr = curr->p_left;
        }
        curr = s.top(); s.pop();
        if (curr->key < x) {
            count++;
        }
        curr = curr->p_right;
    }
    return count;
}

int countGreater(NODE* pRoot, int x) {
    int count = 0;
    stack<NODE*> s;
    NODE* curr = pRoot;
    while (curr || !s.empty()) {
        while (curr!=NULL) {
            s.push(curr);
            curr = curr->p_right;
        }
        curr = s.top(); s.pop();
        if (curr->key > x) count++;
        curr = curr->p_left;
    }
    return count;
}

bool isBST(NODE* pRoot) {
    NODE* curr = pRoot;
    NODE* pre = nullptr;
    int prevValue = INT_MIN;

    while (curr != nullptr) {
        if (curr->p_left == nullptr) {
            if (curr->key <= prevValue) {
                return false;
            }
            prevValue = curr->key;
            curr = curr->p_right;
        }
        else {
            pre = curr->p_left;
            while (pre->p_right != nullptr && pre->p_right != curr) {
                pre = pre->p_right;
            }

            if (pre->p_right == nullptr) {
                pre->p_right = curr;
                curr = curr->p_left;
            }
            else {
                pre->p_right = nullptr;
                if (curr->key <= prevValue) {
                    return false;
                }
                prevValue = curr->key;
                curr = curr->p_right;
            }
        }
    }
    return true;
}

bool isFullBST(NODE* pRoot) {
    if (!pRoot) return true;
    queue<NODE*> q;
    q.push(pRoot);

    while (!q.empty()) {
        NODE* node = q.front(); q.pop();
        if ((node->p_left && !node->p_right) || (!node->p_left && node->p_right))
            return false;

        if (node->p_left) {
            q.push(node->p_left);
        }
        if (node->p_right) {
            q.push(node->p_right);
        }
    }
    return true;
}
