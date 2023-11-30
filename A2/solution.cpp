#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>

void merge(int arr[], const int left, const int mid, const int right) {
    const int subArrayOne = mid - left + 1;
    const int subArrayTwo = right - mid;

    auto *leftArray = new int[subArrayOne];
    auto *rightArray = new int[subArrayTwo];

    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = arr[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = arr[mid + 1 + j];

    auto indexOfSubArrayOne = 0;
    auto indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        } else {
            arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOne) {
        arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    while (indexOfSubArrayTwo < subArrayTwo) {
        arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

void mergeSort(int arr[], int const begin, int const end) {
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    mergeSort(arr, begin, mid);
    mergeSort(arr, mid + 1, end);
    merge(arr, begin, mid, end);
}

void mergeInsertionSort(int arr[], int const begin, int const end) {
    if (begin >= end)
        return;

    if (end - begin <= 50) {
        int i, key, j;
        for (i = begin; i < end; i++) {
            key = arr[i];
            j = i - 1;

            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }

    int mid = begin + (end - begin) / 2;
    mergeSort(arr, begin, mid);
    mergeSort(arr, mid + 1, end);
    merge(arr, begin, mid, end);
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << '\n';
}

void reverseArray(int arr[], int n) {
    for (int i = 0; i < n / 2; ++i) {
        int t = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = t;
    }
}

std::string toString(long long a) {
    return std::to_string(a) + ";";
}

int main() {
    double ans = 0;
    double ans2 = 0;
    double ans_reverse = 0;
    double ans_reverse2 = 0;
    double ans_almost = 0;
    double ans_almost2 = 0;
    int c = 0;
    std::ofstream fout("output_A2.csv");
    for (int n = 500; n <= 4000; n += 100) {
        ++c;
        int arr[n];
        int arr2[n];
        int reverse[n];
        int reverse2[n];
        int almost[n];
        int almost2[n];
        int inf = 1000000000;
        srand(time(nullptr));
        for (int i = 0; i < n; ++i) {
            arr[i] = (rand() + inf) % 3000;
            arr2[i] = arr[i];
            reverse[i] = (rand() + inf) % 3000;
            reverse2[i] = reverse[i];
            almost[i] = (rand() + inf) % 3000;
            almost2[i] = almost[i];
        }
        mergeSort(almost, 0, n);
        mergeSort(almost2, 0, n);
        for (int i = 0; i < 10; ++i) {
            std::swap(almost[i], almost[n - i - 1]);
            std::swap(almost2[i], almost2[n - i - 1]);
        }
        mergeSort(reverse, 0, n);
        mergeSort(reverse2, 0, n);
        reverseArray(reverse, n);
        reverseArray(reverse2, n);

        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(arr, 0, n);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::cout << "random equal arrays: " << millisec << ' ';
        fout << toString(millisec);
        ans += static_cast<int>(millisec);

        start = std::chrono::high_resolution_clock::now();
        mergeInsertionSort(arr2, 0, n);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::cout << millisec << '\n';
        fout << toString(millisec);
        ans2 += static_cast<int>(millisec);


        start = std::chrono::high_resolution_clock::now();
        mergeInsertionSort(reverse, 0, n);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::cout << "end-to-start order equal arrays: " << millisec << ' ';
        fout << toString(millisec);
        ans_reverse += static_cast<int>(millisec);

        start = std::chrono::high_resolution_clock::now();
        mergeInsertionSort(reverse2, 0, n);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::cout << millisec << '\n';
        fout << toString(millisec);
        ans_reverse2 += static_cast<int>(millisec);


        start = std::chrono::high_resolution_clock::now();
        mergeInsertionSort(almost, 0, n);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::cout << "almost sorted arrays: " << millisec << ' ';
        fout << toString(millisec);
        ans_almost += static_cast<int>(millisec);

        start = std::chrono::high_resolution_clock::now();
        mergeInsertionSort(almost2, 0, n);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::cout << millisec << '\n';
        fout << toString(millisec) << '\n';
        ans_almost2 += static_cast<int>(millisec);
        std::cout << "--------------\n";
    }
    ans /= c;
    ans2 /= c;
    ans_reverse /= c;
    ans_reverse2 /= c;
    ans_almost /= c;
    ans_almost2 /= c;
    std::cout << "average results for MergeSort and Merge + InsertionSort\n";
    std::cout << ans << ' ' << ans2 << '\n';
    std::cout << ans_reverse << ' ' << ans_reverse2 << '\n';
    std::cout << ans_almost << ' ' << ans_almost2 << '\n';
}
