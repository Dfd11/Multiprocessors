// =================================================================
//
// File: example11.cpp
// Author(s):
// 23/08/2022
// A01705291 Ramses Aguila Flores
// A01209414 David Flores Diaz
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
#include "utils.h"

// implement your code
void gray_pixel(cv::Mat &src,cv::Mat &dest, int ren, int col){
	float r, g, b;

	r = (float) src.at<cv::Vec3b>(ren, col)[RED];
	g = (float) src.at<cv::Vec3b>(ren, col)[GREEN];
	b = (float) src.at<cv::Vec3b>(ren, col)[BLUE];
   int val = (unsigned char) r * 0.21 + g * 0.72 + b * 0.07 ;
	dest.at<cv::Vec3b>(ren, col)[RED] =  val;
	dest.at<cv::Vec3b>(ren, col)[GREEN] = val;
	dest.at<cv::Vec3b>(ren, col)[BLUE] = val;

}
void gray(cv::Mat &src, cv::Mat &dest) {
	for(int i = 0; i < src.rows; i++) {
		for(int j = 0; j < src.cols; j++) {
			gray_pixel(src, dest, i, j);
		}
	}
}
int main(int argc, char* argv[]) {
	int i;
	double acum;

	if (argc != 2) {
	printf("usage: %s source_file\n", argv[0]);
		return -1;
	}

	cv::Mat src = cv::imread(argv[1], cv::IMREAD_COLOR);
	cv::Mat dest = cv::Mat(src.rows, src.cols, CV_8UC3);
	if (!src.data) {
	printf("Could not load image file: %s\n", argv[1]);
		return -1;
	}

	acum = 0;
	for (i = 0; i < N; i++) {
		start_timer();

		gray(src,dest);// call the implemented function

		acum += stop_timer();
	}

	printf("avg time = %.5lf ms\n", (acum / N));

	/*
	cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
	cv::imshow("Original", src);

	cv::namedWindow("Gray scale", cv::WINDOW_AUTOSIZE);
	cv::imshow("Gray scale", dest);

	cv::waitKey(0);
	*/

	cv::imwrite("gray_scale.png", dest);

	return 0;
}
