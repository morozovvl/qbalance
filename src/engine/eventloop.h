#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <QEventLoop>

class EventLoop : public QEventLoop
{
    Q_OBJECT
public:
    explicit EventLoop(QObject *parent = 0);
    Q_INVOKABLE int	exec()                      { return QEventLoop::exec(); }
    Q_INVOKABLE void	exit(int returnCode = 0)    { QEventLoop::exit(returnCode); }
    Q_INVOKABLE bool	isRunning() const           { return QEventLoop::isRunning(); }
    Q_INVOKABLE void	wakeUp()                    { QEventLoop::wakeUp(); }

/* Пока не будем вызывать эти методы из скриптов
    bool	processEvents ( ProcessEventsFlags flags = AllEvents )
    void	processEvents ( ProcessEventsFlags flags, int maxTime )
*/
};

#endif // EVENTLOOP_H
