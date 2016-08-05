#ifndef BILIBILICRAWLER_H
#define BILIBILICRAWLER_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QStringList>
#include <QDateTime>
#define HTMLPAGE 0
#define INFOPAGE 1

namespace Ui {
class bilibiliCrawler;
}

class bilibiliCrawler : public QWidget
{
    Q_OBJECT

public:
    explicit bilibiliCrawler(QWidget *parent = 0);
    ~bilibiliCrawler();
public slots:
    void getID(QNetworkReply*);
    void getInfo(QNetworkReply*);

private slots:
    void on_goButton_clicked();

private:
    Ui::bilibiliCrawler *ui;
    QNetworkAccessManager *manager;
    void getSign(QStringList arg, QString appkey);
    QString interface = "http://interface.bilibili.com/player?";
    QString clickInfo = QString();
    QString aid = QString();
    QString cid = QString();
    int mode = HTMLPAGE;
    QString *content;
    QString appkey = "8e9fc618fbd41e28";
};

#endif // BILIBILICRAWLER_H
