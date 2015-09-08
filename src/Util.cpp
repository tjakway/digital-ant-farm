#include "Util.hpp"

#include <random>

namespace jakway_antf
{

namespace {
    //mersenne 
    //see http://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
    std::random_device rd;
    std::mt19937 mersenne_rng(rd());
}

int getRandInRangeInclusive(int lower, int upper)
{
    std::uniform_int_distribution<int> distribution(lower, upper);
    return distribution(mersenne_rng);
}

}
