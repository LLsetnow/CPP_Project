
#include <opencv2/opencv.hpp>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc.hpp>  
#include<iostream>  
#include <windows.h>
#include <fstream>   //txt�ļ�

using namespace std;
using namespace cv;


//����ͷ��������
void camera_set(VideoCapture cap)
{
    //cap.set(cv::CAP_PROP_FRAME_WIDTH, 320); // ͼ���� 
    //cap.set(cv::CAP_PROP_FRAME_HEIGHT, 240); // ͼ��߶� 
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280); // ͼ���� 
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720); // ͼ��߶� 
    cap.set(cv::CAP_PROP_FPS, 100); // ֡�� 
    cap.set(cv::CAP_PROP_BRIGHTNESS, 0); // ���� 
    cap.set(cv::CAP_PROP_CONTRAST, 40); // �Աȶ� 
    cap.set(cv::CAP_PROP_SATURATION, 50); // ���Ͷ� 
    cap.set(cv::CAP_PROP_HUE, 50); // ɫ�� 
    cap.set(cv::CAP_PROP_EXPOSURE, -5); // �ع� 

    cout << "FRAME_WIDTH:" << cap.get(cv::CAP_PROP_FRAME_WIDTH) << endl; // ͼ���� 
    cout << "FRAME_HEIGHT:" << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << endl; // ͼ��߶� 
    cout << "FPS:" << cap.get(cv::CAP_PROP_FPS) << endl; // ֡�� 
    cout << "BRIGHTNESS:" << cap.get(cv::CAP_PROP_BRIGHTNESS) << endl; // ���� 
    cout << "CONTRAST:" << cap.get(cv::CAP_PROP_CONTRAST) << endl; // �Աȶ� 
    cout << "SATURATION:" << cap.get(cv::CAP_PROP_SATURATION) << endl; // ���Ͷ� 
    cout << "HUE:" << cap.get(cv::CAP_PROP_HUE) << endl; // ɫ�� 
    cout << "EXPOSURE:" << cap.get(cv::CAP_PROP_EXPOSURE) << endl; // �ع� 
}


//��������ͷ����
void camera()
{
    Mat img;
    Mat frame;
    //������ͷ
	VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cerr << "Error: Could not open camera." << endl;
    }

#pragma region ����ͷ����
    //cap.set(cv::CAP_PROP_FRAME_WIDTH, 320); // ͼ���� 
    //cap.set(cv::CAP_PROP_FRAME_HEIGHT, 240); // ͼ��߶� 
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280); // ͼ���� 
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720); // ͼ��߶� 
    cap.set(cv::CAP_PROP_FPS, 100); // ֡�� 
     cap.set(cv::CAP_PROP_BRIGHTNESS,0); // ���� 
     cap.set(cv::CAP_PROP_CONTRAST, 40); // �Աȶ� 
     cap.set(cv::CAP_PROP_SATURATION, 50); // ���Ͷ� 
     cap.set(cv::CAP_PROP_HUE, 50); // ɫ�� 
     cap.set(cv::CAP_PROP_EXPOSURE, -5); // �ع� 

    cout << "FRAME_WIDTH:" << cap.get(cv::CAP_PROP_FRAME_WIDTH) << endl; // ͼ���� 
    cout << "FRAME_HEIGHT:" << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << endl; // ͼ��߶� 
    cout << "FPS:" << cap.get(cv::CAP_PROP_FPS) << endl; // ֡�� 
    cout << "BRIGHTNESS:" << cap.get(cv::CAP_PROP_BRIGHTNESS) << endl; // ���� 
    cout << "CONTRAST:" << cap.get(cv::CAP_PROP_CONTRAST) << endl; // �Աȶ� 
    cout << "SATURATION:" << cap.get(cv::CAP_PROP_SATURATION) << endl; // ���Ͷ� 
    cout << "HUE:" << cap.get(cv::CAP_PROP_HUE) << endl; // ɫ�� 
    cout << "EXPOSURE:" << cap.get(cv::CAP_PROP_EXPOSURE) << endl; // �ع� 

    // ʹ�� WINDOW_NORMAL ���������С
    namedWindow("����ͷ", WINDOW_NORMAL);
    // ���ô��ڵĴ�С
    resizeWindow("����ͷ", 1280, 720);

#pragma endregion



    while (true)
    {
        cap.read(img);
        //��������frame����,��ֹ����߳�ͬʱ����ͬһ������Դ
        //unique_lock<mutex> lock1(mtx1); 

        //frame = img.clone();

        imshow("����ͷ", img);

        //lock1.unlock(); // ����

        int key = waitKey(1);
        // ���� ESC ���˳�
        if (key == 27)  break;
    }


}

//�����������ͷ����
void camera_par()
{
    // ���軬���������ֵ
    const int slider_max = 200;

    // ����ƫ����
    const int zero_offset = -50;

    VideoCapture cap(0);

    if (!cap.isOpened()) 
    {
        cerr << "Error: Could not open camera." << endl;
    }

    // ��������ͷ�ֱ���
    cap.set(CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(CAP_PROP_FRAME_HEIGHT, 720);

    namedWindow("����ͷ", WINDOW_NORMAL);
    resizeWindow("����ͷ", 1280, 1000);

    // ����������
    int brightness_slider = 50;
    int contrast_slider = 90;
    int saturation_slider = 100;
    int hue_slider = 100;
    int exposure_slider = 45;

    //createTrackbar("���� ", "����ͷ", &brightness, 100);
    //createTrackbar("�Աȶ�", "����ͷ", &contrast, 100);
    //createTrackbar("���Ͷ�", "����ͷ", &saturation, 100);
    //createTrackbar("ɫ��", "����ͷ", &hue, 100);
    //createTrackbar("�ع�", "����ͷ", &exposure, 100);

    createTrackbar("����", "����ͷ", &brightness_slider, slider_max);
    createTrackbar("�Աȶ�", "����ͷ", &contrast_slider, slider_max);
    createTrackbar("���Ͷ�", "����ͷ", &saturation_slider, slider_max);
    createTrackbar("ɫ��", "����ͷ", &hue_slider, slider_max);
    createTrackbar("�ع�", "����ͷ", &exposure_slider, slider_max);

    Mat frame;

    while (true) 
    {
        cap >> frame; // ������ͷ����һ֡
        if (frame.empty()) break;

        // ��������ͷ����
        cap.set(CAP_PROP_BRIGHTNESS, brightness_slider + zero_offset);
        cap.set(CAP_PROP_CONTRAST, contrast_slider + zero_offset);
        cap.set(CAP_PROP_SATURATION, saturation_slider + zero_offset);
        cap.set(CAP_PROP_HUE, hue_slider + zero_offset);
        cap.set(CAP_PROP_EXPOSURE, exposure_slider + zero_offset);

        imshow("����ͷ", frame);

        int key = waitKey(1);
        if (key == 27) break; // �� ESC ���˳�
    }

    cap.release();
    destroyAllWindows();
}

void find_eye()
{
    Mat frame;
   //���� Haar ����������
   CascadeClassifier faceCascade;
   faceCascade.load("D:\\OpenCV\\build\\etc\\haarcascades\\haarcascade_eye.xml");

   // ���軬���������ֵ
   const int slider_max = 200;

   // ����ƫ����
   const int zero_offset = -50;

   VideoCapture cap(0);

   if (!cap.isOpened())
   {
       cerr << "Error: Could not open camera." << endl;
   }

   // ��������ͷ�ֱ���
   cap.set(CAP_PROP_FRAME_WIDTH, 1280);
   cap.set(CAP_PROP_FRAME_HEIGHT, 720);

   namedWindow("����ͷ", WINDOW_NORMAL);
   resizeWindow("����ͷ", 1280, 1000);

   // ����������
   int brightness_slider = 50;
   int contrast_slider = 90;
   int saturation_slider = 100;
   int hue_slider = 100;
   int exposure_slider = 45;

   createTrackbar("����", "����ͷ", &brightness_slider, slider_max);
   createTrackbar("�Աȶ�", "����ͷ", &contrast_slider, slider_max);
   createTrackbar("���Ͷ�", "����ͷ", &saturation_slider, slider_max);
   createTrackbar("ɫ��", "����ͷ", &hue_slider, slider_max);
   createTrackbar("�ع�", "����ͷ", &exposure_slider, slider_max);


   while (true)
   {
       cap >> frame; // ������ͷ����һ֡
       if (frame.empty()) break;

       // ��������ͷ����
       cap.set(CAP_PROP_BRIGHTNESS, brightness_slider + zero_offset);
       cap.set(CAP_PROP_CONTRAST, contrast_slider + zero_offset);
       cap.set(CAP_PROP_SATURATION, saturation_slider + zero_offset);
       cap.set(CAP_PROP_HUE, hue_slider + zero_offset);
       cap.set(CAP_PROP_EXPOSURE, exposure_slider + zero_offset);

       vector<Rect> faces;
       faceCascade.detectMultiScale(frame, faces, 1.3, 12);

       //���Ƽ�⵽���沿
       //faces.size ʶ������������
       for (int i = 0; i < faces.size(); i++)
       {
           rectangle(frame, faces[i].tl(), faces[i].br(), Scalar(255, 0, 0), 3);
       }


       imshow("����ͷ", frame);

       int key = waitKey(1);
       if (key == 27) break; // �� ESC ���˳�

   }
   cap.release();
   destroyAllWindows();
}

//��������ͷ + ����ͼ��
void camera_save()
{
    Mat img;
    Mat frame;
    //������ͷ
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cerr << "Error: Could not open camera." << endl;
    }

#pragma region ����ͷ����
    //cap.set(cv::CAP_PROP_FRAME_WIDTH, 320); // ͼ���� 
    //cap.set(cv::CAP_PROP_FRAME_HEIGHT, 240); // ͼ��߶� 
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280); // ͼ���� 
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720); // ͼ��߶� 
    cap.set(cv::CAP_PROP_FPS, 100); // ֡�� 
    cap.set(cv::CAP_PROP_BRIGHTNESS, 0); // ���� 
    cap.set(cv::CAP_PROP_CONTRAST, 40); // �Աȶ� 
    cap.set(cv::CAP_PROP_SATURATION, 50); // ���Ͷ� 
    cap.set(cv::CAP_PROP_HUE, 50); // ɫ�� 
    cap.set(cv::CAP_PROP_EXPOSURE, -5); // �ع� 

    cout << "FRAME_WIDTH:" << cap.get(cv::CAP_PROP_FRAME_WIDTH) << endl; // ͼ���� 
    cout << "FRAME_HEIGHT:" << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << endl; // ͼ��߶� 
    cout << "FPS:" << cap.get(cv::CAP_PROP_FPS) << endl; // ֡�� 
    cout << "BRIGHTNESS:" << cap.get(cv::CAP_PROP_BRIGHTNESS) << endl; // ���� 
    cout << "CONTRAST:" << cap.get(cv::CAP_PROP_CONTRAST) << endl; // �Աȶ� 
    cout << "SATURATION:" << cap.get(cv::CAP_PROP_SATURATION) << endl; // ���Ͷ� 
    cout << "HUE:" << cap.get(cv::CAP_PROP_HUE) << endl; // ɫ�� 
    cout << "EXPOSURE:" << cap.get(cv::CAP_PROP_EXPOSURE) << endl; // �ع� 

    // ʹ�� WINDOW_NORMAL ���������С
    namedWindow("����ͷ", WINDOW_NORMAL);
    // ���ô��ڵĴ�С
    resizeWindow("����ͷ", 1280, 720);

#pragma endregion

    int frameNumber = 0; // ֡������

    while (true)
    {
        cap.read(img);
        if (img.empty()) break; // �����ȡ����֡�����˳�ѭ��

        imshow("����ͷ", img);

        // �����ļ���
        string filename = "D:\\C Plus Plus Project\\opencv_test0\\photo\\frame_" + to_string(frameNumber++) + ".jpg";
        imwrite(filename, img); // ����ͼ��

        int key = waitKey(1);
        if (key == 27) break; // ���� ESC ���˳�
    }
}


//����ͷ��ֵ�� + ����ͼ��
int threshold_value = 140;
void camera_binary()
{
    Mat img, grayImg, binaryImg;
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cerr << "Error: Could not open camera." << endl;
        return;
    }

    camera_set(cap);

    namedWindow("����ͷ", WINDOW_NORMAL);
    resizeWindow("����ͷ", 1280, 720);

    // ��������
    createTrackbar("��ֵ", "����ͷ", &threshold_value, 255);

    int frameNumber = 0; // ֡������

    while (true)
    {
        cap.read(img);
        if (img.empty()) break; // �����ȡ����֡�����˳�ѭ��

        cout << "���ǵ�" << frameNumber << "��" << endl;

        cvtColor(img, grayImg, COLOR_BGR2GRAY); // ��תΪ�Ҷ�ͼ��
        threshold(grayImg, binaryImg, threshold_value, 255, THRESH_BINARY); // Ӧ�ö�ֵ��

        imshow("����ͷ", binaryImg); // ��ʾ��ֵ�����ͼ��

        // ����ԭʼͼ��Ͷ�ֵ��ͼ����ļ���
        //string filename = "D:\\C Plus Plus Project\\opencv_test0\\photo\\frame_" + to_string(frameNumber) + ".jpg";
        //string binaryFilename = "D:\\C Plus Plus Project\\opencv_test0\\photo_binary\\frame_" + to_string(frameNumber++) + ".jpg";

        //imwrite(filename, img); // ����ԭʼͼ��
        //imwrite(binaryFilename, binaryImg); // �����ֵ��ͼ��

        int key = waitKey(1);
        if (key == 27) break; // ���� ESC ���˳�
    }



}

int threshold_value_R = 140;
int threshold_value_G = 140;
int threshold_value_B = 140;

void camera_binary_RGB()
{
    Mat img, R, G, B, binaryR, binaryG, binaryB;
    Mat redImg, greenImg, blueImg; // ������ʾ�Ĳ�ɫͼ��
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cerr << "Error: Could not open camera." << endl;
        return;
    }

    camera_set(cap);

    // ��������
    namedWindow("Red Channel", WINDOW_NORMAL);
    namedWindow("Green Channel", WINDOW_NORMAL);
    namedWindow("Blue Channel", WINDOW_NORMAL);

    // �������ڴ�С
    resizeWindow("Red Channel", 640, 360);
    resizeWindow("Green Channel", 640, 360);
    resizeWindow("Blue Channel", 640, 360);

    // ��������
    createTrackbar("Threshold", "Red Channel", &threshold_value_R, 255);
    createTrackbar("Threshold", "Green Channel", &threshold_value_G, 255);
    createTrackbar("Threshold", "Blue Channel", &threshold_value_B, 255);

    while (true) 
    {
        cap.read(img);
        if (img.empty()) break;

        // ����ͨ��
        vector<Mat> channels;
        split(img, channels);
        B = channels[0];
        G = channels[1];
        R = channels[2];

        // ��ÿ��ͨ��Ӧ�ö�ֵ��
        //threshold(R, binaryR, threshold_value_R, 255, THRESH_BINARY);
        //threshold(G, binaryG, threshold_value_G, 255, THRESH_BINARY);
        //threshold(B, binaryB, threshold_value_B, 255, THRESH_BINARY);

        //// ��ʾÿ��ͨ��
        //imshow("Red Channel", binaryR);
        //imshow("Green Channel", binaryG);
        //imshow("Blue Channel", binaryB);

        //��ͨ���Ҷ�ͼ
        imshow("Red Channel", R);
        imshow("Green Channel", G);
        imshow("Blue Channel", B);



        // ������ɫ��ֵ��ͼ��
        //vector<Mat> redChannels = { Mat::zeros(img.rows, img.cols, CV_8UC1), Mat::zeros(img.rows, img.cols, CV_8UC1), binaryR };
        //merge(redChannels, redImg);

        //vector<Mat> greenChannels = { Mat::zeros(img.rows, img.cols, CV_8UC1), binaryG, Mat::zeros(img.rows, img.cols, CV_8UC1) };
        //merge(greenChannels, greenImg);

        //vector<Mat> blueChannels = { binaryB, Mat::zeros(img.rows, img.cols, CV_8UC1), Mat::zeros(img.rows, img.cols, CV_8UC1) };
        //merge(blueChannels, blueImg);

        //vector<Mat> redChannels = { Mat::zeros(img.rows, img.cols, CV_8UC1), Mat::zeros(img.rows, img.cols, CV_8UC1), R };
        //merge(redChannels, redImg);

        //vector<Mat> greenChannels = { Mat::zeros(img.rows, img.cols, CV_8UC1), G, Mat::zeros(img.rows, img.cols, CV_8UC1) };
        //merge(greenChannels, greenImg);

        //vector<Mat> blueChannels = { B, Mat::zeros(img.rows, img.cols, CV_8UC1), Mat::zeros(img.rows, img.cols, CV_8UC1) };
        //merge(blueChannels, blueImg);

        // ��ʾÿ��ͨ��
        //imshow("Red Channel", redImg);
        //imshow("Green Channel", greenImg);
        //imshow("Blue Channel", blueImg);

        int key = waitKey(1);
        if (key == 27) break; // ���� ESC �˳�
    }

}

void camera2array()
{
    namedWindow("����ͷ", WINDOW_NORMAL);
    resizeWindow("����ͷ", 186 * 5, 70 * 5);

    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "����ͷ��ʧ��" << endl;
    }

    // ��ʼ������ͷ
    camera_set(cap);

    Mat frame;

    cap >> frame;

    int rows = frame.rows;
    int cols = frame.cols;

    // ����һ�� int ���͵Ķ�ά����
    int** imageArray = new int* [rows];
    for (int i = 0; i < rows; ++i) 
    {
        imageArray[i] = new int[cols];
    }

    int frameNumber = 0; // ֡������

    while (true) 
    {
        // ������ͷ��ȡһ֡
        cap >> frame;
        if (frame.empty()) break;

        // ������ɫͨ��
        vector<Mat> channels;
        split(frame, channels);
        // channels[0] ����ɫͨ����channels[1] ����ɫͨ����channels[2] �Ǻ�ɫͨ��

        // ���ź���³ߴ�
        int newWidth = 186;
        int newHeight = 104;

        Mat scaledImage;
        resize(channels[2], scaledImage, Size(newWidth, newHeight));

        // �ü�ͼ��
        Rect roi(0, 17, 186, 70);
        Mat croppedImage = scaledImage(roi);

        Mat& redChannel = croppedImage;

        // �����ļ���
        string filename = "D:\\C Plus Plus Project\\opencv_test0\\array\\frame_" + to_string(frameNumber++) + ".txt";

        // ����һ���ļ�����д��
        std::ofstream file(filename);

        // �����ɫͨ��
        for (int i = 0; i < redChannel.rows; i++) 
        {
            for (int j = 0; j < redChannel.cols; j++) 
            {
                // ��ȡÿ�����ص�ĺ�ɫֵ
                imageArray[i][j] = redChannel.at<uchar>(i, j);

                file << std::setw(3) << imageArray[i][j] << " ";
            }
            file << "\n";
        }

        // �ر��ļ�
        file.close();

        // ��ʾ���
        imshow("����ͷ", redChannel);

        int key = waitKey(1);
        if (key == 27) break; // ���� ESC �˳�
    }


}



void camera_sobel()
{
    int lowThreshold = 455;
    int highThreshold = 512;

    namedWindow("����ͷ", WINDOW_NORMAL);
    resizeWindow("����ͷ", 1280, 720);

    createTrackbar("����ֵ", "����ͷ", &lowThreshold, 1000);
    createTrackbar("����ֵ", "����ͷ", &highThreshold, 1000);

    VideoCapture cap(0);
    if (!cap.isOpened()) 
    {
        cerr << "����ͷ��ʧ��" << endl;
    }

    // ��ʼ������ͷ
    camera_set(cap);
    Mat frame;
    Mat imgGray, imgBlur, imgCanny, imgDil;
    while (true)
    {
        // ������ͷ��ȡһ֡
        cap >> frame;
        if (frame.empty()) break;

        // Preprocessing
        cvtColor(frame, imgGray, COLOR_BGR2GRAY);
        GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
        //���ӵ���ֵ�ᵼ��ֻ�и����Եı�Ե����⣬�����Ӹ���ֵ���԰���ȥ��һЩ�����ı�Ե��
        Canny(imgBlur, imgCanny, lowThreshold, highThreshold);
        //Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        //dilate(imgCanny, imgDil, kernel);

        // ��ʾ���
        imshow("����ͷ", imgCanny);

        int key = waitKey(1);
        if (key == 27) break; // ���� ESC �˳�
    }

}