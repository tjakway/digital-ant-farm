#ifndef TILE_H
#define TILE_H

#include <stdexcept>
#include <string>

/** adds some clarity instead of using magic true/false all over the place */
#define TILE_DEAD false
#define TILE_ALIVE true

/**
 * Immutable class for represeting one tile on the board
 * contains information about its position and whether its neighbors are alive
 */
class Tile
{
    const int x, y;
    const bool leftAlive, rightAlive, topAlive, bottomAlive;
    /** whether this tile is alive */
    const bool alive;

    public:
    Tile(int paramX, int paramY, bool paramIsAlive, bool paramLeftAlive, bool paramRightAlive, bool paramTopAlive, bool paramBottomAlive)
     : x(paramX), y(paramY),  leftAlive(paramLeftAlive), rightAlive(paramRightAlive), topAlive(paramTopAlive), bottomAlive(paramBottomAlive), alive(paramIsAlive)
    {}

    int getX();
    int getY();

    bool isAlive();

    /** returns whether this tile will be alive in the next generation */
    bool willBeAlive();
};

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

#endif
