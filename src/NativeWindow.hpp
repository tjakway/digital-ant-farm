#ifndef ANTF_NATIVEWINDOW_H
#define ANTF_NATIVEWINDOW_H

#ifdef TESTING
#include "gtest/gtest.h"
#endif

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Double_Window.H>

#include <memory>
#include <mutex>

#include "DisplayBackend.hpp"

namespace jakway_antf
{

class ImageViewer;

class NativeWindow : public DisplayBackend
{
private:
   static const int DEFAULT_WIDTH, DEFAULT_HEIGHT; 

   Fl_Window *window;
   ImageViewer *viewer;

protected:
   
   /**
    * pure virtual function to have a rendering-specialized subclass draw the grid
    * and return a pointer to RGB8 format image data
    */
   virtual std::shared_ptr<unsigned char> drawGrid(const Grid* grid) = 0;
   virtual void processIO(std::shared_ptr<Grid>);

public:
   NativeWindow();
   NativeWindow(int width, int height, const char* label);

   virtual ~NativeWindow();

   virtual int beginEventLoop(int argc, char** argv);

   int getWidth() const;
   int getHeight() const;
   std::string& getLabel() const;
};


/**
 * a typesafe FLTK widget that draws the passed image data 
 */
class ImageViewer : public Fl_Double_Window
{
    static const int DEPTH, BITS;

    std::shared_ptr<unsigned char> imageData;
    std::mutex imageDataMutex;

    // FLTK DRAW METHOD
    void draw();

public:
    ImageViewer(int width, int height, const char *name=0); 

    void setImageData(std::shared_ptr<unsigned char>);
};

}
#endif
