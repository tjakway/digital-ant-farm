#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "Grid.hpp"

#include <vector>
#include <array>

namespace jakway_antf
{
/**
 * assert all tiles in the passed Grid are dead except parameter points
 */
void assertDeadExcept(Grid *grid, std::vector<std::array<POS_TYPE, 2>> points);

}
#endif
