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

#ifndef DOCPARAMETERS_H
#define DOCPARAMETERS_H

#include <QtGui>
#include <QMap>
#include <QList>
#include <QFrame>
#include <QString>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QStringList>
#include "../kernel/app.h"
#include "mycombobox.h"
#include "formgridsearch.h"

class TApplication;
class FormDocument;

class DocParameters : public QFrame {
    Q_OBJECT

public:
    DocParameters(QWidget* pwgt = 0);

    ~DocParameters();
    void addString(QString);
    void removeString(int);
    void setFocus();
    void showText(QString);
    QStringList getKeys() { return dictList; }
    Dictionary* getDictionary(QString dictName) { return dictionaries->value(dictName); }
    void setDictionaries(QMap<QString, Dictionary*>* dicts) { dictionaries = dicts; }
    void setFormDocument(FormDocument* doc) { parentForm = doc; }
    int count() { return strNum; }
    void setApp(TApplication* a) { app = a; }
    void setProgramIdFieldName(QString s) { programIdFieldName = s; }
    void setProgramNameFieldName(QString s) { programNameFieldName = s; }
public slots:
    void dictionaryButtonPressed();

private:
    TApplication*                   app;
    QMap<QString, Dictionary*>*     dictionaries;
    QGridLayout*                    gridLayout;
    FormDocument*                   parentForm;
    QString                         programIdFieldName;
    QString                         programNameFieldName;
    int                             strNum;
    QStringList                     parameters;
    QStringList                     dictList;

};

#endif // DOCPARAMETERS_H
