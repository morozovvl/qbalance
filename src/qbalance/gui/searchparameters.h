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

#ifndef SEARCHPARAMETERS_H
#define SEARCHPARAMETERS_H

#include <QFrame>
#include <QVBoxLayout>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QWidget>
#include <QtCore/QObject>
#include <QtDesigner/QDesignerExportWidget>
#include "../kernel/app.h"
#include "mycombobox.h"
#include "formgridsearch.h"
#include "guifactory.h"

//class TApplication;
class FormGridSearch;
struct sParam;

class QDESIGNER_WIDGET_EXPORT SearchParameters : public QFrame {
    Q_OBJECT

public:
    SearchParameters(QWidget* parentWidget = 0);
    ~SearchParameters();
    void close();
    QVector<sParam> getParameters();              // Возвращает информацию о заданных параметрах поиска
    void setFieldsList(QStringList);
    void setFocus();
    void setFormGrid(FormGridSearch* par) { parentForm = par; }
    void setApp(TApplication* a);
    void setProgramIdFieldName(QString s) { programIdFieldName = s; }
    void setProgramNameFieldName(QString s) { programNameFieldName = s; }
    void setDictionaries(Dictionaries* dicts) { dictionaries = dicts; }
    QString getFilter();
    virtual void keyPressEvent(QKeyEvent*);
    void setParent(QWidget *);
    void clearAllComboBoxes();

signals:
    void requery();

public slots:
    void dictionaryButtonPressed();
    void comboBoxEnterPressed(QWidget*);

private:
    TApplication*       app;
    Dictionaries*       dictionaries;
    QString             programIdFieldName;
    QString             programNameFieldName;
    QGridLayout*        gridLayout;
    QStringList         parameters;
    FormGridSearch*     parentForm;
    void addString(QString, int);
};

#endif // SEARCHPARAMETERS_H
