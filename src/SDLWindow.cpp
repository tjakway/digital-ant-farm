#include "SDLWindow.hpp"

#include "Util.hpp"

#include <stdexcept>
#include <memory>
#include <functional>

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

#include <SDL.h>

using namespace jakway_antf;

//SDLException
SDLException::SDLException(const std::string& what_arg) : std::runtime_error(what_arg) {}

SDLException::SDLException(const std::string& what_arg, const char* sdlGetError) : std::runtime_error(what_arg + "  SDL_GetError: " + std::string(sdlGetError)) {}

//SDLContext inner class
const Uint32 SDLWindow::SDLContext::initFlags = SDL_INIT_TIMER | SDL_INIT_VIDEO;

//used to track if the singleton already exists
bool SDLWindow::SDLContext::exists = false;

//only used in the SDLContext CTOR--thrown if for some reason more than 1 SDLContext object exists
SDLWindow::SDLContext::SDLContextSingletonException::SDLContextSingletonException(const std::string& what_arg)
    : std::logic_error(what_arg) {}

SDLWindow::SDLContext::SDLInitException::SDLInitException(const std::string& what_arg)
    : SDLException("SDL Initialization Error: " + what_arg) {}

SDLWindow::SDLContext::SDLContext()
{
    //should never have 2 SDLContext objects!  its CTOR should only be called once!
    if(exists)
    {
        throw SDLContextSingletonException("SDLContext CTOR called but SDLContext already exists!");
    }
    else
    {
        //initialize SDL, check for errors, and set the flag so we don't initialize twice
        int errorCode = SDL_Init(initFlags);
        if(errorCode != 0)
        {
            throw SDLInitException(SDL_GetError());
        }

        exists = true;
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

SDLWindow::SDLWindow() : NativeWindow()
{ 
    //get the SDL context singleton
    context = SDLContext::GetSDLContext();

    //create a hidden SDL window of the same dimensions as the (visible) FLTK window
    hiddenWindow = SDL_CreateWindow(getLabel().c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, getWidth(), getHeight(), SDL_WINDOW_HIDDEN);
    if(hiddenWindow == nullptr)
    {
        throw SDLException("SDL_CreateWindow failed!", SDL_GetError());
    }

    //need to be able to render to a texture 
    renderer = SDL_CreateRenderer(hiddenWindow, -1, SDL_RENDERER_TARGETTEXTURE);
    if(renderer == nullptr)
    {
        throw SDLException("SDL_CreateRenderer failed!", SDL_GetError());
    }
}

/**
 */
std::shared_ptr<unsigned char> SDLWindow::drawGrid(const Grid* grid)
{
    //draw the Grid using SDL to the hidden window
    draw();
    //get the underlying surface of the hidden window
    //DO NOT delete this surface--it will be deleted when the window is deleted
    SDL_Surface* surface = SDL_GetWindowSurface(hiddenWindow);
    
    //to make sure we have an RGB8 value, copy the window surface to a new surface with that pixel format
    //FLTK can draw this directly with fl_draw_image
    //http://www.fltk.org/doc-1.3/drawing.html#ssect_DirectImageDrawing
    
    SDL_Surface* rgbSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGB888, 0);
    if(rgbSurface == nullptr)
    {
        std::string errorStr("error while converting window surface to RGB8 format.  SDL Error information: "),
            sdlErrorStr(SDL_GetError());
        errorStr += sdlErrorStr;
        throw SDLException(errorStr);
    }

    //may need to lock this surface to directly read pixels
    if(SDL_MUSTLOCK(rgbSurface))
    {
        if(SDL_LockSurface(rgbSurface) != 0)
        {
            std::string errorStr("error while locking copied rgb surface"),
                sdlErrorStr(SDL_GetError());
            errorStr += sdlErrorStr;
            throw SDLException(errorStr);
        }
    }
    //can now directly access pixels

//    const unsigned char* pixelsPtr = reinterpret_cast<const unsigned char*>(rgbSurface->pixels);
    unsigned char* pixelsPtr = (unsigned char*)(rgbSurface->pixels);

    //need a custom deleter because we created a copy of the SDL_Surface
    //we cant directly delete the pixel data but need to delete the underlying SDL_Surface instead
    //see http://stackoverflow.com/questions/10151834/why-cant-i-static-cast-between-char-and-unsigned-char for why this ought to be reinterpret_cast
    auto surfaceDeleter = [rgbSurface](decltype(pixelsPtr) ignored) 
            //don't directly delete the pixel buffer, delete the underlying SDL_Surface instead
            {
                //unlock the surface if necessary
                if(SDL_MUSTLOCK(rgbSurface))
                {
                    SDL_UnlockSurface(rgbSurface);
                }
                SDL_FreeSurface(rgbSurface);
            };
    return std::shared_ptr<unsigned char>(pixelsPtr, surfaceDeleter);
}

void SDLWindow::draw()
{
    

}

SDLWindow::~SDLWindow()
{
    //clean up SDL
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(hiddenWindow);

}
