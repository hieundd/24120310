#include <iostream>
using namespace std;

int linearSearch(int arr[], int n, int &k) {
	for (int i = 0; i < n; i++) {
		if (arr[i] == k) {
			return i;
		}
	}
	return -1;
}

int main()
{
	int n, k;
	cout << "Nhap n: ";
	cin >> n;
	cout << "Nhap so can tim: ";
	cin >> k;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	int x = linearSearch(arr, n, k);
	cout << x << endl;

	delete[] arr;
	return 0;
}
