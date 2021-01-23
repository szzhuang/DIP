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
	int cnt = 0;
	while (1)
	{
		cv::Mat frame;
		cap.read(frame);
		cvtColor(frame, frame, COLOR_BGR2GRAY);

		

		if (cnt == 0)
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
	}
	return 0;
}


//先写一个for循环   循环100次  去读frame 直到读完100帧的frame
//同时把100帧的图片  按照每个图片逐帧去进行累加  存至