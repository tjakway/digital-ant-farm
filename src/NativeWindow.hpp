#ifndef ANTF_NATIVEWINDOW_H
#define ANTF_NATIVEWINDOW_H

#ifdef TESTING
#include "gtest/gtest.h"
#endif

#include "DisplayBackend.hpp"

namespace jakway_antf
{
class NativeWindow : public DisplayBackend
{
private:
   static const int DEFAULT_WIDTH, DEFAULT_HEIGHT; 

protected:
   
   /**
    * pure virtual function to draw to one of the buffers
    */
   virtual void updateWindow(/*need a window type here!*/) = 0;

public:
   NativeWindow();
   NativeWindow(int width, int height, const char* label);

   virtual ~NativeWindow();

   virtual int beginEventLoop(int argc, char** argv);
};

}

#endif
