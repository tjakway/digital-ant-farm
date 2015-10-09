#ifndef ANTF_SDL_WINDOW_H
#define ANTF_SDL_WINDOW_H

#include "NativeWindow.hpp"
#include "SDLException.hpp"

#include <stdexcept>
#include <string>
#include <memory>

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

#include <SDL.h>

namespace jakway_antf
{

/**
 * this class DOES NOT handle the management of whatever grid it might be drawing--that's the responsibility of whichever class is passing Grid to draw()
 * draw() ought to be this class' ONLY interface to a grid
 */
class SDLWindow : public NativeWindow
{
private:
    class SDLContext;

    static const std::array<const Uint8, 4> RenderClearColor;

    /** an offscreen frame used that SDL will render into */
    SDL_Window* hiddenWindow;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    std::shared_ptr<SDLWindow::SDLContext> context;

    class SDLContext
    {
    private:
        static const Uint32 initFlags;
        static bool exists; //statically initialized to false
                            //used to check if the singleton object already exists
        static std::shared_ptr<SDLContext> singletonPtr;
        //can only be obtained from factory method
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
        class SDLInitException : public SDLException
        {
        public:
            SDLInitException(const std::string&);
        };
    };

protected:
    virtual std::shared_ptr<unsigned char> drawGrid(const Grid* grid);
    void draw();

public:
    SDLWindow();
    SDLWindow(int width, int height, const char* label);

    virtual ~SDLWindow();
};



}

#endif
