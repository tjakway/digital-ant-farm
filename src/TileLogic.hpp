#ifndef TILELOGIC_H
#define TILELOGIC_H

#include <stdexcept>
#include <string>

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
    static bool WillBeAlive(const bool alive, const unsigned int numLiveNeighbors);

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
