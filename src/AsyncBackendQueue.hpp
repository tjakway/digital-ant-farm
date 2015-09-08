#ifndef ANTF_ASYNC_BACKEND_QUEUE_H
#define ANTF_ASYNC_BACKEND_QUEUE_H

#include <deque>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "Grid.hpp"

namespace jakway_antf
{

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

    /** the thread function should be a static method to prevent it from running
     *  before AsyncBackendQueue is done being constructed 
     *  no need to declare this as a friend function, static methods have access
     *  to class internals but no this pointer, see 
     *  http://stackoverflow.com/questions/8685786/declaring-c-static-member-functions-as-friends-of-the-class-in-which-it-reside*/
    static void backendThreadProc(AsyncBackendQueue*);

protected:
    /** need to declare this class abstract or we can't call processIO in 
     * backendThreadProc because it will complain this class doesn't provide an implementation*/
    virtual void processIO(std::shared_ptr<Grid>) = 0;

public:
    AsyncBackendQueue();
    virtual ~AsyncBackendQueue();
    virtual void postIO(std::shared_ptr<Grid>);
};

}

#endif
