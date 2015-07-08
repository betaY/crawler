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

#include <QTextStream>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QNetworkRequest req;
    req.setUrl(QUrl("https://www.secure.pixiv.net/login.php?return_to=%2F"));
    req.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/43.0.2357.130 Safari/537.36");
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QNetworkAccessManager man;
    QNetworkCookieJar *cookies = new QNetworkCookieJar();
    man.setCookieJar(cookies);
    QByteArray *data = new QByteArray();
    data->append("mode=login&return_to=http%3A%2F%2Fwww.pixiv.net%2F&pixiv_id=beta168921%40gmail.com&pass=xjy168921&skip=1");
    QNetworkReply *reply = man.post(req,*data);
    req.setUrl(QUrl("http://www.pixiv.net"));
    QNetworkReply *login = man.get(req);

    QObject::connect(login, &QNetworkReply::finished, [&login](){
        QTextStream qerr(stderr);
        qerr << "----------------------------------\n";
        QList<QNetworkReply::RawHeaderPair> headers(login->rawHeaderPairs());
        for (int i = 0; i < headers.size(); ++i)
        {
            qerr << "\"" << headers[i].first << "\" : \"" << headers[i].second << "\"\n";
        }
    });

//    QUrl *url = new QUrl("http://www.pixiv.net");
//    QNetworkRequest req1(*url);
//    req.setUrl(*url);
//    reply = man.get(req);

//    cookies->insertCookie(QNetworkCookie("p_ab_id", "7"));
//    cookies->insertCookie(QNetworkCookie("login_ever", "yes"));
//    cookies->insertCookie(QNetworkCookie("device_token", "ef878b5484ef1a415161e577a9cfb6bd"));
//    cookies->insertCookie(QNetworkCookie("module_orders_mypage", "%5B%7B%22name%22%3A%22everyone_new_illusts%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22spotlight%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22featured_tags%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22contests%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22following_new_illusts%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22mypixiv_new_illusts%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22booth_follow_items%22%2C%22visible%22%3Atrue%7D%5D"));
//    cookies->insertCookie(QNetworkCookie("PHPSESSID", "314f73945470380f25f72ee1469cb3cb"));
//    cookies->setCookiesFromUrl(cookies->allCookies(), QUrl("https://www.secure.pixiv.net/login.php?return_to=%2F"));

//    QByteArray *data = new QByteArray();
//    data->append("mode=login&return_to=http%3A%2F%2Fwww.pixiv.net%2F&pixiv_id=beta168921%40gmail.com&pass=xjy16921&skip=1");

//    QUrlQuery postdata;
//    postdata.addQueryItem("mode","login");
//    postdata.addQueryItem("return_to","/");
//    postdata.addQueryItem("pixiv_id","beta168921@gmail.com");
//    postdata.addQueryItem("pass","xjy168921");
//    postdata.addQueryItem("skip","1");

//    QNetworkReply *reply = man.post(req,postdata.toString(QUrl::FullyDecoded).toUtf8());
//    reply = man.get(req);

//    data->append("mode=login&return_to=http%3A%2F%2Fwww.pixiv.net%2F&pixiv_id=beta168921%40gmail.com&pass=xjy168921&skip=1");


//    req.setUrl((QUrl("http://www.pixiv.net")));

//    QTextStream qerr(stderr);
//    req.setUrl(QUrl("http://www.pixiv.net"));
//    reply = man.get(req);


//    QNetworkReply *reply = man.get(req);

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

        for (int i = 0; i < headers.size(); ++i)
        {
            qerr << "HEADER: " << headers[i].first << " CONTENT: " << headers[i].second << "\n";
        }

        QByteArray response = reply->readAll();
        qerr << "====BEGIN====\n";
        qerr << QString::fromUtf8(response);
        qerr << "\n=====END=====\n";
//        qerr << reply->manager()->configuration().isValid();
//        qerr << reply->manager()->configuration().name();
//        qerr << reply->manager()->cookieJar()->allCookies();
        QList<QNetworkCookie> list = reply->manager()->cookieJar()->cookiesForUrl(QUrl("http://www.pixiv.net"));

        for(int i = 0; i<list.size(); i++) {
            qerr << list.at(i).name() << "\t" << list.at(i).value() << "\n";
        }

        QString stringResp = QString::fromUtf8(response);

        FILE* f = std::fopen("pixiv.html", "w+");
        std::fwrite(response.constData(), 1, response.size(), f);
        std::fclose(f);

//        QNetworkAccessManager *man =  reply->manager();
//        QUrl *url = new QUrl("http://www.pixiv.net");
//        QNetworkRequest login(*url);
//        man->get(login);

//        QRegExp regex("<a href=\".*\" class=\"user _ui-tooltip\" data-tooltip=\"\\(.*)\\\"><img src=\".*\" alt=\".*\" width=\".*\"></a>");
//        int pos = 0;
//        while ((pos = regex.indexIn(stringResp, pos)) != -1) {
//            qerr << "Watching: " << regex.cap(0) << "\n";
//            pos += regex.matchedLength();
//        }
    });

    return a.exec();
}
