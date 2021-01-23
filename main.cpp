#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
using namespace std;
using namespace cv;

int main()
{
	double Lut[256];
	for (int i = 0; i < 256; i++)
	{
		Lut[i] = pow(i * 1.0 / 255, 1 / 2.2) * 255;
		cout << i << "=" << Lut[i] << endl;
	}
}