# encoding: utf-8
#!/usr/bin/python

import MySQLdb, re, sys, urllib2, Queue, urllib, ssl
from urllib2 import Request, urlopen, URLError, HTTPError
# from requests import Request, Session


db = MySQLdb.connect("beta.moe","yudachi","poi","crawler" )
cursor = db.cursor()
cursor.execute("SELECT VERSION()")
data = cursor.fetchone()
print "Database version : %s " % data
ssl._create_default_https_context = ssl._create_unverified_context

def createDB():
	cursor.execute("DROP TABLE IF EXISTS URL")
	sql = """CREATE TABLE URL (urlid INT, url VARCHAR(512), times INT, description VARCHAR(200))"""
	cursor.execute(sql)
	# cursor.execute("CREATE TABLE URL (urlid INT, url VARCHAR(512), description VARCHAR(200))")

	db.close()

def crawler(myurl):
	url_queue = Queue.Queue()
	seen = set()
	textfile = file('pixiv_url','wt')
	seen.add(myurl)
	url_queue.put(myurl)
	logininfo = {"mode":"login",
				"return_to":"/",
				"pixiv_id":"beta168921@gmail.com",
				"pass":"xjy168921",
				"skip":"1"
				}
	user_agent = ("Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_3) "
				"AppleWebKit/537.36 (KHTML, like Gecko) "
				"Chrome/43.0.2357.81 Safari/537.36")
	post_headers = {"User-Agent": user_agent}
	postdata = urllib.urlencode(logininfo)
	
	# try:
	# 	req = urllib2.Request(myurl, postdata, post_headers)
	# 	result = urllib2.urlopen(req)
	# 	# my = urllib2.Request('http://www.pixiv.net/mypage.php#id=9560114')
	# 	# myp = urllib2.urlopen(my)
	# 	# textfile.write(result.read())
	# except Exception, e:
	# 	print e

	

	
	# pixiv_session = requests.Session()
	# login_res = pixiv_session.post(myurl,
	# 	data=logininfo,
	# 	headers=post_headers,
	# 	)
	# if login_res.status_code == 200:
	# 	print "Login Successfully!"
	# else:
	# 	print login_res.text

	while 1:
		if url_queue.qsize() > 0:
			current_url = url_queue.get()
			textfile.write(current_url+'\n')
			print current_url
			print url_queue.qsize()
			try:
				req = urllib2.Request(current_url, postdata, post_headers)
				list = urllib2.urlopen(req)
				# list = urllib.urlopen(current_url)
			except Exception, e:
				print e
			for i in re.findall('''href=["'](.[^"']+)["']''', list.read(), re.I):
				if i.startswith('member') :
					i = 'http://www.pixiv.net/' + i
					i = i.replace('&amp;', '&')
				if i.startswith('/member'):
					i = 'http://www.pixiv.net' + i
					i = i.replace('&amp;', '&')
				if i == "#":
					break
				if i not in seen and 'pixiv.net' in i:
					seen.add(i)
					url_queue.put(i)


			try:
				req = urllib2.Request(current_url, postdata, post_headers)
				list = urllib2.urlopen(req)
				# list = urllib.urlopen(current_url)
			except Exception, e:
				print e
			for i in re.findall('''img src=["'](.[^"']+).jpg["']''', list.read(), re.I):
				i = i+'.jpg'
				print 'img url: ' + i
				try:
					req = urllib2.Request(i)
					referer = i
					req.add_header('Rerferer', referer)
					resp = urllib2.urlopen(req)
				except Exception, e:
					print e
		else:
			break



	# try:	
	# 	list = urllib.urlopen(myurl)
	# except Exception, e:
	# 	print e
	# # for i in list:
	# # 	textfile.write(i)
	# for i in re.findall('''href=["'](.[^"']+)["']''', list.read(), re.I):
	# 	if i == "#":
	# 		break
	# 	print i
	# 	textfile.write(i+'\n')
	# 	sql = "INSERT INTO URL(urlid,url,times,description) VALUES (%d, %s, %d, %s)"
	# 	try:
	# 		cursor.execute(sql,)
	# 	except Exception, e:
	# 		db.rollback()
	# 	# crawler(i)
	# textfile.close()



def main():
	createDB()

	print "Enter the URL you wish to crawl.."
	print 'Usage  - "http://www.pixiv.net" <-- With the double quotes'
	myurl = 'https://www.secure.pixiv.net/login.php'
	crawler(myurl)
	# for i in re.findall('''href=["'](.[^"']+)["']''', urllib.urlopen(myurl).read(), re.I):
	# 	if i == "#":
	# 		break
	# 	print i
	# 	textfile.write(i+'\n')
	# 	for ee in re.findall('''href=["'](.[^"']+)["']''', urllib.urlopen(i).read(), re.I):
	# 		print ee
	# 		textfile.write('\t'+ee+'\n')
	# textfile.close()

main()
