#include<iostream>
#include<opencv2/opencv.hpp>
#include<fstream>


using namespace std;
using namespace cv;

int main()
{
	ifstream f1("E:\\桌面\\视觉\\opencv008\\opencv008\\train-calibrated-shuffled.txt",ios::in);
	string str1, str2;
	string str3, str4;
	str3 = "E:/桌面/视觉/opencv008/opencv008/";
	str4 = "E:/桌面/视觉/opencv008/";
	int i = 0;
	while (f1>>str1)
	{
		i++;
		f1 >> str2;
		Mat img = imread(str3+str1);
		cout << str4 + str2 + '/' + str1;
		imwrite(str4 + str2 +'/' + str1, img);
		cout << i << endl;
	}
	return 0;
}
