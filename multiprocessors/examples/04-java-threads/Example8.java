// =================================================================
//
// File: Example8.java
// Author: Ramses Aguila Flores A01705291
// David Flores Diaz A01209414
// speedup =  67006 /  1038 =  64.5529 = 6455.29 %
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

public class Example8 extends Thread {
	private static final int SIZE = 100_000;
	private int array[],res[],start,end;

	public Example8 (int array[], int res[], int start, int end){
		this.array = array;
		this.res = res;
		this.start = start;
		this.end = end;
	}
	public int[] getArray(){
		return res;
	}

	public void run(){
		int k;
		for (int i=start ; i < end ; i++){
			k = 0;
			for (int j=0 ; j < SIZE ; j++){
				if ( array[i] > array[j] ){
					k++;
				}else if( (array[i] == array[j]) && (i < j) ){
					k++;
				}
			}
			res[k] = array [i];
		}
	}

	public static void main(String args[]) {
		long startTime, stopTime;
		double ms;
		int block;
		Example8 threads[];
		int array[] = new int[SIZE];
		int res[] = new int [SIZE];
		Utils.randomArray(array);
		Utils.displayArray("before",array);
//define number of threads
		block = SIZE / Utils.MAXTHREADS;
//initialize the threads to default
		threads = new Example8[Utils.MAXTHREADS];


		System.out.printf("Starting with %d threads...\n", Utils.MAXTHREADS);
		ms = 0;
//set the limits on each thread
			for (int i = 0 ; i < threads.length ; i++) {
				if (i != threads.length - 1){
					threads[i] = new Example8(array,res,block * i, block * i + block);
				}else {
					threads[i] = new Example8(array,res,block * i, SIZE);
				}
			} 
		for (int i = 0; i < Utils.N ; i++){
			startTime = System.currentTimeMillis();
//start each thread
			for (int i = 0; i < threads.length; i++) {
				threads[i].start();
			}
			for (int i = 0; i < threads.length; i++) {
				try {
					threads[i].join();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
			stopTime = System.currentTimeMillis();
			ms +=  (stopTime - startTime);
		}
		
//print result
		Utils.displayArray("After",res);
		System.out.printf("avg time = %.5f\n", (ms / Utils.N));
	}	
}
