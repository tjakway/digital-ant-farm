#include "Util.hpp"

#include "Types.hpp"

#include <random>
#include <utility>

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

//need type specializations because this is compiled into a library and linked
//with the test code (to avoid compiling the main project code twice)
//only template specializations can be included in library object code, not the templates themselves
template POS_TYPE getRandInRangeInclusive<POS_TYPE>(POS_TYPE, POS_TYPE);
template int getRandInRangeInclusive<int>(int, int);

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

}
