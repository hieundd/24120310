#include <iostream>
#include <fstream>
#include <cstring>
using namespace  std;

void selection_sort(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		int min = i;
		for (int j = i+1; j < n; j++) {
			if (arr[j] < arr[min]) {
				min = j;
			}
		}
		int temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
}
void bubble_sort(int arr[], int n) {
	for (int i = 0; i < n-1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j + 1] = temp;
			}
		}
	}
}
void merge(int arr[], int left, int mid, int right) {
	int i = left, j = mid + 1, k = 0;
	int* temp = new int[right - left + 1];
	while (i <= mid && j <= right) {
		if (arr[i] <= arr[j]) {
			temp[k++] = arr[i++];
		}
		else {
			temp[k++] = arr[j++];
		}
	}
	while (i <= mid) {
		temp[k++] = arr[i++];
	}
	while (j <= right) {
		temp[k++] = arr[j++];
	}
	for (int r = 0; r < k; r++) {
		arr[left + r] = temp[r];
	}
	delete[] temp;
}
void merge_sort(int arr[], int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}
int getmax(int arr[], int n) {
	int max = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
}
void countingsort(int arr[], int n, int exp) {
	int* temp = new int[n];
	int count[10] = { 0 };
	for (int i = 0; i < n; i++) {
		int j = (arr[i] / exp) % 10;
		count[j]++;
	}
	for (int i = 1; i < 10; i++) {
		count[i] += count[i - 1];
	}
	for (int i = n - 1; i >= 0; i--) {
		int j = (arr[i] / exp) % 10;
		temp[count[j] - 1] = arr[i];
		count[j]--;
	}
	for (int i = 0; i < n; i++) {
		arr[i] = temp[i];
	}
	delete[] temp;
}
void radix_sort(int arr[], int n) {
	int maxnum = getmax(arr, n);
	for (int exp = 1; maxnum / exp > 0; exp *= 10) {
		countingsort(arr, n, exp);
	}
}
void insertion_sort(int a[], int n) {
	for (int i = 1; i < n; i++) {
		int key = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > key) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}
void heapify(int arr[], int n, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && arr[left] > arr[largest])
		largest = left;
	if (right < n && arr[right] > arr[largest])
		largest = right;
	if (largest != i) {
		swap(arr[i], arr[largest]);
		heapify(arr, n, largest);
	}
}
void heap_sort(int arr[], int n) {
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);
	for (int i = n - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}

int partition(int a[], int l, int r) {
	int pivot = a[r];
	int i = l - 1;
	for (int j = l; j < r; j++) {
		if (a[j] <= pivot) {
			++i;
			swap(a[i], a[j]);
		}
	}
	++i;
	swap(a[i], a[r]);
	return i;
}

void quick_sort(int a[], int l, int r) {
	if (l < r) {
		int m = (l + r) / 2;
		int p = partition(a, l, r);
		quick_sort(a, l, p - 1);
		quick_sort(a, p + 1, r);
	}
}
int main(int argc,char*argv[]) {
	if (argc != 7) {
		cout << "vui long nhap du so luong!" << endl;
		return 1;
	}
	string algorithm;
	string input;
	string output;
	for (int i = 1; i < argc; i += 2) {
		if (strcmp(argv[i], "-a") == 0) {
			algorithm = argv[i + 1];
		}
		else if (strcmp(argv[i], "-i") == 0) {
			input = argv[i + 1];
		}
		else if (strcmp(argv[i], "-o") == 0) {
			output = argv[i + 1];
		}
	}
	int n;
	ifstream file1(input);
	if (!file1) {
		cout << "khong the mo file de doc" << endl;
		return 1;
	}
	file1 >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		file1 >> arr[i];
	}
	file1.close();
	if (algorithm == "selection-sort") {
		selection_sort(arr, n);
	}
	else if (algorithm == "insertion-sort") {
		insertion_sort(arr, n);
	}
	else if (algorithm == "bubble-sort") {
		bubble_sort(arr, n);
	}
	else if (algorithm == "heap-sort") {
		heap_sort(arr, n);
	}
	else if (algorithm == "merge-sort") {
		merge_sort(arr, 0, n - 1);
	}
	else if (algorithm == "quick-sort") {
		quick_sort(arr, 0, n - 1);
	}
	else if (algorithm == "radix-sort") {
		radix_sort(arr, n);
	}
	ofstream file2(output);
	if (!file2) {
		cout << "khong the tim thay file de ghi" << endl;
		return 1;
	}
	file2 << n << endl;
	for (int i = 0; i < n; i++) {
		file2 << arr[i] << " ";
	}
	file2.close();
	delete[] arr;
	return 0;
}