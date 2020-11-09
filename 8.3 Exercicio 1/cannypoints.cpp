#include <iostream>
#include "opencv2/opencv.hpp"
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cstdlib>

#define CV_AA cv::LINE_AA

using namespace std;
using namespace cv;

int STEP = 5;
int JITTER = 3;
int RAIO = 3;

int step_slider = 5;
int jitter_slider = 3;
int raio_slider = 3;

int step_slider_max = 20;
int jitter_slider_max = 12;
int raio_slider_max = 12;

int top_slider = 10;
int top_slider_max = 200;

char TrackbarName[50];

int width, height;

Mat image, border, points;

void pontilhismo(int, void*)
{
	vector<int> yrange;
	vector<int> xrange;
	
	int width, height, gray;
	int x, y;
	
	width=image.size().width;
	height=image.size().height;

	xrange.resize(height/STEP);
	yrange.resize(width/STEP);

	iota(xrange.begin(), xrange.end(), 0);
	iota(yrange.begin(), yrange.end(), 0);

	for(uint i=0; i<xrange.size(); i++){
		xrange[i]= xrange[i]*STEP+STEP/2;
	}

	for(uint i=0; i<yrange.size(); i++){
		yrange[i]= yrange[i]*STEP+STEP/2;
	}

	points = Mat(height, width, CV_8U, Scalar(255));

	random_shuffle(xrange.begin(), xrange.end());

	for(auto i : xrange){
		random_shuffle(yrange.begin(), yrange.end());
		for(auto j : yrange){
			x = i+rand()%(2*JITTER)-JITTER+1;
			y = j+rand()%(2*JITTER)-JITTER+1;
			gray = image.at<uchar>(x,y);
			circle(points,
				cv::Point(y,x),
				raio_slider,
				CV_RGB(gray,gray,gray),
				-1,
				CV_AA);
		}
	}
	
	vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
	findContours( border, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE );
	for( size_t i = 0; i< contours.size(); i++ )
    {
		for( size_t j = 0; j< contours[i].size(); j++ )
		{
			gray = image.at<uchar>(contours[i][j].y, contours[i][j].x);
			circle(points,
				cv::Point(contours[i][j].x, contours[i][j].y),
				2,
				CV_RGB(gray,gray,gray),
				-1,
				CV_AA);
		}
    }

	imshow("cannypoints", points);
}

void on_trackbar_canny(int, void*){
  Canny(image, border, top_slider, 3*top_slider);
  pontilhismo(top_slider, 0);
}

int main(int argc, char**argv){

	image= imread("Lenna.png", IMREAD_GRAYSCALE);

	width=image.size().width;
	height=image.size().height;

	namedWindow("cannypoints", WINDOW_AUTOSIZE);
	
	sprintf( TrackbarName, "canny");
	createTrackbar( TrackbarName, "cannypoints",
				&top_slider,
                top_slider_max,
                on_trackbar_canny );
				
	sprintf( TrackbarName, "raio");
	createTrackbar( TrackbarName, "cannypoints",
				&raio_slider,
                raio_slider_max,
                pontilhismo ); 
				
	sprintf( TrackbarName, "jitter");
	createTrackbar( TrackbarName, "cannypoints",
				&jitter_slider,
                jitter_slider_max,
                pontilhismo ); 
				
	sprintf( TrackbarName, "step");
	createTrackbar( TrackbarName, "cannypoints",
				&step_slider,
                step_slider_max,
                pontilhismo ); 
				
	on_trackbar_canny(top_slider, 0 );

	waitKey();
  
	return 0;
}