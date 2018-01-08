#pragma once

#include "matrix_traits.hpp"


template <typename Type, template <typename> typename Traits>
struct matrix_strategy {
  MATRIX_DEFINE_INTERNAL_TYPES();

  static auto index(matrix_cref_t matrix, row_t row, col_t col) noexcept -> size_t {
    return row * matrix.col() + col;
  }

  static auto get(matrix_cref_t matrix, row_t row, col_t col) -> elem_cref_t {
    auto i = index(matrix, row, col);

  #ifdef NDEBUG
    return matrix.m_imp[i];
  #else
    return matrix.m_imp.at(i);
  #endif
  }

  static auto get(matrix_ref_t matrix, row_t row, col_t col) -> elem_ref_t {
    auto i = index(matrix, row, col);

  #ifdef NDEBUG
    return matrix.m_imp[i];
  #else
    return matrix.m_imp.at(i);
  #endif
  }

  static void set(matrix_ref_t matrix, row_t row, col_t col, elem_cref_t elem) {
    auto i = index(matrix, row, col);

    matrix.m_imp[i] = elem;
  }
};
