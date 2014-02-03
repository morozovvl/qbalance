#ifndef QTSCRIPTSHELL_QACCESSIBLEOBJECT_H
#define QTSCRIPTSHELL_QACCESSIBLEOBJECT_H

#include <qaccessibleobject.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QAccessibleObject : public QAccessibleObject
{
public:
    QtScriptShell_QAccessibleObject(QObject*  object);
    ~QtScriptShell_QAccessibleObject();

    QAccessibleInterface*  child(int  index) const;
    QAccessibleInterface*  childAt(int  x, int  y) const;
    int  childCount() const;
    QAccessibleInterface*  focusChild() const;
    int  indexOfChild(const QAccessibleInterface*  arg__1) const;
    void*  interface_cast(QAccessible::InterfaceType  arg__1);
    bool  isValid() const;
    QObject*  object() const;
    QAccessibleInterface*  parent() const;
    QRect  rect() const;
    QVector<QPair<QAccessibleInterface* , QAccessible::Relation >  >  relations(QAccessible::Relation  match) const;
    QAccessible::Role  role() const;
    void setText(QAccessible::Text  t, const QString&  text);
    QAccessible::State  state() const;
    QString  text(QAccessible::Text  t) const;
    void virtual_hook(int  id, void*  data);
    QWindow*  window() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QACCESSIBLEOBJECT_H
