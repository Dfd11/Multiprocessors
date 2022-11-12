// =================================================================
//
// File: example7.cu
// Author(s):
// Description: This file contains the code to brute-force all
//				prime numbers less than MAXIMUM using CUDA.
// A01705291 Ramses Aguila Flores 
// A01209414 David Flores Diaz
// speedup = 140.09380 ms / 0.00220 ms = 6367900 %
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda_runtime.h>
#include "utils.h"

#define SIZE 1000000 //1e6
#define THREADS 256
#define BLOCKS	MMIN(32, ((SIZE / THREADS) + 1))

__device__ bool prime(long n){
	long lim;
	if(n<2){
		return false;
	}else{
		lim = sqrt((float)n);
		for (long i=2; i<=lim;i++){
			if(n % i == 0){
				return false;
			}
		}
		return true;
	}
}

__global__ void sum(int *array, long *result) {
        __shared__ long cache[THREADS];

        long tid = threadIdx.x + (blockIdx.x * blockDim.x);
        long cacheIndex = threadIdx.x;

        long acum = 0;
        while (tid < SIZE) {
		if (prime(array[tid])){
                	acum += array[tid];
		}
	        tid += blockDim.x * gridDim.x;
        }
        cache[cacheIndex] = acum;

        __syncthreads();

        long i = blockDim.x / 2;
        while (i > 0) {
                if (cacheIndex < i) {
                        cache[cacheIndex] += cache[cacheIndex + i];
                }
                __syncthreads();
                i /= 2;
        }

        if (cacheIndex == 0) {
                result[blockIdx.x] = cache[cacheIndex];
        }
}

int main(int argc, char* argv[]) {
        int i, *array, *d_a;
        long *results, *d_r;
        double ms;

        array = (int*) malloc( SIZE * sizeof(int) );
        fill_array(array, SIZE,SIZE);
        display_array("array", array,100);

        results = (long*) malloc( BLOCKS * sizeof(long) );

        cudaMalloc( (void**) &d_a, SIZE * sizeof(long) );
        cudaMalloc( (void**) &d_r, BLOCKS * sizeof(long) );

        cudaMemcpy(d_a, array, SIZE * sizeof(int), cudaMemcpyHostToDevice);

        printf("Starting...\n");
        ms = 0;
        for (i = 1; i <= 1; i++) {
                start_timer();

                sum<<<BLOCKS,THREADS>>> (d_a, d_r);

                ms += stop_timer();
        }

        cudaMemcpy(results, d_r, BLOCKS * sizeof(long), cudaMemcpyDeviceToHost);

        long acum = 0;
        for (i = 0; i < BLOCKS; i++) {
                acum += results[i];
        }

        printf("sum = %li\n", acum);
        printf("avg time = %.5lf\n", (ms / N));

        cudaFree(d_r);
        cudaFree(d_a);

        free(array);
        free(results);
        return 0;
}
