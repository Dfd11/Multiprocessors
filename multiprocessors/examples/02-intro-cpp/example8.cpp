// =================================================================
//
// File: example8.cpp
// Author: Pedro Perez
//		David Flores Diaz
//		Ramses Aguila Flores
//		09/05/2022
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

#include <iostream>
#include <iomanip>
#include <cstring>
#include "utils.h"

const int SIZE = 10000; //1e5

using namespace std;

void acomodar(int *x, int *r, int s){
   for (int i=0; i < s; i++){
      int e= x[i];
      int k=0;
      for (int j=0; j < s; j++){
         if( e > x[j] ){
            k++;
         }else if( e == x[j] && i < j){
            k++;
         }
      }
      r[k]=e;
   }
}
// implement your class here

int main(int argc, char* argv[]) {
	int i,*a , *r;
	double ms;
   r = new int[SIZE];
	a = new int[SIZE];
	random_array(a, SIZE);
	display_array("before", a);

	cout << "Starting..." << endl;
	ms = 0;
	// create object here
	for (int i = 0; i < N; i++) {
		start_timer();
      
      acomodar( a ,r ,SIZE);
		// call your method here.

		ms += stop_timer();
	}

	display_array("after", r);
	cout << "avg time = " << setprecision(15) << (ms / N) << " ms" << endl;

	delete [] a;
	return 0;
}
