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

#include <QDebug>
#include "stdlib.h"
#include "openoffice.h"
#include "../kernel/app.h"

OpenOffice::OpenOffice(QObject *parent) : QObject(parent)
{
    ooProcessCommand = "socket,host=localhost,port=2083;urp;StarOffice.ServiceManager";
    sConnectionString = QString(ooProcessCommand).utf16();
}


OpenOffice::~OpenOffice()
{
}


bool OpenOffice::open(QString name)
{
    bool connected = connect();
    if (!connected)                 // Если сходу не удалось подключиться, то наверное сервер OpenOffice не запущен
    {
        QString rdbFile = QApplication::applicationDirPath() + "/offapi.rdb";
        if (QDir().exists(rdbFile))
        {
            // Проверим, существует ли переменная окружения, необходимая для работы OpenOffice. Если нет, то добавим ее
            setenv("URE_MORE_TYPES", QByteArray().append("file:" + rdbFile).constData(), 1);

            ooProcess = new QProcess();
            ooProcess->start("soffice \"--accept=" + ooProcessCommand + "\"  --invisible");
            if (ooProcess->waitForStarted())
            {

                for (int totalAttempts = 0; totalAttempts < 120; totalAttempts++)            // Будем пытаться подключиться к OpenOffice примерно в течении минуты
                {
                    // Сделаем таймаут 500 мс
                    QTime dieTime= QTime::currentTime().addMSecs(500);
                    while( QTime::currentTime() < dieTime )
                        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

                    connected = connect();
                    if (connected)
                        break;
                }
            }
        }
    }
    if (connected)
    {
        fileNameUrl = "file://" + name;

        try
        {
            // Загрузим файл в сервер OpenOffice
            Reference<XComponentLoader> xComponentLoader(xMultiComponentFactoryServer->createInstanceWithContext(
                                                         OUString("com.sun.star.frame.Desktop"),
                                                         xComponentContext), UNO_QUERY);
            if (xComponentLoader.is())
            {
                xComponent = xComponentLoader->loadComponentFromURL(
                             fileNameUrl.utf16(), OUString("_blank"), 0,
                             Sequence < ::com::sun::star::beans::PropertyValue >());
            }
        }
        catch (Exception& e)
        {
        }
    }
    else
    {
        TApplication::exemplar()->showError(QObject::trUtf8("Не удалось запустить") + " Open Office");                   // выдадим сообщение об ошибке
    }
    return connected;
}


void OpenOffice::close()
{
    Reference< XComponent>::query(xMultiComponentFactoryClient)->dispose();
}


bool OpenOffice::connect()
{
    bool result = true;
    OUString sConnectionString(QString("uno:" + ooProcessCommand).utf16());
    xComponentContext = ::cppu::defaultBootstrap_InitialComponentContext();
    xMultiComponentFactoryClient = xComponentContext->getServiceManager();
    xInterface = xMultiComponentFactoryClient->createInstanceWithContext(OUString("com.sun.star.bridge.UnoUrlResolver"), xComponentContext);
    Reference<XUnoUrlResolver> resolver(xInterface, UNO_QUERY);
    try
    {
        xInterface = Reference<XInterface>(resolver->resolve(sConnectionString), UNO_QUERY);
    }
    catch (Exception& e)
    {
        OString o = OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US );
        result = false;
    }
    if (result)
    {
        Reference<XPropertySet> xPropSet(xInterface, UNO_QUERY);
        xPropSet->getPropertyValue(OUString("DefaultContext")) >>= xComponentContext;
//            Reference<XMultiComponentFactory> xMultiComponentFactoryServer(xComponentContext->getServiceManager());
        xMultiComponentFactoryServer = xComponentContext->getServiceManager();
    }
    return result;
}


void OpenOffice::load(QMap<QString, QVariant>* context)
{
    try
    {
        //create xSheetDocument
        Reference<XSpreadsheetDocument> xSheetDocument (xComponent,UNO_QUERY);

        //create an instance of XSpreadsheets, which is a worksheets collection
        Reference<XSpreadsheets> xSheets=xSheetDocument->getSheets();

        //create a class to interact with single worksheets;

        //the single worksheets are referenced by an XIndexAccess interface
        Reference<XIndexAccess> xIndex (xSheets,UNO_QUERY);

        //take the first worksheet (index=0)...
        Any any=xIndex->getByIndex(0);

        //...then create an instance of Xspreadsheet, able to manage
        //single worksheets;
        Reference<XSpreadsheet> xSheet;

        //finally, assign the first worksheet to xSheet
        any >>= xSheet;

        //create an XCellRange interface to interact with cells ranges
        Reference<XCellRange> xCellRange(xSheet,UNO_QUERY);

        Reference<XReplaceable> xReplaceable(xCellRange, UNO_QUERY);
        Reference <XReplaceDescriptor> xReplaceDescriptor = xReplaceable->createReplaceDescriptor();

        foreach (QString key, context->keys())
        {
            xReplaceDescriptor->setSearchString(QString("[" + key + "]").utf16());
            xReplaceDescriptor->setReplaceString(context->value(key).toString().trimmed().utf16());
            xReplaceable->replaceAll(xReplaceDescriptor.get());
        }
    }
    catch (Exception& e)
    {
    }
}

/*
    PropertyValue properties[1];
    try
    {
        Reference<XStorable> xStorable = queryInterface(XStorable, xComponent);
        xStorable.storeToURL(fileNameUrl.utf16(), properties);
    }
    catch(...)
    {

    }
*/
//    Reference<XStorable> xStorable = XStorable.queryInterface(XStorable, xComponent);
//            .storeAsURL(fileNameUrl, xComponent);
//    xComponent.query(
/*
    //create xSheetDocument
    Reference<XSpreadsheetDocument> xSheetDocument (xComponent,UNO_QUERY);

    //create an instance of XSpreadsheets, which is a worksheets collection
    Reference<XSpreadsheets> xSheets=xSheetDocument->getSheets();

    //create a class to interact with single worksheets;

    //the single worksheets are referenced by an XIndexAccess interface
    Reference<XIndexAccess> xIndex (xSheets,UNO_QUERY);

    //take the first worksheet (index=0)...
    Any any=xIndex->getByIndex(0);

    //...then create an instance of Xspreadsheet, able to manage
    //single worksheets;
    Reference<XSpreadsheet> xSheet;

    //finally, assign the first worksheet to xSheet
    any >>= xSheet;

    //create an XCellRange interface to interact with cells ranges
    Reference<XCellRange> xCellRange(xSheet,UNO_QUERY);

    //create an XCell interface to interact with single cells
    Reference<XCell> xCell;

    //take the cell located in column 5, row 6
    int column=1;
    int row=1;
    xCell=xCellRange->getCellByPosition(column,row);

    //write a number in the cell
    xCell->setValue(1960);

    //change cell
//    column=6;
//    row=5;
//    xCell=xCellRange->getCellByPosition(column,row);

    //write a string in the cell
//    sString=OUString::createFromAscii('stringa');
//    xCell->setFormula(sString);
*/
