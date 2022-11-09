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

const int SIZE = 100000000; //1e9

using namespace std;
using namespace tbb;

class AddArray {
private:
	double result;

public:
	AddArray() : result(0) {}

	AddArray(AddArray &x, split): result(0) {}

	double getResult() const {
		return result;
	}

	void operator() (const blocked_range<int> &r) {
		for (int i = r.begin(); i != r.end(); i++) {
			result += 1/pow(i,2);
		}
	}

	void join(const AddArray &x) {
		result += x.result;
	}
};

int main(int argc, char* argv[]) {
	double result = 0;
	double ms;

	cout << "Starting..." << endl;
	ms = 0;
	for (int i = 1; i <= N; i++) {
		start_timer();

		AddArray obj();
		parallel_reduce(blocked_range<int>(1, SIZE), obj);
		result = obj.getResult();

		ms += stop_timer();
	}
	cout << "sum = " << (double) result << endl;
	cout << "avg time = " << setprecision(15) << (ms / N) << " ms" << endl;

	return 0;
}
