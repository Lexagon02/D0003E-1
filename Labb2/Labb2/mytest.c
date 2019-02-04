#include "tinythreads.h"
#include "LCD.h"

void writeChar(char ch, int pos);  // from lab 1

int is_prime(long i);             // from lab 1

void printAt(long num, int pos) {
    int pp = pos;
    writeChar( (num % 100) / 10 + '0', pp);
    pp++;
    writeChar( num % 10 + '0', pp);
}

void computePrimes(int pos) {
    long n;

    for(n = 1; ; n++) {
        if (is_prime(n)) {
            printAt(n, pos);
			yield();
        }
    }
}

int main() {
	
	initLCD();
	
    spawn(computePrimes, 0);
    computePrimes(3);
}

// Checks wheter a number is a prime number by brute force
int is_prime(long i){

	for(int j = 2; j < i; j++ ){
		
		if(!(i % j)){
			
			return 0;
			
		}
		
	}

	return 1;

}