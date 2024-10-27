#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//import images'

Mat imHSV, mask;
int hmin = 0, smin = 0, vmin = 0;
int hmax = 255, smax = 255, vmax = 255;

VideoCapture cap(0);
Mat img;

int main() {

	
	namedWindow("TraceBars", (640, 200));
	createTrackbar("Hue Min", "TraceBars", &hmin, 179);
	createTrackbar("Hue Max", "TraceBars", &hmax, 179);
	createTrackbar("Sat Min", "TraceBars", &smin, 255);
	createTrackbar("Sat Max", "TraceBars", &smax, 255);
	createTrackbar("Val Min", "TraceBars", &vmin, 255);
	createTrackbar("Val Max", "TraceBars", &vmax, 255);

	while (true) {
		cap.read(img);

		cvtColor(img, imHSV, COLOR_BGR2HSV);
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);

		inRange(imHSV, lower, upper, mask);


		cout << hmin << "," << smin << "," << vmin << "," << hmax << "," << smax << "," << vmax << endl;


		imshow("Image", img);
		//imshow("imageHSV", imHSV);
		imshow("ImageMask", mask);


		waitKey(1);

	}
}
