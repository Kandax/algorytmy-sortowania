#pragma once
#include <iostream>

template <typename T>
class MergeSort {
public:
    static void sort(T arr[], int size) {
        if (size < 2) return;

        T* tempArr = new T[size];
        
        solve(arr, tempArr, 0, size - 1);

        delete[] tempArr;
    }

private:
    static void solve(T arr[], T tempArr[], int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            solve(arr, tempArr, left, mid);
            solve(arr, tempArr, mid + 1, right);
            
            merge(arr, tempArr, left, mid, right);
        }
    }

    static void merge(T arr[], T tempArr[], int left, int mid, int right) {
        int i = left;      // Indeks lewej podtablicy
        int j = mid + 1;   // Indeks prawej podtablicy
        int k = left;      // Indeks w tablicy pomocniczej

        // Scalanie do tablicy tymczasowej
        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                tempArr[k++] = arr[i++];
            } else {
                tempArr[k++] = arr[j++];
            }
        }

        // Kopiowanie pozostalych elementow z lewej strony
        while (i <= mid) {
            tempArr[k++] = arr[i++];
        }

        // Kopiowanie pozostalych elementow z prawej strony
        while (j <= right) {
            tempArr[k++] = arr[j++];
        }

        // Przeniesienie posortowanych danych z powrotem do oryginalnej tablicy
        for (int i = left; i <= right; i++) {
            arr[i] = tempArr[i];
        }
    }
};
