#ifndef REPORTTEMPLATE_H
#define REPORTTEMPLATE_H

#include <QString>
#include <QDomDocument>
#include <QDomNode>
#include <QString>
#include <QScriptValue>
#include "../kernel/essence.h"
#include "reportengine.h"

//#define DEFAULT_DICT_REPORT "default_dict_report.ods"          // Отчет будем готовить в формате Open Office 1.0 (запакованный ZIP-ом каталог с XML файлами)
//#define REPORT_DIR      "./reports/"
//#define TMP_DIR         "./tmp/"
#define HEAD_ANNOTATION     "шапка таблицы"
#define BODY_ANNOTATION     "тело таблицы"
#define END_ANNOTATION      "конец таблицы"

class Essence;
class ReportEngine;

class ReportTemplate : public QObject {
public:
    ReportTemplate(Essence*, ReportEngine*, QString fileName = DEFAULT_REPORT);
    virtual ~ReportTemplate() { ; }
    Q_INVOKABLE virtual bool open();
private:
    QList<QString> columns;
    QDomDocument doc;
    QDomElement rootElement;
    QDomElement tableElement;               // Первая таблица в файле
    Essence* parent;
    QString templateFileName;
    ReportEngine* engine;
    bool startOpenOffice(QString fileName = DEFAULT_REPORT);          // Запускает Open Office и загружает в него заданный в параметрах файл
    QString prepareDefaultDocument(QString fileName = DEFAULT_REPORT);   // Готовит документ по умолчанию: берет пустую копию, разархивирует ее, заполняет данными (через метод writeDefaultDocument()), архивирует, передает в каталог с документами
    bool writeDefaultDocument(QString);                                  // Заполняет распакованный документ в XML формате содержимым отчета
    void writeTableHeader(QDomNode);
    void writeTableBody(QDomNode, int);
    void writeTableEnd(QDomNode);
    void writeCellAnnotation(QDomElement, QString);
    void writeCell(QDomElement, QVariant, QVariant::Type type = QVariant::String);
    void writeVariables();                                              // Заполняет поля с переменными в шаблоне
    QDomNode findAnnotation(QString);
    void readAvailableColumns();                                        // Читает из шаблона отчета, какие колонки присутствуют в отчете
};

#endif // REPORTTEMPLATE_H
