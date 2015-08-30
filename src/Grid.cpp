#include "Grid.h"

#include <cassert>
#include "Tile.h"

int Grid::getWidth()
{
    return -1;
}

int Grid::getHeight()
{
    return -1;
}

void Grid::expandGrid()
{
#ifdef DEBUG
    //check the grid is rectangular and not jagged
    //i.e. all sublists are the same size
    //note that the number of sublists does not have to be equal to the number of columns
    for(std::list<bool>* thisSubList : tiles)
    {
        for(std::list<bool>* otherSubList : tiles)
        {
            assert(thisSubList->size() == otherSubList->size());
        }
    }
#endif
    //add 1 tile to the beginning of each sublist (prepending a column)
    //add 1 tile to the end of each sublist (appending a column)
    for(std::list<bool>* thisSubList : tiles)
    {
        thisSubList->push_front(TILE_DEAD);
        thisSubList->push_back(TILE_DEAD);
    }

    //add 1 row to the beginning of the tiles list (prepending a row)
    //add 1 row to the end of the tiles list (appending a column)
    
#ifdef DEBUG
    //check the size is correct

#endif
}


bool Grid::touchingEdges()
{
    //TODO: IMPLEMENT
    return true;
}

Grid::Grid(const Grid& other)
{
    //TODO: IMPLEMENT
}

Grid::Grid(const int width, const int height)
{
    for(int i = 0; i < height; i++)
    {
        //don't have to loop to add items to the list
        //this list CTOR will insert <width> number of bools all at once
        std::list<bool>* subList = new std::list<bool>(width, false);
        //insert the sublist
        tiles.push_back(subList);
    }
}

Grid::~Grid()
{
    for(std::list<bool>* thisSubList : tiles)
    {
        delete thisSubList;
    }
}
