#include <iostream>
using namespace std;

bool findPairWithSum(int arr[], int n, int target) {
    int left = 0, right = n - 1;

    while (left < right) {
        int current_sum = arr[left] + arr[right];

        if (current_sum == target) {
            return true;  
        }
        else if (current_sum < target) {
            left++;  
        }
        else {
            right--; 
        }
    }

    return false;  
}

int main() {
    int n;
    cin >> n;  
    int *arr=new int[n];

    for (int i = 0; i < n; i++) {
        cin >> arr[i];  
    }

    int target;
    cout << "Nhap target: ";
    cin >> target;  

    if (findPairWithSum(arr, n, target)) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    delete[]arr;
    return 0;
}
