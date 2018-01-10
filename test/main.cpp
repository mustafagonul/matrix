#include "gtest/gtest.h"


class matrix_env : public ::testing::Environment {
}

int main(int argc, char** argv)
{
  auto*new matrix_env

  ::testing::InitGoogleTest(&argc, argv);
  ::testing::AddGlobalTestEnvironment();

  return RUN_ALL_TESTS();
}