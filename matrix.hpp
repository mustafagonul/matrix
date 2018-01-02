#pragma once

#include "matrix_traits.hpp"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>


template <typename Type, template <typename> typename Traits = matrix_traits>
class matrix {
public:
  MATRIX_DEFINE();

public:
  matrix(row_t, col_t, elem_t = elem_t{});

public:
  auto get(row_t, col_t) -> elem_ref_t;
  auto get(row_t, col_t) const -> elem_cref_t;
  auto get(row_t, col_t, row_t, col_t) const -> matrix_t;
  
  auto set(row_t, col_t, elem_cref_t) -> void;
  auto set(row_t, col_t, matrix_cref_t) -> void;

  auto add(matrix_cref_t) -> void;
  auto sub(matrix_cref_t) -> void;
  auto mul(elem_t) -> void;
  auto dot(matrix_cref_t) const -> matrix_t;
  auto tr() const -> matrix_t;

  auto row() const noexcept -> row_t { return m_row; }
  auto col() const noexcept -> col_t { return m_col; }

private:
  auto imp() const noexcept -> imp_t { return m_imp; }

private:
  friend class boost::serialization::access;
  template <typename Archive>
  void serialize(Archive & ar, const unsigned int /* file_version */) {
      ar & m_row & m_col & m_imp;
  }

private:
  row_t m_row;
  col_t m_col;
  imp_t m_imp;
};

extern template class matrix<double>;
extern template class matrix<float>;
