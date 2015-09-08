#include "GameRunner.h"

using namespace jakway_antf;

//initialize static fields
const int GameRunner::UNLIMITED_HISTORY = 0,
          GameRunner::NO_HISTORY = -1;

GameRunner::GameRunner(Grid* seed)
{
    currentGen = new Grid(*seed);
}

GameRunner::~GameRunner()
{

}

void GameRunner::runGeneration()
{
    //copy the current gen, mutate it, add the

}
