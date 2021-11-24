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
#include <QtCore/QTextCodec>
#include "bankterminal.h"
#include "../kernel/app.h"
#include "../kernel/tcpclient.h"
#include "../driverfr/driverfr.h"
#include "../kernel/tcpserver.h"


BankTerminal::BankTerminal(QObject *parent) : QObject(parent)
{
    app = 0 /*nullptr*/;
    driverFR = 0 /*nullptr*/;
    termProcess = 0 /*nullptr*/;

    path = "";
#if  defined(Q_OS_LINUX)
    program = "sb_pilot";
#elif   defined(Q_OS_WIN)
    program = "loadparm.exe";
#endif
    remote = false;
    locked = false;
    processFinished = false;
    processResult = false;
}


BankTerminal::~BankTerminal()
{
}


void BankTerminal::getDefaultConfigs(QString configName)
{
    app->setConfig(configName, BANK_TERMINAL_PRINT_WAIT_TIME, "Продолжительность остановок при печати слипов, мс", CONFIG_VALUE_INTEGER, 0);
    app->setConfig(configName, BANK_TERMINAL_PRINT_WAIT_MESSAGE, "Показывать сообщение о продолжении при печати слипов", CONFIG_VALUE_BOOLEAN, false);
    app->setConfig(configName, BANK_TERMINAL_PROGRAM_WAIT_TIME, "Время ожидания окончания работы программы банковского терминала, мс", CONFIG_VALUE_INTEGER, 120000);
    app->setConfig(configName, BANK_TERMINAL_INTERVAL_EMPTY_LINES, "Количество пустых строк между слипами и чеком", CONFIG_VALUE_INTEGER, 2);
#if defined(Q_OS_WIN)
    app->setConfig(configName, BANK_TERMINAL_PATH, "Каталог программы банковского терминала", CONFIG_VALUE_STRING, "C:/BankTerminal/");
#else
    app->setConfig(configName, BANK_TERMINAL_PATH, "Каталог программы банковского терминала", CONFIG_VALUE_STRING, "/home/vladimir/BankTerminal/new1/");
#endif
}


void BankTerminal::removeConfigs()
{
    app->removeConfig(BANK_TERMINAL_PRINT_WAIT_TIME);
    app->removeConfig(BANK_TERMINAL_PRINT_WAIT_MESSAGE);
    app->removeConfig(BANK_TERMINAL_PROGRAM_WAIT_TIME);
    app->removeConfig(BANK_TERMINAL_INTERVAL_EMPTY_LINES);
    app->removeConfig(BANK_TERMINAL_PATH);
}


bool BankTerminal::open()
{
    bool result = false;
    if (app != 0 /*nullptr*/)
    {
        path = app->getConfigValue(BANK_TERMINAL_PATH).toString();
        program = path + program;
        if (QFileInfo(program).exists())        // Программа терминала обнаружена
        {
            if (app->drvFRisValid())            // И присутствует драйвер ФР
            {
                driverFR = app->getDrvFR();

                termProcess = new QProcess(app);
                termProcess->setWorkingDirectory(path);
                connect(termProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(testResult(int, QProcess::ExitStatus)));

                result = true;
            }
            else
                app->showError(QObject::trUtf8("Фискальный регистратор, необходимый для банковского терминала, не найден"));
        }
        else
        {
            TcpClient* tcpClient = app->getTcpClient();
            // а теперь поищем на удаленном, если TcpClient исправен
            if (tcpClient != 0 /*nullptr*/)
            {
                if (tcpClient->sendToServer(BANK_TERMINAL_IS_READY) && tcpClient->waitResult())
                {
                    QString res = tcpClient->getResult();
                    result = (res == "true" ? true : false);
                    if (result)
                        remote = true;
                }
            }
        }
        if (result)
            app->print("Найден банковский терминал.");
        else
            app->print("Банковский терминал не найден.");
    }
    return result;
}


void BankTerminal::close()
{
    if (termProcess != 0 /*nullptr*/)
    {
        disconnect(termProcess, SIGNAL(finished(int exitCode, QProcess::ExitStatus exitStatus)), this, SLOT(testResult(exitCode, exitStatus)));
        delete termProcess;
    }
}


QString BankTerminal::process(int oper, int sum, int type, int track)
{
    QString result = "false";
    if (!remote)
    {
        if (!locked)
        {
            locked = true;
            if (driverFR->Connect())
            {
                QString command = QString("%1 %2").arg(program).arg(oper);
                if (sum > 0)
                    command.append(QString(" %1").arg(sum));
                if (type > 0)
                    command.append(QString(" %1").arg(type));
                if (track > 0)
                    command.append(QString(" %1").arg(track));

                // Очистим предыдущие результаты
                QDir(path).remove("e");
                QDir(path).remove("p");

                // Запустим программу терминала

                app->debug(6, command);

                QTime dieTime= QTime::currentTime().addMSecs(app->getConfigValue(BANK_TERMINAL_PROGRAM_WAIT_TIME).toInt());

                processFinished = false;
                processResult = false;

                termProcess->start(command);

                while (true)
                {
                    // Если процесс вызова терминала завершен
                    if (processFinished)
                    {
                        if (!processResult)
                            result = resultParams.value(MESSAGE);
                        else
                        {
                            printSlip();
                            result = "true";
                        }
                        break;
                    }
                    // Если истекло время ожидания
                    if (QTime::currentTime() >= dieTime)
                    {
                        result = QString(QObject::trUtf8("Время ожидания терминала (%1 c) истекло. Нажмите кнопку <ОТМЕНА> на терминале.")).arg(app->getConfigValue(BANK_TERMINAL_PROGRAM_WAIT_TIME).toInt()/1000);                  // выдадим сообщение об ошибке
                        termProcess->kill();
                        break;
                    }
                    app->sleep(300);
                }

                app->debug(6, result);

                driverFR->DisConnect();
            }
            locked = false;
        }
        else
            result = "Банковский терминал занят. Повторите попытку позже.";
    }
    else
    {
        TcpClient* tcpClient = app->getTcpClient();
        // а теперь поищем на удаленном, если указан его IP
        if (tcpClient != 0 /*nullptr*/)
        {
            tcpClient->sendToServer(QString("%1 %2 %3 %4 %5 ").arg(BANK_TERMINAL_PROCESS)
                                                                      .arg(oper)
                                                                      .arg(sum)
                                                                      .arg(type)
                                                                      .arg(track));
            tcpClient->waitResult();
            result = tcpClient->getResult();
        }
    }
    return result;
}


void BankTerminal::testResult(int /*exitCode*/, QProcess::ExitStatus exitStatus)
{
    processResult = false;
    if (!remote)
    {
        resultParams.clear();
//        if (exitCode == 0 && exitStatus == QProcess::NormalExit)
        if (exitStatus == QProcess::NormalExit)
        {
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
                        processResult = true;
                }
            }
            fileName = path + "p";
            if (QFileInfo(fileName).exists())
            {
                QFile file(fileName);
                if (file.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                    QTextCodec* codec = QTextCodec::codecForName("KOI8-R");
                    QTextStream stream(&file);
                    stream.setCodec(codec);
                    QString line;
                    for (int i = 0; i < 15; i++)
                        line = QString(stream.readLine()).trimmed();
                    if (line.contains(':'))
                    {
                        line = line.split(':').at(1).trimmed();
                        resultParams.insert(CARD_HOLDER_NAME, line);
                    }
                    file.close();
                    if (resultParams.value(RESULT_CODE) == "0")
                        processResult = true;
                }
            }
        }
        processFinished = true;
    }
}


void BankTerminal::printSlip()
{
    if (!remote)
    {
        QString fileName = path + "p";
        if (QFileInfo(fileName).exists() && driverFR != 0 /*nullptr*/)
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
                do
                {
                    line = stream.readLine();
                    lines.append(line);
                } while (!line.isNull());

                // Отпечатаем слипы
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
                }
            }
        }
    }
}


bool BankTerminal::isLocked()
{
    return locked;
}


QString BankTerminal::processRemoteQuery(QString command)
{
    QString result = "Ok";
    if (command.indexOf(BANK_TERMINAL_PROCESS) == 0)
    {
        QStringList argList = command.split(" ");
        int oper = argList.at(1).toInt();
        int sum = argList.at(2).toInt();
        int type = argList.at(3).toInt();
        int track = argList.at(4).toInt();

        result = process(oper, sum, type, track);
    }
    else if (command.indexOf(BANK_TERMINAL_GETCARDCODE) == 0)
    {
        result = getCardCode();
    }
    else if (command.indexOf(BANK_TERMINAL_GETRESULTDATA) == 0)
    {
        QStringList argList = command.split(" ");
        QString key = argList.at(1);
        result = getResultData(key);
    }
    return result;
}


QString BankTerminal::getCardCode()
{
    QString result = "";
    if (!remote)
        result = resultParams.value(CARD_NUMBER);
    else
    {
        TcpClient* tcpClient = app->getTcpClient();
        // а теперь поищем на удаленном, если указан его IP
        if (tcpClient != 0 /*nullptr*/)
        {
            tcpClient->sendToServer(QString("%1 ").arg(BANK_TERMINAL_GETCARDCODE));
            tcpClient->waitResult();
            result = tcpClient->getResult();
        }
    }
    return result;
}


QString BankTerminal::getResultData(QString key)
{
    QString result = "";
    if (!remote)
        result = resultParams.value(key);
    else
    {
        TcpClient* tcpClient = app->getTcpClient();
        // а теперь поищем на удаленном, если указан его IP
        if (tcpClient != 0 /*nullptr*/)
        {
            tcpClient->sendToServer(QString("%1 %2 ").arg(BANK_TERMINAL_GETRESULTDATA).arg(key));
            tcpClient->waitResult();
            result = tcpClient->getResult();
        }
    }
    return result;
}


void BankTerminal::setApp(TApplication* a)
{
    app = a;
}

