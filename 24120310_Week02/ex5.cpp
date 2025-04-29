#include <iostream>
using namespace std;

int minSub(int target, int nums[], int n) {
    int left = 0, sum = 0, minLength = n + 1;  

    for (int right = 0; right < n; ++right) {
        sum += nums[right];

        while (sum >= target) {
            minLength = min(minLength, right - left + 1);
            sum -= nums[left++];
        }
    }
    return minLength == n + 1 ? 0 : minLength;  
}

int main() {
    int target;
    int n;
    cout << "Nhap n: ";
    cin >> n;
    int* nums = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    cout << "Nhap target: ";
    cin >> target;
    cout << minSub(target, nums, n) << endl; 

    return 0;
}
