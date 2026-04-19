#pragma once

#include <iostream>
#include <algorithm>

template <typename T>
class QuickSort {
public:
    static void sort(T arr[], int size) {
        if (size < 2) return;
        solve(arr, 0, size - 1);
    }

private:
    static void solve(T arr[], int left, int right) {
        if (left >= right) return;

        // Podzia³ tablicy i otrzymanie punktu podzia³u
        int p = partition(arr, left, right);

        // Rekurencyjne sortowanie lewej i prawej strony
        // Uwaga: Schemat Hoare'a dzieli tablicê na [left...p] i [p+1...right]
        solve(arr, left, p);
        solve(arr, p + 1, right);
    }

    // Partycja wg Hoare'a 
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


        // Wybor pivota jako element srodkowy 
        //T pivot = arr[left + (right - left) / 2];
        
        int i = left - 1;
        int j = right + 1;

        while (true) {
            // Szukaj elementu po lewej, który powinien byæ po prawej
            do {
                i++;
            } while (arr[i] < pivot);

            // Szukaj elementu po prawej, który powinien byæ po lewej
            do {
                j--;
            } while (arr[j] > pivot);

            // Jeœli indeksy siê spotka³y lub minê³y, koñczymy partycjê
            if (i >= j) return j;

            // Zamiana elementów miejscami
            std::swap(arr[i], arr[j]);
        }
    }
};
