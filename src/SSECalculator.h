#ifndef _SSECALCULATOR_H
#define _SSECALCULATOR_H

#include "BaseCalculator.h"
#include <immintrin.h>
#include <emmintrin.h>
#include <string.h>
#include <type_traits>

template<class DataType>
class SSECalculator : public BaseCalculator<DataType> {
public:
  SSECalculator() = default;
  ~SSECalculator() = default;

  void Sum(const DataType* a, const DataType* b, int size) override {
    auto start = std::chrono::system_clock::now();
    DataType* result = new(std::align_val_t{16}) DataType[size];
    memset(result, 0, sizeof(DataType) * size);
    for (int i = 0; i < size; i += 4) {
      if constexpr (std::is_same_v<DataType, float>) {
        __m128 ra = _mm_loadu_ps(&a[i]);
        __m128 rb = _mm_loadu_ps(&b[i]);
        _mm_storeu_ps(&result[i], _mm_add_ps(ra, rb));
      } else if constexpr (std::is_same_v<DataType, int>) {
        __m128i ra = _mm_loadu_si128(reinterpret_cast<const __m128i_u*>(&a[i]));
        __m128i rb = _mm_loadu_si128(reinterpret_cast<const __m128i_u*>(&b[i]));
        _mm_storeu_si128(reinterpret_cast<__m128i_u*>(&result[i]), _mm_add_epi64(ra, rb));
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
      for (int i = 0; i < size; i += 4) {
        __m128 ra = _mm_loadu_ps(&a[i]);
        __m128 rb = _mm_loadu_ps(&b[i]);
        _mm_storeu_ps(&result[i], _mm_add_ps(ra, rb));
      }
    } else if constexpr (std::is_same_v<DataType, double>) {
      for (int i = 0; i < size; i += 2) {
        //__m128d ra = _mm_loadu_pd(&a[i]);
        //__m128d rb = _mm_loadu_pd(&b[i]);
        //_mm_storeu_pd(&result[i], _mm_mul_pd(ra, rb));
        _mm_storeu_pd(&result[i], _mm_mul_pd(_mm_loadu_pd(&a[i]), _mm_loadu_pd(&b[i])));
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

  void MatrixMul(const Matrix<DataType>& a, const Matrix<DataType>& b) override {
    Matrix<DataType> transpose = this->Transpose(b);
    transpose.Print();
    int a_row = a.GetRow();
    int a_col = a.GetCol();
    int t_col = transpose.GetCol();
    DataType** a_data = a.GetData();
    DataType** t_data = transpose.GetData();
    Matrix<DataType> result(a_row, b_col, 0.00);
    DataType** result_data_ptr = result.GetData();
    if constexpr (std::is_same_v<float>) {
    } else if constexpr (std::is_same_v<double>) {
    }

    for (int i = 0; i < a_row; ++i) {
      for (int j = 0; j < t_row; ++j) {
        __mm128 res = 0;
        for (int k = 0; k < a_col; k += 4) {
          __mm128 cur_res = _mm_mul_ps(&a_data[i][j], &t_data[i][j]);
          res = _mm_add_ps(res, cur_res);
        }
        _mm_storeu_ps(&result_dat_ptr[i][], res);
      }
    }

    //result.Print();
  }

private:
  static constexpr int align_bytes = 16;
  static constexpr int sse_data_bytes = 128 / 8;
  std::string GetClassName() override {return std::string{"SSECalculator"};}
  constexpr int HandleDataSize() {
    return 4;
    //return static_cast<int>(sse_data_bytes / sizeof(DataType));
  }
};

#endif
