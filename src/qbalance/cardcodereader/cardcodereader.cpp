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
#include "../../qextserialport/src/qextserialport.h"
#include "cardcodereader.h"
#include "../kernel/app.h"


CardCodeReader::CardCodeReader(QObject *parent) :
    QObject(parent)
{
    app = 0;
}


CardCodeReader::~CardCodeReader()
{
}


void CardCodeReader::setApp(TApplication* a)
{
    app = a;
}


bool CardCodeReader::open()
{
    bool result = true;
    cardReaderCode = "";
    crPrefix = app->getConfigValue("CARD_READER_PREFIX").toString();
    return result;
}


void CardCodeReader::close()
{
}


void CardCodeReader::readCardReader(QKeyEvent* keyEvent)
{
    QString text;

    if (keyEvent->key() == 59 || keyEvent->key() == 1046)   // Если это клавиша ";" в английской или русской раскладке
        text = ";";
    else
        text = keyEvent->text();

    cardReaderCode.append(text);
    int leftSize = cardReaderCode.size() <= crPrefix.size() ? cardReaderCode.size() : crPrefix.size();
    if (leftSize > 0 && (crPrefix.left(leftSize) == cardReaderCode.left(leftSize)))   // Если начальные введенные символы начинают совпадать с префиксом
    {                                                                // считывателя магнитных карт
        if (crPrefix == cardReaderCode.left(leftSize))       // Если префикс полностью совпал
        {
           if (keyEvent->key() == 44 || keyEvent->key() == 63)     // Последовательность заканчивается клавишей "?"
           {
               QString cardCode = cardReaderCode;
               cardCode.replace(crPrefix, "");
               cardCode.chop(1);
               qDebug() << "emit " + cardCode.trimmed();
               emit cardCodeReaded(cardCode.trimmed());
               cardReaderCode = "";
           }
       }
       keyEvent->setAccepted(true);
   }
   else
       cardReaderCode = "";
}





