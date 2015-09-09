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

}
