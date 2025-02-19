#ifndef _DEFINED_TYPES_H
#define _DEFINED_TYPES_H

#include <iostream>
#include <string.h>

template <class DataType>
class Matrix {
public:
  explicit Matrix(int row, int col, DataType init_value) {
    row_ = row;
    col_ = col;
    data_ = static_cast<DataType**>(malloc(sizeof(DataType*) * row));
    memset(data_, 0, sizeof(DataType*) * row);
    for (int i = 0; i < row; ++i) {
      data_[i] = static_cast<DataType*>(malloc(sizeof(DataType) * col));
      for (int j = 0; j < col; ++j) {
        data_[i][j] = init_value;
      }
    }
  }
  ~Matrix() {
    for (int i = 0; i < row_; ++i) {
      free(data_[i]);
    }
    free(data_);
  }
  int GetRow() const {return row_;}
  int GetCol() const {return col_;}
  DataType** GetData() const {return data_;}
  void Print() {
    for (int i = 0; i < row_; ++i) {
      for (int j = 0; j < col_; ++j) {
        std::cout << data_[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }
private:
  DataType** data_ = nullptr;
  int row_;
  int col_;
};

#endif
