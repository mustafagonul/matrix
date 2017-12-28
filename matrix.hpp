#pragma once

#include "matrix_traits.hpp"


template <typename Type, template <typename> typename Traits = matrix_traits>
class matrix {
public:
  MATRIX_DEFINE();

public:
  matrix(row_t, col_t, elem_t = elem_t{});

public:
  auto get(row_t, col_t) const -> elem_cref_t;
  auto get(row_t, col_t, row_t, col_t) const -> matrix_t;
  
  auto set(row_t, col_t, elem_cref_t) -> void;
  auto set(row_t, col_t, matrix_cref_t) -> void;

  auto add(matrix_cref_t) -> void;
  auto sub(matrix_cref_t) -> void;
  auto mul(elem_t) -> void;
  auto dot(matrix_cref_t) const -> matrix_t;
  auto tr() const -> matrix_t;

  auto row() const -> row_t noexcept { return m_row; }
  auto col() const -> col_t noexcept { return m_col; }

private:
  auto imp() const -> imp_t noexcept { return m_imp; }

private:
  row_t m_row;
  col_t m_col;
  imp_t m_imp;
};

extern template class matrix<double>;
extern template class matrix<float>;
