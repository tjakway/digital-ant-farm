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
    ASSERT_TRUE(grid.getWidth() == (width + 2));
    ASSERT_TRUE(grid.getHeight() == (height + 2));
}
