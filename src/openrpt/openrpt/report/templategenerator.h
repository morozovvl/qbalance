#ifndef TEMPLATEGENERATOR_H
#define TEMPLATEGENERATOR_H

#include <QDomDocument>

#include "report_global.h"

class QRect;
class QFont;
class QVariant;
class IDataSource;

class REPORT_EXPORT TTemplateGenerator
{
public:
    TTemplateGenerator();
    void setDataSource(const IDataSource* source);
    QDomDocument process();
protected:
    QDomElement makeLabel(const QString& string, const QFont& font, const QRect& rect);
    QDomElement makeField(const QString& field, const QFont& font, const QRect& rect);
    QDomElement makeFrame(const QRect& rect, const int& weight, const int& border_width);
    QDomElement makeFont(const QFont& font);
    QDomElement makeRect(const QRect& rect);
    QDomElement makeData(const QString& query, const QString& column);
    QDomElement makeElement(const QString& name, const QVariant& value);
private:
    const IDataSource* Source;
    QDomDocument       Document;
    static const QString TemplatePath;
};

#endif // TEMPLATEGENERATOR_H
