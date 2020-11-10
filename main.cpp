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
	const cv::Point2f pts1[] = {
									cv::Point2f(150,150),
									cv::Point2f(150,300),
									cv::Point2f(350,300),
									cv::Point2f(350,150)};
	//�任�����������
	const cv::Point2f pts2[] = {
									cv::Point2f(200,150),
									cv::Point2f(200,300),
									cv::Point2f(340,270),
									cv::Point2f(340,180)};
	//͸�ӱ任
	cv::Mat	perspective_matrix = getPerspectiveTransform(pts1, pts2);
	//����
	cv::warpPerspective(srcImage, dstImage, perspective_matrix, srcImage.size());
	
	cv::imshow("dst", dstImage);
	cv::imshow("src", srcImage);
	cv::waitKey(0);
}