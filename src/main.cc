#include <iostream>
#include "BaseCalculator.h"
#include "SSECalculator.h"
#include "AVXCalculator.h"

constexpr int arr_size = 100000000;

int main(int argc, char** argv) {
  float* a = new(std::align_val_t{16}) float[arr_size];
  float* b = new(std::align_val_t{16}) float[arr_size];
  for (int i = 0; i < arr_size; ++i) {
    a[i] = 10;
    b[i] = 20;
  }
  Matrix<float> ma(30, 10000, 1.00);
  Matrix<float> mb(10000, 10, 1.00);

  BaseCalculator<float> bc;
  bc.MatrixMul(ma, mb);
  //bc.Mul(a, b, arr_size);

  SSECalculator<float> ssec;
  ssec.MatrixMul(ma, mb);
  //ssec.Mul(a, b, arr_size);

  AVXCalculator<float> avxc;
  avxc.MatrixMul(ma, mb);
  //avxc.Mul(a, b, arr_size);
  return 0;
}
