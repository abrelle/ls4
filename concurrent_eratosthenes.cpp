#include <iostream>
#include <bits/stdc++.h>
#include <chrono>
#include <math.h>
#include <mpi.h>

using namespace std;
using namespace std::chrono;


void initArray(int* array, int begin, int size){
		int value;
		for(int i = 0; i < size; ++i){
		value = begin + i;
    	array[i] = value;
    }
 
}

void sievePrimes(int *array, int firstPrime, int size){
		int add = 1;
        for(int j = 0; j < size; j += add){
        	if(array[j] % firstPrime == 0 && array[j] != firstPrime){
        	   add = firstPrime;
        	   array[j] = -1;
        	
        	}
        }
    
}

int getNextPrime(int* numberArray, int lastPrime, int size){
 
    for (int i = 0; i <= size; ++i){
         	if(numberArray[i] > lastPrime){
         	   return numberArray[i];
       }
    }
    return -1;
}

int countPrimes(int* array, int upperBound){
	int numberOfPrimes = 0;
    for (int i = 0; i < upperBound; ++i){
    	if(array[i] > 1){
    		++numberOfPrimes;
    	}
 	}

 	return numberOfPrimes;       
}

int main(int argc, char** argv) {

	auto start = high_resolution_clock::now();
  	
  	int upperBound = atoi(argv[1]);
    
   
    int rank, nproc;
    int lastPrime = 2;
    int numOfSieves = sqrt(upperBound);
    
    MPI_Init (&argc, &argv);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank );
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);
	
	
	
	int begin = floor(rank*upperBound/nproc);
	int end = floor(((rank+1)*upperBound)/nproc)-1;
	int size = end-begin + 1;

	int* myArray = new int[size];
    initArray(myArray, begin, size);
    
    //cout << "Process " << rank << " is ready" << endl;
	MPI_Barrier(MPI_COMM_WORLD);
	
	while (lastPrime <= numOfSieves && lastPrime != -1){
		
		sievePrimes(myArray, lastPrime, size);
		lastPrime = getNextPrime(myArray, lastPrime, size);
		MPI_Bcast(&lastPrime, 1, MPI_INT, 0, MPI_COMM_WORLD);
	}
	
	int numPrimes = numPrimes = countPrimes(myArray, size);
	//cout << begin << " " << end << " " <<rank << " " << numPrimes << "list -> ";
	//for(int i = 0; i < size; ++i){
		//cout << myArray[i] << " ";
	//}
	//cout << endl;
	
	MPI_Send(&numPrimes, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	
	MPI_Barrier(MPI_COMM_WORLD);
	
	
	int receivedPrimes;
	int totalPrimes = 0;
	if(rank == 0){
		auto stop = high_resolution_clock::now();
		for(int i = 0; i < nproc; ++i){
			MPI_Recv(&receivedPrimes, 1, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			totalPrimes += receivedPrimes;
		}
		cout << endl <<  "Total number of primes " << totalPrimes << endl;
		auto durationMicro = duration_cast<microseconds>(stop - start);
		cout << endl << "Duration in microseconds " << durationMicro.count() << endl << endl;
	}
    
    free(myArray);
    MPI_Finalize();
    return 0;
}
