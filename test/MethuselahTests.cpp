#include "gtest/gtest.h"
#include "Grid.hpp"
#include "TestUtils.hpp"
#include "TestConstants.hpp"
#include <array>
#include <vector>

using namespace jakway_antf;

/**
 * the Diehard pattern lives for 130 generations then dies
 * NOTE: this test does not check the correctness of the intervening generations, just that they exist and that there are no living cells after 130 generations
 */
TEST(MethuselahTests, testDiehard)
{
    auto gridPtr = Grid::readGridFromCSV(TestConstants::DIEHARD_SEED);

    const unsigned int numGenerations = 129;
    for(unsigned int i = 0; i < numGenerations; i++)
    {
        gridPtr->runGeneration();
        ASSERT_FALSE(gridPtr->allDead());
    }

    //the die hard should be dead now
    gridPtr->runGeneration(); //the 130th generation
    ASSERT_TRUE(gridPtr->allDead());

    //no point in running any more generations since all tiles are dead
}
