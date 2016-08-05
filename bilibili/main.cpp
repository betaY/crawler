#include "bilibilicrawler.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bilibiliCrawler w;
    w.show();

    return a.exec();
}
