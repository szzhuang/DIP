#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

//普通背景差分  高斯建模背景差分

int main()
{
	cv::Mat bgMat;
	cv::Mat subMat;
	cv::Mat bny_subMat;

	VideoCapture cap;
	cap.open(0);

	if (!cap.isOpened())
	{
		std::cout << "不能打开视频文件" << std::endl;
		return -1;
	}

	//double fps = cap.get(CAP_PROP_FPS);
	//std::cout << "fps" << std::endl;

	int cnt = 0;

	while (1)
	{
		cv::Mat frame;
		cap.read(frame);
		cvtColor(frame, frame, COLOR_BGR2GRAY);

		if (cnt==0)
		{	
			//第一帧，获得背景图像
			frame.copyTo(bgMat);
		}
		else
		{
			//第二帧开始背景差分
			//背景图像和当前图像相减
			absdiff(frame, bgMat, subMat);
			//差分结果二值化
			threshold(subMat, bny_subMat, 50, 255, THRESH_BINARY);

			imshow("bny_subMat", bny_subMat);
			imshow("subMat", subMat);
			waitKey(30);
		}
		cnt++;
		//bool rSuccess = cap.read(frame);
		//if (!rSuccess)
		//{
		//	std::cout << "不能读取视频" << std::endl;
		//	break;
		//}
		//
		//else
		//{
		//	cv::imshow("frame", frame);
		//}
		//cv::imshow("frame", frame);
		//waitKey(0);
	}
	return 0;
}