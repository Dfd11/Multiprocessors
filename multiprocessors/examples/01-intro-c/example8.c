// =================================================================
//
// File: example8.c
// Author(s):
// 23/08/2022
// A01705291 Ramses Aguila Flores
// A01209414 David Flores Diaz
// Description: This file contains the code that implements the
//				enumeration sort algorithm. The time this implementation
//				takes ill be used as the basis to calculate the
//				improvement obtained with parallel technologies.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define SIZE 50000

// implement your code

void acomodar(int *x, int *r, int s){
	for(int i=0;i<s;i++){
	int e=x[i];
	int k=0;
	for(int j=0;j<s;j++){
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
	int i, *a, *r;
	double ms;

	r = (int*) malloc(sizeof(int) * SIZE);
	a = (int*) malloc(sizeof(int) * SIZE);
	random_array(a, SIZE);
	display_array("before", a);

	printf("Starting...\n");
	ms = 0;
	for (i = 0; i < N; i++) {
		start_timer();

		// call the implemented function
		acomodar(a,r,SIZE);

		ms += stop_timer();
	}
	display_array("after", r);
	printf("avg time = %.5lf ms\n", (ms / N));

	free(a);
	return 0;
}
