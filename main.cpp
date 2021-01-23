#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>
using namespace std;
using namespace cv;

int createMaskByKmeans(cv::Mat src, cv::Mat& mask);

int main()
{
	Mat src = imread("D:\\hog1.jpg");
	Mat mask = Mat::zeros(src.size(), CV_8UC1);
	createMaskByKmeans(src, mask);
	imshow("src", src);
	imshow("mask", mask);
	waitKey(0);
}

int createMaskByKmeans(cv::Mat src, cv::Mat& mask)
{
	if ((mask.type()!=CV_8UC1)||(src.size()!=mask.size()))
	{
		return 0;
	}
	int width = src.cols;
	int height = src.rows;

	int pixNum = width * height;
	int clusterCount = 2;
	Mat labels;
	Mat centers;

	Mat sampleData = src.reshape(3, pixNum);
	Mat km_data;
	sampleData.convertTo(km_data, CV_32F);

	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);
	kmeans(km_data, clusterCount, labels, criteria, clusterCount, KMEANS_PP_CENTERS, centers);

	uchar fg[2] = { 0,255 };
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			mask.at<uchar>(row, col) = fg[labels.at<int>(row * width + col)];
		}
	}
}