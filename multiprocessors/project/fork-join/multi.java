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
import java.util.concurrent.RecursiveTask;
import java.util.concurrent.ForkJoinPool;

public class multi extends RecursiveTask<Double> {
	private static final int SIZE = 100_000_000;
	private int MIN = 1_000;
	private int start,end;
	private double result;

	public multi(int start, int end, int min) {
		this.start = start;
		this.end = end;
		this.MIN = min;
		this.result = 0;
	}

	public double getResult() {
		return this.result;
	}

	protected Double computeDirectly(){
		this.result = 0;
		for (int i = start; i < end; i++) {
			this.result += 1/(Math.pow(i,2));
		}
		return this.result;
	}

	@Override
	protected Double compute(){
		if ( (end - start) <= MIN){
			return computeDirectly();
		} else {
			int mid = ( start + end)/2;
			multi lowerMid = new multi(start,mid,this.MIN);
			lowerMid.fork();
			multi upperMid = new multi(mid,end,this.MIN);
			return upperMid.compute() + lowerMid.join();
		}
	}

	public static void main(String args[]) {
		long startTime, stopTime;
		double acum = 0;
		ForkJoinPool pool;
		for (int min = 1_000 ; min <= 100_000_000 ; min = min * 10){
			double result = 0;

			acum = 0;
			System.out.printf("Starting with %d threads...\n",Utils.MAXTHREADS);
			for (int i = 0; i < Utils.N; i++) {
				startTime = System.currentTimeMillis();

				pool = new ForkJoinPool(Utils.MAXTHREADS);
				result = pool.invoke(new multi(1,SIZE,min));

				stopTime = System.currentTimeMillis();
				acum += (stopTime - startTime);

			}
			System.out.printf("sum = %f\n", Math.sqrt(result*6));
			System.out.printf("MIN=%d \n avg time = %.5f ms\n",min, (acum / Utils.N));
		}
	}
}
