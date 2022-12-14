// =================================================================
//
// File: example2.cpp
// Author(s):
//		David Flores Diaz
// 		Ramses Aguila Flores
//		09/05/2022
// Description: This file contains the code to count the number of
//				even numbers within an array. The time this implementation
//				takes will be used as the basis to calculate the
//				improvement obtained with parallel technologies.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <climits>
#include <algorithm>
#include "utils.h"

const int SIZE = 1000000000; //1e9

using namespace std;

// implement your class here

int contaPares(int n, int *a){
  int res=0;
  for(int i=0; i < n; i++){
  if(a[i]%2 == 0){res++;}
  }
return res;
}

int main(int argc, char* argv[]) {
	int *a;
	double ms;
	int rp=0, result;

	a = new int[SIZE];
	fill_array(a, SIZE);
	display_array("a", a);

	cout << "Starting..." << endl;
	ms = 0;
	// create object here
	for (int i = 0; i < N; i++) {
		start_timer();

		// call your method here.
		rp=contaPares(SIZE,a);
		ms += stop_timer();
	}
	cout << "result = " << result << endl;
	// display the result here
	cout << "number of pair = " << rp << endl; 
	cout << "avg time = " << setprecision(15) << (ms / N) << " ms" << endl;

	delete [] a;
	return 0;
}
