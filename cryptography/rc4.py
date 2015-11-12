import sys

def KSA(key):
    keylength = len(key)

    S = range(256)
    
    j = 0
    for i in range(256):
        j = (j + S[i] + key[i % keylength]) % 256
        S[i], S[j] = S[j], S[i]  

    return S
def encr():
    print plaintext

def PRGA(S):
    i = 0
    j = 0
    while True:
        i = (i + 1) % 256
        j = (j + S[i]) % 256
        S[i], S[j] = S[j], S[i] 
        K = S[(S[i] + S[j]) % 256]
        yield K


def RC4(key):
    S = KSA(key)   
    #print "After KSA", S
    return PRGA(S)


def convertKey(s):
    i=0
    s=list(s)
    for c in s:
        s[i] = ord(c)
        i+=1
    return s

def cyp(): 
     for c in plaintext: 
      print sys.stdout.write("%c" % (ord(c) ^ keystream.next()))

     for c in plaintext: 
      print keystream.next()
     encr()
   




if __name__ == '__main__':
    key = 'bbbb'
    plaintext = 'abcd'

    print "key : ",key
    print "plaintext :", plaintext

    key = convertKey(key)
   
    keystream = RC4(key)
    #print "key stream",keystream 
    
    cyp()


  



