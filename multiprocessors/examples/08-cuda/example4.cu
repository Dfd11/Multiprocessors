// =================================================================
//
// File: example4.cu
// Author(s):
// A01705291 Ramses Aguila Flores 
// A01209414 David Flores Diaz
// speedup = 159.37460 ms / 0.00390 ms = 4086528.20 %
// Description: This file contains the code to count the number of
//				even numbers within an array using CUDA.
//
// =================================================================

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include "utils.h"

#define SIZE 100000000
#define THREADS	256
#define BLOCKS	MMIN(32, ((SIZE / THREADS) + 1))

__global__ void sum(int *array, long *result) {
        __shared__ long cache[THREADS];

        int tid = (blockIdx.x * blockDim.x) + threadIdx.x;
        int cacheIndex = threadIdx.x;

        long acum = 0;
        while (tid < SIZE) {
		if (array[tid] % 2 == 0){ 
                	acum ++;
		}
                tid += blockDim.x * gridDim.x;
        }

        cache[cacheIndex] = acum;

        __syncthreads();

        int lim = blockDim.x / 2;
        while (lim > 0) {
                if (cacheIndex < lim) {
                        cache[cacheIndex] += cache[cacheIndex + lim];
                }
                __syncthreads();
                lim /= 2;
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

        cudaMalloc( (void**) &d_a, SIZE * sizeof(int) );
        cudaMalloc( (void**) &d_r, BLOCKS * sizeof(long) );

        cudaMemcpy(d_a, array, SIZE * sizeof(int), cudaMemcpyHostToDevice);

        printf("Starting...\n");
        ms = 0;
        for (i = 1; i <= N; i++) {
                start_timer();

                sum<<<BLOCKS, THREADS>>> (d_a, d_r);

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

// implement your code
