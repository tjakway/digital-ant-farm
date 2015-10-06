#ifndef ANTF_GRIDCSVIMPORTTEST_H
#define ANTF_GRIDCSVIMPORTTEST_H

#include "gtest/gtest.h"
#include "Grid.hpp"
#include "TestConstants.hpp"

namespace
{
    /**
     * checks that the grid has live cells in a diagonal pattern from the top left to the bottom right
     */
    void checkDiag(std::shared_ptr<jakway_antf::Grid> grid)
    {
        POS_TYPE x = 0, y = 0;


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
            if(x >= grid->getWidth())
            {
                y++;
                x = 0;
            }
        }
    }
}

namespace jakway_antf
{

/**
* Test creating the grid from a CSV spreadsheet containing 1's to mark live cells
*/
TEST(GridCSVImportTests, testOneEmptyCSV)
{
    std::shared_ptr<Grid> grid = Grid::readGridFromCSV(TestConstants::ONES_4X4_CSV);
    checkDiag(grid);
}

/**
 * test reading a CSV containing all 1's
 */
TEST(GridCSVImportTests, testNoBlankCells)
{
    std::shared_ptr<Grid> grid = Grid::readGridFromCSV(TestConstants::NO_BLANKS);
    for(bool tile : *grid)
    {
        ASSERT_TRUE(tile == TILE_ALIVE);
    }
}

/**
 * test reading a CSV containing only strings (no blank cells)
 */
TEST(GridCSVImportTests, testOnlyStrings)
{
    std::shared_ptr<Grid> grid = Grid::readGridFromCSV(TestConstants::ONLY_STRINGS);
    for(bool tile : *grid)
    {
        ASSERT_TRUE(tile == TILE_ALIVE);
    }
}

/**
 * 4x4 spreadsheet with diagonal strings of mixed numbers and characters
 */
TEST(GridCSVImportTests, testDiagStrings)
{
    std::shared_ptr<Grid> grid = Grid::readGridFromCSV(TestConstants::DIAG_STRINGS);
    checkDiag(grid);
}

}
#endif
