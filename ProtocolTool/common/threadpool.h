#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <QObject>
#include <QThreadPool>
#include <QList>
#include <QVector>
#include <QSharedPointer>
#include <QEventLoop>
#include <functional>

#include "workerthread.h"

class ThreadPool : public QObject
{
    Q_OBJECT
public:
    static ThreadPool* instance();
    explicit ThreadPool(int threadCount = 20);
    ~ThreadPool() override;

    void run(const std::function<void()>& callback);

    void waitRun(const std::function<void()>& callback);

    int maxCount() const;

signals:

public slots:

private:
    int m_threadMaxCount = 20;
    int m_workerIndex = 0;
    QSharedPointer<QThreadPool> m_threadPool;
    QVector<QPointer<QEventLoop>> m_eventLoops;
    QVector<QPointer<WorkerThread>> m_workers;
};

#endif // THREADPOOL_H
