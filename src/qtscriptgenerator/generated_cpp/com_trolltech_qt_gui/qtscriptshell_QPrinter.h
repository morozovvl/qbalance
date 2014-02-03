#ifndef QTSCRIPTSHELL_QPRINTER_H
#define QTSCRIPTSHELL_QPRINTER_H

#include <qprinter.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QPrinter : public QPrinter
{
public:
    QtScriptShell_QPrinter(QPrinter::PrinterMode  mode = QPrinter::ScreenResolution);
    QtScriptShell_QPrinter(const QPrinterInfo&  printer, QPrinter::PrinterMode  mode = QPrinter::ScreenResolution);
    ~QtScriptShell_QPrinter();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPRINTER_H
