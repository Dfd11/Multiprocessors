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
public class single {
	private static final int SIZE = 100_000_000;
	private double result;

	public single() {
		this.result = 0;
	}

	public double getResult() {
		return Math.sqrt(result*6);
	}

	public void calculate() {
		result = 0;
		for (int i = 1; i < SIZE; i++) {
			result += 1/(Math.pow(i,2));
		}
	}

	public static void main(String args[]) {
		long startTime, stopTime;
		double acum = 0;


		single e = new single();
		acum = 0;
		System.out.printf("Starting...\n");
		for (int i = 0; i < Utils.N; i++) {
			startTime = System.currentTimeMillis();

			e.calculate();

			stopTime = System.currentTimeMillis();

			acum += (stopTime - startTime);
		}
		System.out.printf("sum = %f\n", e.getResult());
		System.out.printf("avg time = %.5f ms\n", (acum / Utils.N));
	}
}
