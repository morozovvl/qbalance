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

#include <QtCore/QFileInfo>
#include <QtCore/QStringList>
#include <QtCore/QProcess>
#include <QtCore/QDebug>
#include "bankterminal.h"
#include "../kernel/app.h"
#include <../driverfr/driverfr.h>



BankTerminal::BankTerminal(QObject *parent) : QObject(parent)
{
    app = 0;
    path = "";
#ifdef Q_OS_WIN32
        program = "loadparm.exe";
#else
        program = "sb_pilot";
#endif
}


bool BankTerminal::open()
{
    bool result = false;
    if (app != 0)
    {
        path = app->getConfigValue(BANK_TERMINAL_PATH).toString();
        program = path + program;
        if (QFileInfo(program).exists())        // Программа терминала обнаружена
        {
            if (app->drvFRisValid())            // И присутствует драйвер ФР
            {
                driverFR = app->getDrvFR();
                result = true;
            }
            else
                app->showError(QObject::trUtf8("Фискальный регистратор не обнаружен"));
        }
        else
            app->showError(QObject::trUtf8("Программа банковского терминала не обнаружена"));
    }
    return result;
}


void BankTerminal::close()
{

}


bool BankTerminal::process(int oper, int sum, int type, int track)
{
    bool result = false;
    if (driverFR->Connect())
    {
        QProcess* termProcess = new QProcess();
        termProcess->setWorkingDirectory(path);

        QString command = QString("%1 %2").arg(program).arg(oper);
        if (sum > 0)
            command.append(QString(" %1").arg(sum));
        if (type > 0)
            command.append(QString(" %1").arg(type));
        if (track > 0)
            command.append(QString(" %1").arg(track));

#ifdef Q_OS_LINUX
//        if (oper == 1 || oper == 3)
//            app->showMessage(QObject::trUtf8("Вставьте банковскую карту в терминал и нажмите любую клавишу"));
#endif

        // Очистим предыдущие результаты
        QDir(path).remove("e");
        QDir(path).remove("p");

        // Запустим программу терминала
        termProcess->start(command);
        if (!termProcess->waitForFinished(app->getConfigValue(BANK_TERMINAL_PROGRAM_WAIT_TIME).toInt()))
            app->showError(QObject::trUtf8("Время ожидания терминала (1 минута) истекло. Нажмите кнопку <ОТМЕНА> на терминале.") + termProcess->errorString());                  // выдадим сообщение об ошибке
        delete termProcess;

        result = testResult();

        if (!result)
            app->showError(resultParams.value(MESSAGE));
        else
            printSlip();

        driverFR->DisConnect();
    }
    return result;
}


bool BankTerminal::testResult()
{
    bool result = false;
    resultParams.clear();
    QString fileName = path + "e";
    if (QFileInfo(fileName).exists())
    {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextCodec* codec = QTextCodec::codecForName("KOI8-R");
            QTextStream stream(&file);
            stream.setCodec(codec);
            QStringList line = QString(stream.readLine()).split(',');
            resultParams.insert(RESULT_CODE, line.at(0).trimmed());
            resultParams.insert(MESSAGE, line.at(1).trimmed());
            resultParams.insert(CARD_NUMBER, QString(stream.readLine()).trimmed());
            resultParams.insert(VALIDITY_PERIOD, QString(stream.readLine()).trimmed());
            resultParams.insert(AUTHORIZATION_CODE, QString(stream.readLine()).trimmed());
            resultParams.insert(INTERNAL_OPERATION_CODE, QString(stream.readLine()).trimmed());
            resultParams.insert(CARD_TYPE, QString(stream.readLine()).trimmed());
            resultParams.insert(IS_SBERCARD, QString(stream.readLine()).trimmed());
            resultParams.insert(TERMINAL_NUMBER, QString(stream.readLine()).trimmed());
            resultParams.insert(OPERATION_DATETIME, QString(stream.readLine()).trimmed());
            resultParams.insert(LINK_OPERATION_NUMBER, QString(stream.readLine()).trimmed());
            resultParams.insert(CARD_NUMBER_HASH, QString(stream.readLine()).trimmed());
            file.close();
            if (resultParams.value(RESULT_CODE) == "0")
                result = true;
        }
    }
    return result;
}


void BankTerminal::printSlip()
{
    QString fileName = path + "p";
    if (QFileInfo(fileName).exists() && driverFR != 0)
    {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextCodec* codec = QTextCodec::codecForName("KOI8-R");
            QTextStream stream(&file);
            stream.setCodec(codec);

            // Прочитаем слипы
            QStringList lines;
            QString line;
            do {
                line = stream.readLine();
                lines.append(line);
            } while (!line.isNull());

            // Отпечатаем слипы
            driverFR->setShowProgressBar(true);
            int proc = 100 / lines.count();
            for (int i = 0; i < lines.count(); i++)
            {
                line = lines.at(i);
                if (line != "~S\001")
                    driverFR->PrintString(line);
                else
                {
                    driverFR->FeedDocument(app->getConfigValue(BANK_TERMINAL_INTERVAL_EMPTY_LINES).toInt());
                    if (app->getConfigValue(BANK_TERMINAL_PRINT_WAIT_MESSAGE).toBool())
                        app->showMessage(QObject::trUtf8("Оторвите чек и нажмите любую клавишу для продолжения печати"));
                    else
                        app->sleep(app->getConfigValue(BANK_TERMINAL_PRINT_WAIT_TIME).toInt());
                }
                driverFR->setProgressDialogValue(proc * i);
            }
            driverFR->setProgressDialogValue(100);
        }
    }
}
