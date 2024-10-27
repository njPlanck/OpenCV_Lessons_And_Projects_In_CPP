#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//import images

Mat imGray, imBlur, imCanny, imDil;

void getContours(Mat imDil,Mat img) {

	vector<vector<Point>>contours;
	vector<Vec4i>hierachy;

	findContours(imDil, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

	for (int i = 0;i < contours.size();i++) {
		int area = contourArea(contours[i]);
		cout << area << endl;

		vector<vector<Point>>conPoly(contours.size());
		vector<Rect>boundRect(contours.size());
		string objectType;
		if (area > 1000) {

			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri,true);

			
			cout << conPoly[i].size() << endl;
			boundRect[i] = boundingRect(conPoly[i]);
			//rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255,0),5);

			int objCor = (int)conPoly[i].size();

			if (objCor == 3) {
				objectType = "Tri";
			}
			if (objCor == 4) {
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
				cout << aspRatio << endl;

				if (aspRatio > 0.95 && aspRatio < 1.05) {
					objectType = "Square";
				}
				else {
					objectType = "Rect";
				}
			}
			if (objCor > 4) {
				objectType = "Circle";
			}

			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
			putText(img, objectType, {boundRect[i].x,boundRect[i].y-5}, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 1);
		}
	}
}

int main() {
	string path = "Resources/shapes.png";
	Mat img = imread(path);

	cvtColor(img, imGray, COLOR_BGR2GRAY);
	GaussianBlur(imGray, imBlur, Size(3, 3), 3, 0);
	Canny(imBlur, imCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imCanny, imDil, kernel);

	getContours(imDil, img);

	imshow("Image", img);
	/*imshow("Image Gray", imGray);
	imshow("Image Canny", imCanny);
	imshow("Image Dilate", imDil);*/
	waitKey(0);

}
