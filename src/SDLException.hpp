#ifndef ANTF_SDLEXCEPTION_H
#define ANTF_SDLEXCEPTION_H

#include <stdexcept>
#include <string>

namespace jakway_antf
{
class SDLException : public std::runtime_error
{
public:
    SDLException(const std::string&);
    SDLException(const std::string&, const char*);
};

}

#endif
