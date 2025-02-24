#include <iostream>
#include "BaseCalculator.h"
#include "SSECalculator.h"
#include "AVXCalculator.h"

constexpr int arr_size = 100000000;

int main(int argc, char** argv) {
  Matrix<double> ma(1920, 1080, 2.00);
  Matrix<double> mb(1080, 1920, 2.00);

  //BaseCalculator<double> bc;
  //bc.MatrixMul(ma, mb);

  SSECalculator<double> ssec;
  ssec.MatrixMul(ma, mb);

  AVXCalculator<double> avxc;
  avxc.MatrixMul(ma, mb);
  return 0;
}
