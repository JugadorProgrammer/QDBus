#include <QCoreApplication>
#include "fileopener.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qInfo() << argc;
    qInfo() << argv;
    auto fileOpener = FileOpener();

    if(!QDBusConnection::sessionBus().registerService("org.freedesktop.FileOpener"))
    {
        qInfo() << "Failed to register service: " << QDBusConnection::sessionBus().lastError().message();
    }
    else if (!QDBusConnection::sessionBus().registerObject("/FileOpener", &fileOpener, QDBusConnection::ExportAllSlots))
    {
        qFatal("Failed to register object");
    }
    else
    {
        qInfo() << "Opener is started!";
    }

    return a.exec();
}
