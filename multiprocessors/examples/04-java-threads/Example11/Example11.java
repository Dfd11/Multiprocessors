// =================================================================
//
// File: Example11.java
// Author(s): Ramses Aguila Flores A01705291
// David Flores Diaz A01209414
// speedup = 2.3 / 12.5 = 0.184 = 18.4 %
// Description: This file implements the code that transforms a
//				grayscale image. The time this implementation takes will
//				be used as the basis to calculate the improvement obtained
// 				with parallel technologies.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

import java.awt.image.BufferedImage;
import java.io.File;
import javax.imageio.ImageIO;
import java.io.IOException;

public class Example11 extends Thread{
	private int src[],dest[],start,end;

	public Example11 (int src[], int dest[], int start, int end){
		this.src = src;
		this.dest = dest;
		//this.width = width;
		//this.height = height;
		this.start = start;
		this.end = end;
	}
	public int[] getArray(){
		return dest;
	}

	public void run(){
		int val,r,g,b;
		int k;
		for (int i=start ; i < end ; i++){
			val = src[i];
			r = (int)(((val & 0x00ff0000) >> 16) ) ;
			g = (int)(((val & 0x0000ff00) >> 8)  ) ;
			b = (int)((val & 0x000000ff)         ) ;
			val =(int) ((r + g + b) / 3);
			dest  [i] = 0xff << 24 | (val << 16) | (val << 8) | val;
		}
	}

	public static void main(String args[]) {
		long startTime, stopTime;
		double ms;
		int block;
		Example11 threads[];
		if (args.length != 1) {
			System.out.println("usage: java Example11 image_file");
			System.exit(-1);
		}

		final String fileName = args[0];
		File srcFile = new File(fileName);
	        BufferedImage sourcer = null;

		try {
			sourcer = ImageIO.read(srcFile);
		} catch (IOException ioe) {
			ioe.printStackTrace();
		}
		final BufferedImage source = sourcer;
		int w = source.getWidth();
		int h = source.getHeight();
		int src[] = source.getRGB(0, 0, w, h, null, 0, w);
		int dest[] = new int[src.length];
		int SIZE = w * h;

//define number of threads
		block = SIZE / Utils.MAXTHREADS;
//initialize the threads to default
		threads = new Example11[Utils.MAXTHREADS];


		System.out.printf("Starting with %d threads...\n", Utils.MAXTHREADS);
		ms = 0;
//set the limits on each thread
		for (int i = 0 ; i < threads.length ; i++) {
			if (i != threads.length - 1){
				threads[i] = new Example11(src,dest,block * i, block * i + block);
			}else {
				threads[i] = new Example11(src,dest,block * i, SIZE);
			}
		} 
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
		
//print result
		System.out.printf("avg time = %.5f\n", (ms / Utils.N));
		final BufferedImage destination = new BufferedImage(w, h, BufferedImage.TYPE_INT_ARGB);
		destination.setRGB(0, 0, w, h, dest, 0, w);

		javax.swing.SwingUtilities.invokeLater(new Runnable() {
            			public void run() {
               				ImageFrame.showImage("Original - " + fileName, source);
    	 			}
	 	});

		javax.swing.SwingUtilities.invokeLater(new Runnable() {
            			public void run() {
               				ImageFrame.showImage("Gray - " + fileName, destination);
            			}
        	});

	}	
}
