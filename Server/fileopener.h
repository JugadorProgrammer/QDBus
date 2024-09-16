#ifndef FILEOPENER_H
#define FILEOPENER_H

#include <QObject>
#include <QProcess>
#include <QString>
#include <QMap>
#include <QUrl>
#include <QFileInfo>
#include <QDebug>
#include <QDBusMessage>
#include <QDBusConnection>

class FileOpener : public QObject
{
    Q_OBJECT
public:
    FileOpener(QObject *parent = nullptr);

public slots:
    void openFile(const QString &filePath);

private:
    void sendResponse(const QString& responce);
    QString getExtansions();
    QMap<QString, QString> _applications;
};

#endif // FILEOPENER_H
