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

#ifndef BANKTERMINAL_H
#define BANKTERMINAL_H

#include <QtCore/QObject>
#include <QtCore/QHash>
#include <QtCore/QProcess>

#define BANK_TERMINAL_NEEDED                  "BANK_TERMINAL_NEEDED"
#define BANK_TERMINAL_PATH                    "BANK_TERMINAL_PATH"
#define BANK_TERMINAL_PROGRAM_WAIT_TIME       "BANK_TERMINAL_PROGRAM_WAIT_TIME"
#define BANK_TERMINAL_INTERVAL_EMPTY_LINES    "BANK_TERMINAL_INTERVAL_EMPTY_LINES"
#define BANK_TERMINAL_PRINT_WAIT_MESSAGE      "BANK_TERMINAL_PRINT_WAIT_MESSAGE"
#define BANK_TERMINAL_PRINT_WAIT_TIME         "BANK_TERMINAL_PRINT_WAIT_TIME"


#define RESULT_CODE "КодРезультата"
#define MESSAGE "Сообщение"
#define CARD_NUMBER "НомерКарты"
#define VALIDITY_PERIOD "СрокДействия"
#define AUTHORIZATION_CODE "КодАвторизации"
#define INTERNAL_OPERATION_CODE "ВнутрНомерОперации"
#define CARD_TYPE "ТипКарты"
#define IS_SBERCARD "КартаСбербанка"
#define TERMINAL_NUMBER "НомерТерминала"
#define OPERATION_DATETIME "ДатаВремяОперации"
#define LINK_OPERATION_NUMBER "СсылочныйНомерОперации"
#define CARD_NUMBER_HASH "ХэшНомераКарты"
#define CARD_HOLDER_NAME "ИмяДержателяКарты"


#define BANK_TERMINAL_PREFIX     "bankTerminal_"
#define BANK_TERMINAL_IS_READY   BANK_TERMINAL_PREFIX "IsReady"
#define BANK_TERMINAL_PROCESS    BANK_TERMINAL_PREFIX "process"

class TApplication;
class DriverFR;
class TcpClient;

class BankTerminal : public QObject
{
    Q_OBJECT
public:
    explicit BankTerminal(QObject *parent = 0 /*nullptr*/);
    ~BankTerminal();
    virtual bool open();
    virtual void close();
    virtual void setApp(TApplication* a);
    Q_INVOKABLE virtual QString process(int, int = 0, int = 0, int = 0);              // Обработать операцию с картой
    Q_INVOKABLE virtual QString getCardCode();
    Q_INVOKABLE virtual QString getResultData(QString);
    Q_INVOKABLE virtual bool isLocked();
    virtual QString processRemoteQuery(QString);
    virtual void getDefaultConfigs(QString);
    virtual void removeConfigs();

private:
    TApplication* app;
    DriverFR*   driverFR;
    QString     path;
    QString     program;
    QHash<QString, QString> resultParams;
    QProcess* termProcess;
    bool            remote;
    bool            locked;     // Банковский терминал заблокирован на период работы с клиентом

    virtual bool    testResult();
    virtual void    printSlip();
};

Q_DECLARE_INTERFACE(BankTerminal, "org.QBalance.BankTerminal")

#endif // BANKTERMINAL_H
