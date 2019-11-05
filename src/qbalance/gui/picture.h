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

#ifndef PICTURE_H
#define PICTURE_H

#include <QtCore/QtGlobal>

#if QT_VERSION < 0x050000
    #include <QtGui/QApplication>
    #include <QtGui/QDesktopWidget>
    #include <QtGui/QMenu>
    #include <QtGui/QFrame>
    #include <QtDesigner/QDesignerExportWidget>
#else
    #include <QtWidgets/QApplication>
    #include <QtWidgets/QDesktopWidget>
    #include <QtWidgets/QMenu>
    #include <QtWidgets/QFrame>
    #include <QtUiPlugin/QDesignerExportWidget>
#endif

#include <QtCore/QString>
#include <QtGui/QImage>
#include <QtGui/QPaintEvent>


class TApplication;
class FormGrid;


class Picture: public QFrame {
    Q_OBJECT

public:
    Picture(QWidget* parent = nullptr);
    ~Picture();
    Q_INVOKABLE virtual void show(QString);
    virtual void showBigPicture();
    Q_INVOKABLE virtual void setApp(TApplication*);
    Q_INVOKABLE virtual void setVisibility(bool);
    Q_INVOKABLE virtual void setPhotoFileName(QString);
    Q_INVOKABLE virtual QString getPhotoFileName();
    Q_INVOKABLE virtual void setPhotoWindowTitle(QString);
    virtual void        setIsBig(bool big);
    virtual void        setForm(FormGrid* f = nullptr);
    virtual bool        isPictureExist();

protected:
    QString pictureDrawn;
    virtual void paintEvent(QPaintEvent*);
    virtual void mouseDoubleClickEvent(QMouseEvent*);
    virtual void mousePressEvent(QMouseEvent*);

private:
    TApplication*               app;
    FormGrid*                   form;
    int                         pictSize;
    QRect                       bigPictRect;
    bool                        isBigPicture;
    bool                        pictureExist;       // Картинка существует и отображается
    QString                     photoFileName;
    QString                     photoWindowTitle;
};

#endif // PICTURE_H
