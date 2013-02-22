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

#ifndef OPENOFFICE_H
#define OPENOFFICE_H

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QProcess>


#define UNX
#define SAL_UNX
#define CPPU_ENV gcc3
//#include <sal/typesizes.h>

#include <stdio.h>
#include <cppuhelper/bootstrap.hxx>
//#include <osl/file.hxx>
//#include <osl/process.h>

#include <com/sun/star/frame/XDesktop.hpp>
#include <com/sun/star/bridge/XUnoUrlResolver.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/frame/XStorable.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/sheet/XSpreadsheetDocument.hpp>
#include <com/sun/star/sheet/XSpreadsheets.hpp>
#include <com/sun/star/sheet/XSpreadsheet.hpp>
#include <com/sun/star/table/XCell.hpp>
#include <com/sun/star/table/XCellRange.hpp>
#include <com/sun/star/container/XIndexAccess.hpp>
#include <com/sun/star/view/XPrintable.hpp>
#include <com/sun/star/view/PaperOrientation.hpp>
#include <com/sun/star/registry/XSimpleRegistry.hpp>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <com/sun/star/util/XReplaceable.hpp>
#include <string.h>

using namespace rtl;
using namespace cppu;
using namespace com::sun::star::view;
using namespace com::sun::star::table;
using namespace com::sun::star::container;
using namespace com::sun::star::sheet;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::beans;
using namespace com::sun::star::bridge;
using namespace com::sun::star::frame;
using namespace com::sun::star::registry;
using namespace com::sun::star::util;



class OpenOffice : public QObject
{
    Q_OBJECT
public:
    explicit OpenOffice(QObject *parent = 0);
    ~OpenOffice();
    virtual bool open(QString name);
    virtual void load(QMap<QString, QVariant>* context);
    virtual void close();

private:
    QString     fileNameUrl;
    QString     ooProcessCommand;
    QProcess*   ooProcess;

    // Переменные, необходимые для работы с OpenOffice через UNO
    OUString                            sConnectionString;
    Reference<XInterface>               xInterface;
    Reference<XComponent>               xComponent;
    Reference<XComponentContext>        xComponentContext;
    Reference<XMultiComponentFactory>   xMultiComponentFactoryClient;
    Reference<XMultiComponentFactory>   xMultiComponentFactoryServer;

    bool        connect();
};

#endif // OPENOFFICE_H
