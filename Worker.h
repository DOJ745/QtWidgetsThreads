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
    void updateLabelSignal(int seconds); // ������ ��� ���������� �������
    void workFinishedSignal(int result); // ������ � ���������� ������

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

            emit updateLabelSignal(secondsElapsed); // ���������� ������ ��� ���������� �������
            QThread::sleep(1);                      // �������� ������
        }

        emit workFinishedSignal(0);                 // ������������� � ���������� ������
    };
};