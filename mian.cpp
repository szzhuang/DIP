#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

//��ͨ�������  ��˹��ģ�������

int main()
{
	cv::Mat bgMat;
	cv::Mat subMat;
	cv::Mat bny_subMat;

	VideoCapture cap;
	cap.open(0);

	if (!cap.isOpened())
	{
		std::cout << "���ܴ���Ƶ�ļ�" << std::endl;
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
			//��һ֡����ñ���ͼ��
			frame.copyTo(bgMat);
		}
		else
		{
			//�ڶ�֡��ʼ�������
			//����ͼ��͵�ǰͼ�����
			absdiff(frame, bgMat, subMat);
			//��ֽ����ֵ��
			threshold(subMat, bny_subMat, 50, 255, THRESH_BINARY);

			imshow("bny_subMat", bny_subMat);
			imshow("subMat", subMat);
			waitKey(30);
		}
		cnt++;
		//bool rSuccess = cap.read(frame);
		//if (!rSuccess)
		//{
		//	std::cout << "���ܶ�ȡ��Ƶ" << std::endl;
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