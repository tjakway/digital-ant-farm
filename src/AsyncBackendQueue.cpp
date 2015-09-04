#include "AsyncBackendQueue.h"

void AsyncBackendQueue::backendThreadProc()
{

}

AsyncBackendQueue::AsyncBackendQueue()
{
    //instead of making the backend thread a field of AsyncBackendQueue, could make it a separate function in an anonymous namespace that takes as arguments anything it needs to do its job
    //could even declare it as a friend function if it really needed to access private AsyncBackendQueue fields and methods
    //this would prevent the thread from running before AsyncBackendQueue was fully constructed
    backendThread = new std::thread(&AsyncBackendQueue::backendThreadProc);
}

void AsyncBackendQueue::postIO(std::shared_ptr<Grid> postedGrid)
{

}
