// =================================================================
//
// File: Example7.java
// Author(s):
// Ramses Aguila Flores A01705291
// David Flores Diaz A01209414
// speedup = 312.4 / 183.7 = 1.7005 = 170.05 %
// Description: This file contains the code to brute-force all
//				prime numbers less than MAXIMUM. The time this
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

public class Example7 extends Thread {
	private static final int SIZE = 1_000_000;
        private int array[], start, end;
        private double result;

        // place your code here

        public Example7(int array[], int start, int end) {
                this.array = array;
                this.start = start;
                this.end = end;
                this.result = 0;
        }

        public double getResult() {
                return result;
        }

	private boolean prime(int num){
		if(num <2){
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

        public void run() {
                result = 0;
                for(int i = start ; i < end ; i++) {
                        if(prime(i)){
                                result+=i;
                        }
                }
        }


        public static void main(String args[]){
                long startTime, stopTime;
                int array[], block;
                Example7 threads[];
                double ms;
                double result = 0;

                array = new int[SIZE];

                Utils.fillArray(array);
                Utils.displayArray("array", array);

                block = SIZE / Utils.MAXTHREADS;
                threads = new Example7[Utils.MAXTHREADS];

                System.out.printf("Starting with %d threads...\n", Utils.MAXTHREADS);
                ms = 0;

                for (int j = 1; j <= Utils.N; j++) {
                        for (int i = 0; i < threads.length; i++) {
                                if (i != threads.length - 1) {
                                        threads[i] = new Example7(array, (i * block), ((i + 1) * block));
                                } else {
                                        threads[i] = new Example7(array, (i * block), SIZE);
                                }
                        }

                        startTime = System.currentTimeMillis();
                        for (int i = 0; i < threads.length; i++) {
                                threads[i].start();
                        }
                        /** -------- */
                        result = 0;
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
                for (int i = 0; i < threads.length; i++) {
                result += threads[i].getResult();
                }

                System.out.printf("sum = %f\n", result);
                System.out.printf("avg time = %.5f ms\n", (ms / Utils.N));
        }
}

