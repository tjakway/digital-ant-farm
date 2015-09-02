#include "Grid.h"

#include <cassert>
#include "Tile.h"

#include <stdexcept>

#ifdef DEBUG
#include <iostream>
#endif

namespace
{
#ifdef DEBUG
    void assertGridIsRectangular(std::deque<std::deque<bool>*>& tiles)
    {
        //sanity check
        assert(!tiles.empty());

        //check the grid is rectangular and not jagged
        //i.e. all sublists are the same size
        //note that the number of sublists does not have to be equal to the number of columns
        for(std::deque<bool>* thisSubList : tiles)
        {
            for(std::deque<bool>* otherSubList : tiles)
            {
                assert(!otherSubList->empty());
                assert(thisSubList->size() == otherSubList->size());
            }
        }
    }
#endif
}

int Grid::getWidth()
{
    return tiles.front()->size();
}

int Grid::getHeight()
{
    return tiles.size();
}

void Grid::expandGrid()
{
    //check the grid is the right shape before and after we modify it
#ifdef DEBUG
    assertGridIsRectangular(tiles);
#endif
    const int newWidth = getWidth() + 2;

    //add 1 tile to the beginning of each sublist (prepending a column)
    //add 1 tile to the end of each sublist (appending a column)
    for(std::deque<bool>* thisSubList : tiles)
    {
        thisSubList->push_front(TILE_DEAD);
        thisSubList->push_back(TILE_DEAD);
    }

    //add 1 row to the beginning of the tiles list (prepending a row)
    //add 1 row to the end of the tiles list (appending a column)
    std::deque<bool> *firstList = new std::deque<bool>(newWidth, TILE_DEAD),
        *lastList = new std::deque<bool>(newWidth, TILE_DEAD);
    tiles.push_front(firstList);
    tiles.push_back(lastList);
    
    
#ifdef DEBUG
    //check the size is correct
    assertGridIsRectangular(tiles);
#endif
}



/**
 * should this be renamed to liveEdges()?
 */
bool Grid::touchingEdges()
{
    //check top edge for live tiles
    std::deque<bool>* topSubList = tiles.front();
    for(bool thisBool : *topSubList)
    {
        if(thisBool == TILE_ALIVE)
            return true;
    }

    //check bottom edge for live tiles
    std::deque<bool>* bottomSubList = tiles.back();
    for(bool thisBool : *bottomSubList)
    {
        if(thisBool == TILE_ALIVE)
            return true;
    }

    //check the left and right edges
    for(std::deque<bool>* thisSubList : tiles)
    {
        if(thisSubList->front() == TILE_ALIVE || thisSubList->back() == TILE_ALIVE)
            return true;
    }

    //if we haven't found any live tiles yet, there arent any in the edges
    return false;
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
        std::deque<bool>* subList = new std::deque<bool>(width, TILE_DEAD);
        //insert the sublist
        tiles.push_back(subList);
    }
}

Grid::~Grid()
{
    for(std::deque<bool>* thisSubList : tiles)
    {
        delete thisSubList;
    }
}

void Grid::runGeneration()
{
    if(touchingEdges())
        expandGrid();

    assert(!touchingEdges());

}

/**
 * return the selected row (corresponding to x) that contains the passed y value
 * will throw if out of bounds
 */
std::deque<bool>* Grid::getRow(unsigned int x, unsigned int y, std::deque<std::deque<bool>*> paramTiles)
{
    //subtract 1 because y is zero-indexed
    if(tiles.size()-1 < y)
    {
       throw std::out_of_range("y is greater than the number of rows!");
    }

    std::deque<bool>* selectedRow = paramTiles.at(y);
    //subtract 1 because x is zero-indexed
    if(selectedRow->size()-1 < x)
    {
       throw std::out_of_range("x is greater than the number of columns!");
    }
    return selectedRow;
}

void Grid::setTile(unsigned int x, unsigned int y, bool alive)
{
    std::deque<bool>* selectedRow = getRow(x, y, tiles);

    //we've found the tile, modify it
    (*selectedRow)[x] = alive;
}

bool Grid::getTile(unsigned int x, unsigned int y)
{
    std::deque<bool>* selectedRow = getRow(x, y, tiles);
    return (*selectedRow)[x];
}

/**
 * static method to set every tile in the grid to TILE_DEAD
 */
void Grid::clearGrid(Grid* grid)
{
    /**
     * could make this easier by writing a custom iterator for Grid
     */
    for(int x = 0; x < grid->getWidth(); x++)
    {
        for(int y = 0; y < grid->getHeight(); y++)
        {
            grid->setTile(x, y, TILE_DEAD);
        }
    }   
    
    assert(!grid->touchingEdges());
}
