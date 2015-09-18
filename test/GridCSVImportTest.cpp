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
    std::shared_ptr<Grid> grid = Grid::readGridFromCVS(TestConstants::ONE_4X4_CSV);


}

}

#endif
