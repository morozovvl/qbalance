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

#include <QtCore/QCoreApplication>
#include <QtCore/QProcess>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtCore/QTextCodec>
#include <QtCore/QString>
#include <QtCore/QDebug>


bool  copyRecursively(const QString &srcFilePath, const QString &tgtFilePath)
{
    QFileInfo srcFileInfo(srcFilePath);
    if (QDir().exists(srcFilePath))
    {
        if (srcFileInfo.isDir())
        {
            QDir targetDir(tgtFilePath);
            targetDir.cdUp();
            if (!targetDir.mkpath(tgtFilePath))
                return false;
            QDir sourceDir(srcFilePath);
            QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
            foreach (const QString &fileName, fileNames)
            {
                const QString newSrcFilePath = srcFilePath + QLatin1Char('/') + fileName;
                const QString newTgtFilePath = tgtFilePath + QLatin1Char('/') + fileName;
                if (!copyRecursively(newSrcFilePath, newTgtFilePath))
                    return false;
            }
            QDir().rmdir(srcFilePath);
        }
        else
        {
            QFile srcFile(srcFilePath);
            if (srcFile.open(QIODevice::ReadOnly))
            {
                QFile tgtFile(tgtFilePath);
                if (tgtFile.open(QIODevice::WriteOnly))
                {
                    tgtFile.write(srcFile.readAll());
                    tgtFile.close();
                }
                srcFile.close();
                QFile::remove(srcFilePath);
            }
        }
    }
    return true;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
//    QTextCodec::setCodecForTr(codec);
//    QTextCodec::setCodecForCStrings(codec);
//    QTextCodec::setCodecForLocale(codec);
//    QLocale::setDefault(QLocale(QLocale::Russian, QLocale::RussianFederation));

//    TApplication application(argc, argv);

//    application.setOrganizationName("Enterprise");
//    application.setApplicationVersion(BUILD_NUMBER);

//#if QT_VERSION < 0x050000
//    QTextCodec::setCodecForTr(a.codec());
//    QTextCodec::setCodecForCStrings(a.codec());
//#endif
//    QTextCodec::setCodecForLocale(codec);



    QStringList args;
    for (int i = 1; i < argc; i++)
    {
        args.append(QString(argv[i]));
    }

    QString currentPath = QCoreApplication::applicationDirPath();

    copyRecursively(currentPath + "/updates", currentPath);

    QProcess process;
    process.setProcessChannelMode(QProcess::ForwardedChannels);
#if defined(Q_OS_LINUX)
    process.start(currentPath + "/qb_main", args);
#elif defined(Q_OS_WIN)
    process.start(currentPath + "/qb_main.exe", args);
#endif
    process.waitForFinished(-1);
}
