#ifndef FILEOPENER_H
#define FILEOPENER_H

#include <QObject>
#include <QProcess>
#include <QString>

class FileOpener : public QObject
{
    Q_OBJECT
public:
    FileOpener(QObject *parent = nullptr);

public slots:
    void openFile(const QString &filePath);

private:
    const QString _command = "xdg-open";
};

#endif // FILEOPENER_H
