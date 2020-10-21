#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	cv::Mat src_binary;
	cv::Mat srcImage = imread("D:\\coin.jpg", 0);
	cv::Mat labels;
	cv::Mat stats;
	cv::Mat centroids;

	//二值化
	threshold(srcImage, src_binary, 100, 255, THRESH_BINARY);

	//连通域标记，返回连通域个数(num包括背景，硬币个数为num-1)
	int num = connectedComponentsWithStats(src_binary,labels,stats,centroids);
	
	for (int i=1;  i<num ; i++)
	{
		cv::Rect rect;
		rect.x = stats.at<int>(i, 0);
		rect.y = stats.at<int>(i, 1);
		rect.width = stats.at<int>(i, 2);
		rect.height = stats.at<int>(i, 3);
		rectangle(src_binary, rect, CV_RGB(0, 255, 255));
	}

	//输出图像
	imshow("src_binary", src_binary);

	//输出硬币个数
	cout << "Number of coins=" << num-1 << endl;

	waitKey(0);
	return 0;
}