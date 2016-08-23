import hashlib


# http://interface.bilibili.com/playurl?cid=6907160&player=1&ts=1471881577&sign=0edc1e6f1a10a570d3a51df5165e83fb
parm = "cid=6907160&player=1&ts=1471881577"
salt = [0]*32

print "".join(str(x) for x in salt)

for i in range(0, 32):
    for j in range(0, 36):
        if j > 9:
            # continue
            if(j == 10):
                salt[i] = 'a'
            elif(j == 11):
                salt[i] = 'b'
            elif(j == 12):
                salt[i] = 'c'
            elif(j == 13):
                salt[i] = 'd'
            elif(j == 14):
                salt[i] = 'e'
            elif(j == 15):
                salt[i] = 'f'
            elif(j == 16):
                salt[i] = 'g'
            elif(j == 17):
                salt[i] = 'h'
            elif(j == 18):
                salt[i] = 'i'
            elif(j == 19):
                salt[i] = 'j'
            elif(j == 20):
                salt[i] = 'k'
            elif(j == 21):
                salt[i] = 'l'
            elif(j == 22):
                salt[i] = 'm'
            elif(j == 23):
                salt[i] = 'n'
            elif(j == 24):
                salt[i] = 'o'
            elif(j == 25):
                salt[i] = 'p'
            elif(j == 26):
                salt[i] = 'q'
            elif(j == 27):
                salt[i] = 'r'
            elif(j == 28):
                salt[i] = 's'
            elif(j == 29):
                salt[i] = 't'
            elif(j == 30):
                salt[i] = 'u'
            elif(j == 31):
                salt[i] = 'v'
            elif(j == 32):
                salt[i] = 'w'
            elif(j == 33):
                salt[i] = 'x'
            elif(j == 34):
                salt[i] = 'y'
            elif(j == 35):
                salt[i] = 'z'
            else:
                continue
        else:
            salt[i] = j
        print "".join(str(x) for x in salt)


