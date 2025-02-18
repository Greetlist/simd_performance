#ifndef _BASECALCULATOR_H
#define _BASECALCULATOR_H

#include <chrono>
#include <string>
#include <vector>
#include <iostream>
#include <string.h>

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
