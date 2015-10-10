#include "AsyncBackendQueue.hpp"

using namespace jakway_antf;

void AsyncBackendQueue::backendThreadProc(AsyncBackendQueue *asyncBackendQueue)
{
    std::unique_lock<std::mutex> lock(asyncBackendQueue->queueMutex);

    //wait until we have something in the queue
    asyncBackendQueue->queueCond.wait(lock, [asyncBackendQueue](){ return !asyncBackendQueue->genDrawList.empty(); });

    //draw events in the order they're added to the queue
    std::shared_ptr<Grid> oldestEvent = asyncBackendQueue->genDrawList.back();
    //delete the item we just fetched
    asyncBackendQueue->genDrawList.pop_back(); 
    
    asyncBackendQueue->processIO(oldestEvent);

    //unlock (to prevent deadlock) and recurse so the thread loops forever
    //and keeps checking for events
    //it ought to:
    //-wait until it finds an event
    //-call processIO and pass that event
    //-start waiting again
    lock.unlock();
    backendThreadProc(asyncBackendQueue);
}

AsyncBackendQueue::AsyncBackendQueue()
{
    backendThread = new std::thread(AsyncBackendQueue::backendThreadProc, this);
}

AsyncBackendQueue::~AsyncBackendQueue()
{
    delete backendThread;
}

void AsyncBackendQueue::postIO(std::shared_ptr<Grid> postedGrid)
{
    //lock the deque and add the draw event to it
    std::unique_lock<std::mutex> lock(queueMutex);

    genDrawList.push_back(postedGrid);
}
