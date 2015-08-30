#include "gtest/gtest.h"
#include "Grid.h"

TEST(grid_tests, test_ctor)
{
    const int width=10, height=10;
    Grid grid(width, height);
    ASSERT_TRUE(true);
}
