#include <iostream>

#include "NativeWindow.hpp"
#include "SDLWindow.hpp"
using namespace jakway_antf;

int main(int argc, char** argv)
{
    std::cout << "Hello, world!" << std::endl;
    NativeWindow* win = new SDLWindow();
    win->beginEventLoop(argc, argv);
}
