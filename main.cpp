#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <algorithm>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unordered_set>

using namespace std;

// A is sorted array
int binary_search(int* A, int key, int len) {
    int* start = A;
    int mid = len;
    while (len >= 1) {
        mid = len >> 1;
        if (start[mid] == key) { return (start - A) + mid; }
        if (len == 1 && start[mid] != key) { return -1; }
        if (start[mid] < key) { start += mid; }
        len -= mid;
    }
    return -1;
}

TEST_CASE("Binary Search", "[binary-search]") {
    int a[7] = { 1, 4, 6, 8, 10, 15, 100 };
    REQUIRE(binary_search(a, 1, 7) == 0);
    REQUIRE(binary_search(a, 4, 7) == 1);
    REQUIRE(binary_search(a, 6, 7) == 2);
    REQUIRE(binary_search(a, 8, 7) == 3);
    REQUIRE(binary_search(a, 10, 7) == 4);
    REQUIRE(binary_search(a, 15, 7) == 5);
    REQUIRE(binary_search(a, 100, 7) == 6);
    REQUIRE(binary_search(a, 50, 7) == -1);
}

// find_sum_of_two function return true if
// there are two values in array who
// sum to value and returns false otherwise
// O(n) memory
// O(n) complexity
bool find_sum_of_two(vector<int>& A, int val) {
    unordered_set<int> found_values;
    auto it = A.begin();
    for (; it != A.end(); it++) {
        int e = *it;
        int diff = val - e;
        if (found_values.find(diff) != found_values.end()) { return true; }
        found_values.insert(e);
    }
    return false;
}

// find_sum_of_two function return true if
// there are two values in array who
// sum to value and returns false otherwise
// Constant memory
// O(nlogn)
bool find_sum_of_two_2(vector<int>& A, int val) {
    std::sort(A.begin(), A.end());
    int left = 0;
    int right = A.size() - 1;

    while (left != right) {
        int sum = A[left] + A[right];
        if (sum == val) { return true; }
        if (sum < val) { left++; }
        else {
            right--;
        }
    }
    return false;
}

TEST_CASE("Sum of two", "[sum of 2]") {
    vector<int> v = { 2, 1, 8, 4, 7, 3 };
    REQUIRE(find_sum_of_two(v, 3) == true);
    REQUIRE(find_sum_of_two(v, 20) == false);
    REQUIRE(find_sum_of_two(v, 1) == false);
    REQUIRE(find_sum_of_two(v, 2) == false);
    REQUIRE(find_sum_of_two(v, 7) == true);

    REQUIRE(find_sum_of_two_2(v, 3) == true);
    REQUIRE(find_sum_of_two_2(v, 20) == false);
    REQUIRE(find_sum_of_two_2(v, 1) == false);
    REQUIRE(find_sum_of_two_2(v, 2) == false);
    REQUIRE(find_sum_of_two_2(v, 7) == true);
}

template <class T>
void print_array(T arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

void quick_sort(int* arr, int size) {
    if (size <= 1) { return; }
    int index = 0;
    int right = size - 1;
    int pivot = arr[index];
    while (index != right) {
        int e = arr[index + 1];
        if (e <= pivot) {
            //swap
            arr[index + 1] = pivot;
            arr[index] = e;
            index++;
        }
        else {
            //swap next index with right
            int right_val = arr[right];
            arr[index + 1] = right_val;
            arr[right] = e;
            right--;
        }
    }
    //sort left
    quick_sort(arr, index);
    //sort right
    quick_sort(arr + index + 1, size - index - 1);
}

TEST_CASE("Quick sort", "[quick sort]") {
    int a[] = { 0, 33, 6, 21, 12, 19, 29, 38, 22, 14, 40, 0, 0, 0, 0, 0 };
    vector<int> v = { 0, 33, 6, 21, 12, 19, 29, 38, 22, 14, 40, 0, 0, 0, 0, 0 };
    std::sort(v.begin(), v.end());
    quick_sort(a, sizeof(a) / sizeof(int));
    for (int i = 0; i < v.size(); i++) {
        REQUIRE(v[i] == a[i]);
    }
}

int binary_search_rotated(vector<int>& arr, int key) {
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = left + ((right - left) >> 1);
        int left_val = arr[left];
        int right_val = arr[right];
        int mid_val = arr[mid];

        if (mid_val == key) { return mid; }
        else if (left == right) {
            return -1;
        }
        //if the right side is ordered
        if (mid_val <= right_val) {
            //if the key is in the ordered part
            if (key <= right_val && key >= mid_val) { left = mid + 1; }
            //if the key is in the rotated part
            else {
                right = mid - 1;
            }
        }
        //if the left side is ordered
        else {
            //if the key is in the ordered part
            if (key >= left_val && key <= mid_val) { right = mid - 1; }
            //if the key is in the rotated part
            else {
                left = mid + 1;
            }
        }
    }
    return -1;
}

TEST_CASE("Search sorted rotated array", "[rotated array]") {
    vector<int> v1 = { 6, 7, 1, 2, 3, 4, 5 };
    vector<int> v2 = { 4, 5, 6, 1, 2, 3 };

    REQUIRE(binary_search_rotated(v1, 6) == 0);
    REQUIRE(binary_search_rotated(v1, 7) == 1);
    REQUIRE(binary_search_rotated(v1, 1) == 2);
    REQUIRE(binary_search_rotated(v1, 2) == 3);
    REQUIRE(binary_search_rotated(v1, 3) == 4);
    REQUIRE(binary_search_rotated(v1, 4) == 5);
    REQUIRE(binary_search_rotated(v1, 5) == 6);

    REQUIRE(binary_search_rotated(v2, 4) == 0);
    REQUIRE(binary_search_rotated(v2, 5) == 1);
    REQUIRE(binary_search_rotated(v2, 6) == 2);
    REQUIRE(binary_search_rotated(v2, 1) == 3);
    REQUIRE(binary_search_rotated(v2, 2) == 4);
    REQUIRE(binary_search_rotated(v2, 3) == 5);
}

void rotate_array(vector<int>& arr, int n) {
    int len = arr.size();
    n = n % len;
    if (n < 0) { n = n + len; }
    std::reverse(arr.begin(), arr.end());
    std::reverse(arr.begin(), arr.begin() + n);
    std::reverse(arr.begin() + n, arr.end());
}

TEST_CASE("Rotate array", "[rotate array]") {
    vector<int> v1 = { 1, 2, 3, 4, 5 };
    vector<int> v2 = { 4, 5, 1, 2, 3 };
    rotate_array(v1, -3);
    for (int i = 0; i < v1.size(); i++) {
        REQUIRE(v1[i] == v2[i]);
    }
}

int find_low_index(vector<int>& arr, int key) {
    int low = 0;
    int high = arr.size();
    while (high >= low) {
        int mid = low + ((high - low) >> 1);
        if (arr[mid] >= key) { high = mid - 1; }
        else {
            low = mid + 1;
        }
    }
    if (arr[low] == key) { return low; }
    return -1;
}

int find_high_index(vector<int>& arr, int key) {
    int low = 0;
    int high = arr.size();
    while (high >= low) {
        int mid = low + ((high - low) >> 1);
        if (arr[mid] <= key) { low = mid + 1; }
        else {
            high = mid - 1;
        }
    }
    if (arr[high] == key) { return high; }
    return -1;
}

TEST_CASE("Find lwo/high index", "[rotate array]") {
    vector<int> array = { 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 6, 6, 6, 6, 6, 6 };
    int low = find_low_index(array, 5);
    int high = find_high_index(array, 5);
    REQUIRE(low == 15);
    REQUIRE(high == 17);

    low = find_low_index(array, 2);
    high = find_high_index(array, 2);
    REQUIRE(low == 3);
    REQUIRE(high == 7);
}

//O(nlog(n))
void move_zeros_to_left(vector<int>& A) {
    std::sort(A.begin(), A.end(), [](const int a, const int b) {
        if (a == 0) { return true; }
        return false;
    });
}

//O(n)
void move_zeros_to_left_2(vector<int>& A) {
    int read = A.size();
    int write = read;
    while (read >= 0) {
        if (A[read] != 0) {
            A[write] = A[read];
            write--;
        }
        read--;
    }
    while (write >= 0) {
        A[write] = 0;
        write--;
    }
}

TEST_CASE("Move zeros to the left", "[left zeros]") {
    vector<int> v1 = { 1, 1, 0, 2, 0, 3, 5, 0, 8, 13 };
    vector<int> v2 = { 0, 0, 0, 1, 1, 2, 3, 5, 8, 13 };
    move_zeros_to_left(v1);
    for (int i = 0; i < v1.size(); i++) {
        REQUIRE(v1[i] == v2[i]);
    }

    v1 = { 1, 1, 0, 2, 0, 3, 5, 0, 8, 13 };
    move_zeros_to_left_2(v1);
    for (int i = 0; i < v1.size(); i++) {
        REQUIRE(v1[i] == v2[i]);
    }
}

void reverse_string(char* s, int len) {
    int end = len - 1;
    for (int begin = 0; begin < (len >> 1); begin++) {
        //could use xor swap here, but whatever
        char temp = s[begin];
        s[begin] = s[end];
        s[end] = temp;
        end--;
    }
}

void reverse_sentence_words(char* sentence) {
    int len = strlen(sentence);
    reverse_string(sentence, len);
    
    int begin = 0;
    for (int i = 0; i <= len; i++) {
        if (i == len || sentence[i] == ' ') {
            reverse_string(sentence + begin, i - begin);
            begin = i + 1;
        }
    }
}

TEST_CASE("Reverse sentence", "[reverse sentence]") {
    char* a = new char[200];
    char* b = new char[200];

    strcpy(a, "ab cd");
    strcpy(b, "cd ab");
    reverse_sentence_words(a);
    REQUIRE(strcmp(a, b) == 0);

    strcpy(a, "Quick brown fox jumped over the lazy dog");
    strcpy(b, "dog lazy the over jumped fox brown Quick");
    reverse_sentence_words(a);
    REQUIRE(strcmp(a, b) == 0);
}