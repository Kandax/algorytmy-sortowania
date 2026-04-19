#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include "MergeSort.h"
#include "Quicksort.h"
#include "IntroSort.h"


// Generator przekazywany z zewn¹trz - jeden obiekt na ca³y program
void generateData(int arr[], int n, double sortedPercent, std::mt19937& gen, bool reverse = false) {
    if (reverse) {
        for (int i = 0; i < n; i++) arr[i] = n - i;
        return;
    }

    std::uniform_int_distribution<int> dis(0, 1000000);

    // Wype³nij ca³¹ tablicê losowymi wartoœciami
    for (int i = 0; i < n; i++) arr[i] = dis(gen);

    // Posortuj tylko pierwszy fragment
    int sortedCount = static_cast<int>(n * sortedPercent / 100.0);
    std::sort(arr, arr + sortedCount);
}

template <typename T>
bool isSorted(T arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

void runBenchmark() {
    int sizes[] = {10000, 50000, 100000, 500000, 1000000};
    double percentages[] = {0, 25, 50, 75, 95, 99, 99.7};

    // Jeden generator na ca³y benchmark
    std::mt19937 gen(std::random_device{}());

    for (int n : sizes) {
        std::cout << "\n--- Rozmiar tablicy: " << n << " ---\n";

        int* data    = new int[n];
        int* tempArr = new int[n];

        // --- Przypadki z procentowym posortowaniem ---
        for (double p : percentages) {
            long long totalTime = 0;

            for (int i = 0; i < 100; i++) {
                generateData(data, n, p, gen, false); // reverse=false
                std::copy(data, data + n, tempArr);

                auto start = std::chrono::high_resolution_clock::now();

                //QuickSort<int>::sort(tempArr, n);
                //MergeSort<int>::sort(tempArr, n);
                IntroSort<int>::sort(tempArr, n);

                auto end = std::chrono::high_resolution_clock::now();

                totalTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            }

            // Weryfikacja poprawnoœci tylko na ostatniej iteracji
            if (!isSorted(tempArr, n)) {
                std::cerr << "B£¥D SORTOWANIA! n=" << n << " p=" << p << "\n";
            }

            std::cout << "Posortowane w " << p << "%: "
                      << totalTime / 100.0 << " ms (avg)\n";
        }

        // --- Przypadek odwrotnej kolejnoœci ---
        {
            long long totalTime = 0;

            for (int i = 0; i < 100; i++) {
                generateData(data, n, 0, gen, true); // reverse=true
                std::copy(data, data + n, tempArr);

                auto start = std::chrono::high_resolution_clock::now();

                //QuickSort<int>::sort(tempArr, n);
                //MergeSort<int>::sort(tempArr, n);
                IntroSort<int>::sort(tempArr, n);

                auto end = std::chrono::high_resolution_clock::now();

                totalTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            }

            if (!isSorted(tempArr, n)) {
                std::cerr << "B£¥D SORTOWANIA! n=" << n << " odwrotna\n";
            }

            std::cout << "Odwrotna kolejnosc: "
                      << totalTime / 100.0 << " ms (avg)\n";
        }

        delete[] data;
        delete[] tempArr;
    }
}

int main() {
    // Szybka weryfikacja poprawnoœci na ma³ej tablicy
    std::mt19937 gen(std::random_device{}());
    int* tab = new int[1000];
    generateData(tab, 1000, 50, gen);

    //QuickSort<int>::sort(tab, 1000);
    //MergeSort<int>::sort(tab, 1000);
    IntroSort<int>::sort(tab, 1000);

    if (isSorted(tab, 1000)) {
        std::cout << "Weryfikacja OK\n";
    } else {
        std::cerr << "Weryfikacja NIEUDANA\n";
    }

    delete[] tab;
    
    //std::cout << "Quick sort" << std::endl;
    //std::cout << "Merge sort" << std::endl;
    std::cout << "Intro sort" << std::endl;

    runBenchmark();

    return 0;
}