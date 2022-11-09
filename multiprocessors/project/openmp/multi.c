// =================================================================
//
// File: example1.c
// Author: Pedro Perez
// Description: This file contains the code that adds all the 
//				elements of an integer array using OpenMP.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "utils.h"

#define SIZE 100 //1e8

double sum_euler(int size) {
	double acum;
	int i;
	
	acum = 0;
	#pragma omp parallel for shared(size) reduction(+:acum)
	for (i = 1; i < size; i++) {
		acum += 1/pow(i,2);
		//printf("I= %i, Acum= %f\n",i,acum);
	}
	return acum;
}

int main(int argc, char* argv[]) {
	int i;
	double ms, result;
	
	printf("Starting...\n");
	ms = 0;
	for (i = 0; i < N; i++) {
		start_timer();
		
		result = sum_euler( SIZE);
		
		ms += stop_timer();
	}
	printf("sum = %lf\n", result);
	printf("avg time = %.5lf ms\n", (ms / N));

	return 0;	
}
