#include <gtest/gtest.h>
#include "../matrix.hpp"

using elem_t = double;
using matrix_t = matrix<elem_t>;

/*
matrix_t prepare_matrix_a()
{
  matrix_t matrix()
}
*/

TEST(matrix_cpp_test, constructor_1)
{
  size_t max_row = 5;
  size_t max_col = 5;
  elem_t elem = 12345.6789;
  

  for (size_t row = 0; row < max_row; ++row) {
    for (size_t col = 0; col < max_col; ++col) {

      matrix_t matrix(row, col, elem);
      EXPECT_EQ(matrix.row(), row);
      EXPECT_EQ(matrix.col(), col);

      for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
          EXPECT_EQ(matrix.get(i, j), elem);
        }
      }

    }
  }
}

TEST(matrix_cpp_test, constructor_2)
{
  matrix_t m{0, 1, 2, 3, 4};
  EXPECT_EQ(m.row(), 1);
  EXPECT_EQ(m.col(), 5);

  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(m.get(0, i), i);
  }
}

TEST(matrix_cpp_test, get_1)
{
  // This check is done at previous constructor tests
  EXPECT_TRUE(true);
}

TEST(matrix_cpp_test, get_2)
{
  // This check is done at previous constructor tests
  EXPECT_TRUE(true);
}

TEST(matrix_cpp_test, get_3)
{
  size_t max_row = 5;
  size_t max_col = 5;
  size_t sub_row = 2;
  size_t sub_col = 2; 
  

  for (size_t row = sub_row; row < max_row; ++row) {
    for (size_t col = sub_col; col < max_col; ++col) {

      // Initialization
      matrix_t matrix(row, col);
      for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
          elem_t elem = i * row + j;
          matrix.set(i, j, elem);
        }
      }

      // Usual check before getting submatrices
      EXPECT_EQ(matrix.row(), row);
      EXPECT_EQ(matrix.col(), col);
      for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
          elem_t elem = i * row + j;
          EXPECT_EQ(matrix.get(i, j), elem);
        }
      }
      
      // Testing submatrices
      for (size_t i = 0; i < row - sub_row; ++i) {
        for (size_t j = 0; j < col - sub_col; ++j) {

          // Getting submatrices
          auto sm = matrix.get(i, j, i + sub_row, j + sub_col);
          EXPECT_EQ(sm.row(), sub_row);
          EXPECT_EQ(sm.col(), sub_col);
          
          // Checking
          for (size_t si = 0; si < sub_row; ++si) {
            for (size_t sj = 0; sj < sub_col; ++sj) {
              EXPECT_EQ(sm.get(si, sj), matrix.get(si + i, sj + j));
            }
          }

        }
      }

    }
  }
}


