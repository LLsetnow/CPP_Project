
#include <opencv2/opencv.hpp>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc.hpp>  
#include<iostream>  
#include <windows.h>
#include <fstream>   //txt文件

using namespace std;
using namespace cv;


//摄像头参数设置
void camera_set(VideoCapture cap)
{
    //cap.set(cv::CAP_PROP_FRAME_WIDTH, 320); // 图像宽度 
    //cap.set(cv::CAP_PROP_FRAME_HEIGHT, 240); // 图像高度 
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280); // 图像宽度 
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720); // 图像高度 
    cap.set(cv::CAP_PROP_FPS, 100); // 帧率 
    cap.set(cv::CAP_PROP_BRIGHTNESS, 0); // 亮度 
    cap.set(cv::CAP_PROP_CONTRAST, 40); // 对比度 
    cap.set(cv::CAP_PROP_SATURATION, 50); // 饱和度 
    cap.set(cv::CAP_PROP_HUE, 50); // 色调 
    cap.set(cv::CAP_PROP_EXPOSURE, -5); // 曝光 

    cout << "FRAME_WIDTH:" << cap.get(cv::CAP_PROP_FRAME_WIDTH) << endl; // 图像宽度 
    cout << "FRAME_HEIGHT:" << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << endl; // 图像高度 
    cout << "FPS:" << cap.get(cv::CAP_PROP_FPS) << endl; // 帧率 
    cout << "BRIGHTNESS:" << cap.get(cv::CAP_PROP_BRIGHTNESS) << endl; // 亮度 
    cout << "CONTRAST:" << cap.get(cv::CAP_PROP_CONTRAST) << endl; // 对比度 
    cout << "SATURATION:" << cap.get(cv::CAP_PROP_SATURATION) << endl; // 饱和度 
    cout << "HUE:" << cap.get(cv::CAP_PROP_HUE) << endl; // 色调 
    cout << "EXPOSURE:" << cap.get(cv::CAP_PROP_EXPOSURE) << endl; // 曝光 
}


//基础摄像头调用
void camera()
{
    Mat img;
    Mat frame;
    //打开摄像头
	VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cerr << "Error: Could not open camera." << endl;
    }

#pragma region 摄像头设置
    //cap.set(cv::CAP_PROP_FRAME_WIDTH, 320); // 图像宽度 
    //cap.set(cv::CAP_PROP_FRAME_HEIGHT, 240); // 图像高度 
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280); // 图像宽度 
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720); // 图像高度 
    cap.set(cv::CAP_PROP_FPS, 100); // 帧率 
     cap.set(cv::CAP_PROP_BRIGHTNESS,0); // 亮度 
     cap.set(cv::CAP_PROP_CONTRAST, 40); // 对比度 
     cap.set(cv::CAP_PROP_SATURATION, 50); // 饱和度 
     cap.set(cv::CAP_PROP_HUE, 50); // 色调 
     cap.set(cv::CAP_PROP_EXPOSURE, -5); // 曝光 

    cout << "FRAME_WIDTH:" << cap.get(cv::CAP_PROP_FRAME_WIDTH) << endl; // 图像宽度 
    cout << "FRAME_HEIGHT:" << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << endl; // 图像高度 
    cout << "FPS:" << cap.get(cv::CAP_PROP_FPS) << endl; // 帧率 
    cout << "BRIGHTNESS:" << cap.get(cv::CAP_PROP_BRIGHTNESS) << endl; // 亮度 
    cout << "CONTRAST:" << cap.get(cv::CAP_PROP_CONTRAST) << endl; // 对比度 
    cout << "SATURATION:" << cap.get(cv::CAP_PROP_SATURATION) << endl; // 饱和度 
    cout << "HUE:" << cap.get(cv::CAP_PROP_HUE) << endl; // 色调 
    cout << "EXPOSURE:" << cap.get(cv::CAP_PROP_EXPOSURE) << endl; // 曝光 

    // 使用 WINDOW_NORMAL 允许调整大小
    namedWindow("摄像头", WINDOW_NORMAL);
    // 设置窗口的大小
    resizeWindow("摄像头", 1280, 720);

#pragma endregion



    while (true)
    {
        cap.read(img);
        //加锁保护frame变量,防止多个线程同时访问同一数据资源
        //unique_lock<mutex> lock1(mtx1); 

        //frame = img.clone();

        imshow("摄像头", img);

        //lock1.unlock(); // 解锁

        int key = waitKey(1);
        // 按下 ESC 键退出
        if (key == 27)  break;
    }


}

//滑块调节摄像头参数
void camera_par()
{
    // 假设滑动条的最大值
    const int slider_max = 200;

    // 定义偏移量
    const int zero_offset = -50;

    VideoCapture cap(0);

    if (!cap.isOpened()) 
    {
        cerr << "Error: Could not open camera." << endl;
    }

    // 设置摄像头分辨率
    cap.set(CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(CAP_PROP_FRAME_HEIGHT, 720);

    namedWindow("摄像头", WINDOW_NORMAL);
    resizeWindow("摄像头", 1280, 1000);

    // 创建滑动条
    int brightness_slider = 50;
    int contrast_slider = 90;
    int saturation_slider = 100;
    int hue_slider = 100;
    int exposure_slider = 45;

    //createTrackbar("亮度 ", "摄像头", &brightness, 100);
    //createTrackbar("对比度", "摄像头", &contrast, 100);
    //createTrackbar("饱和度", "摄像头", &saturation, 100);
    //createTrackbar("色调", "摄像头", &hue, 100);
    //createTrackbar("曝光", "摄像头", &exposure, 100);

    createTrackbar("亮度", "摄像头", &brightness_slider, slider_max);
    createTrackbar("对比度", "摄像头", &contrast_slider, slider_max);
    createTrackbar("饱和度", "摄像头", &saturation_slider, slider_max);
    createTrackbar("色调", "摄像头", &hue_slider, slider_max);
    createTrackbar("曝光", "摄像头", &exposure_slider, slider_max);

    Mat frame;

    while (true) 
    {
        cap >> frame; // 从摄像头捕获一帧
        if (frame.empty()) break;

        // 更新摄像头参数
        cap.set(CAP_PROP_BRIGHTNESS, brightness_slider + zero_offset);
        cap.set(CAP_PROP_CONTRAST, contrast_slider + zero_offset);
        cap.set(CAP_PROP_SATURATION, saturation_slider + zero_offset);
        cap.set(CAP_PROP_HUE, hue_slider + zero_offset);
        cap.set(CAP_PROP_EXPOSURE, exposure_slider + zero_offset);

        imshow("摄像头", frame);

        int key = waitKey(1);
        if (key == 27) break; // 按 ESC 键退出
    }

    cap.release();
    destroyAllWindows();
}

void find_eye()
{
    Mat frame;
   //加载 Haar 级联分类器
   CascadeClassifier faceCascade;
   faceCascade.load("D:\\OpenCV\\build\\etc\\haarcascades\\haarcascade_eye.xml");

   // 假设滑动条的最大值
   const int slider_max = 200;

   // 定义偏移量
   const int zero_offset = -50;

   VideoCapture cap(0);

   if (!cap.isOpened())
   {
       cerr << "Error: Could not open camera." << endl;
   }

   // 设置摄像头分辨率
   cap.set(CAP_PROP_FRAME_WIDTH, 1280);
   cap.set(CAP_PROP_FRAME_HEIGHT, 720);

   namedWindow("摄像头", WINDOW_NORMAL);
   resizeWindow("摄像头", 1280, 1000);

   // 创建滑动条
   int brightness_slider = 50;
   int contrast_slider = 90;
   int saturation_slider = 100;
   int hue_slider = 100;
   int exposure_slider = 45;

   createTrackbar("亮度", "摄像头", &brightness_slider, slider_max);
   createTrackbar("对比度", "摄像头", &contrast_slider, slider_max);
   createTrackbar("饱和度", "摄像头", &saturation_slider, slider_max);
   createTrackbar("色调", "摄像头", &hue_slider, slider_max);
   createTrackbar("曝光", "摄像头", &exposure_slider, slider_max);


   while (true)
   {
       cap >> frame; // 从摄像头捕获一帧
       if (frame.empty()) break;

       // 更新摄像头参数
       cap.set(CAP_PROP_BRIGHTNESS, brightness_slider + zero_offset);
       cap.set(CAP_PROP_CONTRAST, contrast_slider + zero_offset);
       cap.set(CAP_PROP_SATURATION, saturation_slider + zero_offset);
       cap.set(CAP_PROP_HUE, hue_slider + zero_offset);
       cap.set(CAP_PROP_EXPOSURE, exposure_slider + zero_offset);

       vector<Rect> faces;
       faceCascade.detectMultiScale(frame, faces, 1.3, 12);

       //绘制检测到的面部
       //faces.size 识别到脸部的数量
       for (int i = 0; i < faces.size(); i++)
       {
           rectangle(frame, faces[i].tl(), faces[i].br(), Scalar(255, 0, 0), 3);
       }


       imshow("摄像头", frame);

       int key = waitKey(1);
       if (key == 27) break; // 按 ESC 键退出

   }
   cap.release();
   destroyAllWindows();
}

//基础摄像头 + 保存图像
void camera_save()
{
    Mat img;
    Mat frame;
    //打开摄像头
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cerr << "Error: Could not open camera." << endl;
    }

#pragma region 摄像头设置
    //cap.set(cv::CAP_PROP_FRAME_WIDTH, 320); // 图像宽度 
    //cap.set(cv::CAP_PROP_FRAME_HEIGHT, 240); // 图像高度 
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280); // 图像宽度 
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720); // 图像高度 
    cap.set(cv::CAP_PROP_FPS, 100); // 帧率 
    cap.set(cv::CAP_PROP_BRIGHTNESS, 0); // 亮度 
    cap.set(cv::CAP_PROP_CONTRAST, 40); // 对比度 
    cap.set(cv::CAP_PROP_SATURATION, 50); // 饱和度 
    cap.set(cv::CAP_PROP_HUE, 50); // 色调 
    cap.set(cv::CAP_PROP_EXPOSURE, -5); // 曝光 

    cout << "FRAME_WIDTH:" << cap.get(cv::CAP_PROP_FRAME_WIDTH) << endl; // 图像宽度 
    cout << "FRAME_HEIGHT:" << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << endl; // 图像高度 
    cout << "FPS:" << cap.get(cv::CAP_PROP_FPS) << endl; // 帧率 
    cout << "BRIGHTNESS:" << cap.get(cv::CAP_PROP_BRIGHTNESS) << endl; // 亮度 
    cout << "CONTRAST:" << cap.get(cv::CAP_PROP_CONTRAST) << endl; // 对比度 
    cout << "SATURATION:" << cap.get(cv::CAP_PROP_SATURATION) << endl; // 饱和度 
    cout << "HUE:" << cap.get(cv::CAP_PROP_HUE) << endl; // 色调 
    cout << "EXPOSURE:" << cap.get(cv::CAP_PROP_EXPOSURE) << endl; // 曝光 

    // 使用 WINDOW_NORMAL 允许调整大小
    namedWindow("摄像头", WINDOW_NORMAL);
    // 设置窗口的大小
    resizeWindow("摄像头", 1280, 720);

#pragma endregion

    int frameNumber = 0; // 帧计数器

    while (true)
    {
        cap.read(img);
        if (img.empty()) break; // 如果读取到空帧，则退出循环

        imshow("摄像头", img);

        // 构造文件名
        string filename = "D:\\C Plus Plus Project\\opencv_test0\\photo\\frame_" + to_string(frameNumber++) + ".jpg";
        imwrite(filename, img); // 保存图像

        int key = waitKey(1);
        if (key == 27) break; // 按下 ESC 键退出
    }
}


//摄像头二值化 + 保存图像
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

    namedWindow("摄像头", WINDOW_NORMAL);
    resizeWindow("摄像头", 1280, 720);

    // 创建滑条
    createTrackbar("阈值", "摄像头", &threshold_value, 255);

    int frameNumber = 0; // 帧计数器

    while (true)
    {
        cap.read(img);
        if (img.empty()) break; // 如果读取到空帧，则退出循环

        cout << "这是第" << frameNumber << "张" << endl;

        cvtColor(img, grayImg, COLOR_BGR2GRAY); // 先转为灰度图像
        threshold(grayImg, binaryImg, threshold_value, 255, THRESH_BINARY); // 应用二值化

        imshow("摄像头", binaryImg); // 显示二值化后的图像

        // 构造原始图像和二值化图像的文件名
        //string filename = "D:\\C Plus Plus Project\\opencv_test0\\photo\\frame_" + to_string(frameNumber) + ".jpg";
        //string binaryFilename = "D:\\C Plus Plus Project\\opencv_test0\\photo_binary\\frame_" + to_string(frameNumber++) + ".jpg";

        //imwrite(filename, img); // 保存原始图像
        //imwrite(binaryFilename, binaryImg); // 保存二值化图像

        int key = waitKey(1);
        if (key == 27) break; // 按下 ESC 键退出
    }



}

int threshold_value_R = 140;
int threshold_value_G = 140;
int threshold_value_B = 140;

void camera_binary_RGB()
{
    Mat img, R, G, B, binaryR, binaryG, binaryB;
    Mat redImg, greenImg, blueImg; // 用于显示的彩色图像
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cerr << "Error: Could not open camera." << endl;
        return;
    }

    camera_set(cap);

    // 创建窗口
    namedWindow("Red Channel", WINDOW_NORMAL);
    namedWindow("Green Channel", WINDOW_NORMAL);
    namedWindow("Blue Channel", WINDOW_NORMAL);

    // 调整窗口大小
    resizeWindow("Red Channel", 640, 360);
    resizeWindow("Green Channel", 640, 360);
    resizeWindow("Blue Channel", 640, 360);

    // 创建滑条
    createTrackbar("Threshold", "Red Channel", &threshold_value_R, 255);
    createTrackbar("Threshold", "Green Channel", &threshold_value_G, 255);
    createTrackbar("Threshold", "Blue Channel", &threshold_value_B, 255);

    while (true) 
    {
        cap.read(img);
        if (img.empty()) break;

        // 分离通道
        vector<Mat> channels;
        split(img, channels);
        B = channels[0];
        G = channels[1];
        R = channels[2];

        // 对每个通道应用二值化
        //threshold(R, binaryR, threshold_value_R, 255, THRESH_BINARY);
        //threshold(G, binaryG, threshold_value_G, 255, THRESH_BINARY);
        //threshold(B, binaryB, threshold_value_B, 255, THRESH_BINARY);

        //// 显示每个通道
        //imshow("Red Channel", binaryR);
        //imshow("Green Channel", binaryG);
        //imshow("Blue Channel", binaryB);

        //三通道灰度图
        imshow("Red Channel", R);
        imshow("Green Channel", G);
        imshow("Blue Channel", B);



        // 创建彩色二值化图像
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

        // 显示每个通道
        //imshow("Red Channel", redImg);
        //imshow("Green Channel", greenImg);
        //imshow("Blue Channel", blueImg);

        int key = waitKey(1);
        if (key == 27) break; // 按下 ESC 退出
    }

}

void camera2array()
{
    namedWindow("摄像头", WINDOW_NORMAL);
    resizeWindow("摄像头", 186 * 5, 70 * 5);

    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "摄像头打开失败" << endl;
    }

    // 初始化摄像头
    camera_set(cap);

    Mat frame;

    cap >> frame;

    int rows = frame.rows;
    int cols = frame.cols;

    // 创建一个 int 类型的二维数组
    int** imageArray = new int* [rows];
    for (int i = 0; i < rows; ++i) 
    {
        imageArray[i] = new int[cols];
    }

    int frameNumber = 0; // 帧计数器

    while (true) 
    {
        // 从摄像头读取一帧
        cap >> frame;
        if (frame.empty()) break;

        // 分离颜色通道
        vector<Mat> channels;
        split(frame, channels);
        // channels[0] 是蓝色通道，channels[1] 是绿色通道，channels[2] 是红色通道

        // 缩放后的新尺寸
        int newWidth = 186;
        int newHeight = 104;

        Mat scaledImage;
        resize(channels[2], scaledImage, Size(newWidth, newHeight));

        // 裁剪图像
        Rect roi(0, 17, 186, 70);
        Mat croppedImage = scaledImage(roi);

        Mat& redChannel = croppedImage;

        // 构造文件名
        string filename = "D:\\C Plus Plus Project\\opencv_test0\\array\\frame_" + to_string(frameNumber++) + ".txt";

        // 创建一个文件用于写入
        std::ofstream file(filename);

        // 处理红色通道
        for (int i = 0; i < redChannel.rows; i++) 
        {
            for (int j = 0; j < redChannel.cols; j++) 
            {
                // 提取每个像素点的红色值
                imageArray[i][j] = redChannel.at<uchar>(i, j);

                file << std::setw(3) << imageArray[i][j] << " ";
            }
            file << "\n";
        }

        // 关闭文件
        file.close();

        // 显示结果
        imshow("摄像头", redChannel);

        int key = waitKey(1);
        if (key == 27) break; // 按下 ESC 退出
    }


}



void camera_sobel()
{
    int lowThreshold = 455;
    int highThreshold = 512;

    namedWindow("摄像头", WINDOW_NORMAL);
    resizeWindow("摄像头", 1280, 720);

    createTrackbar("低阈值", "摄像头", &lowThreshold, 1000);
    createTrackbar("高阈值", "摄像头", &highThreshold, 1000);

    VideoCapture cap(0);
    if (!cap.isOpened()) 
    {
        cerr << "摄像头打开失败" << endl;
    }

    // 初始化摄像头
    camera_set(cap);
    Mat frame;
    Mat imgGray, imgBlur, imgCanny, imgDil;
    while (true)
    {
        // 从摄像头读取一帧
        cap >> frame;
        if (frame.empty()) break;

        // Preprocessing
        cvtColor(frame, imgGray, COLOR_BGR2GRAY);
        GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
        //增加低阈值会导致只有更明显的边缘被检测，而增加高阈值可以帮助去除一些较弱的边缘。
        Canny(imgBlur, imgCanny, lowThreshold, highThreshold);
        //Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        //dilate(imgCanny, imgDil, kernel);

        // 显示结果
        imshow("摄像头", imgCanny);

        int key = waitKey(1);
        if (key == 27) break; // 按下 ESC 退出
    }

}