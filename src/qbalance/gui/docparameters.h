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

#include <QtCore/QtGlobal>
#if QT_VERSION < 0x050000
    #include <QtGui/QLabel>
    #include <QtGui/QPushButton>
    #include <QtGui/QSizePolicy>
    #include <QtGui/QLayout>
    #include <QtGui/QLineEdit>
    #include <QtGui/QFrame>
    #include <QtGui/QWidget>
    #include <QtGui/QVBoxLayout>
    #include <QtDesigner/QDesignerExportWidget>
#else
    #include <QtWidgets/QLabel>
    #include <QtWidgets/QPushButton>
    #include <QtWidgets/QSizePolicy>
    #include <QtWidgets/QFrame>
    #include <QtWidgets/QLayout>
    #include <QtWidgets/QLineEdit>
    #include <QtWidgets/QWidget>
    #include <QtWidgets/QVBoxLayout>
    #include <QtUiPlugin/QDesignerExportWidget>
#endif

#include <QtCore/QHash>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtCore/QStringList>

class TApplication;
class FormDocument;
class Dictionary;


class DocParameters : public QFrame {
    Q_OBJECT

public:
    DocParameters(QWidget* pwgt = nullptr);
    ~DocParameters();
    virtual void addString(QString);
    virtual void setFocus();
    virtual void showText(QString);
    virtual QStringList getKeys();
    virtual Dictionary* getDictionary(QString dictName);
    virtual void setDictionaries(QHash<QString, Dictionary*>* dicts);
    virtual void setFormDocument(FormDocument* doc);
    virtual void setApp(TApplication*);

public slots:
    virtual void dictionaryButtonPressed();

private:
    TApplication*                   app;
    QHash<QString, Dictionary*>*    dictionaries;
    QGridLayout*                    gridLayout;
    FormDocument*                   parentForm;
    QString                         programIdFieldName;
    QString                         programNameFieldName;
    int                             strNum;
    QStringList                     parameters;
    QStringList                     dictList;

//    void removeString(int);
};

#endif // DOCPARAMETERS_H
