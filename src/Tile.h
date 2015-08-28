#ifndef TILE_H
#define TILE_H

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
     : x(paramX), y(paramY), alive(paramIsAlive), leftAlive(paramLeftAlive), rightAlive(paramRightAlive), topAlive(paramTopAlive), bottomAlive(paramBottomAlive)
    {}

    const int getX();
    const int getY();

    const bool isAlive();

    /** returns whether this tile will be alive in the next generation */
    const bool willLive();
}

#endif
