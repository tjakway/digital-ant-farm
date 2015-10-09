#include <iostream>
#include <memory>

#include "NativeWindow.hpp"
#include "SDLWindow.hpp"
#include "Grid.hpp"
using namespace jakway_antf;

int main(int argc, char** argv)
{
    NativeWindow* win = new SDLWindow();

    std::shared_ptr<Grid> ptr = std::shared_ptr<Grid>(new Grid(2, 2));
    ptr->setTile(0, 0, TILE_ALIVE);
    ptr->setTile(1, 1, TILE_ALIVE);

    win->postIO(ptr);
    win->beginEventLoop(argc, argv);
}
