#ifndef GRID_H
#define GRID_H

#include <list>

/**
 * TODO: handle grid resizing and tile setting
 */
class Grid
{
private:
    std::list<std::list<bool>> tiles;
    /** expand the grid by adding a column to each side and a row to the top and bottom*/
    void increaseGrid();

public:
    /** copy constructor */
    Grid(const Grid& other);

    int getWidth();
    int getHeight();
};

#endif
