#include "GameRunner.hpp"

using namespace jakway_antf;

//initialize static fields
const int GameRunner::UNLIMITED_HISTORY = 0,
          GameRunner::NO_HISTORY = -1;

GameRunner::GameRunner(Grid* seed)
{
    currentGen = new Grid(*seed);
    //XXX: initialize Backend pointers to the desired polymorphic types
}

GameRunner::~GameRunner()
{
    delete currentGen;
}

void GameRunner::runGeneration()
{
    //copy the current gen, mutate it, add the
    //XXX: IMPLEMENT

}


