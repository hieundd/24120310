#include<iostream>
#include<vector>
#include<stack>
#include<queue>

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

vector<int> NLR(NODE* pRoot) {
	vector<int> v;
	stack<NODE*> s;
	if (pRoot == nullptr) return v;
	s.push(pRoot);
	while (!s.empty()) {
		NODE* curr = s.top();
		s.pop();
		v.push_back(curr->key);
		// Push phải rồi trái
		if (curr->p_right != nullptr)
			s.push(curr->p_right);
		if (curr->p_left != nullptr)
			s.push(curr->p_left);
	}
	return v;
}

vector<int> LNR(NODE* pRoot) {
	vector<int> v;
	stack<NODE*> s;
	NODE* tmp = pRoot;
	while (tmp != nullptr || s.empty() == false) {
		while (tmp != nullptr) {
			s.push(tmp);
			tmp = tmp->p_left;
		}
		tmp = s.top();
		s.pop();
		v.push_back(tmp->key);
		tmp = tmp->p_right;
	}
	return v;
}

vector<int> LRN(NODE* pRoot) {
	vector<int> v;
	stack<NODE*> s;
	while (true) {
		while (pRoot) {
			s.push(pRoot);
			s.push(pRoot);
			pRoot = pRoot->p_left;
		}
		if (s.empty())
			return v;
		pRoot = s.top();
		s.pop();
		if (!s.empty() && s.top() == pRoot)
			pRoot = pRoot->p_right;
		else {
			v.push_back(pRoot->key);
			pRoot = nullptr;
		}
	}
	return v;
}

vector<vector<int>> LevelOrder(NODE* pRoot) {
	if (pRoot == nullptr)
		return {};

	queue<NODE*> q;
	vector<vector<int>> v;
	q.push(pRoot);
	int level = 0;

	while (!q.empty()) {
		int len = q.size();
		v.push_back({});

		for (int i = 0; i < len; i++) {
			NODE* p = q.front();
			q.pop();
			v[level].push_back(p->key);
			if (p->p_left != nullptr)
				q.push(p->p_left);
			if (p->p_right != nullptr)
				q.push(p->p_right);
		}
		level++;
	}
	return v;
}

int count(NODE* pRoot) {
	int dem = 0;
	stack<NODE*> s;
	NODE* tmp = pRoot;
	while (tmp != nullptr || s.empty() == false) {
		while (tmp != nullptr) {
			s.push(tmp);
			tmp = tmp->p_left;
		}
		tmp = s.top();
		s.pop();
		dem++;
		tmp = tmp->p_right;
	}
	return dem;
}

int sumNode(NODE* pRoot) {
	int sum = 0;
	stack<NODE*> s;
	NODE* tmp = pRoot;
	while (tmp != nullptr || s.empty() == false) {
		while (tmp != nullptr) {
			s.push(tmp);
			tmp = tmp->p_left;
		}
		tmp = s.top();
		s.pop();
		sum+= tmp->key;
		tmp = tmp->p_right;
	}
	return sum;
}

int heightNode(NODE* pRoot, int value) {
	if (pRoot == nullptr) return -1;

	NODE* target = nullptr;
	queue<NODE*> q;
	q.push(pRoot);

	while (!q.empty()) {
		NODE* curr = q.front(); q.pop();
		if (curr->key == value) {
			target = curr;
			break;
		}
		if (curr->p_left) q.push(curr->p_left);
		if (curr->p_right) q.push(curr->p_right);
	}

	if (target == nullptr) return -1;

	int height = -1;
	q.push(target);
	while (!q.empty()) {
		int levelSize = q.size();
		while (levelSize--) {
			NODE* curr = q.front(); q.pop();
			if (curr->p_left) q.push(curr->p_left);
			if (curr->p_right) q.push(curr->p_right);
		}
		height++;
	}
	return height;
}

int Level(NODE* pRoot, NODE* p) {
	if (pRoot == nullptr || p == nullptr) return -1;

	queue<NODE*> q;
	q.push(pRoot);
	int level = 0;

	while (!q.empty()) {
		int levelSize = q.size();

		for (int i = 0; i < levelSize; ++i) {
			NODE* curr = q.front();
			q.pop();

			if (curr == p) return level;

			if (curr->p_left) q.push(curr->p_left);
			if (curr->p_right) q.push(curr->p_right);
		}
		level++;
	}
	return -1;
}

int countLeaf(NODE* pRoot) {
	if (pRoot == nullptr) return 0;
	int count = 0;
	stack<NODE*> s;
	s.push(pRoot);
	while (!s.empty()) {
		NODE* curr = s.top(); s.pop();
		if (curr->p_left == nullptr && curr->p_right == nullptr) {
			count++;
		}
		if (curr->p_right) s.push(curr->p_right);
		if (curr->p_left) s.push(curr->p_left);
	}
	return count;
}
