import sys, random;


def primalityTest(num):
    witness = random.randint(1,num - 1);
    if (pow(witness, num - 1,num) != 1):
        return False;
    return True;
    
def main():
    prime = True;
    inputString = sys.argv[1];
    number = eval(inputString);
    
    for i in range(100):
        if not primalityTest(number):
            prime = False;
            break;
    
    if prime:
        print(inputString + " is prime");
    else:
        print(inputString + " is not prime");
        
if __name__ == "__main__":
    main()
