#include <QApplication>
#include <QTextCodec>
#include <QTextStream>
#include <QResource>
#include <QDebug>
#include "kernel/app.h"


bool readParameters(int argc, char *argv[]) {
    bool lContinue = true;
    QTextStream out(stdout);
    out.setCodec(TApplication::codec());
    for (int i = 1; i < argc; i++) {
        if (QString(argv[i]).compare("-h", Qt::CaseInsensitive) == 0 ||
            QString(argv[i]).compare("--help", Qt::CaseInsensitive) == 0) {
            out << QObject::trUtf8("Использование программы: enterprise [Параметр]\n");
            out << QObject::trUtf8("Параметры:\n");
            out << QObject::trUtf8("  -v | --version    - Вывести номер версии программы\n");
            out << QObject::trUtf8("  -d | --debug      - Запустить программу в режиме отладки комманд запросов (файл debug.log)\n");
            out << QObject::trUtf8("  -h | --help       - Вывести список параметров запуска программы\n");
            lContinue = false;
        }
        else if (QString(argv[i]).compare("-v", Qt::CaseInsensitive) == 0 ||
                QString(argv[i]).compare("--version", Qt::CaseInsensitive) == 0) {
            out << QString(QObject::trUtf8("Название программы: %1\n")).arg(TApplication::exemplar()->applicationName());
            out << QString(QObject::trUtf8("Версия: %1\n")).arg(TApplication::exemplar()->applicationVersion());
            out << QString(QObject::trUtf8("Авторы: %1\n")).arg(TApplication::authors());
            lContinue = false;
        }
        else if (QString(argv[i]).compare("-d", Qt::CaseInsensitive) == 0 ||
                QString(argv[i]).compare("--debug", Qt::CaseInsensitive) == 0) {

            if (TApplication::setDebugMode(true))
            {
                TApplication::debug(" Program startup.\n");
            }
            else
            {
                out << QObject::trUtf8("Не могу открыть файл журнала отладки.\n");
                lContinue = false;
            }

        }
    }
    return lContinue;
}


void test() {
    // Процедура для тестирования на "утечки" памяти
    QString dictName("счета");
    for (int i = 0; i < 50; i++) {              // 50 раз откроем, закроем справочник
        Dictionaries* dicts = TApplication::exemplar()->getDictionaries();
        dicts->addDictionary(dictName, 1);
        Dictionary* dict = dicts->getDictionary(dictName);         // Откроем справочник и подсправочники 1-го уровня
        if (dict != 0) {
            dicts->removeDictionary(dictName);
        }
        qDebug() << i;
    }
}


int main(int argc, char **argv)
{
    TApplication application(argc, argv);
    QTextCodec::setCodecForTr(TApplication::codec());
    QTextCodec::setCodecForLocale(TApplication::codec());
    QTextCodec::setCodecForCStrings(TApplication::codec());

    // Инициируем переменные, которые нуждаются в этом

    int lResult = 0;            // по умолчанию программа возвращает 0
    bool lStart = true;         // по умолчанию программа запускается
    if (argc > 1)                               // были заданы какие-то аргументы
        lStart = readParameters(argc, argv);    // прочитаем их
    if (lStart) {
        if (application.open()) {       // Если приложение удалось создать
            application.show();         // Тогда откроем его
            lResult = application.exec();
            application.close();            // Закроем приложение
        }
    }

    TApplication::debug(" Program shutdown.\n\n");
    application.quit();
    return lResult;
}
