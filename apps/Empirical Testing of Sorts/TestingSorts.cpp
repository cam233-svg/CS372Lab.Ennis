#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <iomanip>

template <typename T>
void selectionSort(std::vector<T>& data) {
    int n = static_cast<int>(data.size());
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (data[j] < data[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(data[i], data[minIndex]);
    }
}

template <typename T>
void bubbleSort(std::vector<T>& a) {
    int n = static_cast<int>(a.size());
    for (int i = 0; i <= n - 2; ++i) {
        for (int j = 0; j <= n - 2 - i; ++j) {
            if (a[j + 1] < a[j]) {
                std::swap(a[j], a[j + 1]);
            }
        }
    }
}

template <typename T>
void insertionSort(std::vector<T>& a) {
    int n = static_cast<int>(a.size());
    for (int i = 1; i < n; ++i) {
        T key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = key;
    }
}

template <typename T>
int partition(std::vector<T>& a, int start, int end) {
    T pivot = a[end];
    int pIndex = start;
    for (int i = start; i < end; ++i) {
        if (a[i] <= pivot) {
            std::swap(a[i], a[pIndex]);
            ++pIndex;
        }
    }
    std::swap(a[pIndex], a[end]);
    return pIndex;
}

template <typename T>
void quickSort(std::vector<T>& arr, int low, int high) {
    if (low < high) {
        int s = partition(arr, low, high);
        quickSort(arr, low, s - 1);
        quickSort(arr, s + 1, high);
    }
}

template <typename SortFn>
double timeSort(SortFn sortFn, const std::vector<int>& base) {
    std::vector<int> v = base;
    auto start = std::chrono::high_resolution_clock::now();
    sortFn(v);
    auto stop  = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(stop - start).count();
}

int main() {
    const std::vector<int> sizes = {
        10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000, 250000
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1000000);

    std::cout << "Size,SelectionSort(ms),BubbleSort(ms),InsertionSort(ms),Quicksort(ms)\n";

    for (int size : sizes) {
        std::vector<int> base(size);
        for (int i = 0; i < size; ++i) {
            base[i] = dist(gen);
        }

        double tSel = timeSort([](std::vector<int>& v) { selectionSort(v); }, base);
        double tBub = timeSort([](std::vector<int>& v) { bubbleSort(v);    }, base);
        double tIns = timeSort([](std::vector<int>& v) { insertionSort(v); }, base);
        double tQck = timeSort([](std::vector<int>& v) {
            quickSort(v, 0, static_cast<int>(v.size()) - 1);
        }, base);

        std::cout << size << ","
                  << std::fixed << std::setprecision(3)
                  << tSel << "," << tBub << "," << tIns << "," << tQck << "\n";
        std::cout.flush();
    }

    return 0;
}
