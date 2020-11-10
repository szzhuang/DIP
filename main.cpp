#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat dstImage;
	cv::Mat srcImage = imread("D:\\female.jpg", 1);
	
	//是否取得图像
	if (srcImage.empty())
	{
		return -1;
	}

	//取得图像的长和宽
	int wid = srcImage.cols;
	int high = srcImage.rows;
	cout << "wid=" << wid << endl;
	cout << "high=" << high << endl;

	//变换前的四点坐标
	const cv::Point2f pts1[] = {
									cv::Point2f(48,0),
									cv::Point2f(wid,48),
									cv::Point2f(0,high-48),
									cv::Point2f(wid-48,high) };
	//变换后的四点坐标
	const cv::Point2f pts2[] = {
									cv::Point2f(0,0),
									cv::Point2f(wid,0),
									cv::Point2f(0,high),
									cv::Point2f(wid,high) };
	//透视变换
	cv::Mat	perspective_matrix = getPerspectiveTransform(pts1, pts2);
	//交换
	cv::warpPerspective(srcImage, dstImage, perspective_matrix, srcImage.size());

	cv::imshow("dst", dstImage);
	cv::imshow("src", srcImage);
	cv::waitKey(0);
}