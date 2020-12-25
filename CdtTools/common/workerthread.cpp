#include "workerthread.h"

WorkerThread::WorkerThread()
{

}

void WorkerThread::run(const std::function<void()> &callback)
{
    QMutexLocker locker(&m_mutex);
    m_callbacks.push_back(callback);

    QMetaObject::invokeMethod(this, &WorkerThread::onRun, Qt::QueuedConnection);
}

void WorkerThread::onRun()
{

    m_mutex.lock();

    // 获取内部所以callback
    QList<std::function<void()>> runCallbacks;
//    runCallbacks.swap(m_callbacks);
    runCallbacks = m_callbacks;
    m_callbacks.clear();
    m_mutex.unlock();

    for (const auto& callback : runCallbacks) {
        callback();
    }
}
