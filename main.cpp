#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	cv::Mat srcImage = imread("D:\\male_face.jpg");
	cv::Mat dstImage;

	std::vector<cv::Mat> channels;
	
	//通道分离
	cv::split(srcImage, channels);
	cv::Mat B = channels.at(0);
	cv::Mat G = channels.at(1);
	cv::Mat R = channels.at(2);
	
	//直方图均衡
	equalizeHist(B, B);
	equalizeHist(G, G);
	equalizeHist(R, R);
	cv::merge(channels, dstImage);

	imshow("src", srcImage);
	imshow("dst", dstImage);
	waitKey(0);
	return 0;
}