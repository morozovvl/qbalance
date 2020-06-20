#ifndef OdfPreviewLib_H
#define OdfPreviewLib_H

#include <QtCore/QObject>
#include <QtCore/QHash>
#include <QtGui/QPainter>
#include <QtGui/QPrinter>
#include <QtGui/QPrintPreviewDialog>
#include <QtXml/QDomDocument>

//#include "odfpreviewlib_global.h"


enum DocType {none, ods, odt};
enum StyleFamily {tableNone, tableTable, tableRow, tableColumn, tableCell};


struct BorderStyle
{
    qreal       size;
    QString     type;
    QString     color;
};


struct CellStyle
{
    StyleFamily         type;
    qreal               width;
    qreal               height;
    QString             fontName;
    int                 fontSize;
    bool                bold;
    bool                wrap;
    Qt::Alignment       align;
    BorderStyle         leftBS;     // left border style
    BorderStyle         rightBS;
    BorderStyle         topBS;
    BorderStyle         bottomBS;
    QString             backgroundColor;
};


struct PageStyle
{
    qreal                   width;
    qreal                   height;
    QPrinter::Orientation   orientation;
    qreal                   marginTop;
    qreal                   marginBottom;
    qreal                   marginLeft;
    qreal                   marginRight;
    qreal                   scale;
};


struct RowPos
{
    qreal       y;
    qreal       h;
};

struct ColumnPos
{
    qreal       x;
    qreal       w;
};

class OdfPreviewLib : public QObject
{
    Q_OBJECT

public:
    OdfPreviewLib(QWidget *parent = nullptr);
    ~OdfPreviewLib();

    bool open(const QString);
    bool open(const QDomDocument* const);
    void close();
    void preview();
    void print();

private slots:
    void draw(QPrinter*);

private:
    QPrinter*                   printer;
    QPrintPreviewDialog*        printPreview;
    QDomDocument                content;
    QDomDocument                styles;
    QHash<QString, CellStyle>   contentStyles;
    QHash<QString, PageStyle>   pageStyles;
    QHash<QString, QString>     sheetPrintStyleNames;
    QHash<int, RowPos>          rowsPos;
    QHash<int, ColumnPos>       columnsPos;

    bool                        unzip(QString);
    DocType                     getDocType() const;
    void                        setPrinterConfig();
    void                        drawOds(QPainter*);
    void                        drawOdt(QPainter*);

    qreal                       mmToPixels(qreal) const;
    BorderStyle                 parseBorderTypeString(const QString, const BorderStyle* const = 0) const;
    void                        loadContentStyles();
    void                        loadPageStyles();
    QDomNode                    firstNodeWithAttribute(const QDomNodeList, const QString, const QString);
};

#endif // OdfPreviewLib_H
