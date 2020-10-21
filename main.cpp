#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat srcImage = imread("D:\\coin.jpg", 0);
	cv::Mat src_binary;
	cv::Mat resImage_erode;
	cv::Mat resImage_dilate;
	cv::Mat resImage_open;
	cv::Mat resImage_close;

	//二值化
	threshold(srcImage, src_binary, 100, 255, THRESH_BINARY);

	//算子
	cv::Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	
	//膨胀、腐蚀、开运算、闭运算
	erode(src_binary, resImage_erode, kernel);
	dilate(src_binary, resImage_dilate, kernel);
	morphologyEx(src_binary, resImage_open, MORPH_OPEN, kernel);
	morphologyEx(src_binary, resImage_close, MORPH_CLOSE, kernel);

	imshow("src_srcImage", srcImage);
	imshow("src_binary",src_binary);
	imshow("resImage_erode", resImage_erode);
	imshow("resImage_dilate",resImage_dilate);
	imshow("resImage_open", resImage_open);
	imshow("resImage_close", resImage_close);

	waitKey(0);
	return 0;
}