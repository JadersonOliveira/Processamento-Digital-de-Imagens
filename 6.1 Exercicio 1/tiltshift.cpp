#include <iostream>
#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

double alfa;
int alfa_slider = 0;
int alfa_slider_max = 100;

int top_slider = 0;
int top_slider_max = 100;

int center_slider = 50;
int center_slider_max = 100;

Mat image1, image2, blended, imagehsv;
Mat imageTop;
Mat frame32f, mask1, mask2;
vector<Mat> channels;

int width, height;

char TrackbarName[50];

void on_trackbar_blend(int, void*){
	alfa = (double) alfa_slider/alfa_slider_max ;
	addWeighted( image1, alfa, imageTop, 1-alfa, 0.0, blended);
	imshow("tiltshift", blended);
}

int limitHeightBound(int faixa){
	if(faixa <= 0){
		return 1;
	}else if(faixa >= height){
		return height-1;
	}else{
		return faixa;
	}
}

void on_trackbar_height(int, void*){
	image1.copyTo(imageTop);
	
	int center = center_slider*(height-1)/100;
	int focusedHeight = top_slider*(height-1)/200;
	
	Mat tmp = image2(Rect(0, 0, width, limitHeightBound(center-focusedHeight)));
	tmp.copyTo(imageTop(Rect(0, 0, width, limitHeightBound(center-focusedHeight))));
	tmp = image2(Rect(0, limitHeightBound(center+focusedHeight), width,limitHeightBound(height-(center+focusedHeight))));
	tmp.copyTo(imageTop(Rect(0, limitHeightBound(center+focusedHeight), width,limitHeightBound(height-(center+focusedHeight)))));
	on_trackbar_blend(alfa_slider,0);
}

int main(int argvc, char** argv){
	image1 = imread("Natal_PontaNegra.jpg", IMREAD_COLOR);
	
	width = image1.size().width;
	height = image1.size().height;
	
	image1.copyTo(image2);
	image2.copyTo(imageTop);
	namedWindow("tiltshift", 1);
	
	//Máscara da média
	float media[] = {1,1,1,
					 1,1,1,
					 1,1,1};
					 
	image2.convertTo(image2, CV_32FC3);
	mask1 = Mat(3, 3, CV_32F, media);
	scaleAdd(mask1, 1/9.0, Mat::zeros(3,3,CV_32F), mask2);
	
	for(int i = 0; i < 10; i++){
		filter2D(image2, image2, image2.depth(), mask2, Point(1,1),0);
	}
	
	image2.convertTo(image2, CV_8UC3);
	
	sprintf( TrackbarName, "Alpha x %d", alfa_slider_max );
	createTrackbar( TrackbarName, "tiltshift",
					&alfa_slider,alfa_slider_max,
					on_trackbar_blend );
	on_trackbar_blend(alfa_slider, 0);
	
	sprintf( TrackbarName, "AlturaRegião x %d", top_slider_max );
	createTrackbar( TrackbarName, "tiltshift",&top_slider,
					top_slider_max,on_trackbar_height );
	
	sprintf( TrackbarName, "PosiçãoVertical x %d", center_slider_max );
	createTrackbar( TrackbarName, "tiltshift",&center_slider,
					center_slider_max,on_trackbar_height );
	on_trackbar_height(top_slider, 0);
	
	waitKey(0);
	return 0;
}
	