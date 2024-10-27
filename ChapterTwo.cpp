#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//Basic functionw in openCV

int main() {
	string path = "resources/test.png";
	Mat img = imread(path);   //this reads the image file
	Mat imGray, imBlur,imCanny,imDil,imErode;               //the grayscale image output


	cvtColor(img, imGray, COLOR_BGR2GRAY);
	GaussianBlur(img, imBlur, Size(7, 7), 5, 0);
	Canny(img, imCanny, 50, 150);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));

	dilate(imCanny, imDil,kernel);
	erode(imDil, imErode, kernel);

	imshow("image", img);
	imshow("GreyImage", imGray);
	imshow("BlurImage", imBlur);
	imshow("CannyImage", imCanny);
	imshow("ImageDialation", imDil);
	imshow("ImageErosion", imErode);
	waitKey(0);

	return 0;
}
