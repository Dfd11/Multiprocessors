// =================================================================
//
// File: Example1.java
// Author: Pedro Perez
// Description: This file contains the code that adds all the
//				elements of an integer array. The time this
//				implementation takes will be used as the basis to
//				calculate the improvement obtained with parallel
//				technologies.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================
import java.math.*;
public class multi extends Thread{
	private static final int SIZE = 100_000_000;
	private int start,end;
	private double result;

	public multi(int start, int end) {
		this.start = start;
		this.end = end;
		this.result = 0;
	}

	public double getResult() {
		return this.result;
	}

	public void run() {
		this.result = 0;
		for (int i = start; i < end; i++) {
			this.result += 1/(Math.pow(i,2));
		}
	}

	public static void main(String args[]) {
		long startTime, stopTime;
		double acum = 0;
		int block;
		multi threads[];
		double result = 0;

		acum = 0;
		block = SIZE / Utils.MAXTHREADS;
		threads = new multi[Utils.MAXTHREADS];

		System.out.printf("Starting with %d threads...\n",Utils.MAXTHREADS);
		for (int i = 0; i < Utils.N; i++) {
			for (int j = 0 ; j < threads.length; j++){
				if (j != threads.length - 1){
					threads[j] = new multi((j*block)+1, ((j+1) * block)+1);
				} else {
					threads[j] = new multi((j*block)+1,SIZE);

				}
			}
			startTime = System.currentTimeMillis();

			for (int j = 0; j < threads.length; j++){
				threads[j].start();
			}
			
			for (int j = 0; j < threads.length; j++){
				try {
					threads[j].join();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
			stopTime = System.currentTimeMillis();
			acum += (stopTime - startTime);

			if (i == Utils.N - 1){
				for (int j = 0; j < threads.length ; j++){
					result += threads[j].getResult();
				}
			}
		}
		System.out.printf("sum = %f\n", Math.sqrt(result*6));
		System.out.printf("avg time = %.5f ms\n", (acum / Utils.N));
	}
}
