#include "AsyncBackendQueue.hpp"

using namespace jakway_antf;

void AsyncBackendQueue::backendThreadProc(AsyncBackendQueue *asyncBackendQueue)
{
    std::unique_lock<std::mutex> lock(asyncBackendQueue->queueMutex);

    //sleep until we have something to draw
    while(asyncBackendQueue->genDrawList.empty())
    {
        asyncBackendQueue->queueCond.wait(lock);
    }

    //draw events in the order they're added to the queue
    std::shared_ptr<Grid> oldestEvent = asyncBackendQueue->genDrawList.back();
    //delete the item we just fetched
    asyncBackendQueue->genDrawList.pop_back(); 
    

    asyncBackendQueue->processIO(oldestEvent);
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
