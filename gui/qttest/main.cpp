#include "mainwindow.h"
#include <QTextStream>
#include <cstdio>
#include <QDebug>
#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

void request() {
    QNetworkAccessManager* manage = new QNetworkAccessManager();
    QNetworkReply* reply = manage->get(QNetworkRequest(QUrl("http://www.google.com")));
    QByteArray data = reply->readAll();
    QString str(data);

    QTextStream qerr(stderr);
    qerr << "+++++ start ++++++\n";
    qerr << str;
    qerr << "\n+++++ end +++++";
}

int main(int argc, char *argv[])
{
    request();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
