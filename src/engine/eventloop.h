/************************************************************************************************************
Copyright (C) Morozov Vladimir Aleksandrovich
MorozovVladimir@mail.ru

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*************************************************************************************************************/

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
