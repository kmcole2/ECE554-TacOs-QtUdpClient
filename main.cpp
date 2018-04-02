#include "udpclient.h"
#include <QApplication>
#include <QLabel>
#include <QGridLayout>
#include <QDialog>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    UdpClient *client = new UdpClient;
    client->show();
    return app.exec();
}
