#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	cv::Mat tempMat;
	cv::Mat refMat;
	cv::Mat resultMat;

	VideoCapture cap;

	cap.open(0);

	if (!cap.isOpened())
	{
		cout << "不能打开视频文件" << endl;
		return -1;
	}

	double fps = cap.get(CAP_PROP_FPS);
	
	int cnt = 0;
	int match_method = 0;
	while (1)
	{
		cv::Mat frame;
		bool rSucess = cap.read(frame);
		if (!rSucess)
		{
			cout << "不能从视频文件中读取帧" << endl;
			break;
		}
		else
		{
			if (cnt == 0)
			{
				Rect2d r;
				r = selectROI(frame,true);
				tempMat = frame(r);
				tempMat.copyTo(refMat);
				destroyAllWindows();
				cnt++;
			}
			
			
			matchTemplate(frame, refMat, resultMat, match_method);
			normalize(resultMat, resultMat, 0, 1, NORM_MINMAX, -1, Mat());

			double minVal;
			double maxVal;
			Point minLoc;
			Point maxLoc;
			Point matchLoc;
			Point minLoc2 = Point(minLoc.x + 20, minLoc.y + 20);
			Point maxLoc2 = Point(maxLoc.x + 20, maxLoc.y + 20);

			minMaxLoc(resultMat, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
			
			cv::Rect rect;
			rect.x = minLoc.x;
			rect.y = minLoc.y;
			rect.width = 200;
			rect.height = 250;
			
			if (match_method == 0)
			{
				//line(frame, minLoc, minLoc2, CV_RGB(255, 0, 0), 1, 8, 0);
				rectangle(frame, rect, CV_RGB(255, 0, 0), 1, 8, 0);
			}
			else
			{
				line(frame, maxLoc, maxLoc2, CV_RGB(255, 0, 0), 1, 8, 0);
			}
			cv::imshow("frame", frame);
		}
		waitKey(30);
	}
	return 0;
}