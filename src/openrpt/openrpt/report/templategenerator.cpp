#include "templategenerator.h"
#include <datasource.h>
#include <QString>
#include <QFile>
#include <QRect>
#include <QFont>
#include <QVariant>
#include <QDebug>

const QString TTemplateGenerator::TemplatePath = ":shared/files/template.xml";

namespace Report
{
    class Rectangle
    {
    public:
        static const QString Name;
        static const QString X;
        static const QString Y;
        static const QString Width;
        static const QString Height;
    };

    const QString Rectangle::Name   = QString("rect");
    const QString Rectangle::X      = QString("x");
    const QString Rectangle::Y      = QString("y");
    const QString Rectangle::Width  = QString("width");
    const QString Rectangle::Height = QString("height");

    class Frame: public Rectangle
    {
    public:
        static const QString Name;
        static const QString Weight;
        static const QString BorderWidth;
    };

    const QString Frame::Name        = QString("rect");
    const QString Frame::Weight      = QString("weight");
    const QString Frame::BorderWidth = QString("borderwidth");

    class Label: public Rectangle
    {
    public:
        static const QString Name;
        static const QString String;
    };

    const QString Label::Name   = QString("label");
    const QString Label::String = QString("string");

    class Field: public Rectangle
    {
    public:
        static const QString Name;
    };

    const QString Field::Name = QString("field");

    class Data
    {
    public:
        static const QString Name;
        static const QString Query;
        static const QString Column;
    };
    const QString Data::Name   = QString("data");
    const QString Data::Query  = QString("query");
    const QString Data::Column = QString("column");

    class Font
    {
    public:
        static const QString Name;
        static const QString Face;
        static const QString Size;
        static const QString Weight;
    };
    const QString Font::Name   = QString("font");
    const QString Font::Face   = QString("face");
    const QString Font::Size   = QString("size");
    const QString Font::Weight = QString("weight");

    class Orientation
    {
    public:
        static const QString VCenter;
        static const QString HCenter;
    };

    const QString Orientation::VCenter = QString("vcenter");
    const QString Orientation::HCenter = QString("hcenter");

    class Page
    {
    public:
        static const QString Header;
        static const QString Detail;
    };

    const QString Page::Header = QString("pghead");
    const QString Page::Detail = QString("detail");
}

TTemplateGenerator::TTemplateGenerator()
    : Source(NULL)
{
}

QDomDocument TTemplateGenerator::process()
{
    Document = QDomDocument();
    if (Source)
    {
        QFile file;
        file.setFileName(TTemplateGenerator::TemplatePath);
        if (file.open(QIODevice::ReadOnly))
        {
            if (Document.setContent(&file))
            {
                static unsigned int width;
                if (Source->count() > 0)
                    width = 650 / Source->count();
                else
                    width = 0;
                static QFont header_font = QFont("Helvetica", 12, QFont::Bold);
                static QFont detail_font = QFont("Helvetica", 12, QFont::Normal);
                QDomNode header = Document.elementsByTagName(Report::Page::Header).at(0);
                QDomNode detail = Document.elementsByTagName(Report::Page::Detail).at(0);
                QString field_name;
                QRect rect;
                for (int i = 0; i < Source->count(); ++i)
                {
                    field_name = Source->fieldName(i);
                    rect = QRect(width * i, 0, width, 30);
                    header.appendChild(makeFrame(rect, 1, 1));
                    header.appendChild(makeLabel(field_name, header_font, rect));
                    detail.appendChild(makeFrame(rect, 1, 1));
                    detail.appendChild(makeField(field_name, detail_font, rect));
                }
            }
        }
    }
    return Document;
}

QDomElement TTemplateGenerator::makeLabel(const QString& string, const QFont& font, const QRect& rect)
{
    QDomElement result = Document.createElement(Report::Label::Name);
    result.appendChild(makeRect(rect));
    result.appendChild(makeFont(font));
    result.appendChild(makeElement(Report::Orientation::HCenter, ""));
    result.appendChild(makeElement(Report::Orientation::VCenter, ""));
    result.appendChild(makeElement(Report::Label::String       , string));
    return result;
}

QDomElement TTemplateGenerator::makeField(const QString& field, const QFont& font, const QRect& rect)
{
    QDomElement result = Document.createElement(Report::Field::Name);
    result.appendChild(makeRect(rect));
    result.appendChild(makeFont(font));
    result.appendChild(makeElement(Report::Orientation::HCenter, ""));
    result.appendChild(makeElement(Report::Orientation::VCenter, ""));
    result.appendChild(makeData("test", field));
    return result;
}

QDomElement TTemplateGenerator::makeFrame(const QRect& rect, const int& weight, const int& border_width )
{
    QDomElement result = makeRect(rect);
    result.appendChild(makeElement(Report::Frame::Weight     , weight));
    result.appendChild(makeElement(Report::Frame::BorderWidth, border_width));
    return result;
}

QDomElement TTemplateGenerator::makeFont(const QFont& font)
{
    QDomElement result = Document.createElement(Report::Font::Name);
    result.appendChild(makeElement(Report::Font::Face, font.family()));
    result.appendChild(makeElement(Report::Font::Size, font.pointSize()));
    QString weight;

    switch(font.weight())
    {
        case QFont::Bold:
            weight = "bold"; break;

        case QFont::Normal:
            weight = "normal"; break;
    }

    result.appendChild(makeElement(Report::Font::Weight, weight));
    return result;
}

QDomElement TTemplateGenerator::makeRect(const QRect& rect)
{
    QDomElement result = Document.createElement(Report::Rectangle::Name);
    result.appendChild(makeElement(Report::Rectangle::X     , rect.x()));
    result.appendChild(makeElement(Report::Rectangle::Y     , rect.y()));
    result.appendChild(makeElement(Report::Rectangle::Width , rect.width()));
    result.appendChild(makeElement(Report::Rectangle::Height, rect.height()));
    return result;
}

QDomElement TTemplateGenerator::makeData(const QString& query, const QString& column)
{
    QDomElement result = Document.createElement(Report::Data::Name);
    result.appendChild(makeElement(Report::Data::Query , query));
    result.appendChild(makeElement(Report::Data::Column, column));
    return result;
}

void TTemplateGenerator::setDataSource(const IDataSource* source)
{
    Source = source;
}

QDomElement TTemplateGenerator::makeElement(const QString& name, const QVariant& value)
{
    QDomElement result;
    result = Document.createElement(name);
    result.appendChild(Document.createTextNode(value.toString()));
    return result;
}
