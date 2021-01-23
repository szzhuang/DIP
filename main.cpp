#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	cv::Mat srcImage = imread("D:\\find_words.jpg");
	cv::Mat dstImage;

	//读取行、列像素个数
	int width = srcImage.cols;
	int height = srcImage.rows;

	double gamma = 2.5;
	double Lut[256];
	for (int i = 0; i < 256; i++)
	{
		Lut[i] = pow(i * 1.0 / 255, 1 / gamma) * 255;
		cout << i << "=" << Lut[i] << endl;
	}

	std::vector<cv::Mat> channels;

	//通道分离
	cv::split(srcImage, channels);
	cv::Mat B = channels.at(0);
	cv::Mat G = channels.at(1);
	cv::Mat R = channels.at(2);

	////直方图均衡
	//equalizeHist(B, B);
	//equalizeHist(G, G);
	//equalizeHist(R, R);

	for (int j = 0; j <height ; j++)
	{
		uchar* data = B.ptr<uchar>(j);
		for ( int i = 0; i < width; i++)
		{
			data[i] = Lut[data[i]];
		}
	}

	for (int j = 0; j < height; j++)
	{
		uchar* data = G.ptr<uchar>(j);
		for (int i = 0; i < width; i++)
		{
			data[i] = Lut[data[i]];
		}
	}

	for (int j = 0; j < height; j++)
	{
		uchar* data = R.ptr<uchar>(j);
		for (int i = 0; i < width; i++)
		{
			data[i] = Lut[data[i]];
		}
	}

	cv::merge(channels, dstImage);

	imshow("src", srcImage);
	imshow("dst", dstImage);
	waitKey(0);
	return 0;
}