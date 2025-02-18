#ifndef _AVXCALCULATOR_H
#define _AVXCALCULATOR_H

#include "BaseCalculator.h"
#include <avxintrin.h>
#include <string.h>
#include <type_traits>

template<class DataType>
class AVXCalculator : public BaseCalculator<DataType> {
public:
  AVXCalculator() = default;
  ~AVXCalculator() = default;

  void Sum(const DataType* a, const DataType* b, int size) override {
    auto start = std::chrono::system_clock::now();
    DataType* result = new(std::align_val_t{16}) DataType[size];
    memset(result, 0, sizeof(DataType) * size);
    for (int i = 0; i < size; i += 8) {
      if constexpr (std::is_same_v<DataType, float>) {
        __m256 ra = _mm256_loadu_ps(&a[i]);
        __m256 rb = _mm256_loadu_ps(&b[i]);
        _mm256_storeu_ps(&result[i], _mm256_add_ps(ra, rb));
      } else if constexpr (std::is_same_v<DataType, int>) {
        __m256i ra = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&a[i]));
        __m256i rb = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&b[i]));
        _mm256_storeu_si256(reinterpret_cast<__m256i*>(&result[i]), _mm256_add_epi64(ra, rb));
      }
    }
    auto end = std::chrono::system_clock::now();
    std::cout 
      << GetClassName() << " cost: "
      << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
      << " microseconds."
      << std::endl;
    DataType final_sum = 0;
    for (int i = 0; i < size; ++i) {
      final_sum += result[i];
    }
    std::cout << "final sum: " << final_sum << std::endl;
    delete []result;
  }

  void Mul(const DataType* a, const DataType* b, int size) override {
    auto start = std::chrono::system_clock::now();
    DataType* result = new(std::align_val_t{16}) DataType[size];
    static_assert(!std::is_same_v<DataType, int>, "DataType cannot be [int]");
    if constexpr (std::is_same_v<DataType, float>) {
      for (int i = 0; i < size; i += 8) {
        __m256 ra = _mm256_loadu_ps(&a[i]);
        __m256 rb = _mm256_loadu_ps(&b[i]);
        _mm256_storeu_ps(&result[i], _mm256_mul_ps(ra, rb));
      }
    } else if constexpr (std::is_same_v<DataType, double>) {
      for (int i = 0; i < size; i += 4) {
        //__m256d ra = _mm256_loadu_pd(&a[i]);
        //__m256d rb = _mm256_loadu_pd(&b[i]);
        //_mm256_storeu_pd(&result[i], _mm256_mul_pd(ra, rb));
        _mm256_storeu_pd(&result[i], _mm256_mul_pd(_mm256_loadu_pd(&a[i]), _mm256_loadu_pd(&b[i])));
      }
    }
    auto end = std::chrono::system_clock::now();
    std::cout 
      << GetClassName() << " cost: "
      << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
      << " microseconds."
      << std::endl;
    this->check(result, size);
  }
private:
  static constexpr int align_bytes = 16;
  static constexpr int sse_data_bytes = 128 / 8;
  std::string GetClassName() override {return std::string{"AVXCalculator"};}
  constexpr int HandleDataSize() {
    return 4;
    //return static_cast<int>(sse_data_bytes / sizeof(DataType));
  }
};

#endif
