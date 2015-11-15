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
	//�����ز�ͼ  
	//Mat srcImage = imread("wlj.png", 1);
	//Mat srcScene = imread("62.jpg", 1);
	//imshow("Image", srcImage);
	//imshow("Scene", srcScene);

	//ʹ��SURF���Ӽ��ؼ���  
	int minHessian = 200;
	SurfFeatureDetector detector(minHessian);
	vector<KeyPoint> ImgPoints, ScePoints;
	
	//����detect��������SURF�����ؼ��㣬������vector������
	detector.detect(srcImage, ImgPoints);
	detector.detect(srcScene, ScePoints);

	//����������������������
	SurfDescriptorExtractor extractor;
	Mat descriptors1, descriptors2;
	extractor.compute(srcImage, ImgPoints, descriptors1);
	extractor.compute(srcScene, ScePoints, descriptors2);

	//ʹ��FlannBased����ƥ�� 
	FlannBasedMatcher matcher;
	vector< DMatch > matches;
	matcher.match(descriptors1, descriptors2, matches);
	 
	// ����ռ�
	int ptCount = (int)matches.size();
	Mat p1(ptCount, 2, CV_32F);
	Mat p2(ptCount, 2, CV_32F);

	// ��Keypointת��ΪMat
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

	// ��RANSAC��������F
	Mat m_Fundamental;
	vector<uchar> RANSACStatus;
	m_Fundamental = findFundamentalMat(p1, p2, RANSACStatus, FM_RANSAC);

	// ����Ұ�����
	int OutlinerCount = 0;
	for (int i = 0; i<ptCount; i++)
	{
		if (RANSACStatus[i] == 0) // ״̬Ϊ0��ʾҰ��
		{
			OutlinerCount++;
		}
	}

	// �����ڵ�
	vector<Point2f> ImgPointInlier;
	vector<Point2f> ScePointInlier;
	vector<DMatch> InlierMatches;
	// ���������������ڱ����ڵ��ƥ���ϵ

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

	// ���ڵ�ת��ΪdrawMatches����ʹ�õĸ�ʽ
	//vector<KeyPoint> key1(InlinerCount);
	//vector<KeyPoint> key2(InlinerCount);
	//KeyPoint::convert(ImgPointInlier, key1);
	//KeyPoint::convert(ScePointInlier, key2);

	// ��ʾ����F������ڵ�ƥ��

	//Mat imgMatches;
	//drawMatches(srcImage, key1, srcScene, key2, InlierMatches, imgMatches);//���л���  
	//imshow("ƥ��ͼ", imgMatches);

	//waitKey(0);
	//destroyWindow("ƥ��ͼ");
	
	return InlinerCount;
}

int Judge_Can(Mat Scene, int thr){
	Mat Can = imread("1.png", 1);
	if (Find_Can(Can, Scene) > thr) {
		system("�Ӷ౦.mp3");
		return 1;
	}
	Can = imread("2.png", 1);
	if (Find_Can(Can, Scene) > thr) {
		system("���ϼ�.mp3");
		return 2;
	}
	Can = imread("3.png", 1);
	if (Find_Can(Can, Scene) > thr) {
		system("�Ҵ������.mp3");
		return 3;
	}
	Can = imread("4.png", 1);
	if (Find_Can(Can, Scene) > thr) {
		system("�Ҵ�.mp3");
		return 4;
	}
	Can = imread("5.png", 1);
	if (Find_Can(Can, Scene) > thr) {
		system("��Ŀ.mp3");
		return 5;
	}
	Can = imread("6.png", 1);
	if (Find_Can(Can, Scene) > thr) {
		system("�����.mp3");
		return 6;
	}
	//system("ɶ��û��.mp3");
	return 0;
}

int IsRed(Mat image, double thr){
	Mat HSV, channels[3];
	
	//��ԭͼת��ΪHSVͼ��
	cvtColor(image, HSV, CV_BGR2HSV);
	
	//�������ŵ�
	split(HSV, channels);
	
	//ɸѡĳ��ֵ�ڣ���ɫ�������ص�
	threshold(channels[0], channels[1], 160, 1, CV_THRESH_BINARY);
	threshold(channels[0], channels[0], 5, 1, CV_THRESH_BINARY_INV);
	channels[0] += channels[1];
	erode(channels[0], channels[0], Mat::ones(3, 3, CV_8UC1), Point(1, 1), 3);

	//���ɫ�����ص�����
	Scalar v = cv::sum(channels[0]);
	
	//�жϺ�ɫ���ռ���Ƿ������ֵthr
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
		system("��ɫľ��.mp3");
		cout << "Red dayo~" << endl;
		return 1;
	}
	if (IsYellow(Scene, thr)) {
		system("��ɫľ��.mp3");
		cout << "Yellow dayo~" << endl;
		return 2;
	}
	if (IsGreen(Scene, thr)) {
		system("��ɫľ��.mp3");
		cout << "Green dayo~" << endl;
		return 3;
	}
	if (IsBlue(Scene, thr)) {
		system("��ɫľ��.mp3");
		cout << "Blue dayo~" << endl;
		return 4;
	}
	return 0;
}

int Judge_Book(Mat Scene, double thr){
	Range R(Scene.size().height / 4 * 3, Scene.size().height);
	Scene = Mat::Mat(Scene, R, Range::all());
	
	if (IsRed(Scene, thr)) {
		system("��ɫ�鱾.mp3");
		return 1;
	}
	if (IsLightGreen(Scene, thr)) {
		system("��ɫ�鱾.mp3");
		return 2;
	}
	if (IsLightBlue(Scene, thr)) {
		system("��ɫ�鱾.mp3");
		return 3;
	}
	system("��ɫ�鱾.mp3");
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
//	dcb.fBinary = TRUE;//�Ƿ�����������
//	dcb.fParity = FALSE;//�Ƿ���żУ��
//	dcb.ByteSize = 8;//����λ
//	dcb.Parity = PARITY_NONE;//��żУ�鷽ʽ
//	dcb.StopBits = ONESTOPBIT;//ֹͣλ
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
	//��ʼ������ͨ��
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
	
	//��ȡ����dcb���Դ��ڶ�д��������
	DCB dcb;
	dcb.DCBlength = sizeof(dcb);
	if (GetCommState(Arduino, &dcb) == 0)
		printf("Get State Failed! Error: %d\n", GetLastError());
	dcb.BaudRate = 9600;
	dcb.fBinary = TRUE;//�Ƿ�����������
	dcb.fParity = FALSE;//�Ƿ���żУ��
	dcb.ByteSize = 8;//����λ
	dcb.Parity = PARITY_NONE;//��żУ�鷽ʽ
	dcb.StopBits = ONESTOPBIT;//ֹͣλ
	dcb.fDtrControl = 0;
	dcb.fRtsControl = 0;
	SetCommState(Arduino, &dcb);
	
	if (SetupComm(Arduino, 1000, 1000) == 0)
		printf("Setup Failed! Error: %d\n", GetLastError());
	
	//��ȡ���ڳ�ʱʱ�䣬����������
	COMMTIMEOUTS timeOut;
	GetCommTimeouts(Arduino, &timeOut);

	timeOut.ReadIntervalTimeout = 10;
	timeOut.ReadTotalTimeoutMultiplier = 5;
	timeOut.ReadTotalTimeoutConstant = 20;
	timeOut.WriteTotalTimeoutMultiplier = 5;
	timeOut.WriteTotalTimeoutConstant = 20;

	SetCommTimeouts(Arduino, &timeOut);

	//������ͷ
	VideoCapture cap(1);
	Mat frame;
	char filename[100];
	int i = 0;
	PurgeComm(Arduino, PURGE_TXCLEAR | PURGE_RXCLEAR);

	while (1){
		BYTE x = 0;
		DWORD y;
		//��ȡ����������
		if (ReadFile(Arduino, &x, sizeof(x), &y, NULL)){
			//cout << "Pending..." << x << endl;
			switch (x){
			case 1:
				cap >> frame;
				sprintf(filename, "nimazhale %d.jpg", i++);
				imwrite(filename, frame);
				x = Judge_Box(frame, 0.1);
				WriteFile(Arduino, &x, sizeof(x), &y, NULL);//������д�봮��
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
//	imshow("ԭͼ", src);
//	IsLightBlue(src, 0.3);
//
//	char fileName[100];
//	for (int i = 1; i < 37; i++){
//	cout << i << ' ';
//	sprintf(fileName, "Pictures %d.jpg", i);
//	Mat src = imread(fileName, 1);
//	imshow("ԭͼ", src);
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
