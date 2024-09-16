#include "fileopener.h"

FileOpener::FileOpener(QObject *parent) : QObject(parent)
{
    _applications =
    {
        {"txt","kate"},
        {"cpp","qtcreator"},
        {"hpp","qtcreator"},
        {"c","qtcreator"},
        {"h","qtcreator"},
        {"asm","qtcreator"},
        {"png","gwenview"},
        {"jpg","gwenview"},
        {"pdf","kate"},
        {"docx","onlyoffice-desktopeditors"},
        {"csv","onlyoffice-desktopeditors"},
        {"djvu","okular"},
        {"md","code"},
        {"cs","code"}
    };
}

void FileOpener::openFile(const QString &filePath)
{
    auto fileInfo = QFileInfo(filePath);
    if (!fileInfo.exists())
    {
        qWarning("File does not exist.");
        return;
    }

    auto extention = fileInfo.suffix();
    qInfo() << "File extension: " << filePath;
    if(!_applications.contains(extention))
    {
        qWarning("Application does not found.");
        return;
    }

    auto application = _applications[extention];

    auto qProcess = QProcess();
    if (!qProcess.startDetached(application, QStringList() << filePath))
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

    qProcess.waitForFinished();// /usr/share/mime/packages/freedesktop.org.xml
}
