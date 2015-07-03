#include <QCoreApplication>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QTextStream>
#include <cstdio>

//class MyClass : public QObject
//{
//Q_OBJECT

//public:
//    MyClass();
//    void fetch();

//public slots:
//    void replyFinished(QNetworkReply*);

//private:
//    QNetworkAccessManager* m_manager;
//};

//MyClass::MyClass()
//{
//    m_manager = new QNetworkAccessManager(this);

//    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
//         this, SLOT(replyFinished(QNetworkReply*)));
//}
//void MyClass::fetch()
//{
//    m_manager->get(QNetworkRequest(QUrl("http://www.google.com")));
//}

//void MyClass::replyFinished(QNetworkReply* pReply)
//{

//    QByteArray data=pReply->readAll();
//    QString str(data);

//    //process str any way you like!
//    QTextStream qerr(stderr);
//    qerr << "+++++ start ++++++\n";
//    qerr << str;
//    qerr << "\n+++++ end +++++";
//}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    MyClass *test = new MyClass();
    QNetworkAccessManager *manager;
    QNetworkReply *response = manager->get(QNetworkRequest(QUrl("http://www.google.com")));
    QEventLoop event;
    QObject::connect(response, SIGNAL(finished(QNetworkReply*)),&event,SLOT(quit()));
    event.exec();
    QString html = response->readAll();
    QTextStream qerr(stderr);
    qerr << "+++++ start ++++++\n";
    qerr << html;
    qerr << "\n+++++ end +++++";

    return a.exec();
}
