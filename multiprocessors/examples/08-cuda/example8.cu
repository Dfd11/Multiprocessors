// =================================================================
//
// File: example8.cu
// Author(s):
// Description: This file contains the code that implements the
//				enumeration sort algorithm using CUDA.
// A01705291 Ramses Aguila Flores 
// A01209414 David Flores Diaz
// speedup = 418.82030 ms / 0.00170 ms = 24635470.58 %
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cuda_runtime.h>
#include "utils.h"

#define SIZE 10000
#define THREADS 256
#define BLOCKS	MMIN(32, ((SIZE / THREADS) + 1))

__global__ void sum(int *array, int *result) {

        int tid = threadIdx.x + (blockIdx.x * blockDim.x);


        while (tid < SIZE) {
		////////////////
		int k =0;
		for (int i=0; i < SIZE ; i++){
			if(array[tid] > array[i]){
				k++;
			}else if(array[tid] == array[i] && tid < i){
				k++;
			}
		}
		result[k] = array[tid];
		/////////////////
                tid += blockDim.x * gridDim.x;
        }

}

int main(int argc, char* argv[]) {
        int i, *array, *d_a;
        int *results, *d_r;
        double ms;

        array = (int*) malloc( SIZE * sizeof(int) );
        random_array(array, SIZE);
        display_array("array", array,100);

        results = (int*) malloc( SIZE * sizeof(int) );

        cudaMalloc( (void**) &d_a, SIZE * sizeof(int) );
        cudaMalloc( (void**) &d_r, SIZE * sizeof(int) );

        cudaMemcpy(d_a, array, SIZE * sizeof(int), cudaMemcpyHostToDevice);

        printf("Starting...\n");
        ms = 0;
        for (i = 1; i <= N; i++) {
                start_timer();

                sum<<<BLOCKS, THREADS>>> (d_a, d_r);

                ms += stop_timer();
        }

        cudaMemcpy(results, d_r, SIZE * sizeof(int), cudaMemcpyDeviceToHost);

	display_array("Result",results,100);
	printf("avg time = %.5lf\n", (ms / N));

        cudaFree(d_r);
        cudaFree(d_a);

        free(array);
        free(results);
        return 0;
}
