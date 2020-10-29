#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap(0);

	double scale = 1;

	//0-180
	//肤色
	double i_minH = 0;
	double i_maxH = 20;

	//0-255
	double i_minS = 43;
	double i_maxS = 255;

	//0-255
	double i_minV = 55;
	double i_maxV = 255;

	while (1)
	{
		Mat frame;
		Mat hsvMat;
		Mat detectMat;
		Mat dstMat;
		Mat GaussianMat;

		cap >> frame;
		Size ResImgSiz = Size(frame.cols * scale, frame.rows * scale);
		Mat rFrame = Mat(ResImgSiz, frame.type());
		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);

		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);   //转换成HSV格式

		rFrame.copyTo(detectMat);     //深复制

		cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);    //detectMat是mask
		GaussianBlur(rFrame, GaussianMat, Size(5, 5), 5, 5);     //消噪
		
		rFrame.copyTo(dstMat);
		GaussianMat.copyTo(dstMat, detectMat);    //用detectMat中白色的像素的位置用去噪像素替换原图像
		
		// rframe原图   detectMat是掩膜   
		imshow("while:in the range", detectMat);
		imshow("frame", rFrame);
		imshow("dstMat",dstMat);

		waitKey(30);
	}
}