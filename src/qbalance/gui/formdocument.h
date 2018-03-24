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

#ifndef FORMDOCUMENT_H
#define FORMDOCUMENT_H

#include <QtGui/QWidget>
#include <QtGui/QDateEdit>
#include <QtGui/QTextEdit>
#include <QtGui/QPushButton>
#include "formgrid.h"


class Document;
class DocParameters;
class MyNumericEdit;

class FormDocument : public FormGrid {
    Q_OBJECT
public:
    FormDocument();
    ~FormDocument();
    virtual Document* getParent(bool = false);
    virtual void parametersChangedEvent();
    QDateEdit* getDateEdit();
    QLineEdit* getNumberEdit();
    void showParameterText(QString dictName);
    void showTextEdit(bool show);
    DocParameters*  getDocParameters();

    Q_INVOKABLE QPushButton* getButtonQueryAdd();
    Q_INVOKABLE virtual void setEnabled(bool);
    Q_INVOKABLE void addQueryMenuAction(QString, QString);

public slots:
    virtual void cmdQueryAdd();
    Q_INVOKABLE virtual void cmdOk();
    Q_INVOKABLE virtual void cmdCancel();
    Q_INVOKABLE virtual void show();
    Q_INVOKABLE virtual void hide();
protected:
    QPushButton*                buttonQueryAdd;     // Кнопка "Добавить записи из запроса"
private:
    QDateEdit*      dateEdit;
    QLineEdit*      numberEdit;
    DocParameters*  parameters;
    MyNumericEdit*    itogNumeric;
    QMenu*          queriesMenu;
    QTextEdit*      textEdit;
    virtual void createForm(QString, QWidget* pwgt = 0);
//    virtual QDomElement createWidgetsStructure();

private slots:
    void    saveDate(const QString &);
    void    saveNumber(const QString &);
};

#endif // FORMDOCUMENT_H
