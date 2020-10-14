#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat srcImage = imread("D:\\yaoshuige.jpg", 0);
	cv::Mat resImage_thr;
	cv::Mat resImage_ada;

	//ԭͼ
	imshow("srcImage", srcImage);
	
	//��ֵ��
	threshold(srcImage, resImage_thr, 100, 255, THRESH_OTSU);
	imshow("resImage_thr", resImage_thr);

	//��������Ӧ
	adaptiveThreshold(srcImage, resImage_ada, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 15, 10);
	imshow("resImage_ada", resImage_ada);

	waitKey(0);
	return 0;
}