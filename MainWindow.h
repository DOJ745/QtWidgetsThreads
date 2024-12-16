#pragma once

#include <QtWidgets/QMainWindow>
#include "ThreadManager.h"
#include "ui_MainWindow.h"
#include <memory>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    std::unique_ptr<ThreadManager> threadManager;
    //ThreadManager* threadManager;
    QLabel* label;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onCreateThreadManager()
    {
        /*if (threadManager)
        {
            delete threadManager;
            threadManager = nullptr;
        }*/
        if (threadManager)
        {
            threadManager.reset();
        }

        //threadManager = new ThreadManager();
        threadManager = std::make_unique<ThreadManager>();
        connect(threadManager->GetWorker(), &Worker::updateLabelSignal, this, &MainWindow::updateLabelSlot);
        //connect(threadManager, &ThreadManager::workerFinishResult, this, &MainWindow::workerExitCodeSlot);
        connect(threadManager.get(), &ThreadManager::workerFinishResult, this, &MainWindow::workerExitCodeSlot);
        threadManager->GetWorkerThread().start();
    };

    void onDeleteThreadManager()
    {
        threadManager->StopWorkerThread();
    }

    void updateLabelSlot(int seconds)
    {
        label->setText("Time elapsed: " + QString::number(seconds + 1));
    }

    void workerExitCodeSlot(int code)
    {
        label->setText("Worker exit code: " + QString::number(code));
    }

private:
    Ui::MainWindowClass ui;
};
