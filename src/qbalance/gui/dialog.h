/************************************************************************************************************
Copyright (C) Morozov Vladimir Aleksandrovich
MorozovVladimir@mail.ru

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*************************************************************************************************************/


#ifndef DIALOG_H
#define DIALOG_H

#include <QtCore/QtGlobal>

#if QT_VERSION < 0x050000
    #include <QtGui/QPushButton>
    #include <QtDesigner/QDesignerExportWidget>
#else
    #include <QtWidgets/QPushButton>
    #include <QtUiPlugin/QDesignerExportWidget>
#endif

#include <QtGui/QDialog>
#include <QtGui/QKeyEvent>

class MainWindow;
class Form;
class TApplication;

class Dialog : public QDialog

{
    Q_OBJECT
public:

    Dialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~Dialog();
    Q_INVOKABLE virtual QObject* findChild(QString);
    Q_INVOKABLE virtual bool isFormSelected();

    virtual void setApp(TApplication*);
    Q_INVOKABLE virtual void setForm(Form* f);
    Q_INVOKABLE virtual Form* getForm();
    virtual void    keyPressEvent(QKeyEvent*);
    bool            isFormWidgetChanged();
    void            setFormChanged(bool);

protected:
    virtual void showEvent(QShowEvent*);
    virtual void moveEvent(QMoveEvent*);
    virtual void resizeEvent(QResizeEvent*);

private:
    TApplication*               app;
    Form*                       form;
    QPushButton*                buttonOk;
    QPushButton*                buttonCancel;
    bool                        isSelected;
    bool                        formChanged;
    int                         moveCount;

private slots:
    void    cmdOk();
    void    cmdCancel();
};

#endif // DIALOG_H
