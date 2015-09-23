#include "Grid.hpp"

#include <cassert>
#include <stdexcept>
#include <algorithm>
#include <array>
#include <vector>

#include "Util.hpp"
#include "TileLogic.hpp"
#include "Types.hpp"


using namespace jakway_antf;

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

POS_TYPE Grid::getWidth()
{
    return tiles.front()->size();
}

POS_TYPE Grid::getHeight()
{
    return tiles.size();
}

POS_TYPE Grid::getSize()
{
    return getWidth() * getHeight();
}

void Grid::expandGrid()
{
    //check the grid is the right shape before and after we modify it
#ifdef DEBUG
    assertGridIsRectangular(tiles);
#endif
    const POS_TYPE newWidth = getWidth() + 2;

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

Grid::Grid(const POS_TYPE width, const POS_TYPE height)
{
    //making i the same type is easier
    for(POS_TYPE i = 0; i < height; i++)
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

namespace
{
    /**
     * a barebones immutable Tile class
     */
    class Tile
    {
    private:
        const POS_TYPE x, y;
        const bool alive;
    public:
        Tile(const POS_TYPE pX, const POS_TYPE pY, const bool pAlive)
            : x(pX), y(pY), alive(pAlive) {}

        POS_TYPE getX()
        { return x; }
        POS_TYPE getY()
        { return y; }
        bool isAlive()
        { return alive; }
    };
}


void Grid::runGeneration()
{
    if(touchingEdges())
        expandGrid();

    assert(!touchingEdges());

    std::vector<Tile> differenceList;

    //add all changes to a difference list so that the generation only calculates which tiles live based on ALREADY ALIVE tiles, otherwise you're modifying a tiles' neighbor right before you check if it will live.  THIS IS A BUG!
    for(auto gridIt = begin(); gridIt != end(); gridIt++)
    {
        const bool isAlive = *gridIt;
        unsigned int numLiveNeighbors = gridIt.getNumLiveNeighbors();

        //change the tile based on if it will live
        const bool willBeAlive = TileLogic::WillBeAlive(isAlive, numLiveNeighbors);
        
        //check if the tile has changed
        //if so, add it to the difference list
        if(willBeAlive != isAlive)
        {
            differenceList.emplace_back(gridIt.getX(), gridIt.getY(), willBeAlive);
        }
    }

    //apply the changes to the grid
    for(Tile& diff : differenceList)
    {
        setTile(diff.getX(), diff.getY(), diff.isAlive());
    }
}

/**
 * return the selected row (corresponding to x) that contains the passed y value
 * will throw if out of bounds
 */
std::deque<bool>* Grid::getRow(POS_TYPE x, POS_TYPE y)
{
    //subtract 1 because y is zero-indexed
    if(tiles.size()-1 < y)
    {
       throw std::out_of_range("y is greater than the number of rows!");
    }

    std::deque<bool>* selectedRow = tiles.at(y);
    //subtract 1 because x is zero-indexed
    if(selectedRow->size()-1 < x)
    {
       throw std::out_of_range("x is greater than the number of columns!");
    }
    return selectedRow;
}

void Grid::setTile(POS_TYPE x, POS_TYPE y, bool alive)
{
    std::deque<bool>* selectedRow = getRow(x, y);

    //we've found the tile, modify it
    (*selectedRow)[x] = alive;
}

bool Grid::getTile(POS_TYPE x, POS_TYPE y)
{
    std::deque<bool>* selectedRow = getRow(x, y);
    return (*selectedRow)[x];
}

/**
 * returns true if the tile is alive
 * returns false if the tile is dead or if the tile is outside the grid
 */
bool Grid::getTileIfValid(const POS_TYPE x, const POS_TYPE y)
{
    //POS_TYPE is unsigned, can never be less than 0
    if(x >= getWidth())
        return TILE_DEAD;
    if(y >= getHeight())
        return TILE_DEAD;

    try
    {
        return getTile(x, y);
    }
    //don't catch other exceptions--might be completely unrelated and make debugging very painful
    catch(std::out_of_range& e)
    {
        return false;
    }
}

/**
 * set every tile in the grid to TILE_DEAD
 */
void Grid::clearGrid()
{
    /**
     * could make this easier by writing a custom iterator for Grid
     */
    for(POS_TYPE x = 0; x < getWidth(); x++)
    {
        for(POS_TYPE y = 0; y < getHeight(); y++)
        {
            setTile(x, y, TILE_DEAD);
        }
    }   
    
    assert(!touchingEdges());
}

//********************************
//GRID ITERATOR
//********************************

/**
 * this does the heavy lifting of the iterator
 * get the bool at GridIterator::pos or throw std::out_of_range if pos is invalid
 */
bool* Grid::GridIterator::getTile()
{
    if(xpos > grid->getWidth())
    {
        throw std::out_of_range("Exception in GridIterator: x out of range in getTile()!");
    }
    if(ypos > grid->getHeight())
    {
        throw std::out_of_range("Exception in GridIterator: y out of range in getTile()!");
    }

    //use grid->getRow instead of getRow because we need a pointer to the actual bool in the grid so we can modify it if necessary
    //grid->getTile returns the bool value, which can't be modified
    std::deque<bool>* row = grid->getRow(xpos, ypos);
    return &row->at(xpos);
}

/**
 * prefix increment operator
 */
Grid::GridIterator& Grid::GridIterator::operator++()
{
    //increment x then check if it went off the edge
    //if so, move it back to the leftmost side of the grid and shift to the next row
    xpos++;
    if(xpos >= grid->getWidth())
    {
        xpos = 0;
        ypos++;
    }

    return *this;
}

/**
 * postfix increment operator
 */
Grid::GridIterator Grid::GridIterator::operator++(int)
{
    GridIterator tmp(*this);
    operator++();
    return tmp;
}

/**
 * only true if both iterators point to the same Grid and are at the same position
 * this intentionally is NOT a deep equality test because we want to make sure that if 2 iterators are equal they can modify the same grid
 */
bool Grid::GridIterator::operator==(const GridIterator& other)
{
    return other.grid == grid && other.xpos == xpos && other.ypos == ypos;
}

bool Grid::GridIterator::operator!=(const GridIterator& other)
{
    //implement in terms of ==
    return !(*this == other);
}

bool& Grid::GridIterator::operator*()
{
    return *getTile();
}

unsigned int Grid::GridIterator::getNumLiveNeighbors()
{
    //every tile has 8 neighbors
    std::array<bool, NUM_NEIGHBORS> neighbors;
    neighbors.fill(false);

    //get a list of this tile's neighbors
    auto neighborPosArray = TileLogic::GetNeighbors(getX(), getY());
    assert(neighbors.size() == neighborPosArray.size());

    //check which neighbors are alive
    auto aliveIt = neighbors.begin();
    std::for_each(neighborPosArray.begin(), neighborPosArray.end(), [&aliveIt, this](std::array<POS_TYPE, 2> pos)
        {
            *aliveIt = this->grid->getTileIfValid(pos.front(), pos.back());
        });


    //count them
    unsigned int numLiveNeighbors = 0;
    std::for_each(neighbors.begin(), neighbors.end(), [&numLiveNeighbors](bool alive)
        {
            if(alive)
            {
                numLiveNeighbors++;
            }
        });

    return numLiveNeighbors;
}

POS_TYPE Grid::GridIterator::getX()
{
    return xpos;
}

POS_TYPE Grid::GridIterator::getY()
{
    return ypos;
}

Grid::iterator Grid::begin()
{
    return Grid::GridIterator(this, 0, 0);
}

/**
 * returns an iterator pointing to the off-the-end element (i.e. returns the iterator that would follow the last valid iterator)
 * should NOT be dereferenced
 */
Grid::iterator Grid::end()
{
    //return xpos == 0, ypos == height because incrementing the last valid iterator will set xpos = 0 and increment ypos
    //because xpos and ypos are 0-indexed, the ypos just after the last valid iterator is getHeight()
    return Grid::GridIterator(this, 0, getHeight());
}
