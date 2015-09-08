#ifndef ANTF_NATIVEWINDOW_H
#define ANTF_NATIVEWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include "Backend.hpp"

namespace jakway_antf
{
class NativeWindow
{
private:
   static const int DEFAULT_WIDTH, DEFAULT_HEIGHT; 

   Fl_Window *window;

public:
   NativeWindow();
   NativeWindow(int width, int height);

   virtual ~NativeWindow();
};

}

#endif
