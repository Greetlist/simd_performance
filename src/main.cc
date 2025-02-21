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
  Matrix<double> ma(1920, 1080, 2.00);
  Matrix<double> mb(1080, 1920, 2.00);

  BaseCalculator<double> bc;
  bc.MatrixMul(ma, mb);
  //bc.Mul(a, b, arr_size);

  SSECalculator<double> ssec;
  ssec.MatrixMul(ma, mb);
  //ssec.Mul(a, b, arr_size);

  AVXCalculator<double> avxc;
  avxc.MatrixMul(ma, mb);
  //avxc.Mul(a, b, arr_size);
  return 0;
}
