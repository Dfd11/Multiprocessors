// =================================================================
//
// File: example1.cpp
// Author: Pedro Perez
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

const int SIZE = 100000; //1e9

using namespace std;
using namespace tbb;

class Multi {
private:
	int *array;
	double result;
public:
	Multi(int *a) : array(a), result(0) {}

	Multi(Multi &x, split): array(x.array), result(0) {}

	double getResult() const {
		return sqrt(result*6);
	}

	void operator() (const blocked_range<int> &r) {
		int *a = array;
		for (int i = r.begin(); i != r.end(); i++) {
			result += 1/pow(a[i],2);
		}
	}

	void join(const Multi &x) {
		result += x.result;
	}
};

int main(int argc, char* argv[]) {
	int *a;
	double result = 0;
	double ms;

	a = new int[SIZE];
	fill_array(a, SIZE);
	display_array("a", a);

	cout << "Starting..." << endl;
	ms = 0;
	for (int i = 1; i <= N; i++) {
		start_timer();

//		Multi obj(a);
//		parallel_reduce(blocked_range<int>(0, SIZE), obj);
//		result = obj.getResult();
		result = parallel_reduce(blocked_range<int>(1,SIZE),0.0,[&](blocked_range<int> r, double result){
			for(int i= r.begin() ; i != r.end() ; i++){
				result += 1/pow(i,2);
			}
			return result;
		},plus<double>());
		ms += stop_timer();
	}
	cout << "sum = " << (double) sqrt(result*6) << endl;
	cout << "avg time = " << setprecision(15) << (ms / N) << " ms" << endl;

	delete [] a;
	return 0;
}
