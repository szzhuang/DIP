#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	cv::Mat dstImage;
	cv::Mat srcImage = imread("D:\\female.jpg", 1);
	if (srcImage.empty())
	{
		return -1;
	}
	
	//�任ǰ����������
	const cv::Point2f src_pt[] = {
									cv::Point2f(200,200),
									cv::Point2f(250,200),
									cv::Point2f(200,100)};
	//�任�����������
	const cv::Point2f dst_pt[] = {
									cv::Point2f(300,100),
									cv::Point2f(300,50),
									cv::Point2f(200,100)};
	//����������
	const cv::Mat affine_matrix = cv::getAffineTransform(src_pt, dst_pt);

	cv::warpAffine(srcImage, dstImage, affine_matrix, srcImage.size());

	cv::imshow("dst", dstImage);
	cv::imshow("src", srcImage);
	cv::waitKey(0);
}