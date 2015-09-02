#include "Util.h"

#include <random>

namespace {
    //mersenne 
    //see http://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
    std::random_device rd;
    std::mt19937 mersenne_rng(rd());
}

