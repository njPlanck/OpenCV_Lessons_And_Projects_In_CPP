#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//webcam
Mat img;
vector<vector<int>>newPoints;

vector<vector<int>>myColors{ {15,0,0,255,86,255},
							{77,0,0,179,255,255} };


vector<Scalar>myColorValues{ {255,0,255},
							 {0,255,0} };



Point getContours(Mat imDil) {

	vector<vector<Point>>contours;
	vector<Vec4i>hierachy;

	findContours(imDil, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

	Point myPoint(0, 0);

	for (int i = 0;i < contours.size();i++) {
		int area = contourArea(contours[i]);
		cout << area << endl;

		vector<vector<Point>>conPoly(contours.size());
		vector<Rect>boundRect(contours.size());
		string objectType;
		if (area > 1000) {

			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);


			cout << conPoly[i].size() << endl;
			boundRect[i] = boundingRect(conPoly[i]);
			//rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255,0),5);


			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y;
		}
	}
	return myPoint;
}


vector<vector<int>> findColor(Mat img) {
	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	for (int i = 0;i < myColors.size();i++) {

		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		Mat mask;
		inRange(imgHSV, lower, upper, mask);
		//imshow(to_string(i), mask);
		Point myPoint = getContours(mask);

		if (myPoint.x != 0 && myPoint.y != 0) {
			newPoints.push_back({ myPoint.x,myPoint.y,i });
		}

	}
	return newPoints;

}

void drawOnCanvas(vector<vector<int>>newPoints,vector<Scalar>myColorvalues) {
	for (int i = 0;i < newPoints.size();i++) {
		circle(img, (Point(newPoints[i][0]), Point(newPoints[i][1])), 10, myColorValues[newPoints[i][2]], FILLED);
	}
}

int main() {

	VideoCapture cap(0);


	while (true) {

		cap.read(img);

		newPoints = findColor(img);

		drawOnCanvas(newPoints,myColorValues);

		imshow("Video Recording", img);

		waitKey(1);

	}
}