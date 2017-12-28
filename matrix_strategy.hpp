#pragma once

#include "matrix_traits.hpp"


template <typename Type, template <typename> typename Traits>
struct matrix_strategy {
  DEFINE_MATRIX_INTERNAL_TYPES();

  static auto index(matrix_cref_t matrix, row_t row, col_t col) const {
    return row * matrix.col() + col;
  }

  static auto get(matrix_cref_t matrix, row_t row, col_t col) const {
    auto i = index(matrix, row, col);

    return matrix[index];
  }

  static auto get(matrix_ref_t matrix, row_t row, col_t col) const {
    auto i = index(matrix, row, col);

    return matrix[index];
  }

  static void set(matrix_ref_t matrix, row_t row, col_t col, elem_cref_t elem) {
    auto i = index(matrix, row, col);

    matrix[index] = elem;
  }
}
