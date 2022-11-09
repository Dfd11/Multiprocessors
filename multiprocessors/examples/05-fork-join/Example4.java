// =================================================================
//
// File: Example4.java
// Authors:
// Ramses Aguila Flores A01705291
// David Flores Diaz A01209414
// Speedup = 200.2/44.7  = 4.4787= 447.87 %
// Description: This file contains the code to count the number of
//				even numbers within an array using Java's Fork-Join.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================
import java.util.concurrent.RecursiveTask;
import java.util.concurrent.ForkJoinPool;

public class Example4 extends RecursiveTask<Long> {
	private static final int SIZE = 100_000_000;
	private static final int MIN = 100_000;
	private int array[], start, end;

	// place your code here

	public Example4(int array[], int start, int end){
		this.array = array;
		this.start = start;
		this.end = end;
	}

	protected Long computeDirectly() {
		long result = 0;
		for (int i = start; i < end; i++) {
			if(array[i] % 2 == 0){
				result++;
			}
		}
		return result;
	}

	@Override
	protected Long compute() {
		if ( (end - start) <= MIN ) {
			return computeDirectly();
		} else {
			int mid = start + ( (end - start) / 2 );
			Example4 lowerMid = new Example4(array, start, mid);
			lowerMid.fork();
			Example4 upperMid = new Example4(array, mid, end);
			return upperMid.compute() + lowerMid.join();
		}
	}

	public static void main(String args[]) {
		long startTime, stopTime, result = 0;
		int array[];
		double ms;
		ForkJoinPool pool;

		array = new int[SIZE];
		Utils.fillArray(array);
		Utils.displayArray("array", array);

		System.out.printf("Starting with %d threads...\n", Utils.MAXTHREADS);
		ms = 0;
		for (int i = 0; i < Utils.N; i++) {
			startTime = System.currentTimeMillis();

			pool = new ForkJoinPool(Utils.MAXTHREADS);
			result = pool.invoke(new Example4(array, 0, array.length));

			stopTime = System.currentTimeMillis();
			ms += (stopTime - startTime);
		}
		System.out.printf("sum = %d\n", result);
		System.out.printf("avg time = %.5f ms\n", (ms / Utils.N));
	}

}
