#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct NODE {
	int	key;
	NODE* p_next;
};

struct Stack {
	NODE* top;
};

Stack* intializeStack(Stack& s);
void push(Stack& s, int key);
int pop(Stack& s);
int size(Stack &s);
bool isEmpty(Stack &s);

Stack* intializeStack(Stack &s) {
	s.top = nullptr;
	return&s;
}

void push(Stack& s, int key) {
	NODE* p = new NODE;
	p->key = key;
	p->p_next = nullptr;
	if (isEmpty(s)) {
		s.top = p;
	}
	else {
		p->p_next = s.top;
		s.top = p;
	}
}

int pop(Stack& s) {
	int x;
	NODE* p = s.top;
	if (isEmpty(s)) {
		return -1;
	}
	else {
		x = p->key;
		s.top = p->p_next;
		delete p;
	}
	return x;
}

int size(Stack &s) {
	NODE* p = s.top;
	int count = 0;
	while (p != nullptr) {
		count++;
		p = p->p_next;
	}
	return count;
}
bool isEmpty(Stack &s) {
	if (s.top == nullptr) {
		return true;
	}
	return false;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    Stack s;
    string pre;

    while (fin >> pre) {
        if (pre == "init") {
            intializeStack(s);
        }
        else if (pre == "push") {
            int x;
            fin >> x;
            push(s, x);
        }
        else if (pre == "pop") {
            pop(s);
        }

        if (isEmpty(s)) {
            fout << "EMPTY" << endl;
        }
        else {
            NODE* p = s.top;
            int n = size(s);
            int* arr = new int[n];
            int idx = n - 1;
            while (p != nullptr) {
                arr[idx--] = p->key;
                p = p->p_next;
            }
            for (int i = 0; i < n; ++i) {
                fout << arr[i];
                if (i != n - 1) fout << " ";
            }
            fout << endl;
            delete[] arr;
        }
    }

    fin.close();
    fout.close();
    return 0;
}
