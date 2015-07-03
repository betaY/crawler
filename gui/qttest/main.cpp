#include "mainwindow.h"
#include <QTextStream>
#include <cstdio>
#include <QDebug>
#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

//void request() {
//    QNetworkAccessManager* manage = new QNetworkAccessManager();
//    QNetworkReply* response = manage->get(QNetworkRequest(QUrl("http://www.google.com")));
//    QByteArray data = reply->readAll();
//    QString str(data);

//    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
//    event.exec();
//    QString html = response->readAll();

//    QTextStream qerr(stderr);
//    qerr << "+++++ start ++++++\n";
//    qerr << html;
//    qerr << "\n+++++ end +++++";
//}

int main(int argc, char *argv[])
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
//    QNetworkReply* response = manage->get(QNetworkRequest(QUrl("http://www.google.com")));
//    connect(manager, SIGNAL(finished(response)), this, SLOT(replyFinished(response)));
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl("http://www.google.com")));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
