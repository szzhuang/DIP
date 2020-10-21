#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	cv::Mat srcImage = imread("D:\\circuit.jpg", 0);
	cv::Mat src_contrary = 255 - srcImage;
	cv::Mat src_binary;
	cv::Mat src_erode;
	cv::Mat labels;
	cv::Mat stats;
	cv::Mat centroids;

	threshold(src_contrary, src_binary, 100, 255, THRESH_OTSU);   //二值化
	cv::Mat kernel = getStructuringElement(MORPH_RECT, Size(25, 25));  //算子
	erode(src_binary, src_erode, kernel);  //腐蚀运算
	int num = connectedComponentsWithStats(src_erode, labels, stats, centroids);   //计数

	imshow("src_erode", src_erode);   //显示
	cout << "Number of circles=" << num - 1 << endl;   //输出个数

	waitKey(0);
	return 0;
}