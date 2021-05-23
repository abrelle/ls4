#include <iostream>
#include <bits/stdc++.h>
#include <chrono>
#include <math.h>

using namespace std;
using namespace std::chrono;


void initArray(int* array, int upperBound){
        for (int i = 0; i < upperBound; ++i){
            array[i] = 1;
        }
 
}

void sieve_primes(int *array, int firstPrime, int arraySize){
    if(array[firstPrime] == 1){

        for(int j = pow(firstPrime, 2); j < arraySize; j += firstPrime){
            array[j] = 0;
        }
    }
}

void eratosthenes(int* numberArray, int upperBound){
 
	int numOfSieves = sqrt(upperBound);
    for (int i = 2; i <= numOfSieves; ++i){
        sieve_primes(numberArray, i, upperBound);
        }
}

int countPrimes(int* array, int upperBound){
	int numberOfPrimes = 0;
    for (int i = 2; i <= upperBound; ++i){
    	if(array[i] == 1){
    		++numberOfPrimes;
    	}
 	}
 	return numberOfPrimes;       
}

int main(int argc, char** argv) {
  	
    int upperBound = atoi(argv[1]);
    
    int* numberArray = new int[upperBound];
    
	auto start = high_resolution_clock::now();
    initArray(numberArray, upperBound);
    eratosthenes(numberArray, upperBound);
    cout << "Number of primes " << countPrimes(numberArray, upperBound) << endl;
    
	auto stop = high_resolution_clock::now();
	auto durationMicro = duration_cast<microseconds>(stop - start);
	
	
	cout << endl << "Duration in microseconds " << durationMicro.count() << endl;
	

    return 0;
}
