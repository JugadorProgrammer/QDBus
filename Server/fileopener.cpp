#include "fileopener.h"
#include <QUrl>
#include <QFileInfo>

FileOpener::FileOpener(QObject *parent) : QObject(parent){}

void FileOpener::openFile(const QString &filePath)
{
    auto fileInfo = QFileInfo(filePath);
    if (!fileInfo.exists())
    {
        qWarning("File does not exist.");
        return;
    }

    qInfo() << "Path to file: " << filePath;
    auto qProcess = QProcess();

    if (!qProcess.startDetached(this->_command, QStringList() << filePath))
    {
        qFatal("The process cannot be started!");
        return;
    }

    QObject::connect(&qProcess, &QProcess::readyReadStandardOutput, [&]() {
        QByteArray output = qProcess.readAllStandardOutput();
        qInfo() << "Process output: " << output;
    });

    QObject::connect(&qProcess, &QProcess::readAllStandardError, [&]() {
        QByteArray output = qProcess.readAllStandardError();
        qFatal("Process error: ");
        qFatal(output);
    });

    qProcess.waitForFinished();
}
