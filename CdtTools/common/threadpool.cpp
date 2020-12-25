#include "threadpool.h"
#include <QtConcurrent>
#include <QSemaphore>

ThreadPool::ThreadPool(int threadCount)
    : m_threadPool(new QThreadPool)
    , m_threadMaxCount(threadCount)
{
    m_threadPool->setMaxThreadCount(threadCount);
    m_eventLoops.resize(threadCount);
    m_workers.resize(threadCount);

    QSemaphore startThreadSem;

    for (int i = 0; i < threadCount; i++) {
        QtConcurrent::run(m_threadPool.data(), [this, i, &startThreadSem](){
            // run call back
            auto eventLoop = new QEventLoop();
            auto worker = new WorkerThread();
            this->m_eventLoops[i] = eventLoop;
            this->m_workers[i] = worker;
            startThreadSem.release(1);
            eventLoop->exec();
        });
    }
    startThreadSem.acquire(threadCount);
}

ThreadPool::~ThreadPool()
{
    for (const auto& eventLoop : m_eventLoops) {
        QMetaObject::invokeMethod(eventLoop.data(), &QEventLoop::quit);
    }

    m_threadPool->waitForDone();
}

void ThreadPool::run(const std::function<void()> &callback)
{
    m_workerIndex = (m_workerIndex + 1) % m_workers.size();

    m_workers.at(m_workerIndex)->run(callback);
}

int ThreadPool::maxCount() const
{
    return m_threadMaxCount;
}
