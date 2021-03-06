#include "TileLogic.hpp"

#include <limits>
#include <string>
#include <array>
#include <memory>

using namespace jakway_antf;

/**
 * returns whether this tile will be alive in the next generation
 * note that this function ONLY calculates whether THIS tile will live--does not give any information about neighboring tiles
 * this is OK because by looping through every tile you will get the correct generation
 * implement Conway's 4 rules of the game of life
 */
bool TileLogic::WillBeAlive(const bool alive, const POS_TYPE numLiveNeighbors)
{
    /** 1. Any live cell with fewer than two live neighbours dies, as if caused by under-population. */
    if(alive && numLiveNeighbors < 2) 
        return false;

    /** 2. Any live cell with two or three live neighbours lives on to the next generation. */
    if(alive && (numLiveNeighbors == 2 || numLiveNeighbors == 2))
        return true;

    /** 3. Any live cell with more than three live neighbours dies, as if by overcrowding. */
    if(alive && (numLiveNeighbors > 3))
        return false;

    /** 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction. */
    if(!alive && numLiveNeighbors == 3)
        return true;

    //otherwise no change
    return alive;
}


namespace
{
    /**
     * checks for integer overflow in x or y
     * could make a generic version of this function
     */
    void checkOverflow(const POS_TYPE x, const POS_TYPE y, const std::string& baseExceptionStr)
    {
        std::string exceptionStr(baseExceptionStr);
        //error handling
        //check for overflow errors and construct the appropriate error message
        bool overflowX = false, overflowY = false;
        if(x == std::numeric_limits<POS_TYPE>::max())
            overflowX = true;
        if(y == std::numeric_limits<POS_TYPE>::max())
            overflowY = true;

        const std::string maxValStr = std::to_string(std::numeric_limits<POS_TYPE>::max());
        if(overflowX)
        {
            exceptionStr += (" x == " + maxValStr);
        }
        if(overflowY)
        {
            if(overflowX)
                exceptionStr += ";";
            exceptionStr += (" y == " + maxValStr);
        }
        if(overflowX || overflowY)
            throw std::overflow_error(exceptionStr);
    }
}

std::unique_ptr<std::array<std::array<POS_TYPE,2>, NUM_NEIGHBORS>> TileLogic::GetNeighbors(const POS_TYPE x, const POS_TYPE y)
{
    //check for overflow errors
    std::string exceptionStr = "Error in TileLogic::GetNeighbors:";
    checkOverflow(x, y, exceptionStr);

    //check for underflow errors
    //these get special identifiers so we can handle underflow errors explicitly
    POS_TYPE leftX = x - 1, lowerY = y - 1;
    if(x == 0)
        leftX = std::numeric_limits<POS_TYPE>::max();
    if(y == 0)
        lowerY = std::numeric_limits<POS_TYPE>::max();

    //return neighbor positions
    std::unique_ptr<std::array<std::array<POS_TYPE,2>, NUM_NEIGHBORS>> neighbors
    { new std::array<std::array<POS_TYPE,2>, NUM_NEIGHBORS> { //need an extra set of braces for each std::array, see http://stackoverflow.com/questions/12844475/why-cant-simple-initialize-with-braces-2d-stdarray
        { {{leftX, lowerY}},
          {{leftX, y}},
          {{leftX, y + 1}},
          {{x, lowerY}},
          //the tile is not it's neighbor, skip (x,y)
          {{x, y + 1}},
          {{x + 1, lowerY}},
          {{x + 1, y}},
          {{x + 1, y + 1}} }
    } }; //need an extra brace for the enclosing unique_ptr
    return neighbors;
}
