#include "matrix.h"
#include <iostream>

Matrix::Matrix(std::size_t r, std::size_t c) {
  _rows = r;
  _cols = c;
  if (_rows == 0) {
    _data = 0;
    return;
  }
  _data = new int*[_rows];
  for (size_t i = 0; i < _rows; ++i)
    if (_cols == 0) {
      _data[i] = 0;
    }
    else {
      _data[i] = new int[get_cols()];
    }
}

Matrix::~Matrix() {
  for (size_t i = 0; i < _rows; ++i)
    delete[] _data[i];
  delete[] _data;
}

Matrix::Matrix(const Matrix& m) {
  _rows = m.get_rows();
  _cols = m.get_cols();
  _data = new int*[_rows];
  for (size_t i = 0; i < get_rows(); ++i) {
    _data[i] = new int[_cols];
    for (size_t j = 0; j < get_cols(); ++j)
      set(i, j, m.get(i, j));
  }
}

void swap(Matrix &a, Matrix &b) {
  using std::swap;
  swap(a._rows, b._rows);
  swap(a._cols, b._cols);
  swap(a._data, b._data);
}

Matrix& Matrix::operator=(Matrix m) {
  swap(*this, m);
  return *this;
}

std::size_t Matrix::get_rows() const { return _rows; }
std::size_t Matrix::get_cols() const { return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
  _data[i][j] = val;
}

void Matrix::add(std::size_t i, std::size_t j, int val) {
  _data[i][j] += val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
  return _data[i][j];
}

void Matrix::print(const FILE* f) const {
  for (size_t i = 0; i < get_rows(); ++i)
    for (size_t j = 0; j < get_cols(); ++j)
      std::cout << get(i, j) << " \n"[j + 1 == get_cols()];
}

bool Matrix::operator==(const Matrix& m) const {
  if (get_rows() != m.get_rows() || get_cols() != m.get_cols())
    return false;
  for (size_t i = 0; i < get_rows(); ++i)
    for (size_t j = 0; j < get_cols(); ++j)
      if (get(i, j) != m.get(i, j))
        return false;
  return true;
}

bool Matrix::operator!=(const Matrix& m) const {
  return !(this->operator==(m));
}

Matrix& Matrix::operator+=(const Matrix& m) {
  for (size_t i = 0; i < get_rows(); ++i)
    for (size_t j = 0; j < get_cols(); ++j)
      add(i, j, m.get(i, j));
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
  for (size_t i = 0; i < get_rows(); ++i)
    for (size_t j = 0; j < get_cols(); ++j)
      add(i, j, -m.get(i, j));
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
  *this = *this * m;
  return *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
  Matrix buff = Matrix(*this);
  return buff += m;
}

Matrix Matrix::operator-(const Matrix& m) const {
  Matrix buff = Matrix(*this);
  return buff -= m;
}

Matrix Matrix::operator*(const Matrix& m) const {
  Matrix buff(get_rows(), m.get_cols());
  for (size_t i = 0; i < get_rows(); ++i)
    for (size_t j = 0; j < m.get_cols(); ++j)
      for (size_t k = 0; k < get_cols(); ++k)
        buff.add(i, j, get(i, k) * m.get(k, j));
  return buff;
}
