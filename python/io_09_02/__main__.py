from src.ecdsa import *
from src.ecalgebra import *


# MyPrivateKey = """
#  0e:17:4e:01:fe:de:6d:52:4e:b0:20:f6:06:1d:5b:
#     9a:ae:26:18:4f:01:10:2c:c1:f8:1a:07:da:c9:aa:
#     c1:3c
#     """.replace(" ", "").replace("\n", "").replace(":", "")
MyPrivateKey = int.from_bytes("muede".encode())
# MyPrivateKey = 0x0e174e01fede6d524eb020f6061d5b9aae26184f01102cc1f81a07dac9aac13c

# TODO: Unit Tests Double add, add etc
def test():
    # Example curve: y^2 = x^3 + 2x + 3 over F_97
    p = 97
    a = 2
    b = 3
    G = (3, 6)
    n = 5
    h = 1

    curve = ElipticCurve(p, a, b, G, n, h)

    x, y = G
    assert (y**2 % p) == (x**3 + a * x + b) % p, "G must lie on the curve"
    assert (1 * curve.G) == curve.G, "1 * G should be G"
    assert (0 * curve.G) == ElipticCurve.Point(curve, 0, 0), "0 * G should be INF"

    assert (curve.G + curve.G) == (2 * curve.G), "G + G should equal 2 * G"
    assert ((curve.G + curve.G) + curve.G) == (curve.G + (curve.G + curve.G)), "Addition should be associative"
    triple = curve.G + curve.G + curve.G
    assert (3 * curve.G) == triple, "3 * G should equal G + G + G"
    print("All tests passed.")

def main():
    m1 = "foobar".encode()
    m2 = "foobar123".encode()
    out1 = ecdsa(m1, MyPrivateKey)
    out2 = ecdsa(m2, MyPrivateKey)
    # print(hex(out[0]))
    # print(hex(out[1]))
    asn1Out1 = ecdsa_encode(out1[0], out1[1])
    asn1Out2 = ecdsa_encode(out2[0], out2[1])
    with open("signature1.bin", "bw") as f:
        print(f.write(asn1Out1))
    with open("signature2.bin", "bw") as f:
        print(f.write(asn1Out2))
    with open("message1.bin", "bw") as f:
        print(f.write(m1))
    with open("message2.bin", "bw") as f:
        print(f.write(m2))


    # ecdsa_exploit("./packages/1/signature1.bin", "./packages/1/message1.bin", "./packages/1/signature2.bin", "./packages/1/message2.bin")
    # Doesnt work due to base pow((s1*r-s2*r), -1, n)) in ecdsa_exploit_intern being 0 prob. wrong file reading



if __name__ == "__main__":
    test()
    main()
