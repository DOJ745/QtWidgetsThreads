#pragma once

#include <QObject>
#include <QThread>

class Worker : public QObject
{
    Q_OBJECT

private:
    int secondsElapsed;

public:
    explicit Worker(QObject* parent = nullptr)
        : QObject{ parent }, 
        secondsElapsed{ 0 } {};

signals:
    void updateLabelSignal(int seconds); // Сигнал для обновления надписи
    void workFinishedSignal(int result); // Сигнал о завершении работы

public slots:
    void doWork()
    {
        for (secondsElapsed = 0; secondsElapsed < 5; secondsElapsed++)
        {
            if (QThread::currentThread()->isInterruptionRequested())
            {
                emit workFinishedSignal(1);
                return;
            }

            emit updateLabelSignal(secondsElapsed); // Отправляем сигнал для обновления надписи
            QThread::sleep(1);                      // Имитация работы
        }

        emit workFinishedSignal(0);                 // Сигнализируем о завершении работы
    };
};