//UTIL_H might collide with some headers
#ifndef UTIL_ANTF_H
#define UTIL_ANTF_H

#include <memory>

namespace jakway_antf
{
template<typename T>
T getRandInRangeInclusive(T lower, T upper);

//added for backwards compatibility with C++11 compilers
//make_unique was added in the C++14 standard
//see http://stackoverflow.com/questions/17902405/how-to-implement-make-unique-function-in-c11
//keeping this out of the std namespace just in case
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args);

}

#endif
