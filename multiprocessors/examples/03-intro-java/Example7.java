// =================================================================
//
// File: Example7.java
// Author(s):
// 19/09/2022
// A01705291 Ramses Aguila Flores
// A01209414 David Flores Diaz
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

public class Example7 {
	private static final int SIZE = 1_000_000;
	private boolean array[];

	public Example7(boolean array[]) {
		this.array = array;
	}

	// place yout code here
	static boolean prime (int n){
	  int lim;
	  if (n < 2)
	    return false;
	  lim = (int)Math.sqrt(n);
	  for (int i = 2 ; i <= lim ; i++){
	    if (n % i == 0){
	      return false;
	    }
	  }
	  return true;
	}

	static double sum (int max){
	  double suma=0;
	  for (int i=0 ; i <= max ; i++){
	    if(prime(i)){
	      suma += i;
	    }
	  }
	  return suma;
	}

	public void calculate() {
		// place yout code here
	}

	public static void main(String args[]) {
		boolean array[] = new boolean[SIZE + 1];
		long startTime, stopTime;
		double acum = 0; 
		double res = 0;

		System.out.println("At first, neither is a prime. We will display to TOP_VALUE:");
		for (int i = 2; i < Utils.TOP_VALUE; i++) {
			array[i] = false;
			System.out.print("" + i + ", ");
		}
		System.out.println("");

		// Create the object here.
		acum = 0;
		System.out.printf("Starting...\n");
		for (int i = 0; i < Utils.N; i++) {
			startTime = System.currentTimeMillis();

			// Call yout method here.
			res = sum(SIZE);
			stopTime = System.currentTimeMillis();

			acum += (stopTime - startTime);
		}
		System.out.println("Expanding the numbers that are prime to TOP_VALUE:");
		for (int i = 2; i < Utils.TOP_VALUE; i++) {
			if (array[i]) {
				System.out.print("" + i + ", ");
			}
		}
		System.out.printf("Sum of primes = %f\n", res);
		System.out.println("");
		System.out.printf("avg time = %.5f ms\n", (acum / Utils.N));
	}
}
