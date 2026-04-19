#pragma once

#include <iostream>
#include <algorithm> 
#include <cmath>     

template <typename T>
class IntroSort {
public:
    static void sort(T arr[], int n) {
        if (n < 2) return;
        
        // Limit g³êbokoœci rekurencji: 2 * log2(n)
        int depthLimit = 2 * std::log2(n);
        
        solve(arr, 0, n - 1, depthLimit);
    }

private:
    static void solve(T arr[], int left, int right, int depthLimit) {
        int size = right - left + 1;

        // 1. Jeœli tablica jest ma³a, u¿ywamy InsertionSort 
        if (size < 16) {
            insertionSort(arr, left, right);
            return;
        }

        // 2. Jeœli rekurencja jest zbyt g³êboka, prze³¹czamy siê na HeapSort
        if (depthLimit == 0) {
            heapSort(arr, size, left);
            return;
        }

        // 3. W innym przypadku wykonujemy QuickSort (partycja Hoare'a)
        int p = partition(arr, left, right);
        solve(arr, left, p, depthLimit - 1);
        solve(arr, p + 1, right, depthLimit - 1);
    }

    // QuickSort
    static int partition(T arr[], int left, int right) {

        int mid = left + (right - left) / 2;

    	// Median-of-three: uporz¹dkuj left, mid, right
    	if (arr[left] > arr[mid])
    	    std::swap(arr[left], arr[mid]);
	
    	if (arr[left] > arr[right])
    	    std::swap(arr[left], arr[right]);
	
    	if (arr[mid] > arr[right])
    	    std::swap(arr[mid], arr[right]);
	
    	// arr[left] <= arr[mid] <= arr[right]
    	T pivot = arr[mid];

        //T pivot = arr[left + (right - left) / 2];
        int i = left - 1;
        int j = right + 1;
        while (true) {
            do { i++; } while (arr[i] < pivot);
            do { j--; } while (arr[j] > pivot);
            if (i >= j) return j;
            std::swap(arr[i], arr[j]);
        }
    }

    
    static void heapify(T arr[], int n, int i, int offset) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && arr[offset + l] > arr[offset + largest]) largest = l;
        if (r < n && arr[offset + r] > arr[offset + largest]) largest = r;
        if (largest != i) {
            std::swap(arr[offset + i], arr[offset + largest]);
            heapify(arr, n, largest, offset);
        }
    }
    static void heapSort(T arr[], int n, int offset) {
        for (int i = n / 2 - 1; i >= 0; i--) 
            heapify(arr, n, i, offset);
        for (int i = n - 1; i > 0; i--) {
            std::swap(arr[offset], arr[offset + i]);
            heapify(arr, i, 0, offset);
        }
    }

    static void insertionSort(T arr[], int left, int right) {
        for (int i = left + 1; i <= right; i++) {
            T key = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
};
