#include "SDLException.hpp"

#include <SDL.h>
#include <string>

using namespace jakway_antf;

SDLException::SDLException(const std::string& what_arg) : std::runtime_error(what_arg) {}

SDLException::SDLException(const std::string& what_arg, const char* sdlGetError) : std::runtime_error(what_arg + "  SDL_GetError: " + std::string(sdlGetError)) {}
