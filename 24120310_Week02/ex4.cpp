#include <iostream>
using namespace std;

int TongTrongTai(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

bool CoTheVanChuyen(int weights[], int n, int capacity, int days) {
    int cur = 0, req = 1;

    for (int i = 0; i < n; i++) {
        if (cur + weights[i] > capacity) {
            req++;   
            cur = 0; 
        }
        cur += weights[i];
    }

    return req <= days; 
}

int MinTrongTai(int weights[], int n, int days) {
    int left = weights[n - 1]; 
    int right = TongTrongTai(weights, n); 
    int answer = right;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (CoTheVanChuyen(weights, n, mid, days)) {
            answer = mid;
            right = mid - 1; 
        }
        else {
            left = mid + 1;
        }
    }

    return answer;
}

int main() {
    int n, days;
    cin >> n;
    int *weights=new int [n]; 

    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }
    cin >> days;
    cout << MinTrongTai(weights, n, days) << endl;
    delete []weights;
    return 0;
}
