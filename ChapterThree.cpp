#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//Resize Images and Crop

int main() {
	string path = "resources/test.png";
	Mat img = imread(path);   //this reads the image file
	Mat imgResize,imgCrop;
	
	//cout << img.size() << endl;
	resize(img, imgResize, Size(), 0.5, 0.5);


	Rect roi(100, 100, 300, 350);
	imgCrop = img(roi);

	imshow("image", img);
	imshow("image Resize", imgResize);
	imshow("image Crop", imgCrop);
	waitKey(0);  

	return 0;
}
