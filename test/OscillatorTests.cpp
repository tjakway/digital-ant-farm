#include "gtest/gtest.h"
#include "Grid.hpp"
#include "TestUtils.hpp"
#include <array>
#include <vector>

using namespace jakway_antf;

TEST(OscillatorTests, testBlinker)
{
    std::vector<std::array<POS_TYPE, 2>> firstPeriodLiveTiles ={
        {{2, 1}},
        {{2, 2}},
        {{2, 3}} };

    std::vector<std::array<POS_TYPE, 2>> secondPeriodLiveTiles ={
        {{1, 2}},
        {{2, 2}},
        {{3, 2}} };

    const POS_TYPE width=5, height=5;
    Grid grid(width, height, firstPeriodLiveTiles);

    const unsigned int numGenerations = 100;
    for(unsigned int i = 0; i < numGenerations ; i++)
    {
        //i is even: check first period
        if(i % 2 == 0)
        {
            assertDeadExcept(&grid, &firstPeriodLiveTiles);
        }
        //i is odd: check second period
        else
        {
            assertDeadExcept(&grid, &secondPeriodLiveTiles);
        }

        grid.runGeneration();
        //size should not have changed
        ASSERT_TRUE(grid.getSize() == ((width) * (height)));
    }
}
