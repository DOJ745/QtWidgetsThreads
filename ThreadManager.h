#pragma once
#include "Worker.h"
#include <qtextstream.h>
class ThreadManager : public QObject
{
    Q_OBJECT
    QThread workerThread;
    // Умный указатель с кастомным удалителем для безопасного удаления Worker
    std::unique_ptr<Worker, std::function<void(Worker*)>> worker;

public:
    ThreadManager(): worker(nullptr)
    {
        //worker = new Worker;
        Worker* rawWorker = new Worker;
        worker.reset(rawWorker); // Передаем объект умному указателю
        rawWorker->moveToThread(&workerThread);
        /*connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
        connect(&workerThread, &QThread::started, worker, &Worker::doWork);
        connect(worker, &Worker::workFinishedSignal, this, &ThreadManager::handleResults);*/

        connect(&workerThread, &QThread::finished, worker.get(), &QObject::deleteLater);
        connect(&workerThread, &QThread::started, worker.get(), &Worker::doWork);
        connect(worker.get(), &Worker::workFinishedSignal, this, &ThreadManager::handleResults);

        workerThread.start();
    }
    ~ThreadManager()
    {
        StopWorkerThread();
    }

    /*Worker*& GetWorker()
    {
        return worker;
    }*/

    Worker* GetWorker()
    {
        return worker.get();
    }

    QThread& GetWorkerThread()
    {
        return workerThread;
    }

    void StopWorkerThread()
    {
        if (workerThread.isRunning())
        {
            workerThread.requestInterruption();
            workerThread.quit();
            workerThread.wait(); 
        }
        /*if (worker)
        {
            worker = nullptr;
        }*/
        //worker.reset();
    }

signals:
    void workerFinishResult(int&);

public slots:
    void handleResults(int number)
    {
        emit workerFinishResult(number);
    }
};