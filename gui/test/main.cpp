#include <cstdio>

#include <QCoreApplication>

#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkCookieJar>
#include <QNetworkCookie>

#include <QTextStream>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QNetworkRequest req(QUrl("http://www.pixiv.net/index.php?return_to=%2Fmypage.php"));
    req.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/43.0.2357.130 Safari/537.36");

    QNetworkAccessManager man;
//    QNetworkCookieJar *cookies = new QNetworkCookieJar();
//    cookies->insertCookie(QNetworkCookie("id", "227f9c4f9e0300a1||t=1414033339|et=730|cs=002213fd48d69442b24638839a"));
//    cookies->insertCookie(QNetworkCookie("login_ever", "yes"));
//    cookies->insertCookie(QNetworkCookie("module_orders_mypage    ", "%5B%7B%22name%22%3A%22everyone_new_illusts%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22spotlight%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22featured_tags%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22contests%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22following_new_illusts%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22mypixiv_new_illusts%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22booth_follow_items%22%2C%22visible%22%3Atrue%7D%5D"));
//    cookies->insertCookie(QNetworkCookie("module_orders_mypage", "yes"));
//    cookies->insertCookie(QNetworkCookie("p_ab_id", "7"));
//    cookies->insertCookie(QNetworkCookie("PHPSESSID", "8405122_ae21044e54c09ae54e93cfc41dca9fb0"));
//    man.setCookieJar(cookies);

    QNetworkReply *reply = man.get(req);

    QObject::connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),
                     [&reply](QNetworkReply::NetworkError err)
    {
        QTextStream qerr(stderr);

        qerr << "Error: " << err << "\n";
    });

    QObject::connect(reply, &QNetworkReply::finished, [&reply]()
    {
        QTextStream qerr(stderr);

        QList<QNetworkReply::RawHeaderPair> headers(reply->rawHeaderPairs());

<<<<<<< Updated upstream
        for (int i = 0; i < headers.size(); ++i)
        {
            //qerr << "HEADER: " << headers[i].first << " CONTENT: " << headers[i].second << "\n";
        }

        QByteArray response = reply->readAll();
        qerr << "====BEGIN====\n";
        qerr << QString::fromUtf8(response);
        qerr << "\n=====END=====";

        QString stringResp = QString::fromUtf8(response);

        FILE* f = std::fopen("pixiv.html", "w+");
        std::fwrite(response.constData(), 1, response.size(), f);
        std::fclose(f);

        QRegExp regex("<a href=\".*\" class=\"user _ui-tooltip\" data-tooltip=\"\\(.*)\\\"><img src=\".*\" alt=\".*\" width=\".*\"></a>");
        int pos = 0;
        while ((pos = regex.indexIn(stringResp, pos)) != -1) {
            qerr << "Watching: " << regex.cap(0) << "\n";
            pos += regex.matchedLength();
        }
    });
=======
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    MyClass *test = new MyClass();
    QNetworkAccessManager *manager;
    QNetworkReply *response = manager->get(QNetworkRequest(QUrl("http://www.google.com")));
//    QEventLoop event;
    QObject::connect(response, SIGNAL(finished(QNetworkReply*)),&event,SLOT(quit()));
    event.exec();
    QString html = response->readAll();
    QTextStream qerr(stderr);
    qerr << "+++++ start ++++++\n";
    qerr << html;
    qerr << "\n+++++ end +++++";
>>>>>>> Stashed changes

    return a.exec();
}
