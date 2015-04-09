/****************************************************************************
**
** Copyright (C) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Script Generator project on Qt Labs.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

function tr(s) { return s; }


// PiecesList

function PiecesList(pieceSize, parent)
{
    QListWidget.call(this, parent);
    this.mainWindow = parent;
    this.pieceSize = pieceSize;
    this.dragEnabled = true;
    this.viewMode = QListView.IconMode;
    this.iconSize = new QSize(pieceSize, pieceSize);
    this.spacing = 10;
    this.acceptDrops = true;
    this.showDropIndicator = true;
}

PiecesList.prototype = new QListWidget();

PiecesList.prototype.dragEnterEvent = function(event)
{
    if (event.mimeData().hasFormat("image/x-puzzle-piece"))
        event.accept(null);
    else
        event.ignore(null);
}

PiecesList.prototype.dragMoveEvent = function(event)
{
    if (event.mimeData().hasFormat("image/x-puzzle-piece")) {
        event.setDropAction(Qt.MoveAction);
        event.accept(null);
    } else {
        event.ignore(null);
    }
}

PiecesList.prototype.dropEvent = function(event)
{
    if (event.mimeData().hasFormat("image/x-puzzle-piece")) {
//        var pieceData = event.mimeData().data("image/x-puzzle-piece");
//        var dataStream = new QDataStream(pieceData, QIODevice.ReadOnly);
        var pixmap = this.mainWindow.currentPixmap;
        var location = this.mainWindow.currentLocation;

//        dataStream >> pixmap >> location;

        this.addPiece(this.pixmap, this.location);

        event.setDropAction(Qt.MoveAction);
        event.accept();
    } else {
        event.ignore();
    }
}

PiecesList.prototype.addPiece = function(pixmap, location)
{
    var pieceItem = new QListWidgetItem(this);
    pieceItem.setIcon(new QIcon(pixmap));
    pieceItem.setData(Qt.UserRole, pixmap);
    pieceItem.setData(Qt.UserRole+1, location);
    pieceItem.setFlags(Qt.ItemFlags(Qt.ItemIsEnabled | Qt.ItemIsSelectable | Qt.ItemIsDragEnabled));
}

PiecesList.prototype.startDrag = function(supportedActions)
{
    var item = this.currentItem();

    var itemData = new QByteArray;

//    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    var pixmap = item.data(Qt.UserRole);
    var location = item.data(Qt.UserRole+1);

//    dataStream << pixmap << location;
    this.mainWindow.currentPixmap = pixmap;
    this.mainWindow.currentLocation = location;

    var mimeData = new QMimeData;
    mimeData.setData("image/x-puzzle-piece", itemData);

    var drag = new QDrag(this);
    drag.setMimeData(mimeData);
    drag.setHotSpot(new QPoint(pixmap.width()/2, pixmap.height()/2));
    drag.setPixmap(pixmap);

    if (drag.exec(Qt.MoveAction) == Qt.MoveAction)
        this.takeItem(this.row(item));
}

// PuzzleWidget

function PuzzleWidget(imageSize, parent)
{
    QWidget.call(this, parent);
    this.imageSize = imageSize;
    this.mainWindow = parent;
    this.acceptDrops = true;
    this.minimumSize = new QSize(imageSize, imageSize);
    this.maximumSize = new QSize(imageSize, imageSize);
}

PuzzleWidget.prototype.clear = function()
{
    this.pieceLocations = [];
    this.piecePixmaps = [];
    this.pieceRects = [];
    this.highlightedRect = new QRect();
    this.inPlace = 0;
    this.update();
}

PuzzleWidget.prototype.dragEnterEvent = function(event)
{
    if (event.mimeData().hasFormat("image/x-puzzle-piece"))
        event.accept(null);
    else
        event.ignore(null);
}

PuzzleWidget.prototype.dragLeaveEvent = function(event)
{
    var updateRect = this.highlightedRect;
    this.highlightedRect = new QRect();
    this.update(updateRect);
    event.accept();
}

PuzzleWidget.prototype.dragMoveEvent = function(event)
{
    var updateRect = this.highlightedRect.united(this.targetSquare(event.pos()));

    if (event.mimeData().hasFormat("image/x-puzzle-piece")
        && this.findPiece(this.targetSquare(event.pos())) == -1) {

        this.highlightedRect = this.targetSquare(event.pos());
        event.setDropAction(Qt.MoveAction);
        event.accept(null);
    } else {
        this.highlightedRect = new QRect();
        event.ignore(null);
    }

    this.update(updateRect);
}

PuzzleWidget.prototype.dropEvent = function(event)
{
    if (event.mimeData().hasFormat("image/x-puzzle-piece")
        && this.findPiece(this.targetSquare(event.pos())) == -1) {

//        var pieceData = event.mimeData().data("image/x-puzzle-piece");
//        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        var square = this.targetSquare(event.pos());
        var pixmap = this.mainWindow.currentPixmap;
        var location = this.mainWindow.currentLocation;
//        dataStream >> pixmap >> location;

        this.pieceLocations.push(location);
        this.piecePixmaps.push(pixmap);
        this.pieceRects.push(square);

        this.highlightedRect = new QRect();
        this.update(square);

        event.setDropAction(Qt.MoveAction);
        event.accept();

        if (location.equals(new QPoint(Math.floor(square.x()/this.pieceSize()), Math.floor(square.y()/this.pieceSize())))) {
            this.inPlace++;
            if (this.inPlace == 25)
                this.mainWindow.setCompleted();
        }
    } else {
        this.highlightedRect = new QRect();
        event.ignore();
    }
}

PuzzleWidget.prototype.findPiece = function(pieceRect)
{
    for (var i = 0; i < this.pieceRects.length; ++i) {
        if (pieceRect.equals(this.pieceRects[i]))
            return i;
    }
    return -1;
}

PuzzleWidget.prototype.mousePressEvent = function(event)
{
    var square = this.targetSquare(event.pos());
    var found = this.findPiece(square);

    if (found == -1)
        return;

    var location = this.pieceLocations[found];
    var pixmap = this.piecePixmaps[found];
    this.pieceLocations.splice(found, 1);
    this.piecePixmaps.splice(found, 1);
    this.pieceRects.splice(found, 1);

    if (location.equals(new QPoint(Math.floor(square.x()/this.pieceSize()), Math.floor(square.y()/this.pieceSize()))))
        this.inPlace--;

    this.update(square);

    var itemData = new QByteArray;
//    QDataStream dataStream(&itemData, QIODevice::WriteOnly);

//    dataStream << pixmap << location;
    this.mainWindow.currentPixmap = pixmap;
    this.mainWindow.currentLocation = location;

    var mimeData = new QMimeData;
    mimeData.setData("image/x-puzzle-piece", itemData);

    var drag = new QDrag(this);
    drag.setMimeData(mimeData);
    drag.setHotSpot(event.pos().operator_subtract_assign(square.topLeft()));
    drag.setPixmap(pixmap);

    if (!(drag.exec(Qt.MoveAction) == Qt.MoveAction)) {
        this.pieceLocations.splice(found, 0, location);
        this.piecePixmaps.splice(found, 0, pixmap);
        this.pieceRects.splice(found, 0, square);
        this.update(this.targetSquare(event.pos()));

        if (location.equals(new QPoint(Math.floor(square.x()/this.pieceSize()), Math.floor(square.y()/this.pieceSize()))))
            this.inPlace++;
    }
}

PuzzleWidget.prototype.paintEvent = function(event)
{
    var painter = new QPainter;
    painter.begin(this);
    painter.fillRect(event.rect(), Qt.white);

    if (this.highlightedRect.isValid()) {
        painter.setBrush(new QBrush(new QColor("#ffcccc")));
        painter.setPen(new QPen(Qt.NoPen));
        painter.drawRect(this.highlightedRect.adjusted(0, 0, -1, -1));
    }

    for (var i = 0; i < this.pieceRects.length; ++i)
        painter.drawPixmap(this.pieceRects[i], this.piecePixmaps[i]);
    painter.end();
}

PuzzleWidget.prototype.targetSquare = function(position)
{
    return new QRect(Math.floor(position.x()/this.pieceSize()) * this.pieceSize(), Math.floor(position.y()/this.pieceSize()) * this.pieceSize(), this.pieceSize(), this.pieceSize());
}

PuzzleWidget.prototype.pieceSize = function()
{
    return this.imageSize / 5;
}

// MainWindow

function MainWindow(parent)
{
    QMainWindow.call(this, parent);

    this.setupMenus();
    this.setupWidgets();

    this.sizePolicy = new QSizePolicy(QSizePolicy.Fixed, QSizePolicy.Fixed)
    this.windowTitle = tr("Puzzle");
}

MainWindow.prototype = new QMainWindow()

MainWindow.prototype.openImage = function(fileName)
{
    if (!fileName) {
        fileName = QFileDialog.getOpenFileName(this,
            tr("Open Image"), "", "Image Files (*.png *.jpg *.bmp)");
    }

    if (fileName != "") {
        var newImage = new QPixmap;
        if (!newImage.load(fileName)) {
            QMessageBox.warning(this, tr("Open Image"),
                                tr("The image file could not be loaded."),
                                QMessageBox.Cancel);
            return;
        }
        this.puzzleImage = newImage;
        this.setupPuzzle();
    }
}

MainWindow.prototype.setCompleted = function()
{
    QMessageBox.information(this, tr("Puzzle Completed"),
                            tr("Congratulations! You have completed the puzzle!\n" +
                               "Click OK to start again."),
                            QMessageBox.Ok);

    this.setupPuzzle();
}

MainWindow.prototype.setupPuzzle = function()
{
    var size = Math.min(this.puzzleImage.width(), this.puzzleImage.height());
    this.puzzleImage = this.puzzleImage.copy((this.puzzleImage.width() - size)/2,
        (this.puzzleImage.height() - size)/2, size, size).scaled(this.puzzleWidget.width,
            this.puzzleWidget.height, Qt.IgnoreAspectRatio, Qt.SmoothTransformation);

    this.piecesList.clear();

    for (var y = 0; y < 5; ++y) {
        for (var x = 0; x < 5; ++x) {
            var pieceSize = this.puzzleWidget.pieceSize();
            var pieceImage = this.puzzleImage.copy(x * pieceSize, y * pieceSize, pieceSize, pieceSize);
            this.piecesList.addPiece(pieceImage, new QPoint(x, y));
        }
    }

    for (var i = 0; i < this.piecesList.count; ++i) {
        if (Math.floor(2.0 * Math.random()) == 1) {
            var item = this.piecesList.takeItem(i);
            this.piecesList.insertItem(0, item);
        }
    }

    this.puzzleWidget.clear();
}

MainWindow.prototype.setupMenus = function()
{
    var fileMenu = this.menuBar().addMenu(tr("&File"));

    var openAction = fileMenu.addAction(tr("&Open..."));
    openAction.setShortcuts(QKeySequence.Open);

    var exitAction = fileMenu.addAction(tr("E&xit"));
    exitAction.setShortcuts(QKeySequence.Quit);

    var gameMenu = this.menuBar().addMenu(tr("&Game"));

    var restartAction = gameMenu.addAction(tr("&Restart"));

    openAction.triggered.connect(this, this.openImage);
    exitAction.triggered.connect(qApp, qApp.quit);
    restartAction.triggered.connect(this, this.setupPuzzle);
}

MainWindow.prototype.setupWidgets = function()
{
    var frame = new QFrame;
    var frameLayout = new QHBoxLayout(frame);
    this.puzzleWidget = new PuzzleWidget(400, this);

    this.piecesList = new PiecesList(this.puzzleWidget.pieceSize(), this);

    frameLayout.addWidget(this.piecesList, 0, 0);
    frameLayout.addWidget(this.puzzleWidget, 0, 0);
    this.setCentralWidget(frame);
}

var window = new MainWindow();
window.openImage("images/example.jpg");
window.show();

QCoreApplication.exec();
