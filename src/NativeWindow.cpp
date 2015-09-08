#include "NativeWindow.hpp"

using namespace jakway_antf;

//define static constants
const int NativeWindow::DEFAULT_WIDTH = 640,
             NativeWindow::DEFAULT_HEIGHT = 480;

NativeWindow::NativeWindow() : NativeWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT)
{ }

NativeWindow::NativeWindow(int width, int height)
{
    window = new Fl_Window(width, height);
}

NativeWindow::~NativeWindow()
{
    delete window;
}
