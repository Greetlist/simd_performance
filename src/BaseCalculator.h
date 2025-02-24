#ifndef _BASECALCULATOR_H
#define _BASECALCULATOR_H

#include <chrono>
#include <string>
#include <vector>
#include <iostream>
#include <string.h>

#include "defined_types.h"

template <class DataType>
class BaseCalculator {
public:
  BaseCalculator() = default;
  virtual ~BaseCalculator() = default;

  virtual void Sum(const DataType* a, const DataType* b, int size) {
    auto start = std::chrono::system_clock::now();
    DataType* result = new DataType[size];
    for (int i = 0; i < size; ++i) {
      result[i] = a[i] + b[i];
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

  virtual void Mul(const DataType* a, const DataType* b, int size) {
    auto start = std::chrono::system_clock::now();
    DataType* result = new DataType[size];
    for (int i = 0; i < size; ++i) {
      result[i] = a[i] * b[i];
    }
    auto end = std::chrono::system_clock::now();
    std::cout 
      << GetClassName() << " cost: "
      << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
      << " microseconds."
      << std::endl;
    this->check(result, size);
  }

  virtual void MatrixMul(const Matrix<DataType>& a, const Matrix<DataType>& b) {
    auto start = std::chrono::system_clock::now();
    int a_row = a.GetRow();
    int a_col = a.GetCol();
    int b_col = b.GetCol();
    DataType** a_data = a.GetData();
    DataType** b_data = b.GetData();
    Matrix<DataType> result(a_row, b_col, 0.00);
    DataType** result_data_ptr = result.GetData();
    for (int i = 0; i < a_row; ++i) {
      for (int j = 0; j < b_col; ++j) {
        int cur_result = 0;
        for (int k = 0; k < a_col; ++k) {
          cur_result += a_data[i][k] * b_data[k][j];
        }
        result_data_ptr[i][j] = cur_result;
      }
    }
    auto end = std::chrono::system_clock::now();
    std::cout 
      << GetClassName() << " Matrix Multiply cost: "
      << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
      << " microseconds."
      << std::endl;
    //result.Print();
  }

  Matrix<DataType> Transpose(const Matrix<DataType>& m) {
    int row = m.GetRow();
    int col = m.GetCol();
    Matrix<DataType> result(col, row, 0.00);
    DataType** m_data = m.GetData();
    DataType** r_data = result.GetData();
    for (int j = 0; j < col; ++j) {
      for (int i = 0; i < row; ++i) {
        r_data[j][i] = m_data[i][j];
      }
    }
    return result;
  }

  void check(DataType* vec, int size) {
    for (int i = 0; i < size; ++i) {
      if (vec[i] != 200) {
        std::cout << "Wrong index: " << i << ", value: " << vec[i] << std::endl;
        break;
      }
    }
  }
private:
  virtual std::string GetClassName() {return std::string{"BaseCalculator"};}
};

#endif
