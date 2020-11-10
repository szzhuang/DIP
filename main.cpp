#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat dstImage;
	cv::Mat srcImage = imread("D:\\yaoshuige.jpg");
	Canny(srcImage, dstImage, 50, 100, 3);
	imshow("dstImage", dstImage);
	waitKey(0);
}