#include <iostream>

double mean(const int arr[], const int size) {
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += arr[i];
  }
  return static_cast<double>(sum) / size;
}

int min_element(const int arr[], const int size) {
  int min = arr[0];
  for (int i = 1; i < size; i++) {
    if (arr[i] < min) {
      min = arr[i];
    }
  }
  return min;
}

int max_element(const int arr[], const int size) {
  int max = arr[0];
  for (int i = 1; i < size; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  return max;
}

int count_less_zero(const int arr[], const int size) {
  int count = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] < 0) {
      count++;
    }
  }
  return count;
}

int main() {
  int n;
  std::cin >> n;
  int* arr = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }
  std::cout.precision(1);
  std::cout << std::fixed;
  std::cout << mean(arr, n) << std::endl;
  std::cout << min_element(arr, n) << ' ' << max_element(arr, n) << std::endl;
  std::cout << count_less_zero(arr, n) << std::endl;
  delete[] arr;
  return 0;
}