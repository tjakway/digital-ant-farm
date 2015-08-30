#include "gtest/gtest.h"
#include "Grid.h"

TEST(GridTests, testCtor)
{
    const int width=10, height=10;
    Grid grid(width, height);
    ASSERT_TRUE(true);
}

TEST(GridTests, testExpandSize)
{
    const int width=10, height=10;
    Grid grid(width, height);
    grid.expandGrid();
}
