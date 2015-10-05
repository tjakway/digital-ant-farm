#include "SDLWindow.hpp"

#include "Util.hpp"

#include <stdexcept>
#include <memory>

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

#include <SDL.h>

using namespace jakway_antf;

//used to track if the singleton already exists
bool SDLWindow::SDLContext::exists = false;

//only used in the SDLContext CTOR--thrown if for some reason more than 1 SDLContext object exists
SDLWindow::SDLContext::SDLContextSingletonException::SDLContextSingletonException(const std::string& what_arg)
    : std::logic_error(what_arg) {}

SDLWindow::SDLContext::SDLInitException::SDLInitException(const std::string& what_arg)
    : std::runtime_error("SDL Initialization Error: " + what_arg) {}

SDLWindow::SDLContext::SDLContext()
{
    if(exists)
    {
        throw SDLContextSingletonException("SDLContext CTOR called but SDLContext already exists!");
    }
    else
    {
        int errorCode = SDL_Init(initFlags);
        if(errorCode != 0)
        {
            throw SDLInitException(SDL_GetError());
        }
    }
}

SDLWindow::SDLContext::~SDLContext()
{
    SDL_Quit();
}

std::shared_ptr<SDLWindow::SDLContext> SDLWindow::SDLContext::GetSDLContext()
{
    if(!exists)
    {
        //can't use make_shared because SDLContext has a private constructor
        singletonPtr = std::shared_ptr<SDLWindow::SDLContext>(new SDLWindow::SDLContext());
    }

    return singletonPtr;
}


void SDLWindow::updateWindow(Fl_Double_Window* win)
{
    

}

SDLWindow::SDLWindow() : NativeWindow()
{
    //create a hidden SDL window of the same dimensions as the (visible) FLTK window
    hiddenWindow = SDL_CreateWindow(getLabel().c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, getWidth(), getHeight(), SDL_WINDOW_HIDDEN);

    //need to be able to render to a texture 
    renderer = SDL_CreateRenderer(hiddenWindow, -1, SDL_RENDERER_TARGETTEXTURE);


}

void SDLWindow::draw(Grid *grid)
{

}

SDLWindow::~SDLWindow()
{
    //clean up SDL
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(hiddenWindow);

}
