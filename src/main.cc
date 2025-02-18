#include <iostream>
#include "BaseCalculator.h"
#include "SSECalculator.h"
#include "AVXCalculator.h"

constexpr int arr_size = 100000000;

int main(int argc, char** argv) {
  double* a = new(std::align_val_t{16}) double[arr_size];
  double* b = new(std::align_val_t{16}) double[arr_size];
  for (int i = 0; i < arr_size; ++i) {
    a[i] = 10;
    b[i] = 20;
  }
  BaseCalculator<double> bc;
  bc.Mul(a, b, arr_size);
  SSECalculator<double> ssec;
  ssec.Mul(a, b, arr_size);
  AVXCalculator<double> avxc;
  avxc.Mul(a, b, arr_size);
  return 0;
}
