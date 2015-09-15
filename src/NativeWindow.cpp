#include "NativeWindow.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

using namespace jakway_antf;

//define static constants
const int NativeWindow::DEFAULT_WIDTH = 640,
             NativeWindow::DEFAULT_HEIGHT = 480;

NativeWindow::NativeWindow() : NativeWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, nullptr)
{ }

NativeWindow::NativeWindow(int width, int height, const char* label)
{
    window = new Fl_Double_Window(width, height, label);
}

NativeWindow::~NativeWindow()
{
    delete window;
}

int NativeWindow::beginEventLoop(int argc, char** argv)
{
    window->show(argc, argv);
    return Fl::run();
}
