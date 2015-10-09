#ifndef ANTF_DISPLAYBACKEND_H
#define ANTF_DISPLAYBACKEND_H

#include "AsyncBackendQueue.hpp"

namespace jakway_antf
{

class DisplayBackend : public AsyncBackendQueue
{
public:
    /** need to hook the GUI event loop into the main function*/
    virtual int beginEventLoop(int argc, char** argv) = 0;
};

}

#endif
