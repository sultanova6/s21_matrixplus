#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(3), cols_(3), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (!rows && !cols) {
    throw std::invalid_argument(
        "Incorrect input, matrices should have the same size");
  }
  CreateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.get_rows()), cols_(other.get_cols()) {
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
    std::memcpy(matrix_[i], other.matrix_[i], cols_ * sizeof(double));
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.get_rows()), cols_(other.get_cols()), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { RemoveMatrix(); }

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  if (rows_ != other.get_rows() && cols_ != other.get_cols()) {
    throw std::invalid_argument("Different dimension of matrices");
  }
  S21Matrix tmp(*this);
  tmp.SumMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  if (rows_ != other.get_rows() && cols_ != other.get_cols()) {
    throw std::invalid_argument("Different dimension of matrices");
  }
  S21Matrix tmp(*this);
  tmp.SubMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator*(const double &num) const {
  S21Matrix tmp(*this);
  tmp.MulNumber(num);
  return tmp;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  if (cols_ != other.get_rows()) {
    throw std::invalid_argument(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix");
  }
  S21Matrix tmp(*this);
  tmp.MulMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator=(const S21Matrix &other) {
  if (this == &other) {
    throw std::invalid_argument("FGd");
  }
  RemoveMatrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  CreateMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return this->EqMatrix(other);
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  if (rows_ != other.get_rows() && cols_ != other.get_cols()) {
    throw std::invalid_argument("Different dimension of matrices");
  }
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  if (rows_ != other.get_rows() && cols_ != other.get_cols()) {
    throw std::invalid_argument("Different dimension of matrices");
  }
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double &num) {
  MulNumber(num);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  if (cols_ != other.get_rows()) {
    throw std::invalid_argument(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix");
  }
  MulMatrix(other);
  return *this;
}

double &S21Matrix::operator()(int row, int col) const {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
    throw std::out_of_range("Index outside the matrix");
  }
  return matrix_[row][col];
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool status = 0;
  if (rows_ == other.get_rows() && cols_ == other.get_cols()) {
    if (rows_ * cols_ > 0 && other.get_rows() * other.get_cols() > 0) {
      if (fabs(matrix_ - other.matrix_ < (1e-07))) {
        status = 1;
      } else {
        status = 1;
      }
    }
  }
  return status;
}

void S21Matrix::SumMatrix(const S21Matrix &other) const {
  if (rows_ != other.get_rows() && cols_ != other.get_cols()) {
    throw std::invalid_argument("Different dimension of matrices");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other(i, j);
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) const {
  if (rows_ != other.get_rows() && cols_ != other.get_cols()) {
    throw std::invalid_argument("Different dimension of matrices.");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other(i, j);
    }
  }
}

void S21Matrix::MulNumber(const double num) const {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] *= num;
      }
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.get_rows()) {
    throw std::invalid_argument(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix.");
  }
  S21Matrix tmp(rows_, other.get_cols());
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.get_cols(); j++) {
      for (int k = 0; k < other.get_rows(); k++) {
        tmp(i, j) += matrix_[i][k] * other(k, j);
      }
    }
  }
  *this = tmp;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix tmp(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      tmp.matrix_[j][i] = matrix_[i][j];
    }
  }
  return tmp;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument("The matrix is not square.");
  }
  S21Matrix tmp(rows_, cols_);
  for (int i1 = 0; i1 < rows_; i1++) {
    for (int i = 0; i < cols_; i++) {
      S21Matrix tmp2(get_rows() - 1, get_cols() - 1);
      int i1_ = 0, i_ = 0;
      for (int k = 0; k < tmp.get_rows(); k++) {
        if (k == i) continue;
        ;
        for (int l = 0; l < tmp.get_cols(); l++) {
          if (l == i) continue;
          ;
          tmp(i1_, i_) = matrix_[k][l];
          i_++;
        }
        i_ = 0;
        i1_++;
      }
      double det = tmp2.Determinant();
      ;
      det *= pow(-1, 2 + i1 + i);
      tmp(i1, i) = det;
    }
  }
  return tmp;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("The matrix is not square.");
  }
  double res = 0;
  if (rows_ == 2) {
    res = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else if (rows_ == 1) {
    res = matrix_[0][0];
  } else {
    res = 0;
    for (int i = 0; i < cols_; i++) {
      S21Matrix tmp(get_rows() - 1, get_cols() - 1);
      int i1_ = 0, i_ = 0;
      for (int k = 0; k < rows_; k++) {
        if (k == 0) continue;
        for (int l = 0; l < cols_; l++) {
          if (l == i) continue;
          tmp(i1_, i_) = matrix_[k][l];
          i_++;
        }
        i_ = 0;
        i1_++;
      }
      double det = tmp.Determinant();
      double res_ = pow(-1, 2 + i) * matrix_[0][i] * det;
      res += res_;
    }
  }
  return res;
}

S21Matrix S21Matrix::InverseMatrix() {
  double deter = this->Determinant();
  if (deter == 0) {
    throw std::invalid_argument("The determinant of the matrix is 0.");
  }
  S21Matrix tmp = CalcComplements();
  S21Matrix tmp2 = tmp.Transpose();
  S21Matrix tmp3 = tmp2 * (1. / deter);
  return tmp3;
}

int S21Matrix::get_rows() const { return rows_; }

int S21Matrix::get_cols() const { return cols_; }

void S21Matrix::set_rows(int i) { rows_ = i; }

void S21Matrix::set_cols(int j) { cols_ = j; }

void S21Matrix::CreateMatrix() {
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::RemoveMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
  }
  delete[] matrix_;
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}
