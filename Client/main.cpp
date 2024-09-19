#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusError>
#include <QDebug>

bool tryConnectToBus(const QString& filePath)
{
    // Создание сообщения для вызова метода sayHello
    auto message = QDBusMessage::createMethodCall("org.freedesktop.FileOpener",
                                                          "/FileOpener", //path
                                                          "local.Server.FileOpener", //interface
                                                          "openFile");
    message << filePath;

    // Отправка сообщения и получение ответа
    auto reply = QDBusConnection::sessionBus().call(message);

    if (reply.type() == QDBusMessage::ErrorMessage)
    {
        qInfo() << "Error:" << reply.errorMessage();
        return false;
    }

    QString response = "";

    for(const auto& argument : reply.arguments())
    {
        response += argument.toString();
    }

    qInfo() << "Response: " << response;
    return true;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QString filePath;
    QTextStream input(stdin);

    do
    {
        qInfo() << "Введите путь до файла: ";
        input >> filePath;
    }
    while(tryConnectToBus(filePath));

    return app.exec();
}
