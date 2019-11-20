# Calculating the phi number. For 10 ** 16 the recursion is simple, so we use it 
def phi(num):
    if (num % 5 == 0):
        return num * 4 // 10;
    else:
        return num // 2;

 
def hyper(num, expo, modulo):
    if (modulo == 1):   # if modulo is 1 the result is obviously 0
        return 0;
    if (expo == 1):     # if the exponent is 1 we return the actual number
        return num % modulo;
    return pow(num, hyper(num, expo - 1, phi(modulo)), modulo); # on any other case we return the value recursively calling the same function
    
def main():
    result = hyper(1707, 1783, pow(10,16)); 
    print ("The last 16 digits of 1707 ↑↑ 1783 are",'{0:0{width}}'.format(result, width=16));
    
if __name__ == "__main__":
    main()