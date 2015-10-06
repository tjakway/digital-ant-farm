#include "NativeWindow.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/fl_draw.H>

using namespace jakway_antf;

//define static constants
const int NativeWindow::DEFAULT_WIDTH = 640,
             NativeWindow::DEFAULT_HEIGHT = 480;

NativeWindow::NativeWindow() : NativeWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, nullptr)
{ }

NativeWindow::NativeWindow(int width, int height, const char* label)
{
    window = new Fl_Double_Window(width, height, label);
    Fl_Scroll scroll(0, 0, width, height);
    
}

NativeWindow::~NativeWindow()
{
    delete window;
}

int NativeWindow::beginEventLoop(int argc, char** argv)
{
    Fl::visual(FL_RGB);
    window->show(argc, argv);
    return Fl::run();
}

ImageViewer::ImageViewer(int width, int height, const char *name) : Fl_Double_Window(width,height,name)
{
    end();
    redraw();
}

void ImageViewer::setImageData(std::shared_ptr<unsigned char> data)
{
    std::lock_guard<std::mutex> lock(imageDataMutex);
    imageData = data;
}

void ImageViewer::draw()
{
    std::lock_guard<std::mutex> lock(imageDataMutex);
    //draw over this entire widget-- (0,0) to (width, height)
    fl_draw_image((const unsigned char*)imageData.get(), 0, 0, w(), h());
}
