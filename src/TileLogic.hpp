#ifndef TILELOGIC_H
#define TILELOGIC_H

#include <stdexcept>
#include <string>

#include "Types.hpp"

namespace jakway_antf
{

/**
 * Immutable class for represeting one tile on the board
 * contains information about its position and whether its neighbors are alive
 */
class TileLogic
{
public:
    /** returns whether this tile will be alive in the next generation */
    static bool WillBeAlive(const bool alive, const POS_TYPE numLiveNeighbors);

    /**
     * returns an array of coordinates (pairs of x and y, stored in an std::array of size 2) corresponding to the 8 neighbors of the passed tile
     * NOTE: DOES NOT DO ANY LOGIC OR BOUNDS CHECKING OF THESE COORDINATES--THIS METHOD DOES NOT INTERACT WITH A GRID AT ALL
     * returns numeric_limits<POS_TYPE>::max() for coordinates against the lower edge of the graph (i.e. for a coordinate (0,0) its neighbors would be numeric_limits<POS_TYPE>::max() instead of -1
     * throws std::overflow_error if x or y == numeric_limits<POS_TYPE>::max()
     */
    static std::array<std::array<POS_TYPE,2>, NUM_NEIGHBORS> GetNeighbors(const POS_TYPE x, const POS_TYPE y);

    /**
    * see http://stackoverflow.com/questions/4747706/standard-or-custom-exception-in-c
    * subclass created for the sake of clarity
    */
    class TileException : std::logic_error
    {
        public:
            TileException(const std::string& what_arg)
                : logic_error(what_arg) {}
    };
};

}

#endif
