import hashlib


# http://interface.bilibili.com/playurl?cid=6907160&player=1&ts=1471881577&sign=0edc1e6f1a10a570d3a51df5165e83fb
parm = "cid=6907160&player=1&ts=1471881577"
salt = [0]*32

i = 0
while 1:
    salt = hex(i)[2:].zfill(16)
    i = i+1
    if len(salt) > 16:
        break
    else:
        parmsum = parm + salt
        md5 = hashlib.md5(parmsum).hexdigest()
        print parmsum + "\t" + md5
        if (md5 == '0edc1e6f1a10a570d3a51df5165e83fb'):
            print salt







