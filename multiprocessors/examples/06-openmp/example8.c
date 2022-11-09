// =================================================================
//
// File: example8.c
// Author(s):Ramses Aguila Flores A017055291
// David Flores Diaz A01209414
// Speedup = 426.4 / 82.48 = 5.16 = 516 %
// Description: This file contains the code that implements the
//				enumeration sort algorithm using OpenMP.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "utils.h"

#define SIZE 10000

// implement your code

void enumerate(int *x , int *r, int s){
	int i, j, e,k;
        #pragma omp parallel for shared(x,r,s) private(j,e,k)
	for(i=0;i<s;i++){
	        e=x[i];
       		k=0;
        	for(j=0;j<s;j++){
        		if(e>x[j]){
        			k++;
        		}else if(e==x[j]&&i<j){
                		k++;
                	}
        	}
        	r[k]=e;
  	}
}
int main(int argc, char* argv[]) {
        int i, *a, *aux;
        double ms;

        a = (int*) malloc(sizeof(int) * SIZE);
        aux = (int*) malloc(sizeof(int) * SIZE);
        random_array(a, SIZE);
        display_array("before", a);

        printf("Starting...\n");
        ms = 0;
        for (i = 0; i < N; i++) {
                start_timer();

                memcpy(aux, a, sizeof(int) * SIZE);
                enumerate(a,aux,SIZE);

                ms += stop_timer();

                if (i == (N - 1)) {
                        memcpy(a, aux, sizeof(int) * SIZE);
                }
        }
        display_array("after", a);
        printf("avg time = %.5lf ms\n", (ms / N));

        free(a); free(aux);
        return 0;
}
