#include<iostream>
using namespace std;

int findMin(int nums[], int n) {
    int left = 0, right = n - 1;

    while (left < right) {

        int mid = left + (right - left) / 2;

        if (nums[mid] > nums[right]) {

            left = mid + 1;
        }
        else {

            right = mid;
        }
    }
    return nums[left];
}

int main() {
    int n;
    cin >> n;
    int* nums = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    cout << "phan tu nho nhat la: " << findMin(nums, n);
    delete[]nums;
    return 0;
}