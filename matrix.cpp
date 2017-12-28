#include "matrix.hpp"


template <typename Type, template <typename> typename Traits>
auto matrix<Type, Traits>::get(row_t row, col_t col) const -> elem_t
{
  return strategy_t::get(row, col);
}

template <typename Type, template <typename> typename Traits>
auto matrix<Type, Traits>::get(row_t r1, col_t c1, row_t r2, col_t c2) const -> matrix_t
{
  size_t row = r2 - r1;
  size_t col = c2 - c1;
  matrix_t matrix{row, col};

}

template <typename Type, template <typename> typename Traits>
auto matrix<Type, Traits>::set(row_t row, col_t col, elem_cref_t elem) -> void;
{
  strategy_t::set(row, col, elem);
}

template <typename Type, template <typename> typename Traits>
auto matrix<Type, Traits>::set(row_t r, col_t c, matrix_cref_t matrix) -> void
{
  if (r + matrix.row() >= row())
    throw bad_matrix_row;

  if (c + matrix.col() >= col())
    throw bad_matrix_col;

  for (size_t i = 0; i < matrix.row(); ++i) {
    for (size_t j = 0; j < matrix.col(); ++j) {
      auto elem = matrix.get(i, j);
      set(i + r, j + c, elem);
    }
  }
}

template <typename Type, template <typename> typename Traits>
auto matrix<Type, Traits>::add(matrix_cref_t matrix) -> void
{
  if (row() != matrix.row())
    throw bad_matrix_row;

  if (col != matrix.col())
    throw bad_matrix_col;

  for (size_t i = 0; i < matrix.row(); ++i) {
    for (size_t j = 0; j < matrix.col(); ++j) {
      get(i, j) += matrix.get(i, j);
    }
  }
}

template <typename Type, template <typename> typename Traits>
auto matrix<Type, Traits>::sub(matrix_cref_t matrix) -> void
{
  if (row() != matrix.row())
    throw bad_matrix_row;

  if (col != matrix.col())
    throw bad_matrix_col;

  for (size_t i = 0; i < matrix.row(); ++i) {
    for (size_t j = 0; j < matrix.col(); ++j) {
      get(i, j) -= matrix.get(i, j);
    }
  }
}

template <typename Type, template <typename> typename Traits>
auto matrix<Type, Traits>::mul(elem_t elem) -> void
{
  for (size_t i = 0; i < matrix.row(); ++i) {
    for (size_t j = 0; j < matrix.col(); ++j) {
      get(i, j) *= elem;
    }
  }
}


template <typename Type, template <typename> typename Traits>
auto matrix<Type, Traits>::dot(matrix_cref_t matrix) const -> matrix_t
{
  if (col() != matrix.row())
    throw bad_matrix_operation;

  auto row = row();
  auto idx = col();
  auto col = matrix.col();

  matrix_t result;
  

  for (size_t i = 0; i < row; ++i) {
    for (size_t j = 0; j < col; ++j) {
      elem_t elem{};

      for (size_t k = 0; k < idx; ++k) {
        elem += get(i, k) * matrix.get(k, j);
      }

      result.set(i, j, elem);
    }
  }

  return result;
}

template <typename Type, template <typename> typename Traits>
auto matrix<Type, Traits>::tr() const -> matrix_t
{
  matrix_t matrix(col(), row());

  for (size_t i = 0; i < col(); ++i) {
    for (size_t j = 0; j < row(); ++j) {
      matrix.get(j, i) = matrix.get(i, j);
    }
  }

  return matrix;
}


template class matrix<double>;
template class matrix<float>;