#ifndef ANTF_NATIVEWINDOW_H
#define ANTF_NATIVEWINDOW_H

#ifdef TESTING
#include "gtest/gtest.h"
#endif

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

#include "DisplayBackend.hpp"

namespace jakway_antf
{
class NativeWindow : public DisplayBackend
{
private:
   static const int DEFAULT_WIDTH, DEFAULT_HEIGHT; 

   Fl_Double_Window *window;

protected:
   
   /**
    * pure virtual function to have a rendering-specialized subclass draw the grid
    * and return a pointer to RGB8 format image data
    */
   virtual std::shared_ptr<unsigned char> drawGrid(const Grid* grid) = 0;

public:
   NativeWindow();
   NativeWindow(int width, int height, const char* label);

   virtual ~NativeWindow();

   virtual int beginEventLoop(int argc, char** argv);

   int getWidth() const;
   int getHeight() const;
   std::string& getLabel() const;
};

}

#endif
