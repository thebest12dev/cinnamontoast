#include "../core/ui/Vector2.h"
#include <Windows.h>
#include <gtest/gtest.h>

class VectorTestFixture : public ::testing::Test {
protected:
  reflect::Vector2 vec1;

  void SetUp() override { 
    vec1 = reflect::Vector2(1, 5);
  }
};
TEST_F(VectorTestFixture, VectorAddTest) { 
    reflect::Vector2 vec2(1, 2); 
    reflect::Vector2 added = vec1 + vec2;
    EXPECT_EQ(added.x, 2);
    EXPECT_EQ(added.y, 7);
}