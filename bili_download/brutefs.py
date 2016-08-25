import hashlib, sys, time


# http://interface.bilibili.com/playurl?cid=6907160&player=1&ts=1471881577&sign=0edc1e6f1a10a570d3a51df5165e83fb
parm = "cid=6907160&player=1&ts=1471881577"
#s = ['f']*32
total = float.fromhex('ffffffffffffffffffffffffffffffff')

i = 0
if (len(sys.argv) < 2):
    i = 0
else:
    i = int(sys.argv[1])
while 1:
    salt = hex(i)[2:].zfill(32)
    i = i+1
    if len(salt) > 32:
        break
    else:
        parmsum = parm + salt
        md5 = hashlib.md5(parmsum).hexdigest()
        #print parmsum + "\t" + md5
        sys.stdout.write("\r%.5f%%%%  i=%d\t\t\t\t%s" % (float(i/total)*10000,i,salt))
        sys.stdout.flush()
        if (md5 == '0edc1e6f1a10a570d3a51df5165e83fb'):
            print salt
            f = open('./salt.txt', 'w')
            f.write(salt+'\n')
f.close()







