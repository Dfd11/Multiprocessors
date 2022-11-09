// =================================================================
//
// File: Example8.java
// Author: Ramses Aguila Flores A01705291
//	David Flores Diaz A01209414
// Description: This file implements the enumeration sort algorithm.
// 				The time this implementation takes will be used as the
//				basis to calculate the improvement obtained with
//				parallel technologies.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

import java.util.Arrays;

public class Example8 {
	private static final int SIZE = 100_000;
	private int array[];

	public Example8(int array[]) {
		this.array = array;
	}

	public void doTask() {
		int res [] = new int[SIZE];
		for (int i = 0 ; i < SIZE ; i++){
			int e = array[i];
			int k = 0;
			for (int j = 0; j < SIZE ; j++){
				if (e > array[j]) {
					k++;
				}else if( (e == array[j]) && (i < j)) {
					k++;
				}
			}
			res[k] = e;
		}
		array = res;
	}

	public int[] getSortedArray() {
		return array;
	}

	public static void main(String args[]) {
		int array[] = new int[SIZE];
		long startTime, stopTime;
		double ms;

		Utils.randomArray(array);
		Utils.displayArray("before", array);
		Example8 obj = new Example8(array);
		System.out.printf("Starting...\n");
		ms = 0;
		for (int i = 0; i < Utils.N; i++) {
			startTime = System.currentTimeMillis();

			obj.doTask();	// pace your code here.

			stopTime = System.currentTimeMillis();

			ms += (stopTime - startTime);
		}
		Utils.displayArray("after", obj.getSortedArray());
		System.out.printf("avg time = %.5f\n", (ms / Utils.N));
	}
}
