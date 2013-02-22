#include "report.h"
#include <QString>
#include <QDomDocument>
#include <QPrinter>
#include <QPrintDialog>

#include <renderobjects.h>
#include <orprerender.h>
#include <orprintrender.h>
#include <previewdialog.h>

class TReport_private
{
public:
    TReport_private()
    {
        Render = new ORPreRender;
    }

    ~TReport_private()
    {
        if (Render)
        {
            delete Render;
            Render = NULL;
        }
    }

    ORPreRender* Render;
    ORODocument* Report;
    QDomDocument Document;
};

TReport::TReport()
    : pd(NULL)
{
    pd = new TReport_private;
}
TReport::~TReport()
{
    if (pd)
    {
        delete pd;
        pd = NULL;
    }
}

void TReport::setReport(const QDomDocument& value)
{
    pd->Document = value;
    pd->Render->setDom(pd->Document);
}

QDomDocument& TReport::report() const
{
    return pd->Document;
}

void TReport::setDataSource(const QString& name, IDataSource* source)
{
    pd->Render->setSource(name, source);
}

IDataSource* TReport::dataSource(const QString& name) const
{
    return NULL;
}

void TReport::preview()
{
    pd->Report = pd->Render->generate();

    QPrinter printer(QPrinter::HighResolution);
    printer.setNumCopies(1);

    ORPrintRender render;
    render.setupPrinter(pd->Report, &printer);

    QPrinter* tPrinter = &printer;
    QPrinter pdfPrinter(QPrinter::HighResolution);
    if(!printer.isValid())
    {
      render.setupPrinter(pd->Report, &pdfPrinter);
      pdfPrinter.setOutputFormat(QPrinter::PdfFormat);
      tPrinter = &pdfPrinter;
    }
    PreviewDialog preview(pd->Report, tPrinter, NULL);

    if (preview.exec() == QDialog::Rejected)
      return;

    QPrintDialog qpd(&printer);
    qpd.setMinMax(1, pd->Report->pages());
    if(qpd.exec() == QDialog::Accepted)
    {
      render.setPrinter(&printer);
      render.render(pd->Report);
    }
}

void TReport::print()
{

}
