#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	cv::Mat src_binary;
	cv::Mat labels;
	cv::Mat	stats;
	cv::Mat centroids;
	cv::Mat src_erode;
	cv::Mat srcImage = imread("D:\\clip.jpg", 0);
	int width = srcImage.cols;
	int height = srcImage.rows;
	const int width_out=8;
		

	threshold(srcImage, src_binary, 100, 255, THRESH_BINARY);   //二值化
	cv::Mat src_contrary = 255 - src_binary;   //黑白转换

	for (int i = 0; i < height; i++)   //去除左侧干扰
	{
		uchar* data = src_contrary.ptr<uchar>(i);    //取得行地址
		for (int j = 0; j < width_out; j++)
		{
			data[j] = 0;   //将取得的像素修改为黑色
		}
	}

	cv::Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));  //算子
    erode(src_contrary, src_erode, kernel);  //腐蚀运算

	int num = connectedComponentsWithStats(src_erode, labels, stats, centroids);  //返回连通域个数
	imshow("src_contrary", src_contrary);   
	imshow("src_erode", src_erode);

	cout << "Number of clips=" << num-1 << endl;   //输出回形针个数


	waitKey(0);
	return 0;
}