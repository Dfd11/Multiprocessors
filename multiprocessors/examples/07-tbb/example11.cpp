// =================================================================
//
// File: example11.cpp
// Author(s):
// A01705291 Ramses Aguila Flores 
// A01209414 David Flores Diaz
// speedup = 8.18480 ms / 2.1185 ms = 386.34 %
// Description: This file implements the code that transforms a
//				grayscale image using Intel's TBB. Uses OpenCV,
//				to compile:
//	g++ example11.cpp `pkg-config --cflags --libs opencv4` -ltbb
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
#include "utils.h"

using namespace std;
using namespace cv;
using namespace tbb;
//class Gray {
//private:
//	cv::Mat &src,&dest;
//	int ren,col;
//public:
//	Gray(cv::Mat &s, cv::Mat &d,int rn,int cl) : src(s),dest(d),ren(rn),col(cl) {}
//	
//	Gray(Gray &x,tbb::split) : src(x.src), dest(x.dest) , ren(x.ren) , col(x.col) {}
//
//	void operator()(const blocked_range<int> &r)const{
//		for (int i = r.begin(); i != r.end() ; i++){
//			gray_pixel( i/col , i%col );
//		}
//	}

	void gray_pixel(cv::Mat &src , cv::Mat &dest, int ren, int col){
		float r, g, b;

	        r = (float) src.at<cv::Vec3b>(ren, col)[RED];
	        g = (float) src.at<cv::Vec3b>(ren, col)[GREEN];
	        b = (float) src.at<cv::Vec3b>(ren, col)[BLUE];
	   	int val = (unsigned char) r * 0.21 + g * 0.72 + b * 0.07 ;
	        dest.at<cv::Vec3b>(ren, col)[RED] =  val;
	        dest.at<cv::Vec3b>(ren, col)[GREEN] = val;
        	dest.at<cv::Vec3b>(ren, col)[BLUE] = val;

	}

//};
int main(int argc, char* argv[]) {
	double ms;

	if (argc != 2) {
		printf("usage: %s source_file\n", argv[0]);
		return -1;
	}

	Mat src = imread(argv[1], cv::IMREAD_COLOR);
	Mat dest = Mat(src.rows, src.cols, CV_8UC3);
	int size = src.rows * src.cols;
	if (!src.data) {
		printf("Could not load image file: %s\n", argv[1]);
		return -1;
	}

	cout << "Starting..." << endl;
	ms = 0;
	for (int  i = 0; i < N; i++) {
		start_timer();

		// place your code here
//		Gray obj(src,dest,src.rows,src.cols);
//		parallel_for(blocked_range<int>(0,size),obj);
		parallel_for(blocked_range<int>(0,size),[&](blocked_range<int> r){
			for(int i=r.begin(); i != r.end() ; i++){
				gray_pixel(src,dest,i/src.cols , i%src.cols);
			}
		
		});
		ms += stop_timer();
	}

	cout << "avg time = " << setprecision(15) << (ms / N) << " ms" << endl;


	cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
	cv::imshow("Original", src);

	cv::namedWindow("Gray scale", cv::WINDOW_AUTOSIZE);
	cv::imshow("Gray scale", dest);

	cv::waitKey(0);
	

	cv::imwrite("gray_scale.png", dest);

	return 0;
}
