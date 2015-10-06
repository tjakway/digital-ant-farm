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
    window = new Fl_Window(width, height, label);
    //start adding widgets to this window
    window->begin();
    Fl_Scroll scroll(0, 0, width, height);
    viewer = new ImageViewer(width, height);
    window->end();
}

NativeWindow::~NativeWindow()
{
    delete viewer;
    delete window;
}

int NativeWindow::beginEventLoop(int argc, char** argv)
{
    Fl::visual(FL_RGB);
    window->show(argc, argv);
    return Fl::run();
}

/*************************************************
 *************ImageViewer*************************
 *************************************************/
          //red, green, and blue
const int ImageViewer::DEPTH = 3,
          //8-bit RGB
          ImageViewer::BITS = 8;

ImageViewer::ImageViewer(int width, int height, const char *name) : Fl_Double_Window(width,height,name)
{

    end();
    
    //initialize to a blank image (all black pixel data buffer)
    //in RGB8 each pixel is 8 bits AKA 1 byte
    //the standard says sizeof(char) will always be 1, see http://stackoverflow.com/questions/9727465/will-a-char-always-always-always-have-8-bits
    unsigned char* blankBuf = new unsigned char[width * height * DEPTH];
    //need an explicit deletor or shared_ptr won't use the right delete operator
    std::shared_ptr<unsigned char> blankBufPtr(blankBuf, [](unsigned char* buf)
        {
            delete[] buf;
        });

    setImageData(blankBufPtr);

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
