#ifndef ANTF_SDL_WINDOW_H
#define ANTF_SDL_WINDOW_H

#include "NativeWindow.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

namespace jakway_antf
{

class SDLWindow : public NativeWindow
{

protected:
    virtual void updateWindow(Fl_Double_Window* win);

public:
    SDLWindow();
    SDLWindow(int width, int height, const char* label);

    virtual ~SDLWindow();
};

}

#endif
