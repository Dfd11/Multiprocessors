// =================================================================
//
// File: example1.cpp
// Author: 
// A01705291 Ramses Aguila Flores 
// A01209414 David Flores Diaz
// speedup = 15.8767 ms / 4.1743 ms = 380.34 %
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

const int SIZE = 10000000; //1e9

using namespace std;
using namespace tbb;

//class CountEven {
//private:
//	int *array;
//	long int result;
//
//public:
//	CountEven(int *a) : array(a), result(0) {}
//
//	CountEven(CountEven &x, split): array(x.array), result(0) {}
//
//	long int getResult() {
//		return result;
//	}
//
//	void operator() (const blocked_range<int> &r) {
//		int *a = array;
//		for (int i = r.begin(); i != r.end(); i++) {
//			if (a[i] % 2 == 0){
//				result ++;
//			}
//		}
//	}
//
//	void join(const CountEven &x) {
//		result += x.result;
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
	for (int i = 1; i <= N; i++) {
		start_timer();

//		CountEven obj(a);
//		parallel_reduce(blocked_range<int>(0, SIZE), obj);
		result = parallel_reduce(blocked_range<int>(0, SIZE),0.0,[&](blocked_range<int> r,long int total){
			for (int i = r.begin() ; i != r.end() ; i++){
				if(i%2==0){
					total ++;
				}
			}
			return total;
		},plus<int>());
//		result = obj.getResult();

		ms += stop_timer();
	}
	cout << "sum = " << (long int) result << endl;
	cout << "avg time = " << setprecision(15) << (ms / N) << " ms" << endl;

//	delete [] a;
	return 0;
}
