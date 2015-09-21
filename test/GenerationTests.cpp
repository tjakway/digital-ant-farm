#include "gtest/gtest.h"
#include "Grid.hpp"

namespace jakway_antf
{

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
        for(POS_TYPE x = 0; x < width + 2; x++)
        {
            for(POS_TYPE y = 0; y < height + 2; y++)
            {

            }
        }};

    //set all tiles to alive
    std::for_each(grid.begin(), grid.end(), [](bool& tile) { tile = TILE_ALIVE; });

    //check the grid is OK
    std::for_each(grid.begin(), grid.end(), [](bool& tile) { ASSERT_TRUE(tile == TILE_ALIVE); });
    ASSERT_TRUE(grid.getSize() == (width * height));

    //run generations and assert nothing has changed
    const unsigned int numGenerations = 100;
    for(unsigned int i = 0; i < numGenerations ; i++)
    {
        //after each generation, check the size is still correct and all the tiles are the same
        grid.runGeneration();
        ASSERT_TRUE(grid.getSize() == (width * height));
        std::for_each(grid.begin(), grid.end(), [](bool& tile) { ASSERT_TRUE(tile == TILE_ALIVE); });
    }
    
    
}

}
