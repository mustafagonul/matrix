#pragma once


#include "matrix_traits.hpp"


template <typename TYPE>
class matrix : public matrix_traits<TYPE> {
public:
  matrix(row_t, col_t, elem_t = elem_t{});

public:
  auto get(row_t, col_t, row_t, col_t) const -> matrix_t;
  auto get(row_t, col_t) -> elem_t&;
  auto get(row_t, col_t) const -> elem_t;
  auto set(row_t, col_t, elem_t const&) -> void;

  auto add(matrix_t const&) -> void;
  auto sub(matrix_t const&) -> void;
  auto dot(matrix_t const& ) const -> matrix_t;

private:
  row_t m_row;
  col_t m_row;
  imp_t m_imp;
};

extern template class matrix<double>;
extern template class matrix<float>;
