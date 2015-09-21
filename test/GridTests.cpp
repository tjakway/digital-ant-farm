#include "gtest/gtest.h"
#include "Grid.hpp"
#include "Util.hpp"
#include <list>

namespace
{
    const POS_TYPE width=10, height=10;
}

//google tests needs tests to be declared in the same namespace
namespace jakway_antf
{

TEST(GridTests, testCtor)
{
    Grid grid(width, height);
    ASSERT_TRUE(true);
}

TEST(GridTests, testExpandSize)
{
    Grid grid(width, height);
    //check dimensions
    //check width
    for(std::deque<bool>* thisSubList : grid.tiles)
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
    Grid grid(width, height);
    ASSERT_FALSE(grid.touchingEdges());
    
    grid.setTile(0, 0, TILE_ALIVE);
    ASSERT_TRUE(grid.touchingEdges());

    grid.setTile(0, 0, TILE_DEAD);
    ASSERT_FALSE(grid.touchingEdges());

    //check corners
    //check top left corner
    grid.setTile(0, 0, TILE_ALIVE);
    //this 3-line chunk of code could be refactored into a static function but I think it's clearer to read it inline here
    ASSERT_TRUE(grid.touchingEdges());
    grid.clearGrid();
    ASSERT_FALSE(grid.touchingEdges());

    //check bottom right corner
    grid.setTile(width-1, height-1, TILE_ALIVE);
    ASSERT_TRUE(grid.touchingEdges());
    grid.clearGrid();
    ASSERT_FALSE(grid.touchingEdges());

    //check top right corner
    grid.setTile(width-1, 0, TILE_ALIVE);
    ASSERT_TRUE(grid.touchingEdges());
    grid.clearGrid();
    ASSERT_FALSE(grid.touchingEdges());

    //check bottom left corner
    grid.setTile(0, height-1, TILE_ALIVE);
    ASSERT_TRUE(grid.touchingEdges());
    grid.clearGrid();
    ASSERT_FALSE(grid.touchingEdges());
}

TEST(GridTests, testOutOfBounds)
{
    Grid grid(width, height);
    ASSERT_FALSE(grid.touchingEdges());

    //check setting a tile outside the grid throws an exception
    //the grid should not expand on demand to accomodate this because the grid can only expand by 1 tile per generation and trying to expand further than that is a bug
    //test it with both TILE_ALIVE and TILE_DEAD
    bool exceptionCaught = false;
    try {
        grid.setTile(width + 1, height + 1, TILE_ALIVE);
    } catch(std::out_of_range)
    {
        exceptionCaught = true;
    }
    ASSERT_TRUE(exceptionCaught);

    exceptionCaught = false;
    try {
        grid.setTile(width + 1, height + 1, TILE_DEAD);
    } catch(std::out_of_range)
    {
        exceptionCaught = true;
    }
    ASSERT_TRUE(exceptionCaught);
}

/**
 * test that calling setTile twice doesn't cause errors
 * this test randomly generates its parameters
 */
TEST(GridTests, testDoubleSetting)
{
    const POS_TYPE lower = 10, upper = 1000;
    const POS_TYPE width = getRandInRangeInclusive<POS_TYPE>(lower, upper),
              height = getRandInRangeInclusive<POS_TYPE>(lower, upper);
    Grid grid(width, height);
    ASSERT_FALSE(grid.touchingEdges());

   const POS_TYPE doubleSetPos[] = { getRandInRangeInclusive(lower, width),
                                getRandInRangeInclusive(lower, height) };
   const POS_TYPE numTimesDoubleSet = getRandInRangeInclusive(lower, upper);

   for(POS_TYPE i = 0; i < numTimesDoubleSet; i++)
   {
       //randomly decide to set the tile to alive or dead
       const bool tileState = getRandInRangeInclusive(0, 10) % 2 == 0;
       grid.setTile(doubleSetPos[0], doubleSetPos[1], tileState);
       ASSERT_TRUE(grid.getTile(doubleSetPos[0], doubleSetPos[1]) == tileState);
   }
}

}
