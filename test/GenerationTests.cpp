#include "gtest/gtest.h"
#include "Grid.hpp"
#include <algorithm>

using namespace jakway_antf;

/**
 * the square is a stable shape in the game of life
 * it should never change regardless of how many generations we run
 */
TEST(GenerationTests, testSquare)
{
    const POS_TYPE width=4, height=4;
    Grid grid(width, height);

    ASSERT_TRUE(grid.getSize() == (width * height));

    /**
     * XXX--TODO:
     * check that the grid has 4 live tiles with a 1-cell dead tile buffer around them
     * grid.runGeneration will expand the grid since touchingEdges() is true
     * also change the name of GameRunner.runGeneration because 2 classes with different methods with the same name is confusing
     */
    auto checkGrid = [&grid]() {
        //check the top and bottom edges are dead--we expanded the graph
        for(POS_TYPE x = 0; x < width + 1; x++)
        {
            ASSERT_TRUE(grid.getTile(x, 0) == TILE_DEAD);
            ASSERT_TRUE(grid.getTile(x, height + 1) == TILE_DEAD);
        }

        //check the left and right edges are dead
        for(POS_TYPE y = 0; y < height + 1; y++)
        {
            ASSERT_TRUE(grid.getTile(y, 0) == TILE_DEAD);
            ASSERT_TRUE(grid.getTile(y, width + 1) == TILE_DEAD);
        }

        //the middle of the graph is the square--it should be alive
        ASSERT_TRUE(grid.getTile(1, 1) == TILE_ALIVE);
        ASSERT_TRUE(grid.getTile(2, 1) == TILE_ALIVE);
        ASSERT_TRUE(grid.getTile(1, 2) == TILE_ALIVE);
        ASSERT_TRUE(grid.getTile(2, 2) == TILE_ALIVE);
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
