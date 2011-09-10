#include <QApplication>
#include <QTextCodec>
#include <QTextStream>
#include <QResource>
#include "app.h"


QString         programName = "Enterprise";
QString         programAuthors = "Морозов Владимир (morozovvladimir@mail.ru)";
QString         programVersion = "0.01";
bool            programDebugMode = false;
QTextStream     programDebugStream;
QString         programDebugFileName = "debug.log";
QString         programErrorFileName = "error.log";
QFile           programDebugFile(programDebugFileName);
QString         programLogTimeFormat = "dd.MM.yy hh.mm.ss";
QString         programMaxSumMask = "9999999999.99";
QString         programIdFieldName;
QString         programNameFieldName;
QString         programResourcesFile;

App* app;
QTextCodec* codec;

bool readParameters(int argc, char *argv[]) {
    bool lContinue = true;
    QTextStream out(stdout);
    out.setCodec(codec);
    for (int i = 1; i < argc; i++) {
        if (QString(argv[i]).compare("-h", Qt::CaseInsensitive) == 0 ||
            QString(argv[i]).compare("--help", Qt::CaseInsensitive) == 0) {
            out << QObject::tr("Использование программы: enterprise [Параметр]\n");
            out << QObject::tr("Параметры:\n");
            out << QObject::tr("  -v | --version    - Вывести номер версии программы\n");
            out << QObject::tr("  -d | --debug      - Запустить программу в режиме отладки комманд запросов (файл debug.log)\n");
            out << QObject::tr("  -h | --help       - Вывести список параметров запуска программы\n");
            lContinue = false;
        }
        else if (QString(argv[i]).compare("-v", Qt::CaseInsensitive) == 0 ||
                QString(argv[i]).compare("--version", Qt::CaseInsensitive) == 0) {
            out << QString(QObject::tr("Название программы: %1\n")).arg(programName);
            out << QString(QObject::tr("Версия: %1\n")).arg(programVersion);
            out << QString(QObject::tr("Авторы: %1\n")).arg(programAuthors);
            lContinue = false;
        }
        else if (QString(argv[i]).compare("-d", Qt::CaseInsensitive) == 0 ||
                QString(argv[i]).compare("--debug", Qt::CaseInsensitive) == 0) {
            if (programDebugFile.open(QFile::WriteOnly | QFile::Append)) {
                programDebugStream.setDevice(&programDebugFile);
                programDebugStream << QDateTime().currentDateTime().toString(programLogTimeFormat) << " Program startup.\n";
                programDebugMode = true;
            }
            else {
                out << QObject::tr("Не могу открыть файл журнала отладки.\n");
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
        Dictionaries* dicts = app->getDictionaries();
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
    QApplication application(argc, argv);
    codec = QTextCodec::codecForName("UTF-8");
#ifdef Q_OS_WIN32
    if (QSysInfo::windowsVersion() != QSysInfo::WV_WINDOWS7)
        codec = QTextCodec::codecForName("Windows-1251");
#endif

    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);

    // Инициируем переменные, которые нуждаются в этом
    programMaxSumMask = programMaxSumMask.replace(".", QApplication::keyboardInputLocale().decimalPoint());
    programIdFieldName = QObject::tr("код");
    programNameFieldName = QObject::tr("имя");
    programResourcesFile = QDir::currentPath() + "/src/resources.qrc";

    int lResult = 0;            // по умолчанию программа возвращает 0
    bool lStart = true;         // по умолчанию программа запускается
    if (argc > 1)                               // были заданы какие-то аргументы
        lStart = readParameters(argc, argv);    // прочитаем их
    if (lStart) {
        app = new App(&application);
        if (app->open()) {       // Если приложение удалось создать
            app->show();         // Тогда откроем его
//            test();
            lResult = application.exec();
            app->close();            // Закроем приложение
        }
        delete app;

    }
    if (programDebugMode)
        programDebugStream << QDateTime().currentDateTime().toString(programLogTimeFormat) << " Program shutdown.\n\n";
    application.quit();
    return lResult;
}
