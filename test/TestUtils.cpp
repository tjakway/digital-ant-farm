#include "TestUtils.hpp"

#include "Grid.hpp"

#include "gtest/gtest.h"
#include <iostream>
#include <algorithm>
#include <string>

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
           if(thisIsAlive != TILE_ALIVE)
               printGrid(grid);
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

void printGrid(Grid* grid)
{
    std::cerr << "Grid width: " << grid->getWidth() << ", height: " << grid->getHeight() << std::endl;
    for(auto it = grid->begin(); it != grid->end(); it++)
    {
        std::string itStr;
        if(*it == TILE_ALIVE)
            itStr = "true";
        else
            itStr = "false";
        std::cerr << "(" << it.getX() << ", " << it.getY() << "): " << itStr << std::endl;
    }
}

}
