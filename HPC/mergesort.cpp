#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

// Function to merge two sorted subarrays
void merge(vector<int>& arr, vector<int>& left, vector<int>& right) {
    int i = 0, j = 0, k = 0;
    int leftSize = left.size();
    int rightSize = right.size();

    // Merge elements from left[] and right[] back into arr[]
    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    // Copy the remaining elements of left[], if any
    while (i < leftSize) {
        arr[k++] = left[i++];
    }

    // Copy the remaining elements of right[], if any
    while (j < rightSize) {
        arr[k++] = right[j++];
    }
}

// Function to perform mergesort on an array
void mergesort(vector<int>& arr) {
    int size = arr.size();
    if (size < 2) {
        return;  // Base case: If the array has 0 or 1 element, it is already sorted
    }

    int mid = size / 2;
    vector<int> left(arr.begin(), arr.begin() + mid);
    vector<int> right(arr.begin() + mid, arr.end());

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            // Sort the left subarray recursively
            mergesort(left);
        }

        #pragma omp section
        {
            // Sort the right subarray recursively
            mergesort(right);
        }
    }

    // Merge the sorted subarrays
    merge(arr, left, right);
}

int main() {
    vector<int> arr = {8, 3, 1, 5, 2, 7, 4, 6};

    cout << "Original array:\n";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    // Perform mergesort on the array
    mergesort(arr);

    cout << "Sorted array:\n";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
