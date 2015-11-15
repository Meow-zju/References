#include <afx.h>
#include <windows.h>
#include <iostream>
#include <cstdio>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/legacy/legacy.hpp>  

using namespace cv;
using namespace std;

#define Camera_Num 0

int Find_Can(Mat srcImage, Mat srcScene){
	//载入素材图  
	//Mat srcImage = imread("wlj.png", 1);
	//Mat srcScene = imread("62.jpg", 1);
	//imshow("Image", srcImage);
	//imshow("Scene", srcScene);

	//使用SURF算子检测关键点  
	int minHessian = 200;
	SurfFeatureDetector detector(minHessian);
	vector<KeyPoint> ImgPoints, ScePoints;
	
	//调用detect函数检测出SURF特征关键点，保存在vector容器中
	detector.detect(srcImage, ImgPoints);
	detector.detect(srcScene, ScePoints);

	//计算描述符（特征向量）
	SurfDescriptorExtractor extractor;
	Mat descriptors1, descriptors2;
	extractor.compute(srcImage, ImgPoints, descriptors1);
	extractor.compute(srcScene, ScePoints, descriptors2);

	//使用FlannBased进行匹配 
	FlannBasedMatcher matcher;
	vector< DMatch > matches;
	matcher.match(descriptors1, descriptors2, matches);
	 
	// 分配空间
	int ptCount = (int)matches.size();
	Mat p1(ptCount, 2, CV_32F);
	Mat p2(ptCount, 2, CV_32F);

	// 把Keypoint转换为Mat
	Point2f pt;
	for (int i = 0; i<ptCount; i++)
	{
		pt = ImgPoints[matches[i].queryIdx].pt;
		p1.at<float>(i, 0) = pt.x;
		p1.at<float>(i, 1) = pt.y;

		pt = ScePoints[matches[i].trainIdx].pt;
		p2.at<float>(i, 0) = pt.x;
		p2.at<float>(i, 1) = pt.y;
	}

	// 用RANSAC方法计算F
	Mat m_Fundamental;
	vector<uchar> RANSACStatus;
	m_Fundamental = findFundamentalMat(p1, p2, RANSACStatus, FM_RANSAC);

	// 计算野点个数
	int OutlinerCount = 0;
	for (int i = 0; i<ptCount; i++)
	{
		if (RANSACStatus[i] == 0) // 状态为0表示野点
		{
			OutlinerCount++;
		}
	}

	// 计算内点
	vector<Point2f> ImgPointInlier;
	vector<Point2f> ScePointInlier;
	vector<DMatch> InlierMatches;
	// 上面三个变量用于保存内点和匹配关系

	int InlinerCount = ptCount - OutlinerCount;
	cout << InlinerCount << endl;
	
	InlierMatches.resize(InlinerCount);
	ImgPointInlier.resize(InlinerCount);
	ScePointInlier.resize(InlinerCount);
	InlinerCount = 0;
	for (int i = 0; i<ptCount; i++)
	{
		if (RANSACStatus[i] != 0)
		{
			ImgPointInlier[InlinerCount].x = p1.at<float>(i, 0);
			ImgPointInlier[InlinerCount].y = p1.at<float>(i, 1);
			ScePointInlier[InlinerCount].x = p2.at<float>(i, 0);
			ScePointInlier[InlinerCount].y = p2.at<float>(i, 1);
			InlierMatches[InlinerCount].queryIdx = InlinerCount;
			InlierMatches[InlinerCount].trainIdx = InlinerCount;
			InlinerCount++;
		}
	}

	// 把内点转换为drawMatches可以使用的格式
	//vector<KeyPoint> key1(InlinerCount);
	//vector<KeyPoint> key2(InlinerCount);
	//KeyPoint::convert(ImgPointInlier, key1);
	//KeyPoint::convert(ScePointInlier, key2);

	// 显示计算F过后的内点匹配

	//Mat imgMatches;
	//drawMatches(srcImage, key1, srcScene, key2, InlierMatches, imgMatches);//进行绘制  
	//imshow("匹配图", imgMatches);

	//waitKey(0);
	//destroyWindow("匹配图");
	
	return InlinerCount;
}

int Judge_Can(Mat Scene, int thr){
	Mat Can = imread("1.png", 1);
	if (Find_Can(Can, Scene) > thr) {
		system("加多宝.mp3");
		return 1;
	}
	Can = imread("2.png", 1);
	if (Find_Can(Can, Scene) > thr) {
		system("王老吉.mp3");
		return 2;
	}
	Can = imread("3.png", 1);
	if (Find_Can(Can, Scene) > thr) {
		system("芬达阳光橙.mp3");
		return 3;
	}
	Can = imread("4.png", 1);
	if (Find_Can(Can, Scene) > thr) {
		system("芬达.mp3");
		return 4;
	}
	Can = imread("5.png", 1);
	if (Find_Can(Can, Scene) > thr) {
		system("醒目.mp3");
		return 5;
	}
	Can = imread("6.png", 1);
	if (Find_Can(Can, Scene) > thr) {
		system("美年达.mp3");
		return 6;
	}
	//system("啥都没有.mp3");
	return 0;
}

int IsRed(Mat image, double thr){
	Mat HSV, channels[3];
	
	//将原图转换为HSV图像
	cvtColor(image, HSV, CV_BGR2HSV);
	
	//分离三信道
	split(HSV, channels);
	
	//筛选某阈值内（红色）的像素点
	threshold(channels[0], channels[1], 160, 1, CV_THRESH_BINARY);
	threshold(channels[0], channels[0], 5, 1, CV_THRESH_BINARY_INV);
	channels[0] += channels[1];
	erode(channels[0], channels[0], Mat::ones(3, 3, CV_8UC1), Point(1, 1), 3);

	//求红色的像素点总数
	Scalar v = cv::sum(channels[0]);
	
	//判断红色点的占比是否大于阈值thr
	int result = v[0] > channels[0].total() * thr;
	cout << (double)v[0] / channels[0].total() << endl;
	//imshow("Red", channels[0]*255);
	//waitKey(0);
	return result;
}

int IsYellow(Mat image, double thr){
	Mat HSV, channels[3];
	cvtColor(image, HSV, CV_BGR2HSV);
	split(HSV, channels);
	threshold(channels[0], channels[1], 10, 1, CV_THRESH_BINARY);
	threshold(channels[0], channels[0], 30, 1, CV_THRESH_BINARY_INV);
	channels[0] &= channels[1];
	erode(channels[0], channels[0], Mat::ones(3, 3, CV_8UC1), Point(1, 1), 3);
	Scalar v = cv::sum(channels[0]);
	int result = v[0] > channels[0].total() * thr;
	cout << result << endl;
	//imshow("Yellow", channels[0] * 255);
	//waitKey(0);
	return result;
}

int IsGreen(Mat image, double thr){                                                                    
	Mat HSV, channels[3];
	cvtColor(image, HSV, CV_BGR2HSV);
	split(HSV, channels);
	threshold(channels[0], channels[1], 60, 1, CV_THRESH_BINARY);
	threshold(channels[0], channels[0], 90, 1, CV_THRESH_BINARY_INV);
	channels[0] &= channels[1];
	erode(channels[0], channels[0], Mat::ones(3, 3, CV_8UC1), Point(1, 1), 3);
	Scalar v = cv::sum(channels[0]);
	int result = v[0] > channels[0].total() * thr;
	cout << result << endl;
	//imshow("--", channels[0] * 255);
	//waitKey(0);
	return result;
}

int IsBlue(Mat image, double thr){
	Mat HSV, channels[3];
	cvtColor(image, HSV, CV_BGR2HSV);
	split(HSV, channels);
	threshold(channels[0], channels[1], 105, 1, CV_THRESH_BINARY);
	threshold(channels[0], channels[0], 120, 1, CV_THRESH_BINARY_INV);
	channels[0] &= channels[1];
	erode(channels[0], channels[0], Mat::ones(3, 3, CV_8UC1), Point(1, 1), 3);
	Scalar v = cv::sum(channels[0]);
	int result = v[0] > channels[0].total() * thr;
	cout << result << endl;
	//imshow("--", channels[0] * 255);
	//waitKey(0);
	return result;
}

int IsLightGreen(Mat image, double thr){
	Mat HSV, channels[3];
	cvtColor(image, HSV, CV_BGR2HSV);
	split(HSV, channels);
	threshold(channels[0], channels[1], 40, 1, CV_THRESH_BINARY);
	threshold(channels[0], channels[0], 70, 1, CV_THRESH_BINARY_INV);
	channels[0] &= channels[1];
	erode(channels[0], channels[0], Mat::ones(3, 3, CV_8UC1), Point(1, 1), 3);
	Scalar v = cv::sum(channels[0]);
	int result = v[0] > channels[0].total() * thr;
	cout << result << endl;
	//imshow("--", channels[0] * 255);
	//waitKey(0);
	return result;
}

int IsLightBlue(Mat image, double thr){
	Mat HSV, channels[3];
	cvtColor(image, HSV, CV_BGR2HSV);
	split(HSV, channels);
	threshold(channels[0], channels[1], 90, 1, CV_THRESH_BINARY);
	threshold(channels[0], channels[0], 110, 1, CV_THRESH_BINARY_INV);
	channels[0] &= channels[1];
	erode(channels[0], channels[0], Mat::ones(3, 3, CV_8UC1), Point(1, 1), 3);
	Scalar v = cv::sum(channels[0]);
	int result = v[0] > channels[0].total() * thr;
	cout << result << endl;
	//imshow("--", channels[0] * 255);
	//waitKey(0);
	return result;
}

int Judge_Box(Mat Scene, double thr){
	Range R(Scene.size().height / 2, Scene.size().height);
	Scene = Mat::Mat(Scene, R, Range::all());
	//imshow("test", Scene);
	if (IsRed(Scene, thr)) {
		system("红色木块.mp3");
		cout << "Red dayo~" << endl;
		return 1;
	}
	if (IsYellow(Scene, thr)) {
		system("黄色木块.mp3");
		cout << "Yellow dayo~" << endl;
		return 2;
	}
	if (IsGreen(Scene, thr)) {
		system("绿色木块.mp3");
		cout << "Green dayo~" << endl;
		return 3;
	}
	if (IsBlue(Scene, thr)) {
		system("蓝色木块.mp3");
		cout << "Blue dayo~" << endl;
		return 4;
	}
	return 0;
}

int Judge_Book(Mat Scene, double thr){
	Range R(Scene.size().height / 4 * 3, Scene.size().height);
	Scene = Mat::Mat(Scene, R, Range::all());
	
	if (IsRed(Scene, thr)) {
		system("红色书本.mp3");
		return 1;
	}
	if (IsLightGreen(Scene, thr)) {
		system("绿色书本.mp3");
		return 2;
	}
	if (IsLightBlue(Scene, thr)) {
		system("蓝色书本.mp3");
		return 3;
	}
	system("绿色书本.mp3");
	return 0;
}

//int main(){
//	HANDLE Arduino = CreateFile
//		(_T("COM3:"),
//		GENERIC_READ | GENERIC_WRITE,
//		0,
//		0,
//		OPEN_EXISTING,
//		0,
//		0);
//	if (Arduino == INVALID_HANDLE_VALUE)
//		printf("Open Failed! Error: %d\n", GetLastError());
//
//	DCB dcb;
//	dcb.DCBlength = sizeof(dcb);
//	if (GetCommState(Arduino, &dcb) == 0)
//		printf("Get State Failed! Error: %d\n", GetLastError());
//	dcb.BaudRate = 9600;
//	dcb.fBinary = TRUE;//是否允许传二进制
//	dcb.fParity = FALSE;//是否奇偶校验
//	dcb.ByteSize = 8;//数据位
//	dcb.Parity = PARITY_NONE;//奇偶校验方式
//	dcb.StopBits = ONESTOPBIT;//停止位
//	dcb.fDtrControl = 0;
//	dcb.fRtsControl = 0;
//	SetCommState(Arduino, &dcb);
//
//	if (SetupComm(Arduino, 6000, 6000) == 0)
//		printf("Setup Failed! Error: %d\n", GetLastError());
//
//	for (;;){
//		BYTE x;
//		scanf("%d", &x);
//		printf("%d\n", x);
//		DWORD y = 0;
//		if (WriteFile(Arduino, &x, sizeof(x), &y, 0) == 0)
//			printf("Write Failed! Error: \n", GetLastError());
//		printf("Byte:%d\n", y);
//	} 
//}

int main(){
	//初始化串口通信
	HANDLE Arduino = CreateFile
		(_T("COM3:"),
		GENERIC_READ | GENERIC_WRITE,
		0,
		0,
		OPEN_EXISTING,
		0,
		0);
	if (Arduino == INVALID_HANDLE_VALUE)
		printf("Open Failed! Error: %d\n", GetLastError());
	
	//读取串口dcb，对串口读写进行设置
	DCB dcb;
	dcb.DCBlength = sizeof(dcb);
	if (GetCommState(Arduino, &dcb) == 0)
		printf("Get State Failed! Error: %d\n", GetLastError());
	dcb.BaudRate = 9600;
	dcb.fBinary = TRUE;//是否允许传二进制
	dcb.fParity = FALSE;//是否奇偶校验
	dcb.ByteSize = 8;//数据位
	dcb.Parity = PARITY_NONE;//奇偶校验方式
	dcb.StopBits = ONESTOPBIT;//停止位
	dcb.fDtrControl = 0;
	dcb.fRtsControl = 0;
	SetCommState(Arduino, &dcb);
	
	if (SetupComm(Arduino, 1000, 1000) == 0)
		printf("Setup Failed! Error: %d\n", GetLastError());
	
	//读取串口超时时间，并进行设置
	COMMTIMEOUTS timeOut;
	GetCommTimeouts(Arduino, &timeOut);

	timeOut.ReadIntervalTimeout = 10;
	timeOut.ReadTotalTimeoutMultiplier = 5;
	timeOut.ReadTotalTimeoutConstant = 20;
	timeOut.WriteTotalTimeoutMultiplier = 5;
	timeOut.WriteTotalTimeoutConstant = 20;

	SetCommTimeouts(Arduino, &timeOut);

	//打开摄像头
	VideoCapture cap(1);
	Mat frame;
	char filename[100];
	int i = 0;
	PurgeComm(Arduino, PURGE_TXCLEAR | PURGE_RXCLEAR);

	while (1){
		BYTE x = 0;
		DWORD y;
		//读取串口内数据
		if (ReadFile(Arduino, &x, sizeof(x), &y, NULL)){
			//cout << "Pending..." << x << endl;
			switch (x){
			case 1:
				cap >> frame;
				sprintf(filename, "nimazhale %d.jpg", i++);
				imwrite(filename, frame);
				x = Judge_Box(frame, 0.1);
				WriteFile(Arduino, &x, sizeof(x), &y, NULL);//将数据写入串口
				break;
			case 2:
				cap >> frame;
				sprintf(filename, "nimazhale %d.jpg", i++);
				imwrite(filename, frame);
				if (Judge_Can(frame, 28)){
					x = 1;
				}
				else {
					Judge_Box(frame, 0.1);
					x = 2;
				}
				WriteFile(Arduino, &x, sizeof(x), &y, NULL);
				break;
			case 3:
				cap >> frame;
				sprintf(filename, "nimazhale %d.jpg", i++);
				imwrite(filename, frame);
				if (Judge_Can(frame, 28)){
					x = 1;
				}
				else {
					Judge_Book(frame, 0.08);
					x = 2;
				}
				WriteFile(Arduino, &x, sizeof(x), &y, NULL);
				break;
			case 4:
				cap >> frame;
				sprintf(filename, "nimazhale %d.jpg", i++);
				imwrite(filename, frame);
				x = Judge_Can(frame, 28);
				WriteFile(Arduino, &x, sizeof(x), &y, NULL);
				break;
			case 5:
				cap >> frame;
				sprintf(filename, "nimazhale %d.jpg", i++);
				imwrite(filename, frame);
				x = Judge_Book(frame, 0.08);
				WriteFile(Arduino, &x, sizeof(x), &y, NULL);
				break;
			case 9:
				cap >> frame;
				sprintf(filename, "nimazhale %d.jpg", i++);
				imwrite(filename, frame);
				x = 9;
				WriteFile(Arduino, &x, sizeof(x), &y, NULL);
				break;
			}	
		}
	}		
}

//int main(){
//	/*
//	Mat src = imread("book.png", 1);
//	imshow("原图", src);
//	IsLightBlue(src, 0.3);
//
//	char fileName[100];
//	for (int i = 1; i < 37; i++){
//	cout << i << ' ';
//	sprintf(fileName, "Pictures %d.jpg", i);
//	Mat src = imread(fileName, 1);
//	imshow("原图", src);
//	IsLightGreen(src, 0.2);
//	}
//	*/
//	//Mat Test = imread("Pictures 4.jpg", 1);
//	//Judge_Box(Test, 0.2);
//
//	
//	VideoCapture cap(0);
//	Mat frame;
//	Mat Can = imread("1.png", 1);
//	while (1){
//	cap >> frame;
//	int p = waitKey(50);
//	if (p == 27) break;
//	//if (p == 'x') Judge_Box(frame, 0.15);
//	//if (p == 'c') Judge_Can(frame, 28);
//	//if (p == 'k') Judge_Book(frame, 0.08);
//	if (p == 'c') Find_Can(Can, frame);
//	if (p == 'r') IsRed(frame, 0.1);
//	if (p == 'x') Judge_Box(frame, 0.1);
//	imshow("Camera", frame);
//	}
//	/*
//	char filename[100];
//	Mat a = imread("Pictures 28.jpg", 1);
//	for (int i = 1; i <= 6; i++){
//	sprintf(filename, "%d.png", i);
//	Mat b = imread(filename, 1);
//	Find_Can(b, a);
//	}
//	return 0;
//	*/
//}
//
