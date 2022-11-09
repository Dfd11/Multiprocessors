// =================================================================
//
// File: example1.cpp
// Author:
// A01705291 Ramses Aguila Flores 
// A01209414 David Flores Diaz
// speedup = 1701.1889 ms / 379.1172 ms = 448.72 %
// Description: This file contains the code that adds all the
//				elements of an integer array using Intel's TBB. To compile:
//			  	g++ example1.cpp -ltbb
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <tbb/parallel_reduce.h>
#include <tbb/blocked_range.h>
#include "utils.h"
#include <math.h>
const int SIZE = 5000000; //1e9

using namespace std;
using namespace tbb;

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

//class SumPrime {
//private:
//	int *array;
//	long int result;
//public:
//	SumPrime(int *a) : array(a), result(0) {}
//
//	SumPrime(SumPrime &x, split): array(x.array), result(0) {}
//	
//	~SumPrime(){
//		delete [] array;
//	}
//
//	int getResult() {
//		return result;
//	}
//
//	int prime(int num){
//		if (num < 2){
//			return 0;
//		}
//		int lim = sqrt(num);
//		for (int i=2; i <= lim ; i++){
//				if(num % i == 0){
//					return 0;
//				}
//		}
//		return 1;
//	}
//	void operator() (const blocked_range<int> &r) {
//		int *a = array;
//		for (int i = r.begin(); i != r.end(); i++) {
//			if(prime(a[i])){
//				result += a[i];
//			}
//		}
//	}
//
//	void join(SumPrime &x) {
//		result += x.getResult();
//	}
//};

int main(int argc, char* argv[]) {
//	int *a;
	long int result = 0;
	double ms;

//	a = new int[SIZE];
//	fill_array(a, SIZE);
//	display_array("a", a);

	cout << "Starting..." << endl;
	ms = 0;
	for (int j = 1; j <= N; j++) {
		start_timer();

//		SumPrime obj(a);
//		parallel_reduce(blocked_range<int>(0, SIZE), obj);
		result = parallel_reduce(blocked_range<int>(0, SIZE),0.0,[&](blocked_range<int> r,long int running_total) {
			for (long int i = r.begin() ; i != r.end() ; i++){
				if (prime(i)){
					running_total += i;
				}
			}
			return running_total;
		}, plus<long int>());
//		result = obj.getResult();

		ms += stop_timer();
	}
	cout << "sum = " << (long int) result << endl;
	cout << "avg time = " << setprecision(15) << (ms / N) << " ms" << endl;

//	delete [] a;
	return 0;
}
