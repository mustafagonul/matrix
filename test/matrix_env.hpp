#pragma once

#include "gtest/gtest.h"
#include <random>


class matrix_env : public ::testing::Environment {
public:
  matrix_env();

  virtual ~matrix_env() override;
  virtual void SetUp() override;
  virtual void TearDown() override;
  
private:
 std::random_device* rd;  //Will be used to obtain a seed for the random number engine
 std::mt19937* gen;
};
