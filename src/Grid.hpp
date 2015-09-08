#ifndef GRID_H
#define GRID_H

#include <deque>

#ifdef TESTING
#include "gtest/gtest.h"
#endif


namespace jakway_antf
{

/**
 * TODO: handle grid resizing and tile setting
 */
class Grid
{
#ifdef TESTING
    FRIEND_TEST(GridTests, testCtor);
    FRIEND_TEST(GridTests, testExpandSize);
    FRIEND_TEST(GridTests, testTouchingEdges);
    FRIEND_TEST(GridTests, testOutOfBounds);
    FRIEND_TEST(GridTests, testDoubleSetting);
#endif

private:
    std::deque<std::deque<bool>*> tiles;
    /** expand the grid by adding a column to each side and a row to the top and bottom*/
    void expandGrid();
    /** returns true if there are live tiles on the edge of the grid
     *  call this function at the beginning of every generation to guarantee the grid
     *  always has a buffer of at least 1 empty tile on every side
     *  otherwise we'll try to expand beyond the range of the grid
     *
     *  ought not have side effects
     */
    bool touchingEdges();

    std::deque<bool>* getRow(unsigned int x, unsigned int y, std::deque<std::deque<bool>*> paramTiles);

public:
    /** copy constructor */
    Grid(const Grid& other);

    Grid(const int width, const int height);

    ~Grid();

    /** mutate this grid into the next generation */
    void runGeneration();

    void setTile(unsigned int x, unsigned int y, bool alive);
    bool getTile(unsigned int x, unsigned int y);

    int getWidth();
    int getHeight();

    /**
     * sets the passed Grid to all TILE_DEAD
     * can also just reconstruct the grid object, but this saves a memory allocation
     */
    static void clearGrid(Grid*);
};

}

#endif
