#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	cv::Mat src = imread("D://lena.jpg");
	cv::Mat dst;
	
	cv::Point2f center(src.cols / 2.0, src.rows / 2.0);
	float angle = 10;
	float scale = 1;
	cv::Mat rot = cv::getRotationMatrix2D(center, angle, scale);
	//获取外界四边形
	cv::Rect bbox = cv::RotatedRect(center, src.size(), angle).boundingRect();
	//调整仿射矩阵参数
	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;
	//仿射变换
	cv::warpAffine(src, dst, rot, bbox.size());

	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
}