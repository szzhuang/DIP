#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

int main()
{
	cv::Mat img = imread("D:\\black.png");

	//��ֱ��
	Point pt1(20, 20);
	Point pt2(200, 200);
	line(img, pt1, pt2, CV_RGB(255, 0, 0), 1, 8, 0);
	imshow("������", img);
	
	//�����ο�
	cv::Rect rect;
	rect.x = 10;
	rect.y = 10;
	rect.width=200;
	rect.height=200;
	rectangle(img, rect, CV_RGB(255, 0, 0), 1, 8, 0);
	imshow("�Ӿ��ο�", img);

	waitKey(0);
}