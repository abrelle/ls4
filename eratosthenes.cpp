#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include <omp.h>

using namespace std;


void initArray(int* array, int upperBound){
	#pragma omp parallel for
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
    #pragma omp parallel for schedule(dynamic)
    //pasirinkau dynamic, nes pirmuju iteraciju metu kai kurios gijos buna ilgiau uzimtos
    //todel likusiom gali tekti ilgai laukti, kol bus uzbaigtas  kitu darbas
    for (int i = 2; i <= numOfSieves; ++i){
        sieve_primes(numberArray, i, upperBound);
        }
}

int countPrimes(int* array, int upperBound){
	int numberOfPrimes = 0;
	#pragma omp parallel for schedule(dynamic)
    //cia galetu buti ir statinis
    for (int i = 2; i <= upperBound; ++i){
    	if(array[i] == 1){
    		#pragma omp critical
    		++numberOfPrimes;
    	}
 	}
 	return numberOfPrimes;       
}

int main(int argc, char** argv) {
  	
    int upperBound = atoi(argv[1]);
    
    int* numberArray = new int[upperBound];
    initArray(numberArray, upperBound);
    eratosthenes(numberArray, upperBound);
    cout << "Number of primes " << countPrimes(numberArray, upperBound) << endl;
    cout << endl << "Processors Used = " << omp_get_num_procs() << endl;
    cout << "Threads Used = " << omp_get_max_threads() << endl;
    return 0;
}
