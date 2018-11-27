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

#include "generator.h"
#include "reporthandler.h"
#include "fileout.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>

Generator::Generator()
{
    m_num_generated = 0;
    m_num_generated_written = 0;
    m_out_dir = ".";
}

void Generator::generate()
{
    if (m_classes.size() == 0) {
        ReportHandler::warning(QString("%1: no java classes, skipping")
                               .arg(metaObject()->className()));
        return;
    }


    foreach (AbstractMetaClass *cls, m_classes) {
        if (!shouldGenerate(cls))
            continue;

        QString fileName = fileNameForClass(cls);
        ReportHandler::debugSparse(QString("generating: %1").arg(fileName));

        FileOut fileOut(outputDirectory() + "/" + subDirectoryForClass(cls) + "/" + fileName);
        write(fileOut.stream, cls);

        if( fileOut.done() )
            ++m_num_generated_written;
        ++m_num_generated;
    }
}


void Generator::printClasses()
{
    QTextStream s(stdout);

    AbstractMetaClassList classes = m_classes;
    qSort(classes);

    foreach (AbstractMetaClass *cls, classes) {
        if (!shouldGenerate(cls))
            continue;
        write(s, cls);
        s << endl << endl;
    }
}

void Generator::verifyDirectoryFor(const QFile &file)
{
    QDir dir = QFileInfo(file).dir();
    if (!dir.exists()) {
        if (!dir.mkpath(dir.absolutePath()))
            ReportHandler::warning(QString("unable to create directory '%1'")
                                   .arg(dir.absolutePath()));
    }
}

QString Generator::subDirectoryForClass(const AbstractMetaClass *) const
{
    Q_ASSERT(false);
    return QString();
}

QString Generator::fileNameForClass(const AbstractMetaClass *) const
{
    Q_ASSERT(false);
    return QString();
}

void Generator::write(QTextStream &, const AbstractMetaClass *)
{
    Q_ASSERT(false);
}

bool Generator::hasDefaultConstructor(const AbstractMetaType *type)
{
    QString full_name = type->typeEntry()->qualifiedTargetLangName();
    QString class_name = type->typeEntry()->targetLangName();

    foreach (const AbstractMetaClass *java_class, m_classes) {
        if (java_class->typeEntry()->qualifiedTargetLangName() == full_name) {
            AbstractMetaFunctionList functions = java_class->functions();
            foreach (const AbstractMetaFunction *function, functions) {
                if (function->arguments().size() == 0 && function->name() == class_name)
                    return true;
            }
            return false;
        }
    }
    return false;
}
