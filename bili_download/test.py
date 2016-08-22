import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from PyQt4.QtNetwork import *
from PyQt4.QtWebKit import *
import time

class Render(QWebPage):
    def __init__(self, url):
        # QNetworkProxy.setApplicationProxy(QNetworkProxy(QNetworkProxy.HttpProxy, 'proxy.uku.im', 443))
        self.app = QApplication(sys.argv)
        QWebPage.__init__(self)
        self.loadFinished.connect(self._loadFinished)
        manager = QNetworkAccessManager()
        proxy = QNetworkProxy()
        proxy.setType(QNetworkProxy.HttpProxy)
        proxy.setHostName('proxy.uku.im')
        proxy.setPort(443)
        manager.setProxy(proxy)
        req = QNetworkRequest(QUrl(url))
        req.setRawHeader("User-Agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.103 Safari/537.36")
        req.setRawHeader("Client-IP", "220.181.111.38")
        req.setRawHeader("X-Forwarded-For", "220.181.111.38")

        self.setNetworkAccessManager(manager)
        self.mainFrame().load(req)
        # time.sleep(10)
        # self.mainFrame().load(req, manager.GetOperation)
        print "first"
        # QNetworkProxy.setApplicationProxy(QNetworkProxy(QNetworkProxy.HttpProxy, 'proxy.uku.im', 443))
        # browser = QWebView()
        # page = self.mainFrame().page()
        # browser.setPage(page)
        # browser.load(req)
        # browser.show()

        self.app.exec_()
    def _loadFinished(self, result):
        # time.sleep(10)
        # self.frame = self.mainFrame()
        self.frame = self.currentFrame()


        print "second"
        self.app.quit()

url = raw_input('Enter the url:\n')
r = Render(url)
result = r.frame.toHtml()


formatted_result = str(result.toUtf8())

print formatted_result

f = open('./test.html', 'w')
f.write(result.toUtf8())
f.close()
