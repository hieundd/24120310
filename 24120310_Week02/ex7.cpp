#include <iostream>
using namespace std;

// Hàm s?p x?p m?ng b?ng Selection Sort
void selectionSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i; // Gi? s? ph?n t? nh? nh?t là a[i]
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[minIdx]) minIdx = j;
        }
        // Hoán ??i ph?n t? nh? nh?t v?i a[i]
        int temp = a[i];
        a[i] = a[minIdx];
        a[minIdx] = temp;
    }
}

// Hàm tìm các b? ba có t?ng b?ng 0
void findTriplets(int a[], int n) {
    // B??c 1: S?p x?p m?ng
    selectionSort(a, n);

    // B??c 2: Duy?t t?ng ph?n t? làm ph?n t? ??u tiên c?a b? ba
    for (int i = 0; i < n - 2; i++) {
        // N?u ph?n t? này trùng v?i ph?n t? tr??c ?ó, b? qua ?? tránh trùng l?p
        if (i > 0 && a[i] == a[i - 1]) continue;

        // B??c 3: Dùng hai con tr? ?? tìm b? ba
        int j = i + 1, k = n - 1;
        while (j < k) {
            int sum = a[i] + a[j] + a[k];

            if (sum == 0) {              
                cout << "[" << a[i] << ", " << a[j] << ", " << a[k] << "]\n";               
                while (j < k && a[j] == a[j + 1]) j++;
                while (j < k && a[k] == a[k - 1]) k--;              
                j++;
                k--;
            }
            else if (sum < 0) {
                j++; 
            }
            else {
                k--; 
            }
        }
    }
}
int main() {
    int n;
    cout << "Nhap n: ";
    cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    findTriplets(a, n); 

    return 0;
}

