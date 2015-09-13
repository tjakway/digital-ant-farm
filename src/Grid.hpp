#ifndef GRID_H
#define GRID_H

#ifdef TESTING
#include <gtest/gtest.h>
#endif

#include <deque>

#include "Types.hpp"

#define TILE_ALIVE 1
#define TILE_DEAD 0


namespace jakway_antf
{

/**
 * TODO: handle grid resizing
 */
class Grid
{
#ifdef TESTING
    FRIEND_TEST(GridTests, testCtor);
    FRIEND_TEST(GridTests, testExpandSize);
    FRIEND_TEST(GridTests, testTouchingEdges);
    FRIEND_TEST(GridTests, testOutOfBounds);
    FRIEND_TEST(GridTests, testDoubleSetting);

    FRIEND_TEST(GridIteratorTests, iteratorSanityTest);
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

    std::deque<bool>* getRow(POS_TYPE x, POS_TYPE y);


public:
    /** copy constructor */
    Grid(const Grid& other);

    Grid(const POS_TYPE width, const POS_TYPE height);

    ~Grid();

    /** mutate this grid into the next generation */
    void runGeneration();

    void setTile(POS_TYPE x, POS_TYPE y, bool alive);
    bool getTile(POS_TYPE x, POS_TYPE y);

    POS_TYPE getWidth();
    POS_TYPE getHeight();

    POS_TYPE getSize();

    /**
     * sets the passed Grid to all TILE_DEAD
     * can also just reconstruct the grid object, but this saves a memory allocation
     */
    static void clearGrid(Grid*);

    /** custom iterator*/
    class GridIterator : std::iterator<std::input_iterator_tag, Grid>
    {
    private:
        Grid* grid;
        POS_TYPE xpos, ypos;

        bool* getTile();
    public:
        GridIterator(Grid* pGrid, POS_TYPE pX, POS_TYPE pY) : grid(pGrid), xpos(pX), ypos(pY) {}
        GridIterator(const GridIterator& it) : grid(it.grid), xpos(it.xpos), ypos(it.ypos) {}
        GridIterator& operator++();
        /** the postfix increment operator takes a dummy int value to distinguish it from
         * the prefix increment operator
         * see http://stackoverflow.com/questions/15244094/c-overloading-for-both-pre-and-post-increment*/
        GridIterator operator++(int);
        bool operator==(const GridIterator& other);
        bool operator!=(const GridIterator& other);
        bool& operator*();        
    };
    /** allows for more uniform and predictable syntax
     * access as Grid::iterator */
    typedef GridIterator iterator;

    /**iterator methods*/
    iterator begin();
    iterator end();
};

}

#endif
