#include <opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include <iostream>
#include <vector>
#include <Windows.h>

using namespace cv;

int main() {
	Mat img = imread("D:/Users/32314/source/repos/OpenCV/test1.png");
	const int shuliang = 8;
	int width,height;
	width = img.cols;
	height = img.rows;
	std::vector<Mat> rgb;
	split(img, rgb);
	Mat b = rgb.at(0);
	Mat g = rgb.at(1);
	Mat r = rgb.at(2);
	Mat huidutu;
	cvtColor(img, huidutu, CV_BGR2GRAY);
	int histsize[1] = { 255 };
	float quyu[2] = { 0,255 };
	const float* quyufanwei[1] = { quyu };
	Mat hist0,histR,histG,histB;
	calcHist(&huidutu, 1, 0, Mat(), hist0, 1, histsize, quyufanwei, true, false);
	calcHist(&g, 1, 0, Mat(), histG, 1, histsize, quyufanwei, true, false);
	calcHist(&b, 1, 0, Mat(), histB, 1, histsize, quyufanwei, true, false);
	calcHist(&r, 1, 0, Mat(), histR, 1, histsize, quyufanwei, true, false);
	normalize(hist0, hist0, 0, 256, NORM_MINMAX, -1, Mat());
	normalize(histG, histG, 0, 256, NORM_MINMAX, -1, Mat());
	normalize(histB, histB, 0, 256, NORM_MINMAX, -1, Mat());
	normalize(histR, histR, 0, 256, NORM_MINMAX, -1, Mat());

	float shuzu[256] = { 0 };
 	Mat map0(256, 256, CV_8UC3, Scalar(0, 0, 0));
	Mat mapg(256, 256, CV_8UC3, Scalar(0, 0, 0));
	Mat mapb(256, 256, CV_8UC3, Scalar(0, 0, 0));
	Mat mapr(256, 256, CV_8UC3, Scalar(0, 0, 0));
	for (int i=0; i<255; i++) {
		line(map0, Point(i, 256), Point(i, 256 - hist0.at<float>(i)), CV_RGB(255, 255, 255), 2, 8, 0);
		line(mapg, Point(i, 256), Point(i, 256 - histG.at<float>(i)), CV_RGB(0, 255, 0), 2, 8, 0);
		line(mapb, Point(i, 256), Point(i, 256 - histB.at<float>(i)), CV_RGB(0, 0, 255), 2, 8, 0);
		line(mapr, Point(i, 256), Point(i, 256 - histR.at<float>(i)), CV_RGB(255, 0, 0), 2, 8, 0);
	}

	imwrite("./huidutu.png", huidutu);
	imwrite("./rimg.png", r);
	imwrite("./gimg.png", g);
	imwrite("./bimg.png", b);
	imwrite("./huidutuzhifangtu.png", map0);
	imwrite("./r.png", mapr);
	imwrite("./g.png", mapg);
	imwrite("./b.png", mapb);

	waitKey(0);
	return 0;
}
