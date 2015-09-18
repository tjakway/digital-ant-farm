#ifndef ANTF_GRIDCSVIMPORTTEST_H
#define ANTF_GRIDCSVIMPORTTEST_H

#include "gtest/gtest.h"
#include "Grid.hpp"
#include "TestConstants.hpp"

namespace jakway_antf
{

    /**
     * Test creating the grid from a CSV spreadsheet containing 1's to mark live cells
     */
TEST(GridCSVImportTests, testOneEmptyCSV)
{
    std::shared_ptr<Grid> grid = Grid::readGridFromCSV(TestConstants::ONE_4X4_CSV);
    int x = 0, y = 0;


    //the spreadsheet has 1's diagonally, like this:
    //1 0 0 0
    //0 1 0 0
    //0 0 1 0
    //0 0 0 1
    //except that instead of 0's it has blank cells
    for(bool tile : *grid)
    {
        if(x == y)
            ASSERT_TRUE(tile == TILE_ALIVE);
        else
            ASSERT_TRUE(tile == TILE_DEAD);

        x++;
        y++;
    }
}

}

#endif
