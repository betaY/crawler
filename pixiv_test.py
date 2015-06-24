# encoding: utf-8
#!/usr/bin/python

import MySQLdb, re, sys, urllib2, Queue, urllib, ssl, requests
from urllib2 import Request, urlopen, URLError, HTTPError
from requests import Request, Session

def log_in(url):
	s = requests.Session()
	login_data = {"mode":"login",
				"return_to":"/",
				"pixiv_id":"beta168921@gmail.com",
				"pass":"xjy168921",
				"skip":"1"
				}
	user_agent = ("Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_3) "
				"AppleWebKit/537.36 (KHTML, like Gecko) "
				"Chrome/43.0.2357.81 Safari/537.36")
	post_headers = {"User-Agent": user_agent}
	# postdata = urllib.urlencode(logininfo)
	s.post(url, login_data)

	return s

def crawl(login, url):

	url_queue = Queue.Queue()
	seen = set()
	seen.add(url)
	url_queue.put(url)
	# r = login.get(url)
	text = file('test', 'wt')
	# text.write(r.content)
	while 1:
		if url_queue.qsize() > 0:
			current_url = url_queue.get()
			text.write(current_url+'\n')
			print current_url
			print url_queue.qsize()
			try:
				r = login.get(current_url)
				print current_url, r
				content = r.content
			except Exception, e:
				print e
			id = current_url.split('id=')
			if len(id) > 1:
				id = id[1].split('&')[0]
			else:
				id = id[0]
			for i in re.findall('''href=["'](.[^"']+)["']''', content, re.I):
				if i.startswith('member'):
					i = 'http://www.pixiv.net/' + i
					i = i.replace('&amp;', '&')
				if i.startswith('/member'):
					i = 'http://www.pixiv.net' + i
					i = i.replace('&amp;', '&')
				if i == "#":
					break
				if i not in seen and 'pixiv.net' in i and 'illust_id=' in i:
					seen.add(i)
					url_queue.put(i)
			for i in re.findall('''<img src=["'](.[^"']+)["'] alt=["'](.[^"']+)["']>''', content, re.I):
				# print 'img: '+i[0]+' name: '+i[1]
				if id in i[0]:
					print 'img: '+i[0]+' name: '+i[1]
					name = i[1]
					head = r.headers
					referer = current_url.split('&uarea')[0]
					print "Referer: " +referer
				# 	head['Referer'] = referer
					# pic_r = login.post(i, headers=head)
					# print i, pic_r
					# pic = file(name, 'wt')
					# pic.write(pic_r.content)
		else:
			break




def main():
	print "Enter the URL you wish to crawl.."
	print 'Usage  - "http://www.pixiv.net" <-- With the double quotes'
	login_url = 'https://www.secure.pixiv.net/login.php'
	page = 'http://www.pixiv.net'
	login = log_in(login_url)
	crawl(login, page)

main()