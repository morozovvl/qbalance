#include <QDebug>
#include <QtCore/QStringList>
#include "odfpreviewlib.h"
#include "../../quazip/quazip.h"
#include "../../quazip/quazipfile.h"


OdfPreviewLib::OdfPreviewLib(QWidget *parent) : QObject()
{
    printer         = new QPrinter();
    printPreview    = new QPrintPreviewDialog(printer, parent);

    printPreview->setWindowTitle("Preview Dialog");
    printPreview->setWindowState(Qt::WindowMaximized);
    printPreview->setWindowFlags(Qt::WindowTitleHint);

    connect(printPreview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(draw(QPrinter*)));
}


OdfPreviewLib::~OdfPreviewLib()
{
    disconnect(printPreview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(draw(QPrinter*)));

    delete printPreview;
    delete printer;
}


bool OdfPreviewLib::open(const QString fileName)
{
    bool lResult = false;

    if (printer->isValid())
    {
        if (unzip(fileName))
        {
            lResult = true;
        }
    }

    return lResult;
}


bool OdfPreviewLib::open(const QDomDocument* const doc)
{
    content = *doc;
    return true;
}


DocType OdfPreviewLib::getDocType() const
{
    DocType result = none;

    if (content.elementsByTagName("office:spreadsheet").count() > 0)
        result = ods;
    else if (content.elementsByTagName("office:text").count() > 0)
        result = odt;

    return result;
}


void OdfPreviewLib::close()
{
}


void OdfPreviewLib::preview()
{
    setPrinterConfig();
    printPreview->exec();
}


void OdfPreviewLib::print()
{
    setPrinterConfig();
}


void OdfPreviewLib::draw(QPrinter *printer)
{
    QPainter painter(printer);
    painter.setRenderHints(QPainter::Antialiasing |
                       QPainter::TextAntialiasing |
                       QPainter::SmoothPixmapTransform, true);

    switch (getDocType())
    {
        case ods:
            drawOds(&painter);
            break;
        case odt:
            drawOdt(&painter);
            break;
        default:
            break;
    }
}


bool OdfPreviewLib::unzip(QString fileName)
{
    bool lResult = false;

    QuaZip zip(fileName);
    zip.open(QuaZip::mdUnzip);

    if (zip.setCurrentFile("content.xml"))
    {
        QuaZipFile file(&zip);
        file.open(QIODevice::ReadOnly);

        QByteArray data(file.size(), ' ');
        file.read(data.data(), file.size());

        if (content.setContent(data))
            lResult = true;

        file.close();
    }

    if (lResult)
    {
        lResult = false;
        if (zip.setCurrentFile("styles.xml"))
        {
            QuaZipFile file(&zip);
            file.open(QIODevice::ReadOnly);

            QByteArray data(file.size(), ' ');
            file.read(data.data(), file.size());

            if (styles.setContent(data))
                lResult = true;

            file.close();
        }
    }
    zip.close();

    return lResult;
}


void OdfPreviewLib::setPrinterConfig()
{
    printer->setPageSize(QPrinter::A4);
    printer->setOrientation(QPrinter::Portrait);
    printer->setFullPage(true);
    printer->setPageMargins(10.0, 10.0, 10.0, 10.0, QPrinter::Millimeter);
}


void OdfPreviewLib::drawOds(QPainter* painter)
{
    loadPageStyles();
    loadContentStyles();

    // Calculate row's vertical position and height
    QDomNodeList    rows = content.elementsByTagName("table:table-row");
    qreal   y = 0;
    for (int i = 0; i < rows.count(); i++)
    {
        RowPos pos;

        pos.y = y;
        pos.h = contentStyles[rows.at(i).toElement().attribute("table:style-name")].height;

        rowsPos.insert(i, pos);
        y += pos.h;
    }

    // Calculate column's horizontal position and width
    QDomNodeList    columns = content.elementsByTagName("table:table-column");
    qreal   x = 0;
    for (int i = 0; i < columns.count(); i++)
    {
        ColumnPos pos;

        pos.x = x;
        pos.w = contentStyles[columns.at(i).toElement().attribute("table:style-name")].width;

        columnsPos.insert(i, pos);
        x += pos.w;
    }

    QString pageStyleName = content.elementsByTagName("table:table").at(0).toElement().attribute("table:style-name");
    pageStyleName = firstNodeWithAttribute(content.elementsByTagName("style:style"), "style:name", pageStyleName).toElement().attribute("style:master-page-name");
    pageStyleName = sheetPrintStyleNames.value(pageStyleName);

    // Calculate cell's positions

    qreal leftMargin = pageStyles[pageStyleName].marginLeft;
    qreal rightMargin = pageStyles[pageStyleName].marginRight;
    qreal topMargin = pageStyles[pageStyleName].marginTop;
    qreal bottomMargin = pageStyles[pageStyleName].marginBottom;
    qreal printablePageHeight = pageStyles[pageStyleName].height - topMargin - bottomMargin;
    int     pageCounter = 1;

    qreal rowY = 0;
    qreal rowH = 0;

    rows = content.elementsByTagName("table:table-row");
    for (int i = 0; i < rows.count(); i++)
    {
        qreal colX = 0;
        qreal colW = 0;

        QString text;
        QString styleName;
        int rowSpanned = 0;
        int colSpanned = 0;

        QDomNodeList cells = rows.at(i).childNodes();
        for (int j = 0; j < cells.count(); j++)
        {
            int repeate = 0;
            if (cells.at(j).nodeName() != "table:covered-table-cell")
            {
                if (repeate == 0)
                {
                    repeate = QString(cells.at(j).toElement().attribute("table:number-columns-repeated")).toInt();
                    styleName = cells.at(j).toElement().attribute("table:style-name");
                    if (styleName.size() == 0)
                        styleName = columns.at(j).toElement().attribute("table:default-cell-style-name");
                    text = cells.at(j).firstChildElement("text:p").text();
                }
                else
                    --repeate;

                rowSpanned = QString(cells.at(j).toElement().attribute("table:number-rows-spanned")).toInt();
                colSpanned = QString(cells.at(j).toElement().attribute("table:number-columns-spanned")).toInt();

                rowY = rowsPos[i].y;
                if (rowSpanned > 1)
                {
                    for (int s = 0; s < rowSpanned; s++)
                        rowH += rowsPos[i+s].h;
                }
                else
                    rowH = rowsPos[i].h;

                colX = columnsPos[j].x;
                if (colSpanned > 1)
                {
                    for (int s = 0; s < colSpanned; s++)
                        colW += columnsPos[j+s].w;
                }
                else
                    colW = columnsPos[j].w;

                // If end of printable area reached, add new page
                if ((rowY + rowH) >= pageCounter * printablePageHeight)
                {
                    printer->newPage();
                    pageCounter++;
                }

                int x = mmToPixels(colX + leftMargin);
                int y = mmToPixels(rowY - (pageCounter - 1) * printablePageHeight + topMargin );
                int w = mmToPixels(colW);
                int h = mmToPixels(rowH);

                // Draw borders
                QPen pen;
                pen.setWidth(1);

                painter->setPen(pen);

                if (contentStyles[styleName].leftBS.size > 0)
                    painter->drawLine(x, y, x, y + h);
                if (contentStyles[styleName].rightBS.size > 0)
                    painter->drawLine(x + w, y, x + w, y + h);
                if (contentStyles[styleName].topBS.size > 0)
                    painter->drawLine(x, y, x + w, y);
                if (contentStyles[styleName].bottomBS.size > 0)
                    painter->drawLine(x, y + h, x + w, y + h);

                if (text.size() > 0)
                {
                    // Draw text
                    QRect rect(x, y, w, h);

                    QTextOption textOption;
                    if (!contentStyles[styleName].wrap)
                        textOption.setWrapMode(QTextOption::NoWrap);
                    textOption.setAlignment(contentStyles[styleName].align);
//                  textOption.setFlags(Qt::TextWrapAnywhere);

                    if (contentStyles[styleName].backgroundColor.size() > 0)
                        painter->fillRect(rect, QBrush(QColor(contentStyles[styleName].backgroundColor)));
//                  painter->fillRect(rect, QBrush(QColor(255, 255, 255)));

                    QFont font(contentStyles[styleName].fontName, contentStyles[styleName].fontSize);
                    font.setBold(contentStyles[styleName].bold);

                    painter->setFont(font);
                    painter->drawText(rect, text, textOption);
//                  painter->drawText(rect, Qt::TextWrapAnywhere, text, &rect);
                }
            }
        }
    }
}


void OdfPreviewLib::drawOdt(QPainter* painter)
{
    painter->setFont(QFont("Tahoma",8));
    painter->drawText(100, 100, "It's the text!");
}


qreal OdfPreviewLib::mmToPixels(qreal mm) const
{
    return mm * 0.039370147 * printer->resolution();
}


BorderStyle OdfPreviewLib::parseBorderTypeString(const QString str, const BorderStyle* const defaultBS) const
{
    BorderStyle bs;
    QStringList borderStr = str.split(" ");
    QString s = borderStr.at(0);
    s = s.remove("pt");

    if (s.size() > 0 && s != "none")
    {
        bs.size     = s.toFloat();
        bs.type     = borderStr.at(1);
        bs.color    = borderStr.at(2);
    }
    else if (defaultBS != 0)
    {
        bs = *defaultBS;
    }
    else
    {
        bs.size     = 0;
        bs.type     = "";
        bs.color    = "";
    }

    return bs;
}


void OdfPreviewLib::loadContentStyles()
{
    // Loading styles of rows, columns, cells from document
    QDomNodeList    nl = content.elementsByTagName("style:style");
    for (int i = 0; i < nl.count(); i++)
    {
        QString name = nl.at(i).toElement().attribute("style:name");
        QString styleFamily = nl.at(i).toElement().attribute("style:family");

        CellStyle style;
        style.width = 0;
        style.height = 0;
        style.fontName = "";
        style.fontSize = 0;
        style.align = Qt::AlignLeft;

        BorderStyle bs;
        bs.size = 0;
        bs.type = "";
        bs.color = "";
        style.leftBS = bs;
        style.rightBS = bs;
        style.topBS = bs;
        style.bottomBS = bs;

        if (styleFamily == "table")
        {
            style.type = tableTable;
        }
        else if (styleFamily == "table-row")
        {
            style.type      = tableRow;
            style.height    = QString(nl.at(i).firstChild().toElement().attribute("style:row-height").remove("mm")).toFloat();
        }
        else if (styleFamily == "table-column")
        {
            style.type  = tableColumn;
            style.width = QString(nl.at(i).firstChild().toElement().attribute("style:column-width").remove("mm")).toFloat();
        }
        else if (styleFamily == "table-cell")
        {
            style.type      = tableCell;
            style.fontName  = nl.at(i).firstChildElement("style:text-properties").attribute("style:font-name");
            style.bold      = nl.at(i).firstChildElement("style:text-properties").attribute("fo:font-weight") == "bold" ? true : false;
            style.wrap      = nl.at(i).firstChildElement("style:table-cell-properties").attribute("fo:wrap-option") == "wrap" ? true : false;
            style.fontSize  = QString(nl.at(i).firstChildElement("style:text-properties").attribute("fo:font-size").remove("pt")).toInt();

            QDomElement n = nl.at(i).firstChildElement("style:table-cell-properties");
            bs = parseBorderTypeString(n.attribute("fo:border"));                           // default border style
            style.leftBS    = parseBorderTypeString(n.attribute("fo:border-left"), &bs);
            style.rightBS   = parseBorderTypeString(n.attribute("fo:border-right"), &bs);
            style.topBS     = parseBorderTypeString(n.attribute("fo:border-top"), &bs);
            style.bottomBS  = parseBorderTypeString(n.attribute("fo:border-bottom"), &bs);

            style.backgroundColor = nl.at(i).firstChild().toElement().attribute("fo:background-color");

            QString hAlignment = nl.at(i).firstChildElement("style:paragraph-properties").attribute("fo:text-align");
            if (hAlignment == "start")
                style.align = Qt::AlignLeft;
            else if (hAlignment == "end")
                style.align = Qt::AlignRight;
            else if (hAlignment == "center")
                style.align = Qt::AlignHCenter;

            QString vAlignment = nl.at(i).firstChildElement("style:table-cell-properties").attribute("style:vertical-align");

            if (vAlignment == "top")
                style.align = style.align | Qt::AlignTop;
            else if (vAlignment == "bottom")
                style.align = style.align | Qt::AlignBottom;
            else if (vAlignment == "middle")
                style.align = style.align | Qt::AlignVCenter;

        }
        else
        {
            style.type = tableNone;
        }

        if (style.type != tableNone)
            contentStyles.insert(name, style);
    }
}


void OdfPreviewLib::loadPageStyles()
{
    QDomNodeList    nl = styles.elementsByTagName("style:page-layout");
    for (int i = 0; i < nl.count(); i++)
    {
        QString name = nl.at(i).toElement().attribute("style:name");
        QDomElement e = nl.at(i).toElement().firstChildElement("style:page-layout-properties");

        PageStyle style;
        style.width         = QString(e.attribute("fo:page-width").remove("mm")).toFloat();
        if (style.width == 0)
            style.width = 210;
        style.height        = QString(e.attribute("fo:page-height").remove("mm")).toFloat();
        if (style.height == 0)
            style.height = 297;
        style.orientation   = e.attribute("style:print-orientation") == "portrait" ? QPrinter::Portrait : QPrinter::Landscape;
        style.marginTop     = QString(e.attribute("fo:margin-top").remove("mm")).toFloat();
        style.marginBottom  = QString(e.attribute("fo:margin-bottom").remove("mm")).toFloat();
        style.marginLeft    = QString(e.attribute("fo:margin-left").remove("mm")).toFloat();
        style.marginRight   = QString(e.attribute("fo:margin-right").remove("mm")).toFloat();

        pageStyles.insert(name, style);
    }

    QDomNodeList nl1 = styles.elementsByTagName("style:master-page");
    for (int i = 0; i < nl1.count(); i++)
    {
        QString name = nl1.at(i).toElement().attribute("style:name");
        QString styleName = nl1.at(i).toElement().attribute("style:page-layout-name");
        sheetPrintStyleNames.insert(name, styleName);
    }
}


QDomNode OdfPreviewLib::firstNodeWithAttribute(const QDomNodeList nl, const QString attr, const QString val)
{
    for (int i = 0; i < nl.count(); i++)
    {
        if (nl.at(i).toElement().attribute(attr) == val)
            return nl.at(i);
    }
    return QDomNode();
}

