#include <iostream>
using namespace std;

int sentinelLinearSearch(int a[], int n, int k) {
    int last = a[n - 1];
    a[n - 1] = k;
    int i = 0;
    while (a[i] != k) {
        i++;
    }
    a[n - 1] = last;
    if (i < n - 1 || a[n - 1] == k) {
        return i;
    }
    return -1;

}

int main()
{
    int n, k;
    cout << "Nhap n: ";
    cin >> n;
    cout << "Nhap k: ";
    cin >> k;
    int* a = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int x = sentinelLinearSearch(a, n, k);
    cout << x;
    delete[]a;
    return 0;
}