#include <iostream>
#include <vector>
#include <string>
#include <filesystem>  // C++17 引入的库
#include <fstream>
#include <opencv2/opencv.hpp>
#include <chrono>

#include "ImgProcess.hpp"

using namespace std;
using namespace cv;
using namespace filesystem;
namespace fs = std::filesystem;

#pragma region ImgProcess

void ImgProcess::Mat2Array(cv::Mat& img, std::vector<std::vector<int>>& imgArray) 
{
    int imgHeight = img.rows;
    int imgWidth = img.cols;

    // 初始化 imgArray 的大小
    imgArray.resize(imgHeight, std::vector<int>(imgWidth, 0));

    // 遍历图像像素
    for (int i = 0; i < imgHeight; i++) 
    {
        for (int j = 0; j < imgWidth; j++) 
        {
            int value = img.at<uchar>(i, j); 
            if (value)
                imgArray[i][j] = white;
            else
                imgArray[i][j] = black;
        }

    }
}

void ImgProcess::Array2Mat(vector<vector<int>>& imgArray, Mat& img) // 数组转图像
{
    int imgHeight = imgArray.size();
    int imgWidth = imgArray[0].size();

    // 创建一个单通道图像
    img = Mat::zeros(imgHeight, imgWidth, CV_8UC3);

    for (int i = 0; i < imgHeight; i++)
    {
        for (int j = 0; j < imgWidth; j++)
        {
            int value = imgArray[i][j];
            switch (value)
            {
            case white:
                img.at<Vec3b>(i, j) = Vec3b(255, 255, 255); 
                break;
            case black:
                img.at<Vec3b>(i, j) = Vec3b(0, 0, 0); 
                break;
            case blue:
                img.at<Vec3b>(i, j) = Vec3b(255, 0, 0); 
                break;
            case green:
                img.at<Vec3b>(i, j) = Vec3b(0, 255, 0);
                break;
            case red:
                img.at<Vec3b>(i, j) = Vec3b(0, 0, 255);
                break;
            }
        }
    }
}

void ImgProcess::OTSUBinary(Mat& img)
{
    // 将图像转换为灰度图像
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // 执行大津法二值化
    Mat binary;
    
    int thresh = threshold(gray, binary, black, white, THRESH_OTSU);

    if (thresh > 110)
        thresh = 110;
    if (thresh < 90)
        thresh = 90;

    threshold(gray, binary, thresh, white, THRESH_BINARY); // 大津法二值化处理

    // 将处理后的图像赋值回 img
    img = binary.clone();
}

#pragma endregion

#pragma region FilePath

FilePath::FilePath(string basePath)
{
    inputPath = basePath + "\\input";
    outputPath = basePath + "\\output";
    fileCount = 0;

}

int FilePath::CheckFolder(string basePath)
{
    string inputFolder = "input";
    string outputFolder = "output";
    fs::path inputPath = basePath + "\\" + inputFolder;
    fs::path outputPath = basePath + "\\" + outputFolder;
    int err = 0;
    if (!fs::exists(inputPath))
    {
        cout << "input 文件夹不存在" << endl;
        if (fs::create_directory(inputPath))
        {
            cout << "已创建文件夹" << inputPath <<  endl;
            cout << "请将待处理图像放入" << inputPath << endl;
        }
        else 
        {
            cout << "创建文件夹" << inputPath << "失败" << endl;
        }
        err = 1;
    }

    if (!fs::exists(outputPath))
    {
        cout << "output 文件夹不存在" << endl;
        if (fs::create_directory(outputPath))
        {
            cout << "已创建文件夹" << outputPath << endl;
        }
        else
        {
            cout << "创建文件夹" << outputPath << "失败" << endl;
        }
        err = 1;
    }

    if (err)
    {
        cout << "请检查根目录" << basePath << "是否正确" << endl;
        return 1;
    }
    else
        return 0;
}

void FilePath::CheckImg()
{
    if (fileCount == 0)
    {
        cout << "文件夹" << inputPath << "内没有图像" << endl;
        cout << "请检查文件夹内是否有图像 以及 图像后缀是否为bmp" << endl;
    }
}

void FilePath::GetName(const std::filesystem::path& imgPath)
{
    img = imread(imgPath.string());                   // 读取图像
    imgName = imgPath.stem().string();                // 获取文件名
    imgOutput = outputPath + "\\" + imgName + ".jpg"; // 构造输出图像路径
    txtOutput = outputPath + "\\" + imgName + ".txt"; // 构造输出文本路径
    fileCount++;
    txt.clear();
    txt += "********" + to_string(fileCount) + "********\n";
}


void FilePath::WriteTxt(void)
{
    ofstream f(txtOutput);
    f << txt;
    f.close();
}

#pragma endregion
