from Crypto.Util import number
import random

#---A function using Fermat's test to determine if a number is a prime with error probabilty of 2^(-2000)
def isPrime(num):
    for i in range(1000):
        if not primalityTest(num):
            return False;
    return True;

def primalityTest(num):
    witness = random.randint(1,num - 1);
    if (pow(witness, num - 1,num) != 1):
        return False;
    return True;

#---The function we use to generate our keys, given the order of a group and one of its subgroups
def keyGenerate(p, q):
    x = number.getRandomRange(1, q);
    y = pow(g,x,p)
    return (y,x);

#---We sign our message(input given in binary form) using our private key, @x
def sign(m, p, q, x):
    k = number.getRandomRange(1, q);
    r2 = pow(g,k,p);
    toHash = bin(r2)[2:] + m;
    e = hash(toHash) % q;
    s = (k - x * e) % q;
    return (s,e)

#---After we receive the message(in binary form) we use the public key and the signature (s,e) to verify the sender
def verify(m, s, e, p, q, g, y):
    rv = (pow(g, s, p) * pow(y, e, p)) % p;
    toVerify = bin(rv)[2:] + binM;
    ev = hash(toVerify) % q;
    return ev

if __name__ == "__main__":
    m = "Hello World!";
    binM = ''.join(format(ord(x), '08b') for x in m)
    
#----The group we are going to work with. We construct a "Schnorr Group" https://en.wikipedia.org/wiki/Schnorr_group.
    q = number.getPrime(50); 
    p = 2 * q + 1
    r = 2;
    while not isPrime(p):
        p += q;
        r+=1;    
    h = 2;
    g = pow(h, r, p)
    while g == 1:
        h+=1;
        g = pow(h, r, p)

    y, x = keyGenerate(p,q)                     # We get our keys
    
    s, e = sign(binM, p, q, x);                 # Signing the message. (s,e) is the signature for message m
    
    ev = verify(binM, s, e, p, q, g, y);        # We get a value corresponding to the signature. If ev = e, the sender is verified

    print("We work in Z_p*=%d, with a subgroup of order q=%d with generator g=%d. The public key is y=%d" %(p,q,g,y))
    print("For message %s, the signature is (%d,%d)" %(m, s, e))
    if (e == ev):
        print("Verified!");
    else:
        print("Hmm...");
    print("e = %d, ev = %d" %(e,ev))
    