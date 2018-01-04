#pragma once 

#include "matrix_fwd.hpp"
#include "matrix_exception.hpp"
#include <vector>


template <typename Type>
class matrix_traits {
public:
  using type_t = Type;
  using elem_t = type_t;
  using elem_ref_t = elem_t&;
  using elem_cref_t = elem_t const&;
  using size_t = std::size_t;
  using row_t = size_t;
  using col_t = size_t;
  using imp_t = std::vector<type_t>;
  using imp_cref_t = imp_t const&;
};

#define MATRIX_DEFINE_INTERNAL_TYPES()                \
  using traits_t = Traits<Type>;                      \
  using matrix_t = matrix<Type, Traits>;              \
  using strategy_t = matrix_strategy<Type, Traits>;   \
  using matrix_ref_t = matrix_t&;                     \
  using matrix_cref_t = matrix_t const&;              \
  using type_t = typename traits_t::type_t;           \
  using row_t = typename traits_t::row_t;             \
  using col_t = typename traits_t::col_t;             \
  using elem_t = typename traits_t::elem_t;           \
  using elem_ref_t = typename traits_t::elem_ref_t;   \
  using elem_cref_t = typename traits_t::elem_cref_t; \
  using imp_t  = typename traits_t::imp_t;            \
  using imp_cref_t = typename traits_t::imp_cref_t;


#define MATRIX_DEFINE()                 \
  MATRIX_DEFINE_INTERNAL_TYPES()        \
  friend strategy_t;
  

