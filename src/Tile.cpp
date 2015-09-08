#include "Tile.hpp"

using namespace jakway_antf;

int Tile::getX()
{
    return x;
}

int Tile::getY()
{
    return y;
}

bool Tile::isAlive()
{
    return alive;
}

/**
 * returns whether this tile will be alive in the next generation
 * note that this function ONLY calculates whether THIS tile will live--does not give any information about neighboring tiles
 * this is OK because by looping through every tile you will get the correct generation
 * implement Conway's 4 rules of the game of life
 */
bool Tile::willBeAlive()
{
    /** rules quoted from wikipedia: https://en.wikipedia.org/wiki/Conway's_Game_of_Life#Rules */
    int numLiveNeighbors = 0;
    if(leftAlive == true)
        numLiveNeighbors++;
    if(rightAlive == true)
        numLiveNeighbors++;
    if(topAlive == true)
        numLiveNeighbors++;
    if(bottomAlive == true)
        numLiveNeighbors++;

    /** 1. Any live cell with fewer than two live neighbours dies, as if caused by under-population. */
    if(numLiveNeighbors < 2) 
        return false;

    /** 2. Any live cell with two or three live neighbours lives on to the next generation. */
    if((isAlive() && numLiveNeighbors == 2) || (isAlive() && numLiveNeighbors == 3))
        return true;

    /** 3. Any live cell with more than three live neighbours dies, as if by overcrowding. */
    if(numLiveNeighbors > 3)
        return false;

    /** 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction. */
    if(!isAlive() && numLiveNeighbors == 3)
        return true;

    throw TileException("Invalid game board state -- should never reach here.");
}
