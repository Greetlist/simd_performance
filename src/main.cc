#include <iostream>
#include "BaseCalculator.h"
#include "SSECalculator.h"

constexpr int arr_size = 100000000;

int main(int argc, char** argv) {
  int* a = new(std::align_val_t{16}) int[arr_size];
  int* b = new(std::align_val_t{16}) int[arr_size];
  for (int i = 0; i < arr_size; ++i) {
    a[i] = 1;
    b[i] = 1;
  }
  //BaseCalculator<int> bc;
  //bc.Sum(a, b, arr_size);
  SSECalculator<int> ssec;
  ssec.Sum(a, b, arr_size);
  return 0;
}
