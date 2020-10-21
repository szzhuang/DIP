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
		

	threshold(srcImage, src_binary, 100, 255, THRESH_BINARY);   //��ֵ��
	cv::Mat src_contrary = 255 - src_binary;   //�ڰ�ת��

	for (int i = 0; i < height; i++)   //ȥ��������
	{
		uchar* data = src_contrary.ptr<uchar>(i);    //ȡ���е�ַ
		for (int j = 0; j < width_out; j++)
		{
			data[j] = 0;   //��ȡ�õ������޸�Ϊ��ɫ
		}
	}

	cv::Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));  //����
    erode(src_contrary, src_erode, kernel);  //��ʴ����

	int num = connectedComponentsWithStats(src_erode, labels, stats, centroids);  //������ͨ�����
	imshow("src_contrary", src_contrary);   
	imshow("src_erode", src_erode);

	cout << "Number of clips=" << num-1 << endl;   //������������


	waitKey(0);
	return 0;
}