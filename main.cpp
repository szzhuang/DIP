#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	cv::Mat desImage;
	int size = 5;
	VideoCapture cap;
	
	cap.open(0);

	if (!cap.isOpened())
	{
		std::cout << "不能打开视频文件" << std::endl;
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
			std::cout << "不能从视频里读取帧" << std::endl;
			break;
		}
		else
		{
			cv::medianBlur(frame, desImage, size);
			cv::imshow("desImage", desImage);
			cv::imshow("frame", frame);
		}
		waitKey(30);
	}
}