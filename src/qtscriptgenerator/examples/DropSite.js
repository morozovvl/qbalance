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

function DropArea(dropSiteWindow, parent)
{
    QLabel.call(this, "", parent, Qt.Widget);
    this.dropSiteWindow = dropSiteWindow;
    this.minimumSize = new QSize(200, 200);
    this.setFrameStyle(QFrame.Sunken | QFrame.StyledPanel);
    this.alignment = Qt.AlignCenter;
    this.acceptDrops = true;
    this.autoFillBackground = true;
    this.clearArea();
}

DropArea.prototype = new QLabel();

DropArea.prototype.dragEnterEvent = function(event)
{
    this.text = tr("<drop content>");
    this.setBackgroundRole(QPalette.Highlight);
    event.acceptProposedAction();
    this.dropSiteWindow.updateFormatsTable(event.mimeData());
}

DropArea.prototype.dragMoveEvent = function(event)
{
    event.acceptProposedAction();
}

DropArea.prototype.dropEvent = function(event)
{
    var mimeData = event.mimeData();
    if (mimeData.hasImage()) {
        this.setPixmap(mimeData.imageData());
    } else if (mimeData.hasHtml()) {
        this.text = mimeData.html();
        this.textFormat = Qt.RichText;
    } else if (mimeData.hasText()) {
        this.text = mimeData.text();
        this.textFormat = Qt.PlainText;
    } else if (mimeData.hasUrls()) {
        var urlList = mimeData.urls();
        var text = new String;
        for (var i = 0; i < urlList.length && i < 32; ++i) {
            var url = urlList[i].path();
            text += url + "\n";
        }
        this.text = text;
    } else {
        this.text = tr("Cannot display data");
    }
    this.setBackgroundRole(QPalette.Dark);
    event.acceptProposedAction();
}

DropArea.prototype.dragLeaveEvent = function(event)
{
    this.clearArea();
    event.accept();
}

DropArea.prototype.clearArea = function()
{
    this.text = tr("<drop content>");
    this.setBackgroundRole(QPalette.Dark);
    this.dropSiteWindow.updateFormatsTable();
}

function DropSiteWindow(parent)
{
    QWidget.call(this, parent);

    this.abstractLabel = new QLabel(tr("This example accepts drags from other " +
                                       "applications and displays the MIME types " +
                                       "provided by the drag object."));
    this.abstractLabel.wordWrap = true;
    this.abstractLabel.adjustSize();

    this.formatsTable = new QTableWidget;
    this.formatsTable.columnCount = 2;
    this.formatsTable.editTriggers = QAbstractItemView.NoEditTriggers;
    this.formatsTable.setHorizontalHeaderLabels([tr("Format"), tr("Content")]);
    this.formatsTable.horizontalHeader().stretchLastSection = true;

    this.dropArea = new DropArea(this);

    this.clearButton = new QPushButton(tr("Clear"));
    this.quitButton = new QPushButton(tr("Quit"));

    this.buttonBox = new QDialogButtonBox;
    this.buttonBox.addButton(this.clearButton, QDialogButtonBox.ActionRole);
    this.buttonBox.addButton(this.quitButton, QDialogButtonBox.RejectRole);

    this.clearButton.pressed.connect(this.dropArea, this.dropArea.clearArea);
    this.quitButton.pressed.connect(this, this.close);

    var mainLayout = new QVBoxLayout;
    mainLayout.addWidget(this.abstractLabel, 0, 0);
    mainLayout.addWidget(this.dropArea, 0, 0);
    mainLayout.addWidget(this.formatsTable, 0, 0);
    mainLayout.addWidget(this.buttonBox, 0, 0);
    this.setLayout(mainLayout);

    this.windowTitle = tr("Drop Site");
    this.minimumSize = new QSize(350, 500);
}

DropSiteWindow.prototype = new QWidget();

DropSiteWindow.prototype.updateFormatsTable = function(mimeData)
{
    this.formatsTable.rowCount = 0;
    if (!mimeData)
        return;

    mimeData.formats().forEach(function(format) {
        var formatItem = new QTableWidgetItem(format);
        formatItem.setFlags(Qt.ItemIsEnabled);
        formatItem.setTextAlignment(Qt.AlignTop | Qt.AlignLeft);

        var text = new String;
        if (format == "text/plain") {
            text = mimeData.text().trim();
        } else if (format == "text/html") {
            text = mimeData.html().trim();
        } else if (format == "text/uri-list") {
            var urlList = mimeData.urls();
            for (var i = 0; i < urlList.length && i < 32; ++i)
                text += urlList[i].path() + " ";
        } else {
            var data = mimeData.data(format);
            for (var i = 0; i < data.size() && i < 32; ++i) {
                var hex = data.at(i).toString(16).toUpperCase();
                text += hex + " ";
            }
        }

        var row = this.formatsTable.rowCount;
        this.formatsTable.insertRow(row);
        this.formatsTable.setItem(row, 0, new QTableWidgetItem(format));
        this.formatsTable.setItem(row, 1, new QTableWidgetItem(text));

    }, this);

    this.formatsTable.resizeColumnToContents(0);
}

var window = new DropSiteWindow();
window.show();

QCoreApplication.exec();
