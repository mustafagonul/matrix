#pragma once

#include "matrix_traits.hpp"
#include <initializer_list>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>


template <typename Type, template <typename> typename Traits = matrix_traits>
class matrix {
public:
  MATRIX_DEFINE();

public:
  matrix(row_t, col_t, elem_t = elem_t{}); 
  matrix(std::initializer_list<elem_t>);

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

  
  auto trans() const -> matrix_t;

  template <type_t... Pack>
  static auto array(type_t, type_t... pack) -> matrix_t;

  static auto array(type_t) -> matrix_t

  auto vstack(matric_cref_t) const;
  auto hstack(matric_cref_t) const;

  template <template... Pack>
  static auto vstack(matrix_cref_t, Pack... pack) const;
  
  template <template... Pack>
  static auto hstack(matrix_cref_t, Pack... pack) const;
  

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

template <typename Type, template <typename> typename Traits>
  template <template... Pack>
auto matrix<Type, Traits>::vstack(matrix_cref_t lhs, Pack... pack) const
{
  auto rhs = vstack(pack...);

  return lhs.vstack(rhs)
}

template <typename Type, template <typename> typename Traits>
  template <template... Pack>
auto matrix<Type, Traits>::vstack(matrix_cref_t, Pack... pack) const;


extern template class matrix<double>;
extern template class matrix<float>;
