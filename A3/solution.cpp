#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>

void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int l, int r) {
    for (int i = r / 2 - 1; i >= 0; i--)
        heapify(arr, r, i);

    for (int i = r - 1; i >= l; i--) {
        std::swap(arr[l], arr[i]);
        heapify(arr, i, l);
    }
}

int partition(int arr[], int l, int r) {
    int pivot = arr[r];
    int i = (l - 1);

    for (int j = l; j <= r - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[r]);
    return i + 1;
}

void quickSort(int arr[], int l, int r) {
    if (l < r) {
        int mid = partition(arr, l, r);
        quickSort(arr, l, mid - 1);
        quickSort(arr, mid + 1, r);
    }
}

void reverseArray(int arr[], int n) {
    for (int i = 0; i < n / 2; ++i) {
        int t = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = t;
    }
}

void quickHeapSort(int arr[], int l, int r) {
    if (r - l <= 50) {
        heapSort(arr, l, r);
    } else {
        quickSort(arr, l, r);
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
    std::ofstream fout("output_A3.csv");
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
        quickSort(almost, 0, n);
        quickSort(almost2, 0, n);
        for (int i = 0; i < 10; ++i) {
            std::swap(almost[i], almost[n - i - 1]);
            std::swap(almost2[i], almost2[n - i - 1]);
        }
        quickSort(reverse, 0, n);
        quickSort(reverse2, 0, n);
        reverseArray(reverse, n);
        reverseArray(reverse2, n);

        auto start = std::chrono::high_resolution_clock::now();
        quickSort(arr, 0, n);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::cout << "random equal arrays: " << millisec << ' ';
        fout << toString(millisec);
        ans += static_cast<int>(millisec);

        start = std::chrono::high_resolution_clock::now();
        quickHeapSort(arr2, 0, n);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::cout << millisec << '\n';
        fout << toString(millisec);
        ans2 += static_cast<int>(millisec);


        start = std::chrono::high_resolution_clock::now();
        quickSort(reverse, 0, n);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::cout << "end-to-start order equal arrays: " << millisec << ' ';
        fout << toString(millisec);
        ans_reverse += static_cast<int>(millisec);

        start = std::chrono::high_resolution_clock::now();
        quickHeapSort(reverse2, 0, n);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::cout << millisec << '\n';
        fout << toString(millisec);
        ans_reverse2 += static_cast<int>(millisec);


        start = std::chrono::high_resolution_clock::now();
        quickSort(almost, 0, n);
        elapsed = std::chrono::high_resolution_clock::now() - start;
        millisec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::cout << "almost sorted arrays: " << millisec << ' ';
        fout << toString(millisec);
        ans_almost += static_cast<int>(millisec);

        start = std::chrono::high_resolution_clock::now();
        quickHeapSort(almost2, 0, n);
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
