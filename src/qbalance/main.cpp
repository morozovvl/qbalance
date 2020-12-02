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
//-h 192.168.0.1 -p 5432 -l "sa" -db enterprise -pw ******** -d1 -d4 -d5

#include <QtCore/QtGlobal>

#if QT_VERSION < 0x050000
    #include <QtGui/QStyleFactory>
#else
    #include <QtWidgets/QStyleFactory>
#endif

#include <QtCore/QTextCodec>
#include <QtCore/QTextStream>
#include <QtCore/QResource>
//#include <QtWidgets/QPrinter>
//#include <QtWidgets/QPrinterInfo>
//#include <QtGui/QPainter>
//#include <QtWidgets/QPrintEngine>
#include <QtCore/QDebug>
#include <QtCore/QLibraryInfo>

#include "version.h"
#include "kernel/app.h"
#include "kernel/dictionaries.h"

//#include <mcheck.h>


//#if  defined(Q_OS_LINUX)
//
//    #include "../../breakpad/src/client/linux/handler/exception_handler.h"
//
//    static bool dumpCallback(const google_breakpad::MinidumpDescriptor& descriptor, void*, bool succeeded)
//    {
//        printf("Dump path: %s\n", descriptor.path());
//        return succeeded;
//    }
//
//#endif


//void crash() { volatile int* a = (int*)(NULL); *a = 1; }


int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);

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

    int lResult = 0;
    bool lStart = true;

    if (argc > 1)
        lStart = TApplication::readParameters(argc, argv);

    if (lStart)
    {
        if (application.open())
        {

//#if  defined(Q_OS_LINUX)
//
//            google_breakpad::MinidumpDescriptor descriptor(application.applicationDirPath().append("/crashdumps").toAscii().data());
//            google_breakpad::ExceptionHandler eh(descriptor, NULL, dumpCallback, NULL, true, -1);
////            crash();
//
//#endif
            application.debug(0, "\n");
            application.debug(0, QString("Program startup. v.%1").arg(application.applicationVersion()));

            // Если в качестве параметра задан скрипт, то приложение работает в скриптовом режиме
            if (application.getScript().size() > 0)
                application.setScriptMode(true);

            if (!TApplication::isSendCommandMode())
            {
                TApplication::setStyle(QStyleFactory::create("plastique"));
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
                    application.show();
                    if (application.initApplication())
                    {
                        lResult = application.exec();
                    }
                }
            }
            else
            {
                lResult = application.runScript(application.getScript());
            }

            application.debug(0, "Program shutdown.\n");
            application.close();
        }
        application.quit();
    }
    return lResult;
}
