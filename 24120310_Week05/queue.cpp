#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct NODE {
	int key;
	NODE* p_next;
};

struct Queue {
	NODE* head;
	NODE* tail;
};

Queue* initializeQueue(Queue&q);
void enqueue(Queue & q, int key);
int dequeue(Queue & q);
int size(Queue &q);
bool isEmpty(Queue &q);

Queue* initializeQueue(Queue&q) {
	q.head = nullptr;
	q.tail = nullptr;
	return &q;
}

bool isEmpty(Queue &q) {
	if (q.head == nullptr) {
		return true;
	}
	return false;
}

void enqueue(Queue& q, int key) {
	NODE* p = new NODE;
	p->key = key;
	p->p_next = nullptr;
	if (q.head == nullptr) {
		q.head = p;
		q.tail = p;
	}
	else {
		q.tail->p_next = p;
		q.tail = p;  
	}
}

int dequeue(Queue& q) {
	NODE* p = q.head;
	int x;
	if (isEmpty(q)) {
		return-1;
	}
	else {
		x = p->key;
		q.head = p->p_next;
		delete p;
		if (q.head == nullptr) {
			q.tail = nullptr;
		}
	}
	return x;
}

int size(Queue &q) {
	NODE* p = new NODE;
	p = q.head;
	int count = 0;
	while (p != nullptr) {
		count++;
		p = p->p_next;
	}
	return count;
}


int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	Queue q;
	string pre;

	while (fin >> pre) {
		if (pre == "init") {
			initializeQueue(q);
		}
		else if (pre == "enqueue") {
			int x;
			fin >> x;
			enqueue(q, x);
		}
		else if (pre == "dequeue") {
			dequeue(q);
		}

		if (isEmpty(q)) {
			fout << "EMPTY" << endl;
		}
		else {
			NODE* p = q.head;
			while (p != nullptr) {
				fout << p->key;
				if (p->p_next != nullptr) fout << " ";
				p = p->p_next;
			}
			fout << endl;
		}
	}

	fin.close();
	fout.close();
	return 0;
}