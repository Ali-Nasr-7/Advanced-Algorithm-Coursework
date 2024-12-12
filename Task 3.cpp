#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

void heapify(int arr[], int n, int i, int& comparison_count) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest]) {
        comparison_count++;
        smallest = left;
    }

    if (right < n && arr[right] < arr[smallest]) {
        comparison_count++;
        smallest = right;
    }

    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        heapify(arr, n, smallest, comparison_count);
    }
}

int heap_sort_count(int arr[], int n) {
    int comparison_count = 0;

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, comparison_count);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0, comparison_count);
    }

    return comparison_count;
}

int bubble_sort_count(int arr[], int n) {
    int comparison_count = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            comparison_count++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
    return comparison_count;
}

int selection_sort_count(int arr[], int n) {
    int comparison_count = 0;
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            comparison_count++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[i], arr[min_idx]);
    }
    return comparison_count;
}

int insertion_sort_count(int arr[], int n) {
    int comparison_count = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            comparison_count++;
            arr[j + 1] = arr[j];
            j--;
        }
        comparison_count++;
        arr[j + 1] = key;
    }
    return comparison_count;
}

pair<int, double> run_test(vector<int>& arr, int n, int (*sort_fn)(int[], int)) {
    int* arr_copy = new int[n];
    copy(arr.begin(), arr.end(), arr_copy);

    auto start_time = chrono::high_resolution_clock::now();
    int comparisons = sort_fn(arr_copy, n);
    auto end_time = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = end_time - start_time;
    delete[] arr_copy; 

    return { comparisons, duration.count() };
}

void test_comparisons() {
    ofstream comparison_file("comparisons.csv");

    comparison_file << "Array Size,Heap Sort,Bubble Sort,Selection Sort,Insertion Sort\n";

    cout << setw(10) << "Array Size"
        << setw(15) << "Heap Sort"
        << setw(15) << "Bubble Sort"
        << setw(20) << "Selection Sort"
        << setw(20) << "Insertion Sort" << endl;

    for (int n = 1; n <= 30; n++) {
        vector<int> random_array(n), sorted_array(n), reverse_sorted_array(n);

        for (int i = 0; i < n; i++) {
            random_array[i] = rand() % 1000; 
            sorted_array[i] = i;
            reverse_sorted_array[i] = n - i - 1;
        }

        auto random_res_heap = run_test(random_array, n, heap_sort_count);
        auto random_res_bubble = run_test(random_array, n, bubble_sort_count);
        auto random_res_selection = run_test(random_array, n, selection_sort_count);
        auto random_res_insertion = run_test(random_array, n, insertion_sort_count);

        auto sorted_res_heap = run_test(sorted_array, n, heap_sort_count);
        auto sorted_res_bubble = run_test(sorted_array, n, bubble_sort_count);
        auto sorted_res_selection = run_test(sorted_array, n, selection_sort_count);
        auto sorted_res_insertion = run_test(sorted_array, n, insertion_sort_count);

        auto reverse_sorted_res_heap = run_test(reverse_sorted_array, n, heap_sort_count);
        auto reverse_sorted_res_bubble = run_test(reverse_sorted_array, n, bubble_sort_count);
        auto reverse_sorted_res_selection = run_test(reverse_sorted_array, n, selection_sort_count);
        auto reverse_sorted_res_insertion = run_test(reverse_sorted_array, n, insertion_sort_count);

        cout << setw(10) << n
            << setw(15) << random_res_heap.first
            << setw(15) << random_res_bubble.first
            << setw(20) << random_res_selection.first
            << setw(20) << random_res_insertion.first << endl;

        comparison_file << n << ","
            << random_res_heap.first << "," << random_res_bubble.first << ","
            << random_res_selection.first << "," << random_res_insertion.first << "\n";
        comparison_file << n << ","
            << sorted_res_heap.first << "," << sorted_res_bubble.first << ","
            << sorted_res_selection.first << "," << sorted_res_insertion.first << "\n";
        comparison_file << n << ","
            << reverse_sorted_res_heap.first << "," << reverse_sorted_res_bubble.first << ","
            << reverse_sorted_res_selection.first << "," << reverse_sorted_res_insertion.first << "\n";

    }

    comparison_file.close();

    cout << "\nTest completed. Results saved in 'comparisons.csv'.\n";
}

int main() {
    test_comparisons();
    return 0;
}
