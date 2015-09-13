#include "Util.hpp"

#include "Types.hpp"

#include <random>

namespace jakway_antf
{

namespace {
    //mersenne 
    //see http://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
    std::random_device rd;
    std::mt19937 mersenne_rng(rd());
}

template<typename T>
T getRandInRangeInclusive(T lower, T upper)
{
    std::uniform_int_distribution<T> distribution(lower, upper);
    return distribution(mersenne_rng);
}

template POS_TYPE getRandInRangeInclusive<POS_TYPE>(POS_TYPE, POS_TYPE);
template int getRandInRangeInclusive<int>(int, int);

}
