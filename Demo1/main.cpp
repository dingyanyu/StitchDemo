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

void printUsage();
int parseCmdArgs(int argc, char** argv);

int main(int argc, char* argv[])
{
//	int retval = parseCmdArgs(argc, argv);
//	if (retval) return -1;

	Mat img1 = imread("boat1.jpg");
	Mat img2 = imread("boat2.jpg");
	Mat img3 = imread("boat3.jpg");
	Mat img4 = imread("boat4.jpg");
	Mat img5 = imread("boat5.jpg");
	Mat img6 = imread("boat6.jpg");

	imgs.push_back(img1);
	imgs.push_back(img2);
	imgs.push_back(img3);
	imgs.push_back(img4);
	imgs.push_back(img5);
	imgs.push_back(img6);

	Mat pano;
	Stitcher stitcher = Stitcher::createDefault(try_use_gpu);
	Stitcher::Status status = stitcher.stitch(imgs, pano);

	if (status != Stitcher::OK)
	{
		cout << "Can't stitch images, error code = " << int(status) << endl;
		return -1;
	}
	
	namedWindow(result_name);
	imshow(result_name, pano);
	imwrite(result_name, pano);
	waitKey();
	return 0;
}

