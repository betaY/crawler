#include <cstdio>

#include <QCoreApplication>
#include <QUrlQuery>
#include <QNetworkConfiguration>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QDateTime>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QNetworkRequest req;
    QUrl *login_url = new QUrl("https://www.secure.pixiv.net/login.php?return_to=%2F");
    req.setUrl(*login_url);
    req.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/43.0.2357.130 Safari/537.36");
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QNetworkAccessManager man;
    QNetworkCookieJar *cookies = new QNetworkCookieJar();
    man.setCookieJar(cookies);

    QByteArray *data = new QByteArray();
    data->append("mode=login&return_to=http%3A%2F%2Fwww.pixiv.net%2F&pixiv_id=beta168921%40gmail.com&pass=xjy168921&skip=1");
    QNetworkReply *reply = man.post(req,*data);

    QObject::connect(reply,&QNetworkReply::finished, [&reply, &man](){
        QTextStream qerr(stderr);
        QList<QNetworkReply::RawHeaderPair> headers(reply->rawHeaderPairs());
        for (int i = 0; i < headers.size(); ++i)
        {
            qerr << "HEADER: " << headers[i].first << " CONTENT: " << headers[i].second << "\n";
        }
//        man(reply->manager());
//        qerr << "\n\n";
//        QList<QNetworkCookie> cookie(man->cookieJar()->cookiesForUrl(QUrl("http://www.pixiv.net")));
//        for (int i = 0; i > cookie.size(); ++i) {
//            qerr << cookie[i].toRawForm();
//        }
//        qerr << man.cookieJar()->cookiesForUrl(QUrl("http://www.pixiv.net"));
    });

//    QTextStream qerr(stderr);



    return a.exec();
}
