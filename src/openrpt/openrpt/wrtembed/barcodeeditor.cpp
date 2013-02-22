/*
 * OpenRPT report writer and rendering engine
 * Copyright (C) 2001-2012 by OpenMFG, LLC
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * Please contact info@openmfg.com with any questions on this license.
 */

#include "barcodeeditor.h"

#include <QVariant>
#include <QValidator>
#include <QRegExp>
#include <QDebug>

BarcodeEditor::BarcodeEditor(QWidget* parent, Qt::WindowFlags fl)
    : QDialog(parent, fl)
{
    setupUi(this);

    this->dBarcode = new DBarcodeConfig(this);
    this->dBarcode->setVisible(true);

    this->dMatrixRect = new DMatrixRectConfig(this);
    this->dMatrixRect->setVisible(false);

    this->dMatrixSquare = new DMatrixSquareConfig(this);
    this->dMatrixSquare->setVisible(false);

    this->cbFormat_ViewConfig(0);
    // signals and slots connections
    connect(cbFormat,       SIGNAL(activated(int)),     this,               SLOT(cbFormat_activated(int)));
    connect(cbFormat,       SIGNAL(activated(int)),     this,               SLOT(cbFormat_ViewConfig(int)));
//    connect(sliderMaxVal,   SIGNAL(valueChanged(int)),  labelMaxVal,    SLOT(setNum(int)));
//    connect(sliderMaxVal,   SIGNAL(sliderMoved(int)),   this,           SLOT(sliderMaxVal_sliderMoved(int)));
    connect(buttonOk,       SIGNAL(clicked()),          this,               SLOT(accept()));
    connect(buttonCancel,   SIGNAL(clicked()),          this,               SLOT(reject()));

    connect(buttonOk,       SIGNAL(clicked()),          this->dMatrixRect,  SLOT(setVisible2()));
    connect(buttonCancel,   SIGNAL(clicked()),          this->dMatrixRect,  SLOT(setVisible2()));
    connect(buttonCancel,   SIGNAL(clicked()),          this->dMatrixSquare,SLOT(setVisible2()));
    connect(buttonOk,       SIGNAL(clicked()),          this->dMatrixSquare,SLOT(setVisible2()));

    leXPos->setValidator(new QDoubleValidator(0.0,100.0,3,leXPos));
    leYPos->setValidator(new QDoubleValidator(0.0,100.0,3,leYPos));
    
    leWidth->setValidator(new QDoubleValidator(0.01,100.0,3,leWidth));
    leHeight->setValidator(new QDoubleValidator(0.01,100.0,3,leHeight));
    leNarrowBarWidth->setValidator(new QDoubleValidator(0.005,0.1,3,leNarrowBarWidth));
}

BarcodeEditor::~BarcodeEditor()
{
    // no need to delete child widgets, Qt does it all for us
    delete this->dBarcode;
    delete this->dMatrixRect;
    delete this->dMatrixSquare;
}

void BarcodeEditor::languageChange()
{
    retranslateUi(this);
}

void BarcodeEditor::cbFormat_activated(int)
{
    // the format was changed so we need to recalculate our minimum sizes
}

void BarcodeEditor::sliderMaxVal_sliderMoved( int )
{
    // the slider for the max value length has been changed so we need to recalculate the minimum sizes
}

QString BarcodeEditor::format()
{
    //the alignement is Center
    QString qsAlign = "_C";

    if(this->rbAlignLeft->isChecked())
    {
        qsAlign = "_L";
    }
    if(this->rbAlignRight->isChecked())
    {
        qsAlign = "_R";
    }


    if(!this->cbFormat->currentText().contains("Datamatrix"))
    {
        return this->cbFormat->currentText();
    }
    else if(this->cbFormat->currentIndex() == 7 /*square*/)
    {
        return this->dMatrixSquare->format() + qsAlign;
    }
    else // then it's a rectangular datamatrix
    {
        return this->dMatrixRect->format() + qsAlign;
    }
}

void BarcodeEditor::cbFormat_ViewConfig(int i)
{
    switch(i)
    {
    case 7:
        this->leNarrowBarWidth->setVisible(false);
        this->lnarrowBar->setVisible(false);

        this->_princpalLayout->insertWidget(1,this->dMatrixSquare);
        this->dMatrixSquare->setVisible(true);
        this->dMatrixRect->setVisible2(false);
        this->dBarcode->setVisible(false);
        break;
    case 8:
        this->leNarrowBarWidth->setVisible(false);
        this->lnarrowBar->setVisible(false);

        this->_princpalLayout->insertWidget(1,this->dMatrixRect);
        this->dMatrixSquare->setVisible2(false);
        this->dMatrixRect->setVisible(true);
        this->dBarcode->setVisible(false);
        break;
    default:
        this->leNarrowBarWidth->setVisible(true);
        this->lnarrowBar->setVisible(true);

        this->_princpalLayout->insertWidget(1,this->dBarcode);
        this->dMatrixSquare->setVisible2(false);
        this->dMatrixRect->setVisible2(false);
        this->dBarcode->setVisible(true);
        break;
    }
}

int BarcodeEditor::getCBSlideMaxValue()
{
    return this->dBarcode->getSliderMaxValue();
}

void BarcodeEditor::setCBSliderMaxValue(int value)
{
    this->dBarcode->setSliderMaxValue(value);
}

void BarcodeEditor::closeEvent(QCloseEvent *)
{
    this->dMatrixRect->setVisible2(false);
    this->dMatrixSquare->setVisible2(false);
    this->dMatrixRect->close();
    this->dMatrixSquare->close();
}

void BarcodeEditor::setDatamatrixEditor(QString format)
{
    QRegExp regex("[a-zA-Z]{10}_([0-9]{1,2})_([LCR]{1})");
    regex.indexIn(format);
    int value = regex.cap(1).toInt();
    QString align = regex.cap(2);

    if(value <24)
    {
        //this->cbFormat->setCurrentIndex(this->cbFormat->findText(tr("Datamatrix square")));
        this->cbFormat->setCurrentIndex(7 /*square Datamatrix*/);
        this->dMatrixSquare->setCursorValue(value);
        this->cbFormat_ViewConfig(7);
    }
    else
    {
        //this->cbFormat->setCurrentIndex(this->cbFormat->findText(tr("Datamatrix rectangle")));
        this->cbFormat->setCurrentIndex(8 /*rectangle Datamatrix*/);
        this->dMatrixRect->setIndexValue(value - 24);
        this->cbFormat_ViewConfig(8);
    }

    if(align == "L")
        this->rbAlignLeft->setChecked(true);
    if(align == "C")
        this->rbAlignCenter->setChecked(true);
    if(align == "R")
        this->rbAlignRight->setChecked(true);
}
