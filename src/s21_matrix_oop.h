#ifndef SRC_S21_MATRIX_OOP_H
#define SRC_S21_MATRIX_OOP_H

#include <cmath>
#include <cstring>
#include <iostream>

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  ~S21Matrix();

  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix operator*(const double &num) const;
  S21Matrix operator*(const S21Matrix &other) const;
  S21Matrix operator=(const S21Matrix &other);
  bool operator==(const S21Matrix &other) const;
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const double &num);
  S21Matrix &operator*=(const S21Matrix &other);
  double &operator()(int row, int col) const;

  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other) const;
  void SubMatrix(const S21Matrix &other) const;
  void MulNumber(const double num) const;
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  int get_rows() const;
  int get_cols() const;
  void set_rows(int i);
  void set_cols(int j);

  void CreateMatrix();
  void RemoveMatrix();

 private:
  int rows_, cols_;
  double **matrix_;
};

#endif  // SRC_S21_MATRIX_OOP_H