#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QObject>
#include <QList>
#include <functional>
#include <QMutexLocker>

class WorkerThread : public QObject
{
    Q_OBJECT
public:
    WorkerThread();

    // move?
    void run(const std::function<void()>& callback);
public Q_SLOTS:
    void onRun();

private:
    QList<std::function<void()>> m_callbacks;
    QMutex m_mutex;
};

#endif // WORKERTHREAD_H
