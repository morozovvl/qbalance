#ifndef QTSCRIPTSHELL_QACCESSIBLEBRIDGE_H
#define QTSCRIPTSHELL_QACCESSIBLEBRIDGE_H

#include <qaccessiblebridge.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QAccessibleBridge : public QAccessibleBridge
{
public:
    QtScriptShell_QAccessibleBridge();
    ~QtScriptShell_QAccessibleBridge();

    void notifyAccessibilityUpdate(QAccessibleEvent*  event);
    void setRootObject(QAccessibleInterface*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QACCESSIBLEBRIDGE_H
