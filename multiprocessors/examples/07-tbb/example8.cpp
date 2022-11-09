// =================================================================
//
// File: example8.cpp
// Author:
// A01705291 Ramses Aguila Flores 
// A01209414 David Flores Diaz
//speedup = 381.5452 ms / 91.0088 ms = 419.23 %
// Description: This file contains the code that implements the
//				enumeration sort algorithm using Intel's TBB.
//				To compile: g++ example8.cpp -ltbb
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
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
#include "utils.h"

const int SIZE = 10000;

using namespace std;
using namespace tbb;

class EnumSort {
private:
	int *array, *res;
public:
	EnumSort(int *a, int *r): array(a) , res(r){}
	EnumSort(EnumSort &x,split): array(x.array) , res(x.res) {}

	void operator() (const blocked_range<int> &r) const{
		int k;
		for (int i= r.begin() ; i != r.end() ; i++){
			k=0;
			for (int j = 0; j < SIZE ; j++){
				if (array[i] > array[j] ) {
					k++;
				}else if(( array[i] == array[j]) && (i < j)){
					k++;
				}
			}
			res[k] = array[i];
		}
	}
};
// place your code here
int main (int argc, char* argv[]){
	int *array, *res;
	double ms;

	array = new int[SIZE];
	random_array(array,SIZE);
	display_array("A",array);

	res = new int[SIZE];

	cout << "Starting..." << endl;
	ms = 0;
	EnumSort obj(array,res);
	for (int i=1 ; i<= N ; i++){
		start_timer();
		parallel_for(blocked_range<int>(0,SIZE),obj);
		ms += stop_timer();
	}
	display_array("Res",res);
	cout << "avg time = " << setprecision(15) << (ms/N) << " ms" << endl;

	delete [] array;
	delete [] res;
	return 0;
}
