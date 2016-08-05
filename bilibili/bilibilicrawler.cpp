#include "bilibilicrawler.h"
#include "ui_bilibilicrawler.h"
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QRegExp>
#include <QDebug>
//#include <QStringList>

bilibiliCrawler::bilibiliCrawler(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bilibiliCrawler)
{
    ui->setupUi(this);
    content = new QString();
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getID(QNetworkReply*)));
    //    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(query(QNetworkReply*)));
}

bilibiliCrawler::~bilibiliCrawler()
{
    delete ui;
}

void bilibiliCrawler::getID(QNetworkReply *reply) {
    //    ui->textBrowser->setText("get");
    QString buffer = reply->readAll();
    int pos;
//    qDebug() << mode;
//    qDebug() << clickInfo;
//    QRegExp exp("cid=[0-9]+\\&aid=[0-9]+");
//    int pos = exp.indexIn(buffer);
//    QStringList list = exp.capturedTexts();
//    qDebug() << list.at(0);
//    ui->textBrowser->setText(list.at(0));
//    clickInfo = interface.append(list.at(0));
    qDebug() << clickInfo;
    if (mode == HTMLPAGE) {
        QRegExp exp("cid=[0-9]+\\&aid=[0-9]+");
        pos = exp.indexIn(buffer);
        QStringList list = exp.capturedTexts();
        qDebug() << list.at(0);
//        ui->textBrowser->setText(list.at(0));
        content->append(list.at(0)+"\n");
        clickInfo = interface.append(list.at(0));

        //get cid
        exp.setPattern("cid=[0-9]+");
        pos = exp.indexIn(buffer);
        list = exp.capturedTexts();
        qDebug() << list.at(0);
        cid = list.at(0);
        qDebug() << "cid="<< cid;

        // get aid
        exp.setPattern("aid=[0-9]+");
        pos = exp.indexIn(buffer);
        list = exp.capturedTexts();
        qDebug() << list.at(0);
        aid = list.at(0).mid(1);
        qDebug() << "aid="<< aid;


        QNetworkRequest *req = new QNetworkRequest(QUrl(clickInfo));
        req->setRawHeader("User-Agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.103 Safari/537.36");
        req->setAttribute(QNetworkRequest::FollowRedirectsAttribute, QVariant(true));
        manager->get(*req);
        mode = INFOPAGE;
    } else {
        QRegExp exp("<click>[0-9]+");
        pos = exp.indexIn(buffer);
        QStringList list = exp.capturedTexts();
        qDebug() << list.at(0).mid(QString("<click>").size());
        content->append("click: "+list.at(0).mid(QString("<click>").size())+"\n");
        exp.setPattern("<coins>[0-9]+");
        pos = exp.indexIn(buffer);
        list = exp.capturedTexts();
        qDebug() << list.at(0).mid(QString("<coins>").size());
        content->append("coins: "+list.at(0).mid(QString("<coins>").size())+"\n");
        exp.setPattern("<favourites>[0-9]+");
        pos = exp.indexIn(buffer);
        list = exp.capturedTexts();
        qDebug() << list.at(0).mid(QString("<favourites>").size());
        content->append("favourites: "+list.at(0).mid(QString("<favourites>").size())+"\n");

        QStringList parms;
        QString ts = "ts="+QString::number(QDateTime::currentMSecsSinceEpoch()/1000);

        parms << "accel=1" << cid << "player=1" << ts;
//        parms.pop_front();
        getSign(parms, appkey);
        mode = HTMLPAGE;
    }

    ui->textBrowser->setText(*content);


    //    else if (mode == INFOPAGE) {
    //        qDebug() << (mode == INFOPAGE);
    //        QRegExp exp("<click>[0-9]+");
    //        ui->textBrowser->setText(buffer);
    //    }
    //    buffer.append(list.at(0));

//        QNetworkRequest *req = new QNetworkRequest(QUrl(clickInfo));
//        req->setRawHeader("User-Agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.103 Safari/537.36");
//        req->setAttribute(QNetworkRequest::FollowRedirectsAttribute, QVariant(true));
//        manager->get(*req);

}

void bilibiliCrawler::getInfo(QNetworkReply *reply) {
    QString buffer = reply->readAll();
    ui->textBrowser->setText(buffer);
}

void bilibiliCrawler::getSign(QStringList arg, QString appkey) {
    qStableSort(arg);
    qDebug() << arg;
    QString par = QString();
    QString playurl = "http://interface.bilibili.com/playurl?";
    for(int i = 0; i < arg.size(); i++) {
        par.append(/*QString::number(i)+"="+*/QUrl::toPercentEncoding(arg.at(i), "", "=")+(i < arg.size()-1 ?"&":""));
//        QUrl::toPercentEncoding(arg.at(i), "", "=");
        playurl.append(arg.at(i)+(i < arg.size()-1 ?"&":""));
    }
//    QUrl url(par);
    QByteArray str;
    str.append(par+appkey);
    QString sign = QString(QCryptographicHash::hash(str, QCryptographicHash::Md5).toHex());
    qDebug() << par;
    qDebug() << sign;
    playurl.append("&sign="+sign);
    content->append(sign + "\n");

//    qDebug() << QCryptographicHash::hash(str, QCryptographicHash::Md5).toHex();
//    qDebug() << QUrl::toPercentEncoding(par, "", "=");

    QDateTime local(QDateTime::currentDateTime());
    QDateTime UTC(local.toUTC());
    qDebug() << "Local time is:" << local;
    qDebug() << "UTC time is:" << UTC;
    qDebug() << "No difference between times:" << local.secsTo(UTC);
    qDebug() << QDateTime::currentMSecsSinceEpoch()/1000;
    content->append(playurl);
//    QString playurl = "http://interface.bilibili.com/playurl?";
}



void bilibiliCrawler::on_goButton_clicked() {
    QString input = ui->lineEdit->text();
    QString baseurl = "http://www.bilibili.com/video/";
    baseurl.append(input);
//    ui->textBrowser->setPlainText(baseurl);
    content->append(baseurl+"\n");
    //    manager->get(QNetworkRequest(QUrl(baseurl)));
    QNetworkRequest *req = new QNetworkRequest(QUrl(baseurl));
    req->setRawHeader("User-Agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.103 Safari/537.36");
    //    ui->textBrowser->setPlainText(*req->KnownHeaders);
    req->setAttribute(QNetworkRequest::FollowRedirectsAttribute, QVariant(true));
    qDebug() << baseurl;
    qDebug() << req->rawHeaderList();
    qDebug() << mode;
    mode = HTMLPAGE;
    manager->get(*req);
    qDebug() << clickInfo;
//    if (mode == HTMLPAGE) {
//        manager->get(*req);
//        //         mode = INFOPAGE;
//    } else if (mode == INFOPAGE) {
//        qDebug() << clickInfo;
//    }
}
