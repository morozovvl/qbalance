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


class TApplication;
class DriverFR;

class BankTerminal : public QObject
{
    Q_OBJECT
public:
    explicit BankTerminal(QObject *parent = 0);
    virtual bool open();
    virtual void close();
    virtual void setApp(TApplication* a) { app = a; }
    Q_INVOKABLE virtual bool process(int, int = 0, int = 0, int = 0);              // Обработать операцию с картой
    Q_INVOKABLE virtual QString getCardCode() { return resultParams.value(CARD_NUMBER); }
    Q_INVOKABLE QHash<QString, QString>* getResultData() { return &resultParams; }

private:
    TApplication* app;
    DriverFR*   driverFR;
    QString     path;
    QString     program;
    QHash<QString, QString> resultParams;
    QProcess* termProcess;

    bool    testResult();
    void    printSlip();
};

Q_DECLARE_INTERFACE(BankTerminal, "org.QBalance.BankTerminal")

#endif // BANKTERMINAL_H
