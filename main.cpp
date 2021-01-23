#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <vector>
#include <list>
#include <map>
#include <stack>
using namespace std;
using namespace cv;

int main()
{
	//定义
	cv::Mat binaryImage;
	cv::Mat dilateImage;
	cv::Mat srcImage1 = imread("D://tyre.jpg");
	cv::Mat srcImage = imread("D://tyre.jpg", 0);
	cv::Mat erode_Image;


	threshold(srcImage, binaryImage, 110, 255, THRESH_BINARY);   //二值化
	cv::Mat src_contrary = 255 - binaryImage;                    //反转
	cv::Mat kernel = getStructuringElement(MORPH_RECT, Size(15, 15));      
	morphologyEx(src_contrary, dilateImage, MORPH_CLOSE, kernel);   //闭运算
	cv::Mat kernel_erode = getStructuringElement(MORPH_RECT, Size(3, 3));
	erode(dilateImage, erode_Image, kernel_erode);
	
																	
	//找出连通域
	//再用圆形度去找目标点
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(erode_Image, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	float k[1000];

	for (int i = 0; i < contours.size(); i++)
	{
		RotatedRect rbox = minAreaRect(contours[i]);
		//drawContours(srcImage1, contours, i, 1, 8);
		cv::Point2f vtx[4];
		rbox.points(vtx);

		float Y = sqrt((vtx[0].y - vtx[1].y) * (vtx[0].y - vtx[1].y) + (vtx[0].x - vtx[1].x) * (vtx[0].x - vtx[1].x));
		float X = sqrt((vtx[1].y - vtx[2].y) * (vtx[1].y - vtx[2].y) + (vtx[1].x - vtx[2].x) * (vtx[1].x - vtx[2].x));
		k[i] = X / Y;

		
		if (k[i] >= 0.97 )
		{
			if (k[i] <= 1.1)
			{
				for (int j = 0; j < 4; j++)
				{
					cv::line(srcImage1, vtx[j], vtx[j < 3 ? j + 1 : 0], cv::Scalar(0, 0, 255), 2, LINE_AA);
				}
			}
		}
	  }
	imshow("dilate", dilateImage);
	imshow("dst", srcImage1);
	waitKey(0);
}