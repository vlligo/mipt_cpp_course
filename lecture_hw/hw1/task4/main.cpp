#include <iostream>

int main() {
  // int*** represents floors -> shelves -> compartments.
  // void* holds either an int[] of totals or a double[] of averages,
  // depending on the mode selected at runtime.
  // Input is assumed valid; stock counts and totals fit in int.
  // In order of simplicity shelves number and compartments number is 2

  int floors;
  int mode;  // 0 = totals, 1 = averages
  std::cin >> floors >> mode;

  int*** stock = new int**[floors];
  for (int i = 0; i < floors; i++) {
    stock[i] = new int*[2];
    for (int j = 0; j < 2; j++) {
      stock[i][j] = new int[2];
      for (int k = 0; k < 2; k++) {
        std::cin >> stock[i][j][k];
      }
    }
  }

  void* results;
  if (mode == 0) {
    results = new int[floors];
  } else {
    results = new double[floors];
  }

  for (int i = 0; i < floors; i++) {
    int total = 0;
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        total += stock[i][j][k];
      }
    }

    if (mode == 0) {
      static_cast<int*>(results)[i] = total;
    } else {
      static_cast<double*>(results)[i] = total / 4.0;
    }
  }

  for (int i = 0; i < floors; i++) {
    if (mode == 0) {
      std::cout << static_cast<int*>(results)[i] << std::endl;
    } else {
      std::cout << static_cast<double*>(results)[i] << std::endl;
    }
  }

  if (mode == 0) {
    delete[] static_cast<int*>(results);
  } else {
    delete[] static_cast<double*>(results);
  }

  for (int i = 0; i < floors; i++) {
    for (int j = 0; j < 2; j++) {
      delete[] stock[i][j];
    }
    delete[] stock[i];
  }
  delete[] stock;

  return 0;
}