// =================================================================
//
// File: example4.c
// Author(s):
// 23/08/2022
// A01705291 Ramses Aguila Flores 
// A01209414 David Flores Diaz
// Description: This file contains the code to count the number of
//				even numbers within an array. The time this implementation
//				takes will be used as the basis to calculate the
//				improvement obtained with parallel technologies.
//
// =================================================================

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// array size
#define SIZE 1000000000 //1x10^9

// implement your code

int contaPares(int n, int *a){
int res=0;
for(int i=0; i < n; i++){
  if(a[i]%2 == 0){res++;}	
  }
return res;
}

int main(int argc, char* argv[]) {
	int i, j,*a, x, rp=0, result;
	double ms;

	a = (int *) malloc(sizeof(int) * SIZE);
	fill_array(a, SIZE);
	display_array("a", a);

	printf("Starting...\n");
	ms = 0;
	for (i = 0; i < N; i++) {
		start_timer();

		// call the implemented function
		rp=contaPares(SIZE,a);
		ms += stop_timer();
	}
	printf("number of pair number = %i\n",rp);
	printf("result = %i\n", result);
	printf("avg time = %.5lf ms\n", (ms / N));
	// must display: result = 500000000

	free(a);
	return 0;
}
