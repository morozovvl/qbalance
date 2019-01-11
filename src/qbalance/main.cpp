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
// Пример параметров для запуска из консоли
//-h 192.168.0.1 -p 5432 -l "sa Морозов Владимир Александрович" -db enterprise -pw ******** -d1 -d4 -d5

#include <QtCore/QTextCodec>
#include <QtCore/QTextStream>
#include <QtCore/QResource>
//#include <QtWidgets/QPrinter>
//#include <QtWidgets/QPrinterInfo>
//#include <QtGui/QPainter>
//#include <QtWidgets/QPrintEngine>
#include <QtWidgets/QStyleFactory>
#include <QtCore/QDebug>

#include "version.h"
#include "kernel/app.h"
#include "kernel/dictionaries.h"

//#include "crashhandler/crashhandler.h"

//#include <mcheck.h>


//#if defined(Q_OS_LINUX)
//#define CRASHHANDLER
//#endif


// Процедура для создания ошибки сегментирования
//int buggyFunc() {
//    delete reinterpret_cast<QString*>(0xFEE1DEAD);
//    return 0;
//}


int main(int argc, char *argv[])
{
//    mtrace();

    QLocale::setDefault(QLocale(QLocale::Russian, QLocale::RussianFederation));

    TApplication application(argc, argv);

    application.setOrganizationName("Enterprise");
    application.setApplicationVersion(BUILD_NUMBER);

#if QT_VERSION < 0x050000
    QTextCodec::setCodecForTr(application.codec());
    QTextCodec::setCodecForCStrings(application.codec());
#endif
    QTextCodec::setCodecForLocale(application.codec());

//#ifdef CRASHHANDLER
//    Breakpad::CrashHandler::instance()->Init(TApplication::exemplar()->getCrashDumpsPath());
//#endif

//    buggyFunc();

    int lResult = 0;            // по умолчанию программа возвращает 0
    bool lStart = true;         // по умолчанию программа запускается
    if (argc > 1)                               // были заданы какие-то аргументы
        lStart = TApplication::readParameters(argc, argv);    // прочитаем их
    if (lStart)
    {

        application.debug(0, "\n");
        application.debug(0, QString("Program startup. v.%1").arg(application.applicationVersion()));

        // Если в качестве параметра задан скрипт, то приложение работает в скриптовом режиме
        if (application.getScript().size() > 0)
            application.setScriptMode(true);

        if (!TApplication::isSendCommandMode())
        {
            TApplication::setStyle(QStyleFactory::create("plastique"));
            if (application.open())
            {       // Если приложение удалось создать

                if (application.isScriptMode())
                {
                    if (application.initApplication())
                    {
                        lResult = application.runScript(application.getScript());
                    }
                }
                else if (application.isServerMode())
                {
                    if (application.initApplication())
                    {
                        lResult = application.exec();
                    }
                }
                else
                {
                    application.show();         // Откроем приложение
                    if (application.initApplication())
                    {
                        lResult = application.exec();
                    }
                }
                application.close();            // Закроем приложение
            }
        }
        else
        {
            lResult = application.runScript(application.getScript());
        }

        application.debug(0, "Program shutdown.\n");
        application.quit();
    }
    return lResult;
}
