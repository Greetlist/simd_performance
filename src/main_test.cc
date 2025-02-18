#include <iostream>
#include <chrono>
#include <emmintrin.h>
#include <immintrin.h>
#include <cassert>
#include <string.h>

constexpr int arr_size = 100000000;

void check(double* c) {
  for (int i = 0; i < arr_size; ++i) {
    if (c[i] != 200) {
      std::cout << "Wrong index: " << i << ", value: " << c[i] << std::endl;
      break;
    }
  }
  memset(c, 0, sizeof(double) * arr_size);
}

int main_test(int argc, char** argv) {
  double* a = new(std::align_val_t{16}) double[arr_size];
  double* b = new(std::align_val_t{16}) double[arr_size];
  double* c = new(std::align_val_t{16}) double[arr_size];
  for (int i = 0; i < arr_size; ++i) {
    a[i] = 10;
    b[i] = 20;
  }

  auto s1 = std::chrono::system_clock::now();
  for (int i = 0; i < arr_size; ++i) {
    c[i] = a[i] * b[i];
  }
  auto e1 = std::chrono::system_clock::now();
  std::cout 
    << "cost: "
    << std::chrono::duration_cast<std::chrono::microseconds>(e1 - s1).count()
    << " microseconds."
    << std::endl;
  check(c);

  auto s2 = std::chrono::system_clock::now();
  for (int i = 0; i < arr_size; i += 2) {
    _mm_storeu_pd(&c[i], _mm_mul_pd(_mm_loadu_pd(&a[i]), _mm_loadu_pd(&b[i])));
    //__m128d ra = _mm_loadu_pd(&a[i]);
    //__m128d rb = _mm_loadu_pd(&b[i]);
    //_mm_storeu_pd(&c[i], _mm_mul_pd(ra, rb));
  }
  auto e2 = std::chrono::system_clock::now();
  std::cout 
    << "cost: "
    << std::chrono::duration_cast<std::chrono::microseconds>(e2 - s2).count()
    << " microseconds."
    << std::endl;
  check(c);

  auto s3 = std::chrono::system_clock::now();
  for (int i = 0; i < arr_size; i += 4) {
    _mm256_storeu_pd(&c[i], _mm256_mul_pd(_mm256_loadu_pd(&a[i]), _mm256_loadu_pd(&b[i])));
    //__m256d ra = _mm256_loadu_pd(&a[i]);
    //__m256d rb = _mm256_loadu_pd(&b[i]);
    //_mm256_storeu_pd(&c[i], _mm256_mul_pd(ra, rb));
  }
  auto e3 = std::chrono::system_clock::now();
  std::cout 
    << "cost: "
    << std::chrono::duration_cast<std::chrono::microseconds>(e3 - s3).count()
    << " microseconds."
    << std::endl;
  check(c);
  return 0;
}
