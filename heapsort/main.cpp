#include <iostream>
#include <algorithm>

using namespace std;


void swap(int a[], int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void heapify(int a[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[largest] < a[left])
        largest = left;

    if (right < n && a[largest] < a[right])
        largest = right;

    if (largest != i) {
        swap(a, i, largest);
        heapify(a, n, largest);
    }
}

void heapSort(int a[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(a, size, i);

    for (int i = size - 1; i >= 0; i--) {
        swap(a, 0, i);
        heapify(a, i, 0);
    }
}

int main() {
    int a[] = {6, 3, 2, 7, 4, 5, 0};
    int k = 3;

    // // O(n * k) - bubble sort
    // for (int i = 0; i < k; i++) {
    //     for (int j = 0; j < sizeof(a) / sizeof(a[0]) - 1; j++) {
    //         if (a[j] > a[j + 1]) {
    //             swap(a, j, j + 1);
    //         }
    //     }
    // }

    // // O(k * log(n)) - heapify k times
    // for (int i = 0; i < k; i++) {
    //     heapify(a, sizeof(a) / sizeof(a[0]), 0);
    // }

    // O(k * log(n)) - heap sort
    heapSort(a, sizeof(a) / sizeof(a[0]));

    // Output sorted array
    cout << "Sorted array: ";
    for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
        cout << a[i] << " ";
    }

    return 0;
}


