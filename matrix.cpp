#include "matrix.hpp"
#include "matrix_strategy.hpp"
#include <algorithm>

template <typename Type, template <typename> typename Traits>
matrix<Type, Traits>::matrix(row_t row, col_t col, elem_t elem)
  : m_row{row}
  , m_col{col}
  , m_imp(row * col, elem)
{
}

template <typename Type, template <typename> typename Traits>
matrix<Type, Traits>::matrix(std::initializer_list<elem_t> const& l)
  : m_row{1}
  , m_col{l.size()}
  , m_imp{l}
{
}

template <typename Type, template <typename> typename Traits>
matrix<Type, Traits>::matrix(row_t row, col_t col, imp_cref_t imp)
  : m_row{row}
  , m_col{col}
  , m_imp(imp)
{
}

template <typename Type, template <typename> typename Traits>
matrix<Type, Traits>::matrix(row_t row, col_t col, imp_cref_t imp1, imp_cref_t imp2)
  : m_row{row}
  , m_col{col}
  , m_imp(imp1)
{
  std::copy(imp2.begin(), imp2.end(), std::back_inserter(m_imp));
}

template <typename Type, template <typename> typename Traits>
auto matrix<Type, Traits>::get(row_t row, col_t col) -> elem_ref_t
{
  return strategy_t::get(*this, row, col);
}


template <typename Type, template <typename> typename Traits>
auto matrix<Type, Traits>::get(row_t row, col_t col) const -> elem_cref_t
{
  return strategy_t::get(*this, row, col);
}

template <typename Type, template <typename> typename Traits>
auto matrix<Type, Traits>::get(row_t r1, col_t c1, row_t r2, col_t c2) const -> matrix_t
{
  size_t row = r2 - r1; // TODO mustafa: 
  size_t col = c2 - c1; // TODO mustafa: 
  matrix_t matrix(row, col);

  for (row_t i = 0; i < row; ++i) {
    for (col_t j = 0; j < col; ++j) {
      matrix.get(i, j) = get(i + r1, j + c1);
    }
  }

  return matrix;
}

template <typename Type, template <typename> typename Traits>
auto matrix<Type, Traits>::set(row_t row, col_t col, elem_cref_t elem) -> void
{
  strategy_t::set(*this, row, col, elem);
}

template <typename Type, template <typename> typename Traits>
auto matrix<Type, Traits>::set(row_t r, col_t c, matrix_cref_t matrix) -> void
{
  if (r + matrix.row() >= row())
    throw bad_matrix_row{};

  if (c + matrix.col() >= col())
    throw bad_matrix_col{};

  for (row_t i = 0; i < matrix.row(); ++i) {
    for (col_t j = 0; j < matrix.col(); ++j) {
      auto elem = matrix.get(i, j);
      set(i + r, j + c, elem);
    }
  }
}

template <typename Type, template <typename> typename Traits>
auto matrix<Type, Traits>::add(matrix_cref_t matrix) -> void
{
  if (row() != matrix.row())
    throw bad_matrix_row{};

  if (col() != matrix.col())
    throw bad_matrix_col{};

  for (row_t i = 0; i < matrix.row(); ++i) {
    for (col_t j = 0; j < matrix.col(); ++j) {
      get(i, j) += matrix.get(i, j);
    }
  }
}

template <typename Type, template <typename> typename Traits>
auto matrix<Type, Traits>::sub(matrix_cref_t matrix) -> void
{
  if (row() != matrix.row())
    throw bad_matrix_row{};

  if (col() != matrix.col())
    throw bad_matrix_col{};

  for (row_t i = 0; i < matrix.row(); ++i) {
    for (col_t j = 0; j < matrix.col(); ++j) {
      get(i, j) -= matrix.get(i, j);
    }
  }
}

template <typename Type, template <typename> typename Traits>
auto matrix<Type, Traits>::mul(elem_t elem) -> void
{
  for (row_t i = 0; i < row(); ++i) {
    for (col_t j = 0; j < col(); ++j) {
      get(i, j) *= elem;
    }
  }
}

template <typename Type, template <typename> typename Traits>
auto matrix<Type, Traits>::dot(matrix_cref_t matrix) const -> matrix_t
{
  if (col() != matrix.row())
    throw bad_matrix_operation{};

  auto rw = row();
  auto ix = col();
  auto cl = matrix.col();

  matrix_t result(rw, cl);
  
  for (row_t i = 0; i < rw; ++i) {
    for (col_t j = 0; j < cl; ++j) {
      elem_t elem{};

      for (size_t k = 0; k < ix; ++k) {
        elem += get(i, k) * matrix.get(k, j);
      }

      result.set(i, j, elem);
    }
  }

  return result;
}

template <typename Type, template <typename> typename Traits>
auto matrix<Type, Traits>::transpose() const -> matrix_t
{
  matrix_t matrix(col(), row());

  for (row_t i = 0; i < col(); ++i) {
    for (col_t j = 0; j < row(); ++j) {
      matrix.get(j, i) = matrix.get(i, j);
    }
  }

  return matrix;
}

template <typename Type, template <typename> typename Traits>
bool matrix<Type, Traits>::equal(matrix_cref_t m) const noexcept
{
  if (row() != m.row())
    return false;

  if (col() != m.col())
    return false;

  for (row_t i = 0; i < row(); ++i) {
    for (col_t j = 0; j < col(); ++j) {
      if (get(i, j) != m.get(i, j))
        return false;
    }
  }

  return true;
}

template <typename Type, template <typename> typename Traits>
auto matrix<Type, Traits>::vstack(matrix_cref_t cref) const -> matrix_t
{
  if (col() != cref.col())
    throw bad_matrix_col{};

  auto rw = row() + cref.row();
  auto cl = col();

  return matrix_t(rw, cl, m_imp, cref.m_imp);
}

template <typename Type, template <typename> typename Traits>
auto matrix<Type, Traits>::hstack(matrix_cref_t ref) const -> matrix_t
{
  if (row() != ref.row())
    throw bad_matrix_row{};

  auto t1 = transpose();
  auto t2 = ref.transpose();

  // auto sm = t1.vstack(t2);
  // auto tm = sm.transpose();
  // return tm;

  return t1.vstack(t2).transpose();
}


template class matrix<double>;
template class matrix<float>;