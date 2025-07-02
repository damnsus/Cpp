#pragma once

#include <algorithm>
#include <vector>

template <size_t N, size_t M, typename T = int64_t>
class Matrix {
 public:
  Matrix();
  Matrix(const std::vector<std::vector<T> >& k_vec);
  Matrix(const T& k_elem);
  Matrix(const Matrix& k_matrix);
  Matrix& operator=(const Matrix& k_matrix);
  ~Matrix();
  Matrix& operator+=(const Matrix<N, M, T>& k_matrix);
  Matrix& operator-=(const Matrix<N, M, T>& k_matrix);
  Matrix& operator*=(const T& k_elem);
  bool operator==(const Matrix<N, M, T>& k_matrix) const;
  Matrix<M, N, T> Transposed() const;
  T& operator()(size_t row, size_t column);
  const T& operator()(size_t row, size_t column) const;
  T Trace() const;

 private:
  T** matrix_;
  static T TraceFoo(const Matrix<N, N, T>& k_matrix);
};

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix() {
  matrix_ = new T*[N];
  for (size_t i = 0; i < N; ++i) {
    matrix_[i] = new T[M];
    for (size_t j = 0; j < M; ++j) {
      matrix_[i][j] = T();
    }
  }
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(const std::vector<std::vector<T> >& k_vec) {
  matrix_ = new T*[N];
  for (size_t i = 0; i < N; ++i) {
    matrix_[i] = new T[M];
    for (size_t j = 0; j < M; ++j) {
      matrix_[i][j] = k_vec[i][j];
    }
  }
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(const T& k_elem) {
  matrix_ = new T*[N];
  for (size_t i = 0; i < N; ++i) {
    matrix_[i] = new T[M];
    for (size_t j = 0; j < M; ++j) {
      matrix_[i][j] = k_elem;
    }
  }
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(const Matrix& k_matrix) {
  matrix_ = new T*[N];
  for (size_t i = 0; i < N; ++i) {
    matrix_[i] = new T[M];
    for (size_t j = 0; j < M; ++j) {
      matrix_[i][j] = k_matrix(i, j);
    }
  }
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator=(const Matrix& k_matrix) {
  Matrix<N, M, T> temp(k_matrix);
  std::swap(*this, temp);
  return *this;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::~Matrix() {
  for (size_t i = 0; i < N; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator+=(const Matrix<N, M, T>& k_matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      matrix_[i][j] += k_matrix(i, j);
    }
  }
  return *this;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator-=(const Matrix<N, M, T>& k_matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      matrix_[i][j] -= k_matrix(i, j);
    }
  }
  return *this;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator*=(const T& k_elem) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      matrix_[i][j] *= k_elem;
    }
  }
  return *this;
}

template <size_t N, size_t M, typename T>
bool Matrix<N, M, T>::operator==(const Matrix<N, M, T>& k_matrix) const {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      if (matrix_[i][j] != k_matrix.matrix_[i][j]) {
        return false;
      }
    }
  }
  return true;
}

template <size_t N, size_t M, typename T>
Matrix<M, N, T> Matrix<N, M, T>::Transposed() const {
  Matrix<M, N, T> temp;
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      temp(i, j) = matrix_[j][i];
    }
  }
  return temp;
}

template <size_t N, size_t M, typename T>
T& Matrix<N, M, T>::operator()(size_t row, size_t column) {
  return matrix_[row][column];
}

template <size_t N, size_t M, typename T>
const T& Matrix<N, M, T>::operator()(size_t row, size_t column) const {
  return matrix_[row][column];
}

template <size_t N, size_t M, typename T>
T Matrix<N, M, T>::TraceFoo(const Matrix<N, N, T>& k_matrix) {
  T trace = k_matrix(0, 0);
  for (size_t i = 1; i < N; ++i) {
    trace += k_matrix(i, i);
  }
  return trace;
}

template <size_t N, size_t M, typename T>
T Matrix<N, M, T>::Trace() const {
  return TraceFoo(*this);
}

/////////////////////////////////////////////////////////////

template <size_t N, size_t M, typename T = int64_t>
Matrix<N, M, T> operator+(const Matrix<N, M, T>& k_matrix1,
                          const Matrix<N, M, T>& k_matrix2) {
  Matrix<N, M, T> temp(k_matrix1);
  temp += k_matrix2;
  return temp;
}

template <size_t N, size_t M, typename T = int64_t>
Matrix<N, M, T> operator-(const Matrix<N, M, T>& k_matrix1,
                          const Matrix<N, M, T>& k_matrix2) {
  Matrix<N, M, T> temp(k_matrix1);
  temp -= k_matrix2;
  return temp;
}

template <size_t N, size_t M, size_t K, typename T>
Matrix<N, K, T> operator*(const Matrix<N, M, T>& k_matrix1,
                          const Matrix<M, K, T>& k_matrix2) {
  Matrix<N, K, T> temp;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < K; ++j) {
      for (size_t k = 0; k < M; ++k) {
        temp(i, j) += k_matrix1(i, k) * k_matrix2(k, j);
      }
    }
  }
  return temp;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> operator*(const Matrix<N, M, T>& k_matrix, const T& k_elem) {
  Matrix<N, M, T> temp(k_matrix);
  temp *= k_elem;
  return temp;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> operator*(const T& k_elem, const Matrix<N, M, T>& k_matrix) {
  return k_matrix * k_elem;
}
