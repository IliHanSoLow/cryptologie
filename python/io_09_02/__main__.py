from src.ecdsa import *


MyPrivateKey = 0x0e174e01fede6d524eb020f6061d5b9aae26184f01102cc1f81a07dac9aac13c

def main():
    m = "Hello World".encode()
    out = ecdsa(m, MyPrivateKey)
    print(hex(out[0]))
    print(hex(out[1]))
    asn1Out = ecdsa_encode(out[0], out[1])
    with open("outfile.bin", "bw") as f:
        print(f.write(asn1Out))

if __name__ == "__main__":
    main()
