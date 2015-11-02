#include "NativeWindow.hpp"


using namespace jakway_antf;

//define static constants
const int NativeWindow::DEFAULT_WIDTH = 640,
             NativeWindow::DEFAULT_HEIGHT = 480;

NativeWindow::NativeWindow() : NativeWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, nullptr)
{ }

NativeWindow::NativeWindow(int width, int height, const char* label)
{
}

NativeWindow::~NativeWindow()
{
}

int NativeWindow::beginEventLoop(int argc, char** argv)
{
}
