// =================================================================
//
// File: Example11.java
// Author(s):Ramses Aguila Flores A01705291
// David Flores Diaz A01209414
// Speedup = 5 / 7 = 0.7142 = 71.42 %
// Description: This file implements the code that transforms a
//				grayscale image using Java's Fork-Join.
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
import java.util.concurrent.RecursiveAction;
import java.util.concurrent.ForkJoinPool;

public class Example11 extends RecursiveAction {
        private int src[],dest[],start,end;
	private int MIN = 8_000;
        public Example11 (int src[], int dest[], int start, int end){
                this.src = src;
                this.dest = dest;
                this.start = start;
                this.end = end;
        }

	protected void computeDirectly(){
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

	@Override
	protected void compute(){
		if ((end-start) <= MIN){
			computeDirectly();
		}else{
			int mid = (start+end)/2;
			invokeAll(new Example11(src,dest,start,mid),
				  new Example11(src,dest,mid,end));
		}
	}

        public static void main(String args[]) {
                long startTime, stopTime;
                double ms;
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
		
		ForkJoinPool pool;
                System.out.printf("Starting with %d threads...\n", Utils.MAXTHREADS);
                ms = 0;
	                startTime = System.currentTimeMillis();
			pool = new ForkJoinPool(Utils.MAXTHREADS);
			pool.invoke(new Example11(src,dest,0,SIZE));
	                stopTime = System.currentTimeMillis();
	                ms +=  (stopTime - startTime);
		
                System.out.printf("avg time = %.5f\n", (ms / 1));
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
