#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	cv::Mat srcImage = imread("D:\\bottle.jpg");
	cv::Mat binaryImage;
	cv::Mat erodeImage;
	std::vector<cv::Mat> channels;

	cv::split(srcImage, channels);
	cv::Mat R = channels.at(2);

	threshold(R, binaryImage, 210, 255, THRESH_BINARY);
	
	cv::Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(binaryImage, erodeImage, MORPH_ERODE, kernel);
	
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(erodeImage, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	
	float k[10000];
	
	for (int i = 0; i < contours.size(); i++)
	{
		RotatedRect rbox = minAreaRect(contours[i]);
		//drawContours(srcImage, contours, i, Scalar(0, 255, 255), 1, 8);
	
		cv::Point2f vtx[4];
		rbox.points(vtx);
	
		//for (int j = 0; j < 4; j++)
		//{
		//	if (j < 3)
		//	{
		//		line(srcImage, vtx[j], vtx[j + 1], CV_RGB(255, 0, 0), 1, 8, 0);
		//	}
		//	else
		//	{
		//		line(srcImage, vtx[j], vtx[0], CV_RGB(255, 0, 0), 1, 8, 0);
		//	}
		//}
	
		float Y = sqrt((vtx[0].y - vtx[1].y) * (vtx[0].y - vtx[1].y) + (vtx[0].x - vtx[1].x) * (vtx[0].x - vtx[1].x));
		float X = sqrt((vtx[1].y - vtx[2].y) * (vtx[1].y - vtx[2].y) + (vtx[1].x - vtx[2].x) * (vtx[1].x - vtx[2].x));
		k[i] = X / Y;

		if (k[i] >= 0.9)
		{
			if (k[i] <= 1.1)
			{
				for (int j = 0; j < 4; j++)
				{
					cv::line(srcImage, vtx[j], vtx[j < 3 ? j + 1 : 0], cv::Scalar(0, 0, 255), 2, LINE_AA);
				}
			}
		}
	}

	imshow("src", srcImage);
	//imshow("binaryImage", binaryImage);
	//imshow("erode", erodeImage);
	waitKey(0);
	return 0;
}
