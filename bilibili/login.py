# encoding: utf-8
#!/usr/bin/python

#import MySQLdb, re, sys, urllib2, Queue, urllib, ssl, requests, os
#from urllib2 import Request, urlopen, URLError, HTTPError
#from requests import Request, Session
import urllib2
import sys, gzip, re
from StringIO import StringIO

headers = {"User-Agent":"Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.103 Safari/537.36"}
# post_headers = {"User-Agent": user_agent}

class bilibili(object):
    """docstring for bilibili"""
    def __init__(self, baseUrl):
        super(bilibili, self).__init__()
        self.baseUrl = baseUrl
        self.html = None
        self.id = None
        self.click = None
        self.coins = None
        self.favourites = None
        self.danmu = None

    def getPage(self, url):
        try:
            # url = self.baseUrl
            request = urllib2.Request(url, headers=headers)
            response = urllib2.urlopen(request)
            # print response.read()
            html = None
            if response.info().get('Content-Encoding') == 'gzip':
                buf = StringIO(response.read())
                f = gzip.GzipFile(fileobj = buf)
                html = f.read()
            else:
                html = response.read()
            print html
            self.html = html
            return response
        except urllib2.URLError, e:
            if hasattr(e, "reason"):
                print u"url error", e.reason
                return None

    def getPageAV(self, av_num):
        try:
            url = self.baseUrl+'video/'+str(av_num)+''
            request = urllib2.Request(url, headers=headers)
            response = urllib2.urlopen(request)
            html = None
            # print response.getcode()
            # print response.read().decode('gzip')
            if response.info().get('Content-Encoding') == 'gzip':
                buf = StringIO(response.read())
                f = gzip.GzipFile(fileobj=buf)
                html = f.read()
            else:
                html = response.read()
            print html
            self.html = html
            return response
        except Exception, e:
            if hasattr(e, "reason"):
                print u"url error", e.reason
                return None
            else:
                print e

    def getId(self):
        m = re.findall('cid=[0-9]+\&aid=[0-9]+', self.html)
        id = None
        for x in m:
            id = x
        self.id = id
        #if id[3]=='=':
        #    self.id = id[:3]+':'+id[4:]
        print self.id

    def getClickInfo(self):
        interface = "http://interface.bilibili.com/player?"
        if (self.id != None):
            interface = interface+self.id
        print interface
        request = urllib2.Request(interface, headers=headers)
        response = urllib2.urlopen(request)
        info = response.read()
        click = re.findall('<click>[0-9]+', info)[0]
        self.click = click[len('<click>'):]
        coins = re.findall('<coins>[0-9]+', info)[0]
        self.coins = coins[len('<coins>'):]
        favourites = re.findall('<favourites>[0-9]+', info)[0]
        self.favourites = favourites[len('<favourites>'):]
        danmu = re.findall('<danmu>[0-9]+', info)[0]
        self.danmu = danmu[len('<danmu>'):]
        print 'click: '+self.click
        print 'coins: '+self.coins
        print 'favourites: '+self.favourites
        print 'danmu: '+self.danmu



def main():
    print "Enter the URL you wish to crawl.."
    print 'Usage  - "http://www.bilibili.com" <-- With the double quotes'
    # login_url = 'https://www.secure.pixiv.net/login.php'
    # page = 'http://www.pixiv.net'
    # login = log_in(login_url)
    baseUrl = "http://www.bilibili.com/"
    bili = bilibili(baseUrl)
    # bili.getPage(baseUrl);
    # crawl(login, page)
    if len(sys.argv) == 1 :
        bili.getPage(baseUrl)
    else:
        bili.getPageAV(sys.argv[1])
    if(bili.html != None):
        bili.getId()
        bili.getClickInfo()

main()
