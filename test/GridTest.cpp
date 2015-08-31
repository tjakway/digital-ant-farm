#include "gtest/gtest.h"
#include "Grid.h"
#include <list>

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
    //check dimensions
    //check width
    for(std::list<bool>* thisSubList : grid.tiles)
    {
        ASSERT_TRUE(thisSubList->size() == width);
    }
    //check height
    ASSERT_TRUE(grid.tiles.size() == height);

    grid.expandGrid();
    ASSERT_TRUE(grid.getWidth() == (width + 2));
    ASSERT_TRUE(grid.getHeight() == (height + 2));
}

TEST(GridTests, testTouchingEdges)
{
    const int width=10, height=10;
    Grid grid(width, height);
    ASSERT_FALSE(grid.touchingEdges());
    

}
