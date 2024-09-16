#include <QCoreApplication>
#include "fileopener.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    auto fileOpener = FileOpener();

    if(!QDBusConnection::sessionBus().registerService("com.example.FileOpener"))
    {
        qFatal("Failed to register service");
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
