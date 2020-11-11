#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	cv::Mat src = imread("D://component.jpg");
	cv::Mat grayImage;
	cv::Mat elementRect;
	cv::Mat binaryImage;
	cv::Mat cannyImage;
	cv::Mat dst;

	cvtColor(src, grayImage, COLOR_BGR2GRAY);    //转换为灰度图
	elementRect = getStructuringElement(MORPH_RECT, Size(3, 3));  //闭运算核
	morphologyEx(grayImage, grayImage, MORPH_CLOSE, elementRect);   //闭运算
	threshold(grayImage, binaryImage, 125, 255, THRESH_BINARY);  //二值化
	Canny(binaryImage, cannyImage, 50, 125, 3);     //边缘提取

	std::vector<cv::Vec4i> lines;
	HoughLinesP(cannyImage, lines, 1, CV_PI / 180, 35, 20, 25);
	for (int i = 0; i < lines.size(); i++)
	{
		cv::Point pt1(lines[i][0], lines[i][1]);
		cv::Point pt2(lines[i][2], lines[i][3]);
		line(src, pt1, pt2, CV_RGB(255, 0, 0), 1, 8, 0);
	}

	//imshow("grayImage", grayImage);
	//imshow("binaryImage", binaryImage);
	imshow("cannyImage", cannyImage);
	imshow("src", src);
	waitKey(0);
}