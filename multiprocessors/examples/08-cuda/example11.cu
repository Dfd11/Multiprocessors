// =================================================================
//
// File: example11.cpp
// Author(s):
// A01705291 Ramses Aguila Flores 
// A01209414 David Flores Diaz
// speedup = 7.68680 ms / 0.00310 ms = 247961.29 %
// Description: This file implements the code that transforms a
//				grayscale image. Uses OpenCV, to compile:
//				g++ example11.cpp `pkg-config --cflags --libs opencv4`
//
//				The time this implementation takes will be used as the
//				basis to calculate the improvement obtained with
//				parallel technologies.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include "utils.h"
typedef unsigned char uchar;

__global__ void gray(uchar *src, uchar *dest, int size) { 

	int tid = ((blockIdx.x * blockDim.x) + threadIdx.x) * 3;
	while (tid < size){
		int val = 0;
		val += src[tid + 0];
		val += src[tid + 1];
		val += src[tid + 2];

		val /= 3;

		dest[tid + 0] = val;
		dest[tid + 1] = val;
		dest[tid + 2] = val;

		tid += blockDim.x * gridDim.x * 3;
	}
}

int main(int argc, char* argv[]) {
	int i;
	double acum; 
 	uchar *dev_src, *dev_dest;
		
	cv::Mat  src = cv::imread(argv[1],cv::IMREAD_COLOR);
	cv::Mat dest = cv::Mat(src.rows, src.cols, CV_8UC3);

  	long size = src.rows * src.cols * 3;

	cudaMalloc((void**) &dev_src, size * sizeof(uchar));
	cudaMalloc((void**) &dev_dest, size * sizeof(uchar));
	
	cudaMemcpy(dev_src, src.data, size * sizeof(uchar), cudaMemcpyHostToDevice);
	
	acum = 0;
	printf("Starting...\n");
	for (i = 0; i < N; i++) {
		start_timer();

		gray<<<src.rows, src.cols>>>(dev_src, dev_dest, size);

		acum += stop_timer();
	}
	
	cudaMemcpy(dest.data, dev_dest, size*sizeof(uchar), cudaMemcpyDeviceToHost);
	
	cudaFree(dev_dest);
	cudaFree(dev_src);
	
	printf("avg time = %.5lf ms\n", (acum / N));

	cv::imwrite("gray.bmp", dest);

	return 0;
}
