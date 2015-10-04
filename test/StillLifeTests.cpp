#include "gtest/gtest.h"
#include "Grid.hpp"
#include "TestUtils.hpp"
#include <algorithm>
#include <array>
#include <vector>

using namespace jakway_antf;

/**
 * the square is a stable shape in the game of life
 * it should never change regardless of how many generations we run
 */
TEST(StillLifeTests, testBlock)
{
    const POS_TYPE width=2, height=2;
    Grid grid(width, height);

    ASSERT_TRUE(grid.getSize() == (width * height));

    /**
     * check that the grid has 4 live tiles with a 1-cell dead tile buffer around them
     * grid.runGeneration will expand the grid since touchingEdges() is true
     */
    auto checkGrid = [&grid]() {
        std::vector<std::array<POS_TYPE, 2>> liveTiles ={
            {{1, 1}},
            {{1, 2}},
            {{2, 1}},
            {{2, 2}} };

        assertDeadExcept(&grid, &liveTiles);
        };

    //set all tiles to alive
    std::for_each(grid.begin(), grid.end(), [](bool& tile) { tile = TILE_ALIVE; });

    //check the grid is OK
    std::for_each(grid.begin(), grid.end(), [](bool& tile) { ASSERT_TRUE(tile == TILE_ALIVE); });
    ASSERT_TRUE(grid.getSize() == (width * height));

    //after running the first generation the grid will be expanded--this requires a new checking function
    //run generations and assert nothing has changed
    const unsigned int numGenerations = 100;
    for(unsigned int i = 0; i < numGenerations ; i++)
    {
        //after each generation, check the size is still correct and all the tiles are the same
        grid.runGeneration();
        checkGrid();
        ASSERT_TRUE(grid.getSize() == ((width+2) * (height+2)));
    }
}

/**
 * a non-square still life somewhat larger than the rectangle
 */
TEST(StillLifeTests, testBeehive)
{
    std::vector<std::array<POS_TYPE, 2>> liveTiles ={
        {{1, 2}},
        {{2, 1}},
        {{2, 3}},
        {{3, 1}},
        {{3, 3}},
        {{4, 2}} };

    //initialize the grid with the list of live tiles
    const POS_TYPE width=6, height=5;
    Grid grid(width, height, liveTiles);

    ASSERT_TRUE(grid.getSize() == (width * height));

    auto checkGrid = [&grid, &liveTiles]() {

        assertDeadExcept(&grid, &liveTiles);
        };

    //run generations and assert nothing has changed
    //the grid will NOT expand because it's been allocated with a 1-tile buffer
    const unsigned int numGenerations = 100;
    for(unsigned int i = 0; i < numGenerations ; i++)
    {
        //after each generation, check the size is still correct and all the tiles are the same
        grid.runGeneration();
        checkGrid();
        //size should not have changed
        ASSERT_TRUE(grid.getSize() == ((width) * (height)));
    }
}
