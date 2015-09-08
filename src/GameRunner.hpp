#ifndef GAME_RUNNER_H
#define GAME_RUNNER_H

#include <vector>

#include "Grid.hpp"

namespace jakway_antf
{

class GameRunner
{
private:
    /** constants for numGenHistory */
    static const int UNLIMITED_HISTORY,
                     NO_HISTORY;

private:
    std::vector<Grid*> oldGenerations;
    Grid *currentGen;
    /** the game's starting configuration
     *  because Conway's Game of Life is a 0-player game it's deterministic and the
     *  entire game can be recreated (very slowly) by just replaying it. */
    Grid *seedGrid;

    /** counter for generations elapsed*/
    unsigned long genElapsed;

    /** how many generations to store
     *  set to NO_HISTORY to not store any past grids (i.e. don't store any past generations)
     *  set to UNLIMITED_HISTORY to store an unlimited number of generations
     */
    long numGenHistory;

public:
    /**
     * input: starting state of the board
     */
    GameRunner(Grid* seed);
    ~GameRunner();
    void runGeneration();

};

}

#endif
