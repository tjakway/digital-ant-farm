#ifndef BACKEND_ANTF_H
#define BACKEND_ANTF_H

#include <memory>

#include "Grid.hpp"

namespace jakway_antf
{

/**
 * pure virtual interface all backends must derive from
 * backends might include printing a log, displaying the game on the screen, writing to a video file, etc.
 */
class Backend
{
protected:
    virtual void processIO(std::shared_ptr<Grid>) = 0;

public:
    virtual void postIO(std::shared_ptr<Grid>) = 0;

};

#endif

}
