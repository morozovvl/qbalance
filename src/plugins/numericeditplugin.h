#ifndef NUMERICEDITPLUGIN_H
#define NUMERICEDITPLUGIN_H

#include <QLineEdit>
#include <QDesignerCustomWidgetInterface>

class NumericEditPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    NumericEditPlugin( QObject *parent = 0 );

    bool isContainer() const;
    bool isInitialized() const;
    QIcon icon() const;
    QString codeTemplate() const;
    QString domXml() const;
    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget *createWidget( QWidget *parent );
    void initialize( QDesignerFormEditorInterface *core );

private:
    bool m_initialized;
};
#endif // NUMERICEDITPLUGIN_H


