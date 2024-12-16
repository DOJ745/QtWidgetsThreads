#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , threadManager(nullptr)
{
    ui.setupUi(this);
    label = ui.labelStatus;

    connect(ui.startThreadButton, &QPushButton::clicked, this, &MainWindow::onCreateThreadManager);
    connect(ui.stopThreadButton, &QPushButton::clicked, this, &MainWindow::onDeleteThreadManager);
}

MainWindow::~MainWindow()
{
    /*if (threadManager)
    {
        threadManager->StopWorkerThread();  // Остановка потока
        delete threadManager;               // Уничтожение ThreadManager
        threadManager = nullptr;
    }*/
}
