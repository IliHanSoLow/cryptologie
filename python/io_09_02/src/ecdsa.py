import hashlib
from random import randrange
from .ecalgebra import *

# ecdsa(message, private_key)
def ecdsa(m: bytes, d: int) -> tuple[int, int]:
    n = P256.n
    k = randrange(n)
    return ecdsa_real(k, m, d)

# ecdsa_real(private_key, message, random_skalar)
def ecdsa_real(k:int, m: bytes, d: int) -> tuple[int, int]:
    n = P256.n
    e = int.from_bytes(hashlib.sha256(m).digest(), 'big')
    R = k*P256.G
    s = (e+R. x*d) * pow(k, -1, n) %n
    return (R.x, s)


# Ecdsa-Sig-Value  ::=  SEQUENCE  {
#       r     INTEGER,
#       s     INTEGER  }
def ecdsa_encode(r:int, s:int) -> bytes:
    # FIXME: THE FUCKING MAGIC VALUE SEEMS TO BE WRONG
    #       IF I ADD 1 BIT THE BYTESIZE SOMEHOW DOESNT INCREASE BY 1
    lr = int(r.bit_length()+7)//8 +1
    ls = int(s.bit_length()+7)//8 +1
    rb = r.to_bytes(lr, 'big')
    sb = s.to_bytes(ls, 'big')
    lg = lr + ls + 4
    return (bytes([0x30, lg, 0x02, lr]) + b"\x00" + rb + bytes([0x02, ls])  + b"\x00" + sb)

# publicKey(private_key)
def publicKey(d:int) -> 'ElipticCurve.Point':
    return d*P256.G
