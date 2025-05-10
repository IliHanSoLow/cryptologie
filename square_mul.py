import sys

def square_and_multiply(base, exponent, modulo):
    # Exponent zero => result is 1 mod N
    if exponent == 0:
        return 1 % N

    bin_exponent = bin(exponent)[2:]
    result = base % modulo
    for bit in bin_exponent[1:]:
        # result = y=b^2
        result = (result * result) % modulo
        # result = y*a
        if bit == '1':
            result = (result * base) % modulo
    return result
    
print(square_and_multiply(int(sys.argv[1]),int(sys.argv[2]),int(sys.argv[3])))

