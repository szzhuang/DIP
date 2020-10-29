#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	cv::Mat desImage;
	cv::Size size(10,10);
	VideoCapture cap;

	cap.open(0);

	if (!cap.isOpened())
	{
		std::cout << "���ܴ���Ƶ�ļ�" << std::endl;
		return-1;
	}

	double fps = cap.get(CAP_PROP_FPS);
	std::cout << "fps" << fps << std::endl;
	while (1)
	{
		cv::Mat frame;
		bool rSucess = cap.read(frame);
		if (!rSucess)
		{
			std::cout << "���ܴ���Ƶ���ȡ֡" << std::endl;
			break;
		}
		else
		{
			blur(frame, desImage, size);
			cv::imshow("frame", frame);
			cv::imshow("desImage", desImage);
		}
		waitKey(30);
	}
}