#pragma once

#include "matrix_traits.hpp"


template <typename Type, template <typename> typename Traits = matrix_traits>
class matrix {
public:
  using traits_t = Traits<Type>;
  using matrix_t = matrix<Type, Traits>;

  using type_t = typename traits_t::type_t;
  using row_t  = typename traits_t::row_t;
  using col_t  = typename traits_t::col_t;
  using elem_t = typename traits_t::elem_t;
  using imp_t  = typename traits_t::imp_t;

public:
  matrix(row_t, col_t, elem_t = elem_t{});

public:
  auto get(row_t, col_t) -> elem_t&;
  auto get(row_t, col_t) const -> elem_t;
  auto get(row_t, col_t, row_t, col_t) const -> matrix_t;
  
  auto set(row_t, col_t, elem_t const&) -> void;
  auto set(row_t, col_t, matrix_t const&) -> void;

  auto add(matrix_t const&) -> void;
  auto sub(matrix_t const&) -> void;
  auto mul(elem_t) -> void;
  auto dot(matrix_t const& ) const -> matrix_t;
  auto tr() const -> matrix_t;

private:
  row_t m_row;
  col_t m_col;
  imp_t m_imp;
};

extern template class matrix<double>;
extern template class matrix<float>;
