#pragma once 


#include "matrix_exception.hpp"
#include <vector>


template <typename TYPE>
class matrix_traits {
public:
  using type_t = TYPE;
  using elem_t = type_t;
  using size_t = unsigned;
  using row_t = size_t;
  using col_t = size_t;
  using matrix_t = Matrix<type_t>;
  using imp_t = std::vector<type_t>;

};