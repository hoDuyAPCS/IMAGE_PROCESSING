//Ho Cong Duy 1751060
//OpenCV project
//1. Change an RGB image into grayscale image Vs
//2. Change brightness of the image + A trackbar to change the brightness parameter
//3. Change the contrast of the image + A trackbar to change the contrast parameter

//in case you're compiling this code on ubuntu, remember to add `pkg-config --cflags --libs opencv` at the end of the command

//#include "stdafx.h" -> this is used only on Window
#include <iostream>
#include <string>
#include <string.h>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;
using namespace std;
//GLOBAL DATA
//read the input image from file
Mat image;

int RGB2Gray(const cv::Mat &srcImg, cv::Mat &dstImg)
{
	//image failure
	if (srcImg.data == NULL || srcImg.rows <= 0 || srcImg.cols <= 0)
		return 0;
	
	int width = srcImg.cols; 
	int height = srcImg.rows;

	dstImg = cv::Mat(height, width, CV_8UC1, Scalar(0));

	int srcnChannels = srcImg.channels();
	int dstnChannels = dstImg.channels();

	for (int y = 0; y < height; y++)
	{
		const uchar* pSrcRow = srcImg.ptr<uchar>(y);
		uchar* pDstRow = dstImg.ptr<uchar>(y);

		for (int x = 0; x < width; x++, pSrcRow += srcnChannels, pDstRow += dstnChannels)
		{
			uchar B = pSrcRow[0];
			uchar G = pSrcRow[1];
			uchar R = pSrcRow[2];
			float gray = (float)(R + G + B) / 3;//grayscaling
			pDstRow[0] = (uchar)gray;
		}
	}

	return 1;
}

void brightnessCallback(int iValueForBrightness, void *userData){
     Mat dst;
     int iValueForContrast = *( static_cast<int*>(userData) );

     //Calculating brightness and contrast value
     int iBrightness = iValueForBrightness - 50;
     double dContrast = iValueForContrast / 50.0;

     //Calculated contrast and brightness value
     cout << "MyCallbackForBrightness : Contrast=" << dContrast << ", Brightness=" << iBrightness << endl;

     //adjust the brightness and contrast
     image.convertTo(dst, -1, dContrast, iBrightness); 

     //show the brightness and contrast adjusted image
     imshow("EDIT_WINDOW", dst);
}

void contrastCallback(int iValueForContrast, void *userData){
     Mat dst;
     int iValueForBrightness = *( static_cast<int*>(userData) );

     //Calculating brightness and contrast value
     int iBrightness = iValueForBrightness - 50;
     double dContrast = iValueForContrast / 50.0;

     //Calculated contrast and brightness value
     cout << "MyCallbackForContrast : Contrast=" << dContrast << ", Brightness=" << iBrightness << endl;

     //adjust the brightness and contrast
     image.convertTo(dst, -1, dContrast, iBrightness); 

     //show the brightness and contrast adjusted image
     imshow("EDIT_WINDOW", dst);
}
int main(){
	string path;
	cout << "Please enter input image path :";getline(cin,path);//well sortoff
	image = imread(path, CV_LOAD_IMAGE_COLOR);
	
	//failure
	if(image.empty()){
		cout << "CANNOT FIND THE IMAGE"<<endl;
		return 0;
	}

	imshow("INPUT_IMAGE",image);
	//create and set the window name
	namedWindow("EDIT_WINDOW",1);

	Mat gray_image;
	RGB2Gray(image,gray_image);//create grayscale
	
	int brightness = 50;
    int contrast = 50;

    //Create track bar to change brightness
    createTrackbar("Brightness", "EDIT_WINDOW", &brightness, 100, brightnessCallback, &contrast);

    //Create track bar to change contrast
    createTrackbar("Contrast", "EDIT_WINDOW", &contrast, 100, contrastCallback, &brightness);

	//show the image on window
	imshow("EDIT_WINDOW",image);
	imshow("GRAYSCALE_OUTPUT",gray_image);

	//wait until a key is pressed
	waitKey(0);
	//close all windows
	destroyAllWindows();
	return 0;
}
