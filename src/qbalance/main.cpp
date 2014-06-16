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

#include <QtCore/QTextCodec>
#include <QtCore/QTextStream>
#include <QtCore/QResource>
#include <QtPlugin>
#include "kernel/app.h"


bool readParameters(int argc, char *argv[]) {
    bool lContinue = true;
    QTextStream out(stdout);
    out.setCodec(TApplication::codec());
    for (int i = 1; i < argc; i++) {
        if (QString(argv[i]).compare("-h", Qt::CaseInsensitive) == 0 ||
            QString(argv[i]).compare("--help", Qt::CaseInsensitive) == 0)
        {
            out << QObject::trUtf8("Использование программы: qbalance [Параметр]\n");
            out << QObject::trUtf8("Параметры:\n");
            out << QObject::trUtf8("  -v | --version    - Вывести номер версии программы\n");
            out << QObject::trUtf8("  -d1| --debug1     - Запустить программу в режиме отладки комманд запросов (файл debug1.log)\n");
            out << QObject::trUtf8("  -d2| --debug2     - Запустить программу в режиме отладки алгоритмов ядра (файл debug2.log)\n");
            out << QObject::trUtf8("  -d3| --debug3     - Запустить программу в режиме отладки скриптов (файл debug3.log)\n");
            out << QObject::trUtf8("  -h | --help       - Вывести список параметров запуска программы\n");
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
    // Инициируем переменные, которые нуждаются в этом

#if QT_VERSION < 0x050000
    QTextCodec::setCodecForTr(TApplication::codec());
    QTextCodec::setCodecForCStrings(TApplication::codec());
#endif
    QTextCodec::setCodecForLocale(TApplication::codec());

    int lResult = 0;            // по умолчанию программа возвращает 0
    bool lStart = true;         // по умолчанию программа запускается
    if (argc > 1)                               // были заданы какие-то аргументы
        lStart = readParameters(argc, argv);    // прочитаем их
    if (lStart) {
        TApplication application(argc, argv);
        QStringList paths = application.libraryPaths();
        application.setLibraryPaths(paths);
        if (application.open()) {       // Если приложение удалось создать
            application.show();         // Откроем приложение
            lResult = application.exec();
        }
        application.close();            // Закроем приложение
        application.quit();
    }

    TApplication::debug(0, "Program shutdown.\n");
    return lResult;

}
