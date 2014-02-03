#ifndef QTSCRIPTSHELL_QITEMEDITORFACTORY_H
#define QTSCRIPTSHELL_QITEMEDITORFACTORY_H

#include <qitemeditorfactory.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QItemEditorFactory : public QItemEditorFactory
{
public:
    QtScriptShell_QItemEditorFactory();
    ~QtScriptShell_QItemEditorFactory();

    QWidget*  createEditor(int  userType, QWidget*  parent) const;
    QByteArray  valuePropertyName(int  userType) const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QITEMEDITORFACTORY_H
