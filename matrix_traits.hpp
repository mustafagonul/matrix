#pragma once 

#include "matrix_exception.hpp"
#include <vector>


template <typename Type>
class matrix_traits {
public:
  using type_t = Type;
  using elem_t = type_t;
  using size_t = unsigned;
  using row_t = size_t;
  using col_t = size_t;
  using imp_t = std::vector<type_t>;

};