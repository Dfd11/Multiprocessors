// =================================================================
//
// File: example7.c
// Author(s):
// 10/10/2022
// speedup = 141.46/34.89= 4.0544  
// A01705291 Ramses Aguila Flores
// A01209414 David Flores Diaz
// Description: This file contains the code to brute-force all
//				prime numbers less than MAXIMUM using OpenMP.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include <omp.h>

#define MAXIMUM 1000000 //1e6

// implement your code
	double prime(int n){
   		int lim;
   		if (n < 2)
      		  return 0;
   		lim = sqrt(n);
   		for (int i = 2 ; i <= lim ; i++){
      			if (n % i == 0) {
         	  	  return 0;
      			}
   		}
   		return 1;
	}

	double sum (int max){
   		double suma=0;
		#pragma omp parallel for shared(max) reduction(+:suma)
  	 	for (int i = 0 ; i <= max ; i++){
      		  if (prime(i)){
         		suma += i;
      		  }
   		}
  		return suma;
	}

	int main(int argc, char* argv[]) {
		int i, *a;
		double ms;
   		double res;
		a = (int *) malloc(sizeof(int) * (MAXIMUM + 1));
		printf("At first, neither is a prime. We will display to TOP_VALUE:\n");
		for (i = 2; i < TOP_VALUE; i++) {
	  	  if (a[i] == 0) {
	  	  printf("%i ", i);
	  	  }
		}

		printf("\n");
		printf("Starting...\n");
		ms = 0;
		for (i = 0; i < N; i++) {
			start_timer();
    		res = sum(MAXIMUM);// call the implemented function
			ms += stop_timer();
		}

   		printf("RES=%f \n",res);
		printf("Expanding the numbers that are prime to TOP_VALUE:\n");
		for (i = 2; i < TOP_VALUE; i++) {
	  	  if (a[i] == 1) {
	  	  printf("%i ", i);
	  	  }
		}
		printf("\n");
		printf("avg time = %.5lf ms\n", (ms / N));

		free(a);
		return 0;
	}
