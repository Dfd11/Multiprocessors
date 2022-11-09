// =================================================================
//
// File: Example7.java
// Author(s):
// Ramses Aguila Flores A01705291
// David Flores Diaz A01209414
// speedup = 312.4 / 56 = 5.5785 = 557.85 %
// Description: This file contains the code to brute-force all
//				prime numbers less than MAXIMUM using Java's
//				Fork-Join.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

import java.util.Arrays;
import java.math.*;
import java.util.concurrent.RecursiveTask;
import java.util.concurrent.ForkJoinPool;

public class Example7 extends RecursiveTask<Double> {
	private static final int MAXIMUM = 1_000_000;
	private static final int MIN = 1_000;
	private int array[], start, end;

  // place your code here
	public Example7(int array[], int start, int end){
		this.array = array;
		this.start = start;
		this.end = end;
	}

	private boolean prime(int num){
		if(num < 2){
			return false;
		}
		int lim=(int)Math.sqrt(num);
		for (int i=2;i<=lim;i++){
			if(num % i == 0){
			return false;
			}
		}
		return true;
	}

	protected Double computeDirectly() {
                double result = 0;
                for (int i = start; i < end; i++) {
                        if(prime(i)){
                                result+=i;
                        }
                }
		return result;
        }

	@Override
        protected Double compute() {
                if ( (end - start) <= MIN ) {
                        return computeDirectly();
                } else {
                        int mid = start + ( (end - start) / 2 );
                        Example7 lowerMid = new Example7(array, start, mid);
                        lowerMid.fork();
                        Example7 upperMid = new Example7(array, mid, end);
                        return upperMid.compute() + lowerMid.join();
                }
        }

	public static void main(String args[]) {
                long startTime, stopTime; 
		double result = 0;
                int array[];
                double ms;
                ForkJoinPool pool;

                array = new int[MAXIMUM];
                Utils.fillArray(array);
                Utils.displayArray("array", array);

                System.out.printf("Starting with %d threads...\n", Utils.MAXTHREADS);
                ms = 0;
                for (int i = 0; i < Utils.N; i++) {
                        startTime = System.currentTimeMillis();

                        pool = new ForkJoinPool(Utils.MAXTHREADS);
                        result = pool.invoke(new Example7(array, 0, array.length));

                        stopTime = System.currentTimeMillis();
                        ms += (stopTime - startTime);
                }
                System.out.printf("sum = %f\n", result);
                System.out.printf("avg time = %.5f ms\n", (ms / Utils.N));
        }

}
