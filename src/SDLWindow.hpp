#ifndef ANTF_SDL_WINDOW_H
#define ANTF_SDL_WINDOW_H

#include "NativeWindow.hpp"

#include <stdexcept>
#include <string>
#include <memory>

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

#include <SDL.h>

namespace jakway_antf
{

class SDLException : public std::runtime_error
{
    SDLException(const std::string&);
}

class SDLWindow : public NativeWindow
{
private:
    std::unique_ptr<Grid> grid;

    /** an offscreen frame used that SDL will render into */
    SDL_Window* hiddenWindow;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    shared_ptr<SDLContext> context;

    class SDLContext
    {
    private:
        static const Uint32 initFlags;
        static bool exists; //statically initialized to false
                            //used to check if the singleton object already exists
        static std::shared_ptr<SDLContext> singletonPtr;
        SDLContext();
    public:
        //not copyable
        SDLContext(const SDLContext&) = delete;

        ~SDLContext();

        static std::shared_ptr<SDLContext> GetSDLContext();

        //except inner classes
        class SDLContextSingletonException : public std::logic_error
        {
        public:
            SDLContextSingletonException(const std::string&);
        };
        class SDLInitException : public std::runtime_error
        {
        public:
            SDLInitException(const std::string&);
        };
    };

protected:
    virtual void updateWindow(Fl_Double_Window* win);
    void draw();

public:
    SDLWindow(std::unique_ptr<Grid>);
    SDLWindow(int width, int height, const char* label, std::unique_ptr<Grid> pGrid);

    virtual ~SDLWindow();

    void setGrid(Grid *grid);
};



}

#endif
