/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Script Generator project on Qt Labs.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

function tr(s) { return s; }


function ImageComposer(parent)
{
    QWidget.call(this, parent);

    this.sourceButton = new QToolButton();
    this.sourceButton.setIconSize(ImageComposer.resultSize);

    this.operatorComboBox = new QComboBox();
    this.addOp(QPainter.CompositionMode_SourceOver, tr("SourceOver"));
    this.addOp(QPainter.CompositionMode_DestinationOver, tr("DestinationOver"));
    this.addOp(QPainter.CompositionMode_Clear, tr("Clear"));
    this.addOp(QPainter.CompositionMode_Source, tr("Source"));
    this.addOp(QPainter.CompositionMode_Destination, tr("Destination"));
    this.addOp(QPainter.CompositionMode_SourceIn, tr("SourceIn"));
    this.addOp(QPainter.CompositionMode_DestinationIn, tr("DestinationIn"));
    this.addOp(QPainter.CompositionMode_SourceOut, tr("SourceOut"));
    this.addOp(QPainter.CompositionMode_DestinationOut, tr("DestinationOut"));
    this.addOp(QPainter.CompositionMode_SourceAtop, tr("SourceAtop"));
    this.addOp(QPainter.CompositionMode_DestinationAtop, tr("DestinationAtop"));
    this.addOp(QPainter.CompositionMode_Xor, tr("Xor"));

    this.destinationButton = new QToolButton();
    this.destinationButton.setIconSize(ImageComposer.resultSize);

    this.equalLabel = new QLabel(tr("="));

    this.resultLabel = new QLabel();
    this.resultLabel.minimumWidth = ImageComposer.resultSize.width();

    this.sourceButton["clicked()"].connect(this, this.chooseSource);
    this.operatorComboBox["activated(int)"].connect(
            this, this.recalculateResult);
    this.destinationButton["clicked()"].connect(
            this, this.chooseDestination);

    var mainLayout = new QGridLayout();
    mainLayout.addWidget(this.sourceButton, 0, 0, 3, 1);
    mainLayout.addWidget(this.operatorComboBox, 1, 1);
    mainLayout.addWidget(this.destinationButton, 0, 2, 3, 1);
    mainLayout.addWidget(this.equalLabel, 1, 3);
    mainLayout.addWidget(this.resultLabel, 0, 4, 3, 1);
    mainLayout.sizeConstraint = QLayout.SetFixedSize;
    this.setLayout(mainLayout);

    this.sourceImage = new QImage();
    this.destinationImage = new QImage();
    this.resultImage = new QImage(ImageComposer.resultSize, QImage.Format_ARGB32_Premultiplied);

    this.loadImage("images/butterfly.png", "sourceImage", this.sourceButton);
    this.loadImage("images/checker.png", "destinationImage", this.destinationButton);

    this.windowTitle = tr("Image Composition");
}

ImageComposer.resultSize = new QSize(200, 200);

ImageComposer.prototype = new QWidget();

ImageComposer.prototype.chooseSource = function()
{
    this.chooseImage(tr("Choose Source Image"), "sourceImage", this.sourceButton);
}

ImageComposer.prototype.chooseDestination = function()
{
    this.chooseImage(tr("Choose Destination Image"), "destinationImage", this.destinationButton);
}

ImageComposer.prototype.recalculateResult = function()
{
    var mode = this.currentMode();

    var painter = new QPainter(this.resultImage);
    painter.setCompositionMode(QPainter.CompositionMode_Source);
    painter.fillRect(this.resultImage.rect(), new QBrush(new QColor(Qt.transparent)));
    painter.setCompositionMode(QPainter.CompositionMode_SourceOver);
    painter.drawImage(0, 0, this.destinationImage);
    painter.setCompositionMode(mode);
    painter.drawImage(0, 0, this.sourceImage);
    painter.setCompositionMode(QPainter.CompositionMode_DestinationOver);
    painter.fillRect(this.resultImage.rect(), new QBrush(new QColor(Qt.white)));
    painter.end();

    this.resultLabel.setPixmap(QPixmap.fromImage(this.resultImage));
}

ImageComposer.prototype.addOp = function(mode, name)
{
    this.operatorComboBox.addItem(name, mode);
}

ImageComposer.prototype.chooseImage = function(title, property, button)
{
    var fileName = QFileDialog.getOpenFileName(this, title);
    if (!fileName.isEmpty())
        loadImage(fileName, property, button);
}

ImageComposer.prototype.loadImage = function(fileName, property, button)
{
    var image = new QImage(fileName);

    var fixedImage = new QImage(ImageComposer.resultSize, QImage.Format_ARGB32_Premultiplied);
    var painter = new QPainter(fixedImage);
    painter.setCompositionMode(QPainter.CompositionMode_Source);
    painter.fillRect(fixedImage.rect(), new QBrush(new QColor(Qt.transparent)));
    painter.setCompositionMode(QPainter.CompositionMode_SourceOver);
    painter.drawImage(this.imagePos(image), image);
    painter.end();
    button.icon = new QIcon(QPixmap.fromImage(fixedImage));

    this[property] = fixedImage;

    this.recalculateResult();
}

ImageComposer.prototype.currentMode = function()
{
    return this.operatorComboBox.itemData(this.operatorComboBox.currentIndex);
}

ImageComposer.prototype.imagePos = function(image)
{
    return new QPoint((ImageComposer.resultSize.width() - image.width()) / 2,
                      (ImageComposer.resultSize.height() - image.height()) / 2);
}

var composer = new ImageComposer();
composer.show();
QCoreApplication.exec();
