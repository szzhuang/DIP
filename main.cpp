#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

int main()
{
	cv::Mat img = imread("D:\\SHUTU.png", 0);
	float histgram[256] = { 0 };
	int height = img.rows;
	int width = img.cols;
	float total = height * width;

	for (int j = 0; j < height; j++)
	{
		uchar* data = img.ptr<uchar>(j);
		for (int i = 0; i < width; i++)
		{
			int value = data[i];
			histgram[value]++;
		}
	}
	for (int i = 0; i < 256; i++)
	{
		histgram[i] /= total;
		std::cout << "histgram" << histgram[i] << std::endl;
	}
	waitKey(0);
	return 0;
}