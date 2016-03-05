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

#ifdef Q_OS_LINUX
#define CRASHHANDLER
#endif


#include <QtCore/QTextCodec>
#include <QtCore/QTextStream>
#include <QtCore/QResource>
#include "kernel/app.h"
#include "crashhandler/crashhandler.h"


// Процедура для создания ошибки сегментирования
int buggyFunc() {
    delete reinterpret_cast<QString*>(0xFEE1DEAD);
    return 0;
}

bool readParameters(int argc, char *argv[]) {
    bool lContinue = true;
    QTextStream out(stdout);
//    out.setCodec(TApplication::codec());
    for (int i = 1; i < argc; i++) {
        if (QString(argv[i]).compare("-?", Qt::CaseInsensitive) == 0 ||
            QString(argv[i]).compare("--help", Qt::CaseInsensitive) == 0)
        {
            out << QObject::trUtf8("Использование программы: qbalance [Параметр]\n");
            out << QObject::trUtf8("Параметры:\n");
            out << QObject::trUtf8("  -? | --help       - Вывести список параметров запуска программы\n");
            out << QObject::trUtf8("  -v | --version    - Вывести номер версии программы\n");
            out << QObject::trUtf8("  -d1| --debug1     - Запустить программу в режиме отладки комманд запросов (файл debug1.log)\n");
            out << QObject::trUtf8("  -d2| --debug2     - Запустить программу в режиме отладки алгоритмов ядра (файл debug2.log)\n");
            out << QObject::trUtf8("  -d3| --debug3     - Запустить программу в режиме отладки скриптов (файл debug3.log)\n");
            out << QObject::trUtf8("  -d4| --debug4     - Запустить программу в режиме отладки устройства COM-порта (файл debug4.log)\n");
            out << QObject::trUtf8("  -d5| --debug5     - Запустить программу в режиме отладки обмена между экземплярами приложения (файл debug5.log)\n");
            out << QObject::trUtf8("  -h | --host       - IP адрес хоста\n");
            out << QObject::trUtf8("  -p | --port       - Порт на хосте\n");
            out << QObject::trUtf8("  -db| --database   - Наименование базы данных\n");
            out << QObject::trUtf8("  -l | --login      - Логин\n");
            out << QObject::trUtf8("  -pw| --password   - Пароль\n");
            out << QObject::trUtf8("  -s | --script     - Выполнить скрипт с заданным именем и выйти\n");
            out << QObject::trUtf8("  -sp| --scriptparameter - Параметр для скрипта (имя файла или строка, которую скрипт должен сам разобрать)\n");
            out << QObject::trUtf8("  -sr| --server     - Запустить программу в режиме сервера\n");
            out << QObject::trUtf8("  -c | --command    - Послать команду хосту (адрес и порт д.б. заданы параметрами -h и -p, команда в параметре -s)\n");
            out << QObject::trUtf8("  -dc| --def_conf   - Загрузить конфигурационные параметры по умолчанию\n");
            lContinue = false;
        }
        else if (QString(argv[i]).compare("-v", Qt::CaseInsensitive) == 0 ||
                QString(argv[i]).compare("--version", Qt::CaseInsensitive) == 0)
        {
            out << QString(QObject::trUtf8("Название программы: %1\n")).arg(TApplication::exemplar()->applicationName());
            out << QString(QObject::trUtf8("Версия: %1\n")).arg(TApplication::exemplar()->applicationVersion());
            out << QString(QObject::trUtf8("Авторы: %1\n")).arg(TApplication::authors());
            lContinue = false;
        }
        else if (QString(argv[i]).compare("-d1", Qt::CaseInsensitive) == 0 ||
                QString(argv[i]).compare("--debug1", Qt::CaseInsensitive) == 0)
            {
                TApplication::setDebugMode(1);
            }
        else if (QString(argv[i]).compare("-d2", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--debug2", Qt::CaseInsensitive) == 0)
            {
                TApplication::setDebugMode(2);
            }
        else if (QString(argv[i]).compare("-d3", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--debug3", Qt::CaseInsensitive) == 0)
            {
                TApplication::setDebugMode(3);
            }
        else if (QString(argv[i]).compare("-d4", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--debug4", Qt::CaseInsensitive) == 0)
            {
                TApplication::setDebugMode(4);
            }
        else if (QString(argv[i]).compare("-d5", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--debug5", Qt::CaseInsensitive) == 0)
            {
                TApplication::setDebugMode(5);
            }
        else if (QString(argv[i]).compare("-h", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--host", Qt::CaseInsensitive) == 0)
            {
                TApplication::host = argv[++i];
            }
        else if (QString(argv[i]).compare("-p", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--port", Qt::CaseInsensitive) == 0)
            {
                TApplication::port = QString(argv[++i]).toInt();
            }
        else if (QString(argv[i]).compare("-db", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--database", Qt::CaseInsensitive) == 0)
            {
                TApplication::database = argv[++i];
            }
        else if (QString(argv[i]).compare("-l", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--login", Qt::CaseInsensitive) == 0)
            {
                TApplication::username = argv[++i];
            }
        else if (QString(argv[i]).compare("-pw", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--password", Qt::CaseInsensitive) == 0)
            {
                TApplication::password = argv[++i];
            }
        else if (QString(argv[i]).compare("-s", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--script", Qt::CaseInsensitive) == 0)
            {
                TApplication::script = argv[++i];
            }
        else if (QString(argv[i]).compare("-sp", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--scriptparameter", Qt::CaseInsensitive) == 0)
            {
                TApplication::scriptParameter = argv[++i];
            }
        else if (QString(argv[i]).compare("-sr", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--server", Qt::CaseInsensitive) == 0)
            {
                TApplication::serverMode = true;
            }
        else if (QString(argv[i]).compare("-c", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--command", Qt::CaseInsensitive) == 0)
            {
                TApplication::setSendCommandMode(true);
            }
        else if (QString(argv[i]).compare("-dc", Qt::CaseInsensitive) == 0 ||
                 QString(argv[i]).compare("--def_conf", Qt::CaseInsensitive) == 0)
            {
                TApplication::loadDefaultConfig = true;
            }
    }
    return lContinue;
}


void test() {
    // Процедура для тестирования на "утечки" памяти
    QString dictName("счета");
    for (int i = 0; i < 50; i++) {              // 50 раз откроем, закроем справочник
        Dictionaries* dicts = TApplication::exemplar()->getDictionaries();
        dicts->addDictionary(dictName);
        Dictionary* dict = dicts->getDictionary(dictName);         // Откроем справочник и подсправочники 1-го уровня
        if (dict != 0) {
            dicts->removeDictionary(dictName);
        }
    }
}


int main(int argc, char *argv[])
{
    TApplication application(argc, argv);
#if QT_VERSION < 0x050000
    QTextCodec::setCodecForTr(application.codec());
    QTextCodec::setCodecForCStrings(application.codec());
#endif
    QTextCodec::setCodecForLocale(application.codec());

#ifdef CRASHHANDLER
    Breakpad::CrashHandler::instance()->Init(TApplication::exemplar()->getCrashDumpsPath());
#endif

//    buggyFunc();

    int lResult = 0;            // по умолчанию программа возвращает 0
    bool lStart = true;         // по умолчанию программа запускается
    if (argc > 1)                               // были заданы какие-то аргументы
        lStart = readParameters(argc, argv);    // прочитаем их
    if (lStart) {
        QStringList paths = application.libraryPaths();
        application.setLibraryPaths(paths);
        application.setDebugMode(0);

        // Если в качестве параметра задан скрипт, то приложение работает в скриптовом режиме
        if (application.getScript().size() > 0)
            application.setScriptMode(true);

        if (application.open())
        {       // Если приложение удалось создать
            application.debug(0, "Program startup.");
            if (application.isScriptMode())
                lResult = application.runScript(application.getScript());
            else if (application.isServerMode())
                lResult = application.exec();
            else
            {
                application.show();         // Откроем приложение
                lResult = application.exec();
            }
            application.debug(0, "Program shutdown.\n");
        }
        application.close();            // Закроем приложение
        application.quit();
    }
    return lResult;
}
