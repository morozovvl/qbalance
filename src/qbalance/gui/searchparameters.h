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

#include <QtCore/QtGlobal>

#if QT_VERSION < 0x050000
    #include <QtGui/QLabel>
    #include <QtGui/QPushButton>
    #include <QtGui/QSizePolicy>
    #include <QtGui/QFrame>
    #include <QtGui/QLayout>
    #include <QtGui/QCheckBox>
    #include <QtGui/QLineEdit>
    #include <QtGui/QVBoxLayout>
    #include <QtGui/QWidget>
    #include <QtDesigner/QDesignerExportWidget>
#else
    #include <QtWidgets/QLabel>
    #include <QtWidgets/QPushButton>
    #include <QtWidgets/QSizePolicy>
    #include <QtWidgets/QFrame>
    #include <QtWidgets/QLayout>
    #include <QtWidgets/QCheckBox>
    #include <QtWidgets/QLineEdit>
    #include <QtWidgets/QVBoxLayout>
    #include <QtWidgets/QWidget>
    #include <QtUiPlugin/QDesignerExportWidget>
#endif

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QObject>
//#include <QtDesigner/QDesignerExportWidget>


class TApplication;
class FormGridSearch;
class Dictionaries;
struct sParam;

class SearchParameters : public QFrame {
    Q_OBJECT

public:
    SearchParameters(QWidget* parentWidget = 0 /*nullptr*/);
    ~SearchParameters();
    virtual void close();
    virtual QVector<sParam> getParameters();              // Возвращает информацию о заданных параметрах поиска
    virtual void setParameter(QString, QString);
    virtual void setFieldsList(QStringList);
    virtual void setFocus();
    virtual void setFormGrid(FormGridSearch* par);
    virtual void setApp(TApplication* a);
    virtual void setProgramIdFieldName(QString s);
    virtual void setProgramNameFieldName(QString s);
    virtual void setDictionaries(Dictionaries* dicts);
    virtual QString getFilter();
    virtual QString getFilter(QString, QString = "");
    virtual QString getSearchValue(QString);
    virtual void keyPressEvent(QKeyEvent*);
    virtual void setParent(QWidget *);
    virtual void clearAllComboBoxes();
    virtual int  getParametersCount();

signals:
    void requery();

public slots:
    virtual void dictionaryButtonPressed();
    virtual void comboBoxEnterPressed(QWidget*);

private:
    TApplication*       app;
    Dictionaries*       dictionaries;
    QString             programIdFieldName;
    QString             programNameFieldName;
    QGridLayout*        gridLayout;
    QStringList         parameters;
    FormGridSearch*     parentForm;
    virtual void addString(QString, int);
};

#endif // SEARCHPARAMETERS_H
