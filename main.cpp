#include <iostream>;
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

	//��ת10�ȣ����ų߶�Ϊ
	float angle = 10, scale = 1;
	//��ת����Ϊͼ������
	cv::Point2f center(srcImage.cols * 0.5, srcImage.rows * 0.5);
	//��ñ任����
	const cv::Mat affine_matrix = getRotationMatrix2D(center, angle, scale);

	cv::warpAffine(srcImage, dstImage, affine_matrix, srcImage.size());

	cv::imshow("src", srcImage);
	cv::imshow("dst", dstImage);
	
	waitKey(0);
}