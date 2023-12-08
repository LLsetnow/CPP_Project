

#include <opencv2/opencv.hpp>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc.hpp>  
#include<iostream>  

#include"function.h"

using namespace std;
using namespace cv;

#pragma region 自定义函数

//滑条回调函数
void ThresholdCallback(int threshold, void* userdata)
{
    //reinterpret_cast<Mat*>(userdata)：这是 C++ 中的强制类型转换操作。
    // 它告诉编译器将 userdata（其类型为 void*）解释为指向 Mat 类型的指针。
    //userdata：这是传递给回调函数的用户数据
    Mat* img_gray = reinterpret_cast<Mat*>(userdata);
    Mat img_binary;
    cv::threshold(*img_gray, img_binary, threshold, 255, THRESH_BINARY);
    imshow("二值化", img_binary);
}

//从给定的二值图像中检测轮廓，并根据轮廓的形状识别出不同的几何形状
void getContours(Mat imgDil, Mat img) {

    //vector 向量组
    vector<vector<Point>> contours; //轮廓数据
    vector<Vec4i> hierarchy;

    //通过预处理的二值图像找到所有轮廓contours
    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); 
    //drawContours(img, contours, -1, Scalar(255, 0, 255), 2); //绘制所有轮廓

    for (int i = 0; i < contours.size(); i++)
    {
        double area = contourArea(contours[i]); //计算每个轮廓区域
        cout << area << endl;

        vector<vector<Point>> conPoly(contours.size());
        vector<Rect> boundRect(contours.size());
        string objectType;

        if (area > 1000) //过滤噪声
        {
            //找轮廓的近似多边形或曲线
            double peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

            cout << conPoly[i].size() << endl;
            boundRect[i] = boundingRect(conPoly[i]); //找每个近似曲线的最小上边界矩形

            int objCor = (int)conPoly[i].size();

            if (objCor == 3) { objectType = "Tri"; }
            if (objCor == 4) {

                float aspRatio = (float)boundRect[i].width / boundRect[i].height; //宽高比
                cout << aspRatio << endl;
                if (aspRatio > 0.95 && aspRatio < 1.05) {
                    objectType = "Square";
                }
                else {
                    objectType = "Rect";
                }
            }
            if (objCor > 4) { objectType = "CirCle"; }

            drawContours(img, conPoly, i, Scalar(255, 0, 255), 2); //绘制滤除噪声后的所有轮廓
            rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 2); //绘制边界框
            putText(img, objectType, { boundRect[i].x, boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 1);
        }
    }
}


#pragma endregion



int main()
{

#pragma region 图像读取
    //string img_path = "D:\\C Plus Plus Project\\opencv_test0\\img\\img.png";
    //Mat img = imread(img_path);
    //imshow("Image", img);
#pragma endregion

#pragma region 视频读取
    /*
    string video_path = "D:\\C Plus Plus Project\\opencv_test0\\video\\EX02.mp4";
    VideoCapture cap(video_path); //视频捕捉对象
    Mat video_img;
    while (true) 
    {
        cap.read(video_img);
        imshow("Image", video_img);
        waitKey(1);
    }
    */
#pragma endregion

#pragma region 摄像头读取
    
    //VideoCapture camera_cap(0);
    //Mat camera_img;

    //while (true) 
    //{
    //    camera_cap.read(camera_img);
    //    imshow("Image", camera_img);
    //    waitKey(1);
    //}
    
#pragma endregion

#pragma region 图像处理:色彩空间转化,高斯模糊,canny,滤波,膨胀

    /*
    Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;
        
    //灰度化
    cvtColor(img, imgGray, COLOR_BGR2GRAY); 

    //高斯模糊（主要改变卷积核大小
    GaussianBlur(img, imgBlur, Size(11, 11), 0, 100); 

    //边缘检测
    Canny(imgBlur, imgCanny, 60, 50);

    //返回指定大小和形状的结构元素，用于形态学操作
    Mat kernel = getStructuringElement(MORPH_RECT, Size(7, 7));

    //膨胀 输入图   输出图 卷积核
    dilate(imgCanny, imgDil, kernel);

    //腐蚀
    erode(imgDil, imgErode, kernel);

    imshow("Gray Image", imgGray);
    imshow("Blur Image", imgBlur);
    imshow("Canny Image", imgCanny);
    imshow("ImageDilation", imgDil);
    imshow("ImageErode", imgErode);
    */
#pragma endregion

#pragma region 缩放和裁剪

    /*
    Mat imgResize, imgCrop;

    //size: 列  行
    cout << img.size() << endl;
    resize(img, imgResize, Size(), 0.5, 0.5);
    cout << imgResize.size() << endl;


    //创建一个矩形区域

    //参数说明：第一个参数（200）是矩形左上角的 x 坐标。
    //参数说明：第二个参数（100）是矩形左上角的 y 坐标。
    //参数说明：第三个参数（300）是矩形的宽度。
    //参数说明：第四个参数（300）是矩形的高度。
    Rect roi(500, 500, 100, 100);
    imgCrop = img(roi);

    imshow("Image", img);
    imshow("ImageResieze", imgResize);
    imshow("ImageCrop", imgCrop);
    */
#pragma endregion

#pragma region 绘制形状和文字

    /*
    
    //创建一个 Mat图像
    //参数说明：第一个参数（512）定义了图像的高度（行数）。
    //参数说明：第二个参数（512）定义了图像的宽度（列数）。
    //参数说明：第三个参数（CV_8UC3）指定了图像的类型：
    //参数说明：CV_8U 表示 8 位无符号整数。
    //参数说明：C3 表示 3 个颜色通道（即彩色图像，如 RGB）。
    //参数说明：第四个参数（Scalar(255, 255, 255)）定义了初始化颜色值，这里是白色。
    //Scalar对象的三个参数分别对应于 B（蓝色）、G（绿色）、R（红色）通道的值。
    Mat my_img(512, 512, CV_8UC3, Scalar(255, 255, 255));


    //在my_img矩阵上画圆
    //                 列   行
    //参数说明：Point(256, 256) :这定义了圆心的坐标。
    //参数说明：155:这是圆的半径
    //参数说明：Scalar(0, 69, 255) :这定义了圆的颜色
    //参数说明：FILLED :这个参数指定了圆的绘制方式。FILLED 表示圆是实心的
    //参数说明：如果你想要一个空心圆，可以用一个正整数来代替 FILLED，表示线的粗细。
    circle(my_img, Point(256, 256), 155, Scalar(0, 69, 255), FILLED);

    //绘制矩形
    //参数说明：Point(130, 226), Point(382, 286) - 这些是矩形两个对角顶点的坐标
    //参数说明：Scalar(255, 255, 255) - 这指定了矩形的颜色
    //参数说明： -1 这是构成矩形的线的厚度。当设置为 - 1 时，表示矩形应该被填充。
    rectangle(my_img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), -1);

    //绘制连接两点的线段
    line(my_img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);

    //绘制一个文本字符串
    //参数说明：Point(237, 262) 起点
    //参数说明：FONT_HERSHEY_DUPLEX 字体
    //参数说明：0.95 字体大小
    putText(my_img, "L.L.'s Workshop", Point(137, 262), FONT_HERSHEY_DUPLEX, 0.95, Scalar(0, 69, 255), 2);

    imshow("my_image", my_img);

    */
#pragma endregion

#pragma region 透视变换

    /*
    string load_img_path = "D:\\C Plus Plus Project\\opencv_test0\\img\\card.jpg";
    Mat load_img = imread(load_img_path);
    float w = 250, h = 350;
    Mat matrix, imgWarp;


    //原点坐标           左上        右上        左下        右下

    Point2f src[4] = { {529, 142}, {771, 190}, {405, 395}, {674, 457} };
    //目标点坐标
    Point2f dst[4] = { {0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h} };

    //构建变换矩阵
    matrix = getPerspectiveTransform(src, dst);

    //透视变换
    //参数说明：load_img 输入图像
    //参数说明：imgWarp  输出图像
    //参数说明：matrix   变换矩阵
    //参数说明：Point(w, h) 这个参数指定了输出图像的大小
    warpPerspective(load_img, imgWarp, matrix, Point(w, h));

    for (int i = 0; i < 4; i++) 
    {
        circle(load_img, src[i], 1, Scalar(0, 0, 255), FILLED);
    }

    imshow("Image", load_img);
    imshow("ImageWarp", imgWarp);

    */
   
#pragma endregion

#pragma region 颜色检测

    /*
    Mat imgHSV, mask;
    int hmin = 0, smin = 110, vmin = 153;
    int hmax = 19, smax = 240, vmax = 255;

    string path = "D:\\C Plus Plus Project\\opencv_test0\\img\\lambo.png";
    Mat img_color = imread(path);

    //将BGR颜色空间的图像转换为HSV颜色空间
    cvtColor(img_color, imgHSV, COLOR_BGR2HSV);

    //创建一个名为"Trackbars"的窗口
    namedWindow("Trackbars", (640, 200));

    //创建 色调、饱和度、明度 最小和最大值 的 滑动条
    //参数说明： 滑动条名称,窗口名称,数据地址,调节最大值
    createTrackbar("色调   最小值", "Trackbars", &hmin, 179);
    createTrackbar("色调   最大值", "Trackbars", &hmax, 179);
    createTrackbar("饱和度 最小值", "Trackbars", &smin, 255);
    createTrackbar("饱和度 最大值", "Trackbars", &smax, 255);
    createTrackbar("明度   最小值", "Trackbars", &vmin, 255);
    createTrackbar("明度   最大值", "Trackbars", &vmax, 2555);

    while (true) 
    {

        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);

        //使用inRange函数根据HSV范围过滤图像，生成掩模（mask）。
        inRange(imgHSV, lower, upper, mask);

        imshow("Image", img_color);
        //imshow("Image HSV", imgHSV);
        imshow("Image Mask", mask);
        waitKey(1);

    }

    */
#pragma endregion

#pragma region 二值化(窗口滑块)

    
    //string path = "D:\\C Plus Plus Project\\opencv_test0\\img\\gray.png"; // 替换为你的图像路径
    //Mat img = imread(path, IMREAD_COLOR);
    //Mat img_gray;
    //cvtColor(img, img_gray, COLOR_BGR2GRAY);

    //// 使用 WINDOW_NORMAL 允许调整大小
    //namedWindow("二值化", WINDOW_NORMAL); 
    //// 设置窗口的大小
    //resizeWindow("二值化", 600, 400); 

    //namedWindow("灰度图", WINDOW_NORMAL);
    //resizeWindow("灰度图", 600, 400);
    //imshow("灰度图", img_gray);

    //int threshold_value = 128; // 初始阈值

    ////参数说明： ThresholdCallback， 滑动条值变化时调用的回调函数
    ////参数说明：img_gray， 传递给回调函数的额外数据
    //createTrackbar("阈值", "二值化", &threshold_value, 255, ThresholdCallback, &img_gray);

    //while (true)
    //{
    //    ThresholdCallback(threshold_value, &img_gray);
    //    waitKey(1);
    //}
    
#pragma endregion

#pragma region 轮廓检测

    /*
    string path = "D:\\C Plus Plus Project\\opencv_test0\\img\\shapes.png";
    Mat img = imread(path);
    Mat imgGray, imgBlur, imgCanny, imgDil;
    
    // Preprocessing
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
    Canny(imgBlur, imgCanny, 25, 75);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgCanny, imgDil, kernel);
    
    //getContours(imgDil, img);
    
    namedWindow("原图", WINDOW_NORMAL);
    namedWindow("灰度图", WINDOW_NORMAL);
    namedWindow("模糊图", WINDOW_NORMAL);
    namedWindow("边缘检测图", WINDOW_NORMAL);
    namedWindow("膨胀图", WINDOW_NORMAL);

    imshow("原图", img);
    imshow("灰度图", imgGray);
    imshow("模糊图", imgBlur);
    imshow("边缘检测图", imgCanny);
    imshow("膨胀图", imgDil);
    */
    
#pragma endregion 


#pragma region 人眼识别

    /*
    //string path = "D:\\C Plus Plus Project\\opencv_test0\\img\\img.png";
    //Mat img = imread(path);

    string video_path = "D:\\C Plus Plus Project\\opencv_test0\\video\\eye.mp4";
    VideoCapture cap(video_path); //视频捕捉对象

    //加载 Haar 级联分类器
    CascadeClassifier faceCascade;
    faceCascade.load("D:\\OpenCV\\build\\etc\\haarcascades\\haarcascade_eye.xml");
    
    namedWindow("Image", WINDOW_NORMAL);
    resizeWindow("Image", 600, 400);
    Mat img;

    //cap.read(img);
    //int frameWidth = img.cols;
    //int frameHeight = img.rows;
    //VideoWriter video("D:\\C Plus Plus Project\\opencv_test0\\video\\output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(frameWidth, frameHeight));

    while (true)
    {
        //视频读取完毕
        if (cap.read(img) == 0)
        {
            cout << "读取完毕" << endl;
            break;
        }

        //使用 detectMultiScale 方法检测图像中的面部。检测到的面部存储在 Rect 类型的向量 faces 中 
        //右上角（Top - Right）:
        //X坐标：rect.br().x （右下角的 x 坐标）
        //Y坐标：rect.tl().y （左上角的 y 坐标）

        //左下角（Bottom - Left） :
        //X坐标：rect.tl().x （左上角的 x 坐标）
        //Y坐标：rect.br().y （右下角的 y 坐标）
        vector<Rect> faces;
        faceCascade.detectMultiScale(img, faces, 1.3, 12);

        //绘制检测到的面部
        //faces.size 识别到脸部的数量
        for (int i = 0; i < faces.size(); i++)
        {
            //if(i == 2 )break;
            rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 0), 3);
        }

        //video.write(img);

        imshow("Image", img);

        int key = waitKey(1);
        // 按下 ESC 键退出
        if (key == 27)  return 0;
            
    }

    VideoWriter video("output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(cap.get(CAP_PROP_FRAME_WIDTH), cap.get(CAP_PROP_FRAME_HEIGHT)));
    // 释放 VideoWriter 资源
    //video.release();
    */
#pragma endregion




    //camera();
    //camera_par();
    //find_eye();
    //camera_save();
    //camera_binary();
    //camera_binary_RGB();
    //camera2array();
    camera_sobel();

    return 0;
}



