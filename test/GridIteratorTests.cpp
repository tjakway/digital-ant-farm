#include "gtest/gtest.h"

#include "Grid.hpp"

namespace {
    const int width=10, height=10;
}

namespace jakway_antf
{


/**
 * Make sure regular begin()/end() iterator looping syntax and
 * C++11 for-each syntax works
 */
TEST(GridIteratorTests, testIteratorSyntax)
{
   Grid grid(width, height);

   //give the grid a predictable pattern: every other tile is alive
   //the first tile will be alive
   bool alive = true;
   for(int y = 0; y < grid.getWidth(); y++)
   {
       for(int x = 0; x < grid.getHeight(); x++)
       {
            grid.setTile(x, y, alive);
            alive = !alive;
       }
   }

   //regular iterator syntax OK
   alive = true;
   for(Grid::GridIterator it = grid.begin(); it != grid.end(); it++)
   {
        bool tileValue = *it;
        ASSERT_TRUE(alive == tileValue);
        alive = !alive;
   }

   alive = true;
   //C++11 for-each loop OK
   for(bool tileValue : grid)
   {
        ASSERT_TRUE(alive == tileValue);
        alive = !alive;
   }
}

/**
 * make sure we actually iterate through every tile
 */
TEST(GridIteratorTests, testIteratorCount)
{
    Grid grid(width, height);
    
    //loop through the grid and make sure we iterate the correct number of times
    int i = 0;
    for(bool tile : grid)
    {
        i++;
    } 

    ASSERT_TRUE(i == grid.getSize());
}

TEST(GridIteratorTests, testOutOfBounds)
{
    Grid grid(width, height);

    //an exception out to be thrown when dereferencing an iterator outside of the grid
    bool exceptionThrown = false;
    auto it = grid.end();
    try
    {
        *it;
    }
    catch(std::out_of_range)
    {
       exceptionThrown = true; 
    }
    ASSERT_TRUE(exceptionThrown);
}

/**
 * try iterating through a very large grid
 */
TEST(GridIteratorTests, testHugeGrid)
{
    const int hugeWidth = 1000, hugeHeight = 1000;
    Grid hugeGrid(hugeWidth, hugeHeight);

    ASSERT_TRUE(hugeGrid.getSize() == (hugeWidth * hugeHeight));
    int i = 0;
    for(auto n : hugeGrid)
    {
        i++;
    }

    ASSERT_TRUE(i == hugeGrid.getSize());
}

//tests iterating over non-square grids
TEST(GridIteratorTests, testTallGrid)
{
    const int tallWidth = 488, tallHeight = 923;
    Grid grid(tallWidth, tallHeight);

    int i = 0;
    for(auto n : grid)
    {
        i++;
    }
    ASSERT_TRUE(i == grid.getSize());
}
TEST(GridIteratorTests, testWideGrid)
{

}

}
