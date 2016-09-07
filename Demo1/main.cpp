#include <iostream>
#include <fstream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching.hpp"

using namespace std;
using namespace cv;

bool try_use_gpu = false;
vector<Mat> imgs;
string result_name = "result.jpg";


int main(int argc, char* argv[])
{
//	int retval = parseCmdArgs(argc, argv);
//	if (retval) return -1;

	Mat img1 = imread("boat1vga.jpg");
	Mat img2 = imread("boat2vga.jpg");
	Mat img3 = imread("boat3vga.jpg");
	Mat img4 = imread("boat4vga.jpg");
	Mat img5 = imread("boat5vga.jpg");
	Mat img6 = imread("boat6vga.jpg");

	imgs.push_back(img1);
	imgs.push_back(img2);
	imgs.push_back(img3);
	imgs.push_back(img4);
	imgs.push_back(img5);
	imgs.push_back(img6);

	//记录起始时间
	double time0 = static_cast<double>(getTickCount());
	Mat pano;
	Stitcher stitcher = Stitcher::createDefault(try_use_gpu);
	Stitcher::Status status = stitcher.stitch(imgs, pano);

	if (status != Stitcher::OK)
	{
		cout << "Can't stitch images, error code = " << int(status) << endl;
		return -1;
	}
	
	//计算运行时间并输出
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "此方法运行时间为:" << time0 << "秒" << endl;		//输出运行时间
	namedWindow(result_name);

	//显示效果图
	imshow(result_name, pano);
	imwrite(result_name, pano);
	waitKey();
	return 0;
}

