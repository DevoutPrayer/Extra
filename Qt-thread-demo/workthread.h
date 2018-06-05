#ifndef WORKTHREAD_H
#define WORKTHREAD_H
#include <QThread>
#include <QMutex>
class WorkThread : public QThread
{
    Q_OBJECT
public:
    WorkThread(QMutex *mutex_);
    QMutex *mutex;
protected:
    void run();
public slots:
    void slot_delete();
signals:
    void signal_finished();
};
#endif // WORKTHREAD_H
