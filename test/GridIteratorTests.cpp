#include "gtest/gtest.h"

#include "Grid.hpp"

namespace jakway_antf
{

const int width=10, height=10;

TEST(GridIteratorTests, iteratorSanityTest)
{
   Grid grid(width, height);

   for(Grid::GridIterator it = grid.begin(); it != grid.end(); it++)
   {

   }


}

}
