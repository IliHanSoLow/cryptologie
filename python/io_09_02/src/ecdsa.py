import hashlib
from random import randrange
from .ecalgebra import *


# ecdsa(message, private_key)
def ecdsa(m: bytes, d: int, k=randrange(P256.n)) -> tuple[int, int]:
    return ecdsa_real(k, m, d)

# ecdsa_real(private_key, message, random_skalar)
def ecdsa_real(k:int, m: bytes, d: int) -> tuple[int, int]:
    n = P256.n
    e = int.from_bytes(hashlib.sha256(m).digest(), 'big')
    print(hex(e))
    print(f"{e=}")
    R = k*P256.G
    print(f"{R=}")
    s = ((e+(R.x*d))%n) * pow(k, -1, n) %n
    print(f"{s=}")
    return (R.x, s)


# Ecdsa-Sig-Value  ::=  SEQUENCE  {
#       r     INTEGER,
#       s     INTEGER  }
def ecdsa_encode(r:int, s:int) -> bytes:
    lr = int(r.bit_length()+7)//8
    ls = int(s.bit_length()+7)//8
    rb = r.to_bytes(lr, 'big')
    sb = s.to_bytes(ls, 'big')
    if rb[0]>>7:
        rb = b"\x00" + rb
    if sb[0]>>7:
        sb = b"\x00" + sb
    lg = len(rb) + len(sb) + 4
    return (b'\x30' + lg.to_bytes(1) + b"\x02" + len(rb).to_bytes(1)   + rb + b"\x02" + len(sb).to_bytes(1) + sb)

def ecdsa_decode(a: bytes) -> tuple[int, int]:
    rl = a[3]
    sl = a[4+rl+1]
    r = bytes(a[4:4+rl])
    s = bytes(a[4+rl+1:sl])
    return (int.from_bytes(r), int.from_bytes(s))

def ecdsa_exploit_intern(s1: int, s2: int, e1: int, e2: int, r: int):
    n = P256.n
    res = ((s2*e1 - s1*e2)*pow((s1*r-s2*r), -1, n)) %n
    return res


def ecdsa_exploit(sigfile1, msgfile1, sigfile2, msgfile2):
    sig1 = b""
    msg1 = b""
    sig2 = b""
    msg2 = b""

    with open(sigfile1, 'rb') as f:
        sig1 = f.read()
    with open(sigfile2, 'rb') as f:
        sig2 = f.read()
    with open(msgfile1, 'rb') as f:
        msg1 = f.read()
    with open(msgfile2, 'rb') as f:
        msg2 = f.read()

    print(list(sig1))
    print(list(sig2))

    e1 = int.from_bytes(hashlib.sha256(msg1).digest())
    e2 = int.from_bytes(hashlib.sha256(msg2).digest())
    (r1, s1) = ecdsa_decode(sig1)
    (r2, s2) = ecdsa_decode(sig2)

    if r1 != r2:
        print("r1 != r2, so exploit is not possible")
        k=-1
    else:
        k = ecdsa_exploit_intern(s1, s2, e1, e2, r1)
    return k



# publicKey(private_key)
def publicKey(d:int) -> 'ElipticCurve.Point':
    return d*P256.G
