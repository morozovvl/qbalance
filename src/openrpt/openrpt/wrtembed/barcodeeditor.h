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

#ifndef BARCODEEDITOR_H
#define BARCODEEDITOR_H

#include <QDialog>
#include <QGridLayout>
#include <QString>

#include "ui_barcodeeditor.h"

#include "dbarcodeconfig.h"
#include "dmatrixrectconfig.h"
#include "dmatrixsquareconfig.h"

class BarcodeEditor : public QDialog, public Ui::BarcodeEditor
{
    Q_OBJECT

public:
    BarcodeEditor(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~BarcodeEditor();

    QString format();
    void setCBSliderMaxValue(int value);
    int getCBSlideMaxValue();

    void setDatamatrixEditor(QString format);

public slots:
    virtual void cbFormat_activated(int);
    virtual void sliderMaxVal_sliderMoved(int);
    void cbFormat_ViewConfig(int);

protected slots:
    virtual void languageChange();

protected:
    void closeEvent(QCloseEvent *);

private:
    DMatrixSquareConfig* dMatrixSquare;
    DMatrixRectConfig* dMatrixRect;
    DBarcodeConfig* dBarcode;
};

#endif // BARCODEEDITOR_H
