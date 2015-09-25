#include "TestUtils.hpp"

#include "gtest/gtest.h"
#include <algorithm>

namespace jakway_antf
{

void assertDeadExcept(Grid *grid, std::vector<std::array<POS_TYPE, 2>> points)
{
   for(Grid::iterator it = grid->begin(); it != grid->end(); it++)
   {
       //check if points has this coordinate
       std::array<POS_TYPE, 2> thisGridPoint { {it.getX(), it.getY()} };

       const bool thisIsAlive = grid->getTile(it.getX(), it.getY());
       if(std::find(points.begin(), points.end(), thisGridPoint) != points.end())
       {
           //points contains this coordinate
           ASSERT_TRUE(thisIsAlive == TILE_ALIVE);
       }
       else
       {
           //if this coordinate isn't in the list of points that must be alive,
           //assert that it's dead
           ASSERT_TRUE(thisIsAlive == TILE_DEAD);
       }
   }
}

}
