class ElipticCurve:
    class Point:
        def __init__(self, curve: 'ElipticCurve', x:int, y: int) -> None:
            self.curve: ElipticCurve = curve
            self.x: int = x
            self.y: int = y

        def __eq__(self, other) -> bool:
            if not isinstance(other, ElipticCurve.Point):
                return False
            return (self.curve == other.curve and self.x == other.x and self.y == other.y)
            # if (isinstance(other, ElipticCurve.Point) and self.isInf == other.isInf and
            #         self.curve == other.curve and self.x == other.x and self.y == other.y):
            #     return True
            # return False

        def __add__(self, other: 'ElipticCurve.Point') -> 'ElipticCurve.Point':
            if self.x == 0 and self.y == 0:
                return other
            elif other.x ==0 and other.y == 0:
                return self

            if self.x == other.x and (self.y != other.y or self.y == 0):
                return ElipticCurve.Point(self.curve, 0, 0)

            if self == other:
                return 2*self
            if self.curve != other.curve:
                raise Exception("Points dont operate on the same curve")

            p= self.curve.p
            s = ((self.y-other.y)* pow(self.x-other.x, -1, p))%p
            tx = int(s*s - self.x - other.x) % p
            ty = int(s* (self.x - tx) - self.y) % p
            return ElipticCurve.Point(self.curve, tx,ty)


        def __repr__(self):
            return f"{self.x}, {self.y}"

        def double(self) -> 'ElipticCurve.Point':
            if self.x == 0 and self.y == 0:
                return self
            p= self.curve.p
            a = self.curve.a
            s = ((3*pow(self.x, 2, p)+a) * pow(2*self.y, -1, p)) %p
            tx = int(s*s - 2*self.x) % p
            ty = int(s* (self.x - tx) - self.y) % p
            return ElipticCurve.Point(self.curve, tx,ty)


        def __rmul__(self, other: int)->'ElipticCurve.Point':
            if self.x == 0 and self.y == 0:
                return self

            p= self.curve.p
            n = self
            r = ElipticCurve.Point(self.curve, 0, 0)

            while other:
                if other & 1:
                    r = (r+n)
                n = n.double()
                other>>=1

            return r

    # y^2 = x^3 + ax + b mod p
    def __init__(self, p:int, a:int, b:int, G:tuple[int,int], n:int, h:int):
        self.p:int                = p
        self.a:int                = a
        self.b:int                = b
        self.G:ElipticCurve.Point = ElipticCurve.Point(self, G[0], G[1])
        self.n:int                = n
        self.h:int                = h

    def __eq__(self, other) -> bool:
        if (isinstance(other, ElipticCurve) and self.p == other.p and self.a == other.a and
                self.b == other.b and self.G.x == other.G.x and self.G.y == other.G.y # the G buissnes needs to be done to avoid recursion
                and self.n == other.n and self.h == other.h):
            return True
        return False

    def isOnCurve(self, other:'ElipticCurve.Point') -> bool:
        a = pow(other.x, 3, self.p) + self.a*other.x + self.b
        if a == pow(other.y, 2, self.p):
            return True
        return False


P256 = ElipticCurve(
    0xffffffff00000001000000000000000000000000ffffffffffffffffffffffff,
    0xffffffff00000001000000000000000000000000fffffffffffffffffffffffc,
    0x5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604b,
    (0x6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296,
       0x4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5),
    0xffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551,
    0x1)
