// =================================================================
//
// File: Example8.java
// Author(s):Ramses Aguila Flores A01705291
// David Flores Diaz A01209414
// Speedup =10739 / 5077.7 = 2.1149= 211.49 %
// Description: This file implements the enumeration sort algorithm
// 				using Java's Fork-Join.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================
import java.util.concurrent.RecursiveAction;
import java.util.concurrent.ForkJoinPool;

public class Example8 extends RecursiveAction {
	private static final int SIZE = 100_000;
	private static final int MIN = 1_000;
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

	protected void computeDirectly(){
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
	@Override
	protected void compute(){
		if( ( end - start ) <= MIN ){
			computeDirectly();
		}else {
			int mid = (start+end)/2 ;
			invokeAll(new Example8(array,res,start,mid),
				  new Example8(array,res,mid,end));
		}
	}

	public static void main(String args[]) {
		long startTime, stopTime;
		double ms;
		int array[] = new int[SIZE];
		int res[] = new int [SIZE];

		ForkJoinPool pool;
		Utils.randomArray(array);
		Utils.displayArray("before",array);
		System.out.printf("Starting with %d threads...\n", Utils.MAXTHREADS);
		ms = 0;
		for (int i = 0; i < Utils.N; i++) {
			startTime = System.currentTimeMillis();

			pool = new ForkJoinPool(Utils.MAXTHREADS);
			pool.invoke(new Example8(array, res, 0, array.length));

			stopTime = System.currentTimeMillis();
			ms += (stopTime - startTime);
		}
		Utils.displayArray("after", res);
		System.out.printf("avg time = %.5f\n", (ms / Utils.N));
	}
}
