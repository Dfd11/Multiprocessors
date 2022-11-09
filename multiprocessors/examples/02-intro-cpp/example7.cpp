// =================================================================
//
// File: example7.cpp
// Author: David Flores Diaz
//	   Ramses Aguila Flores
//  09/05/2022
// Description: This file contains the code to brute-force all
//				prime numbers less than MAXIMUM. The time this
//				implementation takes will be used as the basis to
//				calculate the improvement obtained with parallel
//				technologies.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <algorithm>
#include "utils.h"

#define MAXIMUM 5000000 //5e6

using namespace std;

// implement your class here
double prime(int n){
   int lim;
   if (n < 2)
      return 0;
   lim=sqrt(n);
   for (int i = 2; i <= lim; i++){
      if (n % i == 0){
         return 0;
      }
   }
   return 1;

}
double sum (int max){
   double suma=0;
   for (int i = 0; i <= max ; i++){
      if (prime(i)){
         suma += i;
      }
   }
   return suma;
}
int main(int argc, char* argv[]) {
	int i,*a;
	double ms;
   double res=0;
   a = new int[MAXIMUM +1];
	cout << "Starting..." << endl;
	ms = 0;
	// create object here
	for (int i = 0; i < N; i++) {
		start_timer();

      res = sum(MAXIMUM);// call the implemented function

		ms += stop_timer();
	}
	cout << "result = " << setprecision(15) << res;
	cout << "avg time = " << setprecision(15) << (ms / N) << " ms" << endl;

	delete [] a;
	return 0;
}


