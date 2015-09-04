#ifndef ANTF_ASYNC_BACKEND_QUEUE_H
#define ANTF_ASYNC_BACKEND_QUEUE_H

#include <deque>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "Grid.h"

class AsyncBackendQueue
{
    //don't implement processIO--leave pure virtual
    
private:
    /** a list of the generations to draw */
    std::deque<std::shared_ptr<Grid>> genDrawList;
    std::mutex  queueMutex;
    /** condition variable to signal the queue*/
    std::condition_variable queueCond;

    std::thread *backendThread;

    void backendThreadProc();

public:
    AsyncBackendQueue();
    virtual void postIO(std::shared_ptr<Grid>);
};

#endif
